#ifndef __EXODUS_HPP__
#define __EXODUS_HPP__

#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>

class StartMenuC;
class OptionsMenuC;
class LoadMenuC;
class SaveMenuC;

class Exodus : public QMainWindow
{
Q_OBJECT

public:
  Exodus();
  ~Exodus();

  void init();
  
  void showMain();
  void showExtro();
  void clean();

  void FullScreen(bool fs);

public slots:
  void showIntro();
  void startGame();
  void loadGame();
  void showOptions();
  void showCredits();
  void exit();

private:
  StartMenuC *startMenu;
  OptionsMenuC *options;
  LoadMenuC *loadMenu;
  SaveMenuC *saveMenu;

protected:
  
};

#endif
