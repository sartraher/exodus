
#include "startmenu.h"
#include "soundmanager.h"
#include "intromanager.h"
#include <QPainter>

StartMenuC::StartMenuC(QWidget *parent) : QWidget(parent)
{
  setupUi(this);

  SoundManager::play("e:/Coding/exodus/sounds/music/Point of no return.mp3");
  
  QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(exit()));
}

StartMenuC::~StartMenuC()
{
}

void StartMenuC::paintEvent(QPaintEvent* pe)
{
  QStyleOption styleOption;
  styleOption.init(this);
  QPainter painter(this);
  style()->drawPrimitive(QStyle::PE_Widget, &styleOption, &painter, this);

  #pragma warning( suppress : 4100 )
}


