#ifndef __SAVELOADMENU_H__
#define __SAVELOADMENU_H__

#include <QWidget>
#include "ui_loadmenu.h"
#include "ui_savemenu.h"

class SaveMenuC : public QWidget, public Ui_SaveMenu
{
public:
  SaveMenuC(QWidget *parent=NULL);
  ~SaveMenuC();
private:
protected:
};

class LoadMenuC : public QWidget, public Ui_LoadMenu
{
public:
  LoadMenuC(QWidget *parent=NULL);
  ~LoadMenuC();

public slots:
  void loadGame();

private:
protected:
};

#endif