#ifndef __SCRIPTMANAGER_H__
#define __SCRIPTMANAGER_H__

class ScriptManager
{
 public:
  static void loadScripts();
  
 private:
  static ScriptManager *_instance;

 protected:
  ScriptManager();
  ~ScriptManager();
};

#endif
