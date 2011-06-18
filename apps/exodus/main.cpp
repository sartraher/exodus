#include "exodus.h"
#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  Exodus ex;

  ex.init();
  ex.FullScreen(true);
  ex.showIntro();
  ex.showMain();
  ex.showExtro();
  //ex.clean();

  ex.show();  
  return a.exec();
}
