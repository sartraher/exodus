#include "exodus.h"
#include "saveloadmenu.h"
#include "soundmanager.h"
#include "startmenu.h"
#include "intromanager.h"
#include "optionsmenu.h"
#include "game/gamemanager.h"
#include <QMessageBox>


Exodus::Exodus() : QMainWindow(NULL)
{
  startMenu = NULL;
  options = NULL;
  loadMenu = NULL;
  saveMenu = NULL;
  this->setStyleSheet("QMainWindow { background-color: black; }");
}

Exodus::~Exodus()
{
}

void Exodus::FullScreen(bool fs)
{
  if(fs) 
  {
    this->move(0,0);
    this->setWindowFlags( Qt::FramelessWindowHint | Qt::Tool /*| Qt::WindowStaysOnTopHint*/ );
    resize(QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen()).size());
    setFocusPolicy( Qt::StrongFocus );
    qApp->processEvents();
    show();
    setFocus();
  } 
  else 
  {
    show();
   }
}

void Exodus::init()
{
  //ScriptManager::loadScripts();
}

void Exodus::showIntro()
{
  IntroManagerC::playIntro("MainIntro", this);
}

void Exodus::showMain()
{
  startMenu = new StartMenuC(this);
  startMenu->setGeometry(0,0,this->width(), this->height());
  startMenu->show();

  QObject::connect(startMenu->introButton, SIGNAL(clicked()), this, SLOT(showIntro()));
  QObject::connect(startMenu->startButton, SIGNAL(clicked()), this, SLOT(startGame()));
  QObject::connect(startMenu->loadButton, SIGNAL(clicked()), this, SLOT(loadGame()));
  QObject::connect(startMenu->optionsButton, SIGNAL(clicked()), this, SLOT(showOptions()));
  QObject::connect(startMenu->creditsButton, SIGNAL(clicked()), this, SLOT(showCredits()));  
  QObject::connect(startMenu->exitButton, SIGNAL(clicked()), this, SLOT(exit()));
}

void Exodus::showExtro()
{
  //IntroManagerC::playIntro("Extro", this);
}

void Exodus::clean()
{
  if(startMenu)
    delete startMenu;
}

void Exodus::exit()
{
  clean();
  qApp->quit();
}

void Exodus::startGame()
{
  GameManagerC::newGame(startMenu);
}

void Exodus::loadGame()
{
  loadMenu = new LoadMenuC(startMenu);

  loadMenu->move((startMenu->width()-loadMenu->width())/2, (startMenu->height()-loadMenu->height())/2);

  QObject::connect(loadMenu->loadButton, SIGNAL(clicked()), loadMenu, SLOT(loadGame()));
  QObject::connect(loadMenu->loadButton, SIGNAL(clicked()), loadMenu, SLOT(deleteLater()));
  QObject::connect(loadMenu->cancelButton, SIGNAL(clicked()), loadMenu, SLOT(deleteLater()));

  loadMenu->show();
}

void Exodus::showOptions()
{
  options = new OptionsMenuC(startMenu);
  options->move((startMenu->width()-options->width())/2, (startMenu->height()-options->height())/2);

  QObject::connect(options->okButton, SIGNAL(clicked()), options, SLOT(saveOptions()));
  QObject::connect(options->okButton, SIGNAL(clicked()), options, SLOT(deleteLater()));
  QObject::connect(options->cancelButton, SIGNAL(clicked()), options, SLOT(deleteLater()));

  options->show();
}

void Exodus::showCredits()
{
  IntroManagerC::playIntro("Credits", this);
}