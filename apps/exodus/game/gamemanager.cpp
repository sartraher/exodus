#include "gamemanager.h"

#include "world.h"
#include "base.h"
#include "research.h"
#include "spacestation.h"
#include "../intromanager.h"
#include "../soundmanager.h"
//#include "exostrat/ogrewidget.h"
#include "ogrewidget.h"

#include <QPixmap>
#include <QPainter>

/**********************************************************
* Actual game
**********************************************************/

GameC::GameC()
{
}

GameC::~GameC()
{
}

void GameC::init(QWidget *parent)
{
  world = new WorldC(parent);
  QPixmap pix(":/images/earthmap.jpg");

  for(int xIndex=0; xIndex<1000; xIndex++)
  {
    for(int yIndex=0; yIndex<1000; yIndex++)
    {
      int x = (pix.width()*xIndex)/1000.0;
      int y = (pix.height()*yIndex)/1000.0;
      int width = pix.width()/1000;
      int height = pix.height()/1000;
      QPixmap tile = pix.copy(x, y, width, height);
      world->fields[xIndex][yIndex].init(xIndex, yIndex, &tile);
    }
  }

  QPixmap *resMap = new QPixmap(pix.width(), pix.height());
  resMap->fill();

  QPainter painter(resMap);

  for(int xIndex=0; xIndex<1000; xIndex++)
  {
    for(int yIndex=0; yIndex<1000; yIndex++)
    {
      QColor col =  world->fields[xIndex][yIndex].tileCol;

      int width = world->fields[xIndex][yIndex].width;
      int height = world->fields[xIndex][yIndex].height;

      int x = (world->fields[xIndex][yIndex].x*resMap->width())/1000.0;
      int y = (world->fields[xIndex][yIndex].y*resMap->height())/1000.0;
      
      painter.fillRect(QRect(x, y, width+1, height+1), col);
    }
  }

  painter.end();
  world->worldMap = resMap;
  //resMap->save("e:/temp/resMap.png");
}

/**********************************************************
* Game Manager Interface
**********************************************************/

GameManagerC::GameManagerC()
{
}

GameManagerC::~GameManagerC()
{
}

void GameManagerC::newGame(QWidget *parent)
{
  //IntroManagerC::playIntro("GameIntro", parent);
  SoundManager::stop();
  GameC *game = new GameC();
  game->init(parent);
  game->world->setGeometry(0,0,parent->width(), parent->height());
  game->world->show();

  //game->exostrat = new OgreWidget(parent);
  //game->exostrat->setGeometry(0,0,parent->width(), parent->height());
  //game->exostrat->show();
}

void GameManagerC::loadGame(QString filename)
{
}

void GameManagerC::saveGame(QString filename)
{

}