#include "soundmanager.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <QMessageBox>

SoundManager* SoundManager::_instance=NULL;


void ERRCHECK(FMOD_RESULT result)
{
  if (result != FMOD_OK)
  {
    printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
    exit(-1);
  }
}

SoundManager::SoundManager()
{
  system        = NULL;
  channel       = NULL;
  FMOD_RESULT       result;
  unsigned int      version;

  result = FMOD::System_Create(&system);
  ERRCHECK(result);

  result = system->getVersion(&version);
  ERRCHECK(result);

  if (version < FMOD_VERSION)
  {
      printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
      return;
  }

  result = system->init(32, FMOD_INIT_NORMAL, 0);
  ERRCHECK(result);
}

SoundManager::~SoundManager()
{
}

void SoundManager::play(QString filename)
{
  if(_instance==NULL)
    _instance=new SoundManager();

  FMOD::Sound *sound;  
  QByteArray   bytes  = filename.toAscii();
  const char * ptr    = bytes.data();
  _instance->system->createSound(ptr, FMOD_HARDWARE, 0, &sound);  

  
  _instance->system->playSound(FMOD_CHANNEL_FREE, sound, false, &(_instance->channel));  
}
 
void SoundManager::pause()
{
  if(_instance==NULL)
    _instance=new SoundManager();

  if(_instance->channel)
    _instance->channel->setPaused(true);
}

void SoundManager::resume()
{
  if(_instance==NULL)
    _instance=new SoundManager();

  if(_instance->channel)
    _instance->channel->setPaused(false);
}

void SoundManager::stop()
{
  if(_instance==NULL)
    _instance=new SoundManager();

  if(_instance->channel)
    _instance->channel->stop();
}

