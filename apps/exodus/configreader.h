#ifndef __CONFIGREADER_H__
#define __CONFIGREADER_H__

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QHash>
#include <QList>
#include <QStringList>

class ConfigItem
{
 public:
  ConfigItem(QString key, QString value);
  ~ConfigItem();

  QString key;
  QString value;
 private:
 protected:
};

class ConfigReader
{
 public:
  ConfigReader(QString filename);
  ~ConfigReader();

  void loadConfig();
  QStringList getBlocks();
  QStringList getItemNames(QString block);
  ConfigItem getItem(QString block, QString itemName);

 private:
  QHash<QString, QList<ConfigItem> > itemsPerBlock;
  QFile *file;

 protected:
};

#endif
