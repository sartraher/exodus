#ifndef __OPTIONSMENU_H__
#define __OPTIONSMENU_H__

#include <QWidget>
#include "ui_optionsmenu.h"

class OptionsMenuC : public QWidget,  public  Ui_OptionsMenu
{
public:
  OptionsMenuC(QWidget *parent);
  ~OptionsMenuC();

public slots:
  void saveOptions();

private:
protected:
};

#endif