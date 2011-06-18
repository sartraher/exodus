#ifndef __WORLD_H__
#define __WORLD_H__

#include <QWidget>
#include <QPixmap>

#include "ui_geostatus.h"

class QPaintEvent;

class FieldC
{ 
  enum Temperature { VERYCOLD, COLD, NORMAL, HOT, VERYHOT };
  enum Resources { NONE=0, IRON=1, CHOPPER=2, GOLD=4, BAUXIT=8, SILVER=16, QUARZ=32, OTHERMETAL=64, CRISTAL=128 };
public:

  enum FieldType { WATER, FOREST, MONTAIN, DESERT, PLAIN, ICE, NOTYPE };

  FieldC();
  ~FieldC();

  void init(int _x, int _y, QPixmap *pix);

  // Field attributes
  FieldType type;
  Temperature temp;
  Resources res;

  // Localisation data
  int tectonicalPlate;
  FieldC *neibours;

  // Data for redrawing the map, coord will also be used for climatic calculations
  int x;
  int y;
  int width;
  int height;
  QColor tileCol;
private: 

protected:
  QColor getAverageColor(QPixmap *pix);
  FieldC::Resources calculateResources(double iron, double chopper, double gold, double bauxit, double silver, double quarz, double otherMetal, double cristal);
  double getRandom();

};

class GeoStatusC : public QWidget, public Ui_GeoStatus
{
public:
  GeoStatusC(QWidget *parent=NULL);
  ~GeoStatusC();

private:
protected:
};

class WorldC : public QWidget
{
  Q_OBJECT
public:
  WorldC(QWidget *parent=NULL);
  ~WorldC();

  virtual void paintEvent(QPaintEvent* pe);
  virtual void mouseMoveEvent ( QMouseEvent * event );
  virtual void keyReleaseEvent ( QKeyEvent * event );
  virtual void resizeEvent ( QResizeEvent * event );

  QString getRegionType(FieldC::FieldType type);

  FieldC fields[1000][1000];
  QPixmap *worldMap;

signals:
  void mouseOver(int x, int y);

private:  
  GeoStatusC *statusWidget;

protected:
};

#endif