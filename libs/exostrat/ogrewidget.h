#ifndef __OGREWIDGET_H__
#define __OGREWIDGET_H__
 
#include <QGLWidget>
#include <QX11Info>

#include "exostratapi.h"
 
namespace Ogre
{
  class RenderSystem;
  class Root;
  class RenderWindow;
  class Camera;
  class Viewport;
  class SceneManager;
  //class RenderSystemList;
}

class EXOSTRATEXPORT OgreWidget : public QGLWidget
{
  //Q_OBJECT;
 
 public:
  OgreWidget( QWidget *parent=NULL ); 
  virtual ~OgreWidget();
 
 protected:
  virtual void initializeGL();
  virtual void resizeGL( int, int );
  virtual void paintGL();
 
  void init();
 
  //virtual Ogre::RenderSystem* chooseRenderer( Ogre::RenderSystemList* );
 
  Ogre::Root *mOgreRoot;
  Ogre::RenderWindow *mOgreWindow;
  Ogre::Camera *mCamera;
  Ogre::Viewport *mViewport;
  Ogre::SceneManager *mSceneMgr;
};
 
#endif