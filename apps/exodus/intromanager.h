#ifndef __INTROMANAGER_H__
#define __INTROMANAGER_H__

#include <QWidget>
#include <QString>
#include <QHash>
#include <QFont>

namespace Phonon
{
  class VideoPlayer;
}

class ESCKeyFilter : public QObject
{
  Q_OBJECT
public:
  bool eventFilter(QObject *obj, QEvent *event);
private:
protected:
};

class ActionDataC
{
public:
  enum actionType{RUN=0};

  ActionDataC(QString _type, QString data);
  ~ActionDataC();

  actionType type;
  int steps;
  int increment;
private:
protected:
};

class TextDataC
{
public:
  TextDataC();
  TextDataC(QString data);
  ~TextDataC();

  QString posX;
  QString posY;
  QFont font;
private:
protected:
};

enum IntroType {MOVIE=0, SCRIPT};
class IntroDataC
{
public:
  IntroDataC();
  IntroDataC(QString _filename, QStringList _script, IntroType _type);
  ~IntroDataC();

  IntroType type;
  QString filename;
  QStringList script;
private:
protected:
};

class ScriptWidgetC : public QWidget
{
  Q_OBJECT
public:
  ScriptWidgetC(QWidget *parent);
  ~ScriptWidgetC();

  void drawAction(ActionDataC action, QMap<QString, TextDataC> texts);
private:
protected:
};

class IntroManagerC : public QObject
{
  Q_OBJECT
public:
  static bool playIntro(QString name, QWidget *parent=NULL);
  static bool stopIntro();

public slots:
  bool deletePlayer();

private:
  static IntroManagerC *_instance;
  QHash<QString, IntroDataC> intros;
  Phonon::VideoPlayer *player;

protected:
  IntroManagerC();
  ~IntroManagerC();

  void loadIntros();
  bool isVideo(QString name);
  QString getVideoPath(QString name);
  QStringList getVideoScript(QString name);
};

#endif