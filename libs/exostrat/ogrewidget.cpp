#include "ogrewidget.h"

#include <OGRE/Ogre.h>
#include <QFile>

OgreWidget::OgreWidget( QWidget *parent ) : QGLWidget( parent ), mOgreWindow(NULL)
{
  init();
}

OgreWidget::~OgreWidget()
{
  mOgreRoot->shutdown();
  delete mOgreRoot;
  destroy();
}

/**
 * @brief init the object
 * @author kito berg-taylor
 */
void OgreWidget::init()
{
  // create the main ogre object
  mOgreRoot = new Ogre::Root;

  mOgreRoot->loadPlugin("RenderSystem_GL_d");
  Ogre::String rName("OpenGL Rendering Subsystem");
  Ogre::RenderSystemList rList = mOgreRoot->getAvailableRenderers();
  Ogre::RenderSystemList::iterator it = rList.begin();
  Ogre::RenderSystem *rSys = 0;
  while(it != rList.end())
  {
    rSys = * (it++);
    Ogre::String strx=rSys->getName();
    if(strx == rName)
    {
      mOgreRoot->setRenderSystem(rSys);
      break;
    }
  }
  mOgreRoot->initialise(false); // don't create a window
}
 
/**
 * @brief setup the rendering context
 * @author Kito Berg-Taylor
 */
void OgreWidget::initializeGL()
{
  //== Creating and Acquiring Ogre Window ==//

  // Get the parameters of the window QT created

  Ogre::String winHandle=Ogre::StringConverter::toString((size_t)(HWND)winId());

  Ogre::NameValuePairList params;
  params["parentWindowHandle"] = winHandle;

  mOgreWindow = mOgreRoot->createRenderWindow( "QOgreWidget_RenderWindow",
                          this->width(),
                          this->height(),
                          false,
                          &params );

  //mOgreWindow->setActive(true);
  //WId ogreWinId = 0x0;
  //mOgreWindow->getCustomAttribute( "WINDOW", &ogreWinId );

  //assert( ogreWinId );

  //this->create( ogreWinId );
  setAttribute( Qt::WA_PaintOnScreen, true );
  setAttribute( Qt::WA_NoBackground );

  //== Ogre Initialization ==//
  Ogre::SceneType scene_manager_type = Ogre::ST_EXTERIOR_CLOSE;

  mSceneMgr = mOgreRoot->createSceneManager( scene_manager_type );
  mSceneMgr->setAmbientLight( Ogre::ColourValue(1,1,1) );

  mCamera = mSceneMgr->createCamera( "QOgreWidget_Cam" );
  mCamera->setPosition( Ogre::Vector3(0,1,0) );
  mCamera->lookAt( Ogre::Vector3(0,0,0) );
  mCamera->setNearClipDistance( 1.0 );

  Ogre::Viewport *mViewport = mOgreWindow->addViewport( mCamera );
  mViewport->setBackgroundColour( Ogre::ColourValue( 1.0,1.0,1.0 ) );
}
 
/**
 * @brief render a frame
 * @author Kito Berg-Taylor
 */
void OgreWidget::paintGL()
{
  assert( mOgreWindow );
  mOgreRoot->_fireFrameStarted();
  mOgreWindow->update();
  mOgreRoot->_fireFrameEnded();
}
 
/**
 * @brief resize the GL window
 * @author Kito Berg-Taylor
 */
void OgreWidget::resizeGL( int width, int height )
{
  assert( mOgreWindow );
  mOgreWindow->windowMovedOrResized();
  mCamera->setAspectRatio(Ogre::Real(width) / Ogre::Real(height));
}
 
/**
 * @brief choose the right renderer
 * @author Kito Berg-Taylor
 */
/*
Ogre::RenderSystem* OgreWidget::chooseRenderer( Ogre::RenderSystemList *renderers )
{
  // It would probably be wise to do something more friendly 
  // that just use the first available renderer
  return *renderers->begin();
}*/