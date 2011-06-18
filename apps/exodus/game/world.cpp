#include "world.h"

#include <QTime>
#include <QPaintEvent>
#include <QPainter>

FieldC::FieldC()
{
}

FieldC::~FieldC()
{
}

void FieldC::init(int _x, int _y, QPixmap *pix)
{
  x = _x;
  y = _y;
  width = pix->width();
  height = pix->height();

  tileCol = getAverageColor(pix);

  if(tileCol == Qt::black) // Outside of the map
  {    
    type = NOTYPE;
    temp = VERYCOLD;
    //tileCol = Qt::black;
    res = NONE;
  }
  else if(tileCol.blue()>230 && tileCol.green()>230 && tileCol.red()>230) // Permaforst regions
  {
    type = ICE;
    temp = VERYCOLD;
    //tileCol = Qt::white;
    res = calculateResources(10, 10, 3, 5, 3, 0.5, 15, 0); // Too much? we will see
  }
  else if(tileCol.blue()<50 && tileCol.green()<50 && tileCol.red()<50)
  {
    type = MONTAIN;
    temp = COLD;
    //tileCol = Qt::darkGray;
    res = calculateResources(30, 20, 1, 5, 1, 2, 20, 1);
  }
  else if(tileCol.blue()>tileCol.red() && tileCol.blue()>tileCol.green())
  {
    type = WATER;
    temp = NORMAL;
    //tileCol = Qt::blue;
    res = calculateResources(1, 1, 1, 1, 1, 3, 1, 1);
  }
  else if(tileCol.red()>tileCol.blue() && tileCol.red()>tileCol.green())
  {
    type = DESERT;
    temp = x<500?HOT:VERYHOT;
    //tileCol = Qt::red;
    res = calculateResources(1, 1, 1, 10, 1, 30, 1, 10);
  }
  else if(tileCol.green()>tileCol.blue() && tileCol.green()>tileCol.red())
  {
    if(tileCol.red()>175)
    {
      type = PLAIN;
      temp = x<500?NORMAL:HOT;
      //tileCol = Qt::green;
      res = calculateResources(5, 5, 0.5, 0.5, 5, 5, 5, 5);
    }
    else
    {
      type = FOREST;
      temp = x<500?NORMAL:HOT;
      //tileCol = Qt::darkGreen;
      res = calculateResources(5, 5, 0.5, 0.5, 5, 5, 5, 5);
    }
  }

  tileCol = QColor(tileCol.red()*0.75, tileCol.green()*0.75, tileCol.blue()*0.75); // Later from options
}

FieldC::Resources FieldC::calculateResources(double iron, double chopper, double gold, double bauxit, double silver, double quarz, double otherMetal, double cristal)
{
  Resources resource = NONE;

  if(iron<getRandom())
    resource = (Resources)(resource | IRON);

  if(chopper<getRandom())
    resource = (Resources)(resource | CHOPPER);

  if(gold<getRandom())
    resource = (Resources)(resource | GOLD);

  if(bauxit<getRandom())
    resource = (Resources)(resource | BAUXIT);

  if(silver<getRandom())
    resource = (Resources)(resource | SILVER);

  if(quarz<getRandom())
    resource = (Resources)(resource | QUARZ);

  if(otherMetal<getRandom())
    resource = (Resources)(resource | OTHERMETAL);

  if(cristal<getRandom())
    resource = (Resources)(resource | CRISTAL);

  return res;
}

double FieldC::getRandom()
{
  QTime time = QTime::currentTime();
  qsrand((uint)time.msec());
  return (qrand()%10000)/100;
}

QColor FieldC::getAverageColor(QPixmap *pix)
{
  QImage img = pix->toImage();
  qint64 r=0;
  qint64 g=0;
  qint64 b=0;
  for(int xIndex=0; xIndex<img.width(); xIndex++)
    for(int yIndex=0; yIndex<img.height(); yIndex++)
    {
      QRgb rgb = img.pixel(xIndex, yIndex);
      
      r+= (rgb & 0xFF0000) >> 16;
      g+= (rgb & 0x00FF00) >> 8;
      b+= (rgb & 0x0000FF);
    }  

  int pixels = img.width()*img.height();
  return QColor(r/pixels, g/pixels, b/pixels);
}

GeoStatusC::GeoStatusC(QWidget *parent) : QWidget(parent)
{
  setupUi(this);
}

GeoStatusC::~GeoStatusC()
{
}


WorldC::WorldC(QWidget *parent) : QWidget(parent)
{
  statusWidget = new GeoStatusC(this);
  statusWidget->show();
  this->setMouseTracking(true);
}

WorldC::~WorldC()
{
  delete statusWidget;
}

void WorldC::paintEvent(QPaintEvent* pe)
{
  QPainter paint(this);
  paint.drawPixmap(QRect(0, 0, this->width(), this->height()), *worldMap, QRect(0, 0, worldMap->width(), worldMap->height())); // World
  paint.drawPixmap(QRect(this->width()/20,((this->height()/10)*4),(this->width()/5),(this->width()/5)), *worldMap, QRect(0,0,worldMap->width(),worldMap->height())); // Magnifyingglass
  QWidget::paintEvent(pe);
}

void WorldC::mouseMoveEvent ( QMouseEvent * event )
{

  int x = event->pos().x()/(this->width()/1000.0);
  int y = event->pos().y()/(this->height()/1000.0);

  // Coordinates
  QString text = QString("(%1|%2)").arg(x).arg(y);
  if(!statusWidget->tableWidget->item(0,1))
    statusWidget->tableWidget->setItem(0,1, new QTableWidgetItem(text));
  else
    statusWidget->tableWidget->item(0,1)->setText(text);

  // Region type
  text = getRegionType(fields[x][y].type);
  if(!statusWidget->tableWidget->item(1,1))
    statusWidget->tableWidget->setItem(1,1, new QTableWidgetItem(text));
  else
    statusWidget->tableWidget->item(1,1)->setText(text);

  // Region status
  text  = "Undiscovert";
  if(!statusWidget->tableWidget->item(2,1))
    statusWidget->tableWidget->setItem(2,1, new QTableWidgetItem(text));
  else
    statusWidget->tableWidget->item(2,1)->setText(text);
}

void WorldC::keyReleaseEvent ( QKeyEvent * event )
{
  if(event->key()==Qt::Key_F10)
    this->hide();
}

void WorldC::resizeEvent ( QResizeEvent * event )
{
  statusWidget->setGeometry(this->width()/20, ((this->height()/10)*7), (this->width()/5), (this->height()/7.5));
}


QString WorldC::getRegionType(FieldC::FieldType type)
{
  QString text="";
  switch(type)
  {
  case FieldC::WATER:
    text = "Water";
    break;
  case FieldC::FOREST:
    text = "Forest";
    break;
  case FieldC::MONTAIN:
    text = "Mountain";
    break;
  case FieldC::DESERT:
    text = "Desert";
    break;
  case FieldC::PLAIN:
    text = "Plain";
    break;
  case FieldC::ICE:
    text = "Ice";
    break;
  }
  return text;
}
