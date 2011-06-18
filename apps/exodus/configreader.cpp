#include "configreader.h"

/****************************************************
 * Config Items
 ****************************************************/

ConfigItem::ConfigItem(QString key, QString value)
{
  this->key = key;
  this->value = value;
}

ConfigItem::~ConfigItem()
{
}

/****************************************************
 * Config Items
 ****************************************************/

ConfigReader::ConfigReader(QString filename)
{
  file = new QFile(filename);
  if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  loadConfig();
}

ConfigReader::~ConfigReader()
{
  file->close();
}

void ConfigReader::loadConfig()
{
  QTextStream in(file);
  QString actBlock="";
  
  while (!in.atEnd()) 
  {
    QString line = in.readLine();
    
    if(line.startsWith("[") && line.contains("]"))
      actBlock = line.mid(1, line.indexOf("]")-1);
    else if(line.contains("="))
    {
      QStringList keyVal = line.split("=");
      itemsPerBlock[actBlock].append(ConfigItem(keyVal[0], keyVal[1]));
    }
    
  }
}

QStringList ConfigReader::getBlocks()
{
  QStringList blocks;

  for(QHash<QString, QList<ConfigItem> >::iterator it=itemsPerBlock.begin(); it!=itemsPerBlock.end(); it++)
    blocks.append(it.key());

  return blocks;
}

QStringList ConfigReader::getItemNames(QString block)
{
  QStringList items;

  if(itemsPerBlock.contains(block))
    for(int index=0; index<itemsPerBlock[block].size(); index++)
      items.append(itemsPerBlock[block][index].key);

  return items;
}

ConfigItem ConfigReader::getItem(QString block, QString itemName)
{
  if(itemsPerBlock.contains(block))
    for(int index=0; index<itemsPerBlock[block].size(); index++)
      if(itemsPerBlock[block][index].key==itemName)
	      return itemsPerBlock[block][index];

  return ConfigItem("","");
}
