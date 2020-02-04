#include <iostream>

#include "sound_manager.h"

#include "read_data.h"

//SOUND_MANAGER *SOUND_MANAGER::_mInstance = new SOUND_MANAGER;
SOUND_MANAGER *SOUND_MANAGER::_mInstance = 0;

#define SOUND_MNG_SOUNDWAVE_FILEPATH        "./sound";
#define SOUND_MNG_SOUNDWAVE_FILE_EXPLOSION  "explosion.wav"
#define SOUND_MNG_SOUNDWAVE_FILE_FIRE       "missle.wav"
#define SOUND_MNG_SOUNDWAVE_FILE_STAMINA    "warning_not_enough_stamina.wav"

SOUND_MANAGER::SOUND_MANAGER()
{
    init();
}

void SOUND_MANAGER::init(int numSounds)
{
    mNumSounds = numSounds;
    std::string filePath = SOUND_MNG_SOUNDWAVE_FILEPATH;
    std::string soundFileName;
    //////////////////////////////////////////////////////
    /*
    soundFileName = filePath 
        + "/" 
        + SOUND_MNG_SOUNDWAVE_FILE_EXPLOSION;
    */

    //
    soundFileName = filePath 
        + "/" 
        + DATA_READER::getSoundFileName_Explosion();
    //
    mSound_Explosion = new SOUND*[mNumSounds];
    for (int i = 0; i < mNumSounds;++i) {
        mSound_Explosion[i] = new SOUND;
        
        mSound_Explosion[i]->init(soundFileName, i==0);
    }

    //
    /*
    soundFileName = filePath 
        + "/" 
        + SOUND_MNG_SOUNDWAVE_FILE_FIRE;
    */
    //
    //
    soundFileName = filePath 
        + "/" 
        + DATA_READER::getSoundFileName_Fire();
    //

    mSound_Fire = new SOUND*[mNumSounds];
    for (int i = 0; i < mNumSounds;++i) {
        mSound_Fire[i] = new SOUND;
        
        mSound_Fire[i]->init(soundFileName, false);
    }
    //
    //
    /*
    soundFileName = filePath 
        + "/" 
        + SOUND_MNG_SOUNDWAVE_FILE_STAMINA;
    */
    //
    //
    soundFileName = filePath 
        + "/" 
        + DATA_READER::getSoundFileName_Stamina();
    //
    mSound_Stamina = new SOUND*[mNumSounds];
	debugFilePath = soundFileName;
	std::cout<<"stamina file: "<<debugFilePath<<std::endl;
    for (int i = 0; i < mNumSounds;++i) {
        mSound_Stamina[i] = new SOUND;
        
        mSound_Stamina[i]->init(soundFileName, false);
    }
    //
    //
    soundFileName = filePath 
        + "/" 
        + DATA_READER::getSoundFileName_LevelUp();
	debugFilePath = soundFileName;
    //
    mSound_LevelUp = new SOUND*[mNumSounds];
    for (int i = 0; i < mNumSounds;++i) {
        mSound_LevelUp[i] = new SOUND;
        
        mSound_LevelUp[i]->init(soundFileName, false);
    }
    //
    mSoundIndex_Explosion = 0;
    mSoundIndex_Fire = 0;
    mSoundIndex_Stamina = 0;
    mSoundIndex_LevelUp = 0;

}


 void SOUND_MANAGER::play_Explosion()
 {
     std::cout << "SOUND_MANAGER::play_Explosion()" << std::endl;

     mSound_Explosion[mSoundIndex_Explosion]->play();
     mSoundIndex_Explosion = (mSoundIndex_Explosion+1)%mNumSounds;
 }

 void SOUND_MANAGER::play_Fire()
 {
     std::cout << "SOUND_MANAGER::play_Fire()" << std::endl;
	 //std::cout<<"playing :"<<mSoundIndex_Fire<<"/"<<mNumSounds<<" fire soundds"<<std::endl;
     mSound_Fire[mSoundIndex_Fire]->play();
     mSoundIndex_Fire = (mSoundIndex_Fire+1)%mNumSounds;
 }

 void SOUND_MANAGER::play_Stamina()
 {
     std::cout << "SOUND_MANAGER::play_Stamina()" << std::endl;

     mSound_Stamina[mSoundIndex_Stamina]->play();
     mSoundIndex_Stamina = (mSoundIndex_Stamina+1)%mNumSounds;
 }

  void SOUND_MANAGER::play_LevelUp()
 {
     std::cout << "SOUND_MANAGER::play_LevelUp()" << std::endl;
     mSound_LevelUp[mSoundIndex_LevelUp]->play();
     mSoundIndex_LevelUp = (mSoundIndex_LevelUp+1)%mNumSounds;
 }
