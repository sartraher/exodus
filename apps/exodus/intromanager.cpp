#include "intromanager.h"
#include "soundmanager.h"
#include "configreader.h"

#include <Phonon/VideoPlayer>
#include <Phonon/VideoWidget>
#include <QGridLayout>
#include <QEventLoop>
#include <QKeyEvent>

IntroManagerC* IntroManagerC::_instance=NULL;

IntroManagerC::IntroManagerC()
{
  player = NULL;
  loadIntros();
}

IntroManagerC::~IntroManagerC()
{
}

void IntroManagerC::loadIntros()
{
  ConfigReader reader("E:/Coding/exodus/scripts/intros.cfg");

  QStringList blocks = reader.getBlocks();

  for(int index=0; index<blocks.size(); index++)
  {
    QString block = blocks[index];
    QStringList items = reader.getItemNames(block);
        
    QString type = reader.getItem(block, "type").value;

    if(type=="movie")
    {
      QString filename = reader.getItem(block, "file").value;
      IntroDataC data(filename, QStringList(), MOVIE);
      intros[block] = data;
    }
    else if(type=="script")
    {
      QStringList script;
      QString item="";

      for(int itemIndex=0; (item = reader.getItem(block, QString("item_%1").arg(itemIndex)).value)!=""; itemIndex++)
        script.append(item);

      IntroDataC data("", script, SCRIPT);
      intros[block] = data;
    }
  }
}

bool IntroManagerC::isVideo(QString name)
{
  if(intros[name].type==MOVIE)
    return true;

  return false;
}

QString IntroManagerC::getVideoPath(QString name)
{
  return intros[name].filename;
}

QStringList IntroManagerC::getVideoScript(QString name)
{
  return intros[name].script;
}

bool IntroManagerC::playIntro(QString name, QWidget *parent)
{
  SoundManager::pause();

  if(IntroManagerC::_instance==NULL)
    IntroManagerC::_instance = new IntroManagerC();


  if(_instance->isVideo(name))
  {
    QString path = _instance->getVideoPath(name);

    // Because of problems with QMainWindow and Layouts
    QWidget *holder = new QWidget(parent);
    holder->resize(parent->size());
    holder->show();

    QGridLayout *grid = new QGridLayout(holder);
    grid->setSpacing(20);

    IntroManagerC::_instance->player = new Phonon::VideoPlayer(Phonon::VideoCategory, holder);
    QObject::connect(IntroManagerC::_instance->player, SIGNAL(finished()), IntroManagerC::_instance, SLOT(deletePlayer()));    

    grid->addWidget(IntroManagerC::_instance->player, 1, 1);
    IntroManagerC::_instance->player->show();
    Phonon::MediaSource source(path);

    bool exists = QFile::exists(path);

    Phonon::MediaSource::Type type = source.type();
    IntroManagerC::_instance->player->play(source);

    parent->installEventFilter(new ESCKeyFilter());

    holder->setLayout(grid);
    QEventLoop *loop = new QEventLoop(holder);
    QObject::connect(IntroManagerC::_instance->player, SIGNAL(finished()), loop, SLOT(quit()));    
    QObject::connect(IntroManagerC::_instance->player, SIGNAL(finished()), holder, SLOT(deleteLater()));
    loop->exec();    
  }
  else
  {
    QStringList script = _instance->getVideoScript(name);

    QMap<QString, TextDataC> texts;

    for(int index=0; index<script.size(); index++)
    {
      // item_0=Text:"Music";CENTER,DOWNUP,Arial,20
      QString statement = script[index];

      if(!statement.contains(":"))
        continue;

      QStringList keyVal = statement.split(":");
      QStringList data = keyVal[1].split(";");

      if(keyVal[0].toUpper()=="TEXT")
      { 
        if(data.size()<2)
          continue;

        QString text = data[0];
        TextDataC textData = TextDataC(data[1]);
        texts[text] = textData;
      }
      else if(keyVal[0].toUpper()=="ACTION")
      {        
        if(data.size()<2)
          continue;

        ActionDataC action(data[0], data[1]);
                
        ScriptWidgetC *holder = new ScriptWidgetC(parent);
        holder->resize(parent->size());
        holder->show();
        holder->drawAction(action, texts);
        texts.clear();
      }
    }
  }

  SoundManager::resume();
  return false;
}

bool IntroManagerC::stopIntro()
{
  if(IntroManagerC::_instance==NULL)
    IntroManagerC::_instance = new IntroManagerC();

  if(IntroManagerC::_instance->player)
    IntroManagerC::_instance->player->seek(IntroManagerC::_instance->player->totalTime());

  return true;
}

bool IntroManagerC::deletePlayer()
{
  if(player)
    player->deleteLater();

  player = NULL;

  return true;
}

bool ESCKeyFilter::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::KeyPress) 
  {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);     

    if(keyEvent->key()==Qt::Key_Escape)
    {
      IntroManagerC::stopIntro();
      return true;
    }
  } 
  else 
    return QObject::eventFilter(obj, event);

  return false;
}

/******************************************************************************************
  Litte widget to draw script statements
******************************************************************************************/

ScriptWidgetC::ScriptWidgetC(QWidget *parent)
{
}

ScriptWidgetC::~ScriptWidgetC()
{
}

void ScriptWidgetC::drawAction(ActionDataC action, QMap<QString, TextDataC> texts)
{
  if(action.type==ActionDataC::RUN)
  {

  }
}

/******************************************************************************************
  Data Holder
******************************************************************************************/

IntroDataC::IntroDataC()
{
  filename = "";
  script.clear();
  type = MOVIE;
}

IntroDataC::IntroDataC(QString _filename, QStringList _script, IntroType _type)
{
  filename = _filename;
  script = _script;
  type = _type;
}

IntroDataC::~IntroDataC()
{
}

TextDataC::TextDataC()
{
}

TextDataC::TextDataC(QString data)
{
  QStringList segments = data.split(",");

  if(segments.size()<4)
    return;

  posX = segments[0];
  posY = segments[1];
  font = QFont(segments[2]);
  font.setPointSize(segments[3].toInt());
}

TextDataC::~TextDataC()
{
}

ActionDataC::ActionDataC(QString _type, QString data)
{
  if(_type.toUpper()=="RUN")
    type = RUN;

  QStringList segments = data.split(",");

  if(segments.size()<2)
    return;

  steps = segments[0].toInt();
  increment = segments[1].toInt();
}

ActionDataC::~ActionDataC()
{
}