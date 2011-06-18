#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include "fmod/api/inc/fmod.hpp"
#include "fmod/api/inc/fmod_dsp.h"
#include "fmod/api/inc/fmod_errors.h"
#include <QString>

class SoundManager
{
 public:
  static void play(QString filename);
  static void pause();
  static void resume();
  static void stop();

 private:
  static SoundManager *_instance;

  FMOD::System *system;
  FMOD::Channel *channel;
 protected:
  SoundManager();
  ~SoundManager();
};

#endif
