#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include <QString>

class QWidget;
class WorldC;
class OgreWidget;

class GameC
{
public:
  GameC();
  ~GameC();

  void init(QWidget *parent=NULL);

  WorldC *world;
  OgreWidget *exostrat;

private: 

protected:
};

class GameManagerC
{
public:
  GameManagerC();
  ~GameManagerC();

  static void newGame(QWidget *parent=NULL);
  static void loadGame(QString filename);
  static void saveGame(QString filename);
private:
protected:
};

#endif