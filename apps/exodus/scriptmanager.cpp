#include "scriptmanager.h"
#include "configreader.h"
#include <QFile>

ScriptManager* ScriptManager::_instance=NULL;

ScriptManager::ScriptManager()
{
}

ScriptManager::~ScriptManager()
{
}

void ScriptManager::loadScripts()
{
  if(_instance==NULL)
    _instance=new ScriptManager();

  ConfigReader reader("../scripts/scripts.cfg");

  QStringList categories = reader.getBlocks();

  if(categories.contains("MOVIES"))
  {
  }
  else if(categories.contains("INTERFACE"))
  {
  }
  /*
  ofstream scripts("../scripts/scripts.cfg");
  if (myfile.is_open())
  {
    myfile << "This is a line.\n";
    myfile << "This is another line.\n";
    myfile.close();
  }
  */
}
 
