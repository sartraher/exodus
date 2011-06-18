#ifndef __STARTMENU_H__
#define __STARTMENU_H__

#include <QWidget>
#include "ui_startmenu.h"

class StartMenuC : public QWidget, public Ui_StartMenu
{
  Q_OBJECT
public:
  StartMenuC(QWidget *parent=NULL);
  ~StartMenuC();

  virtual void paintEvent(QPaintEvent* pe);

private:
protected:
};

#endif