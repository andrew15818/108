//
// Student Name:
// Student ID:
// Student Email Address:
//
//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
// Select and move characters

#ifndef __ParticleSystemManager_h_
#define __ParticleSystemManager_h_
 
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreParticleSystem.h>
#include <OgreParticleEmitter.h>
using namespace Ogre;

class SpecialEffectManager {
protected:
    SceneManager *mSceneMgr;
    int mNumParticleSystems;
    SceneNode **mParticleNodes;
    ParticleEmitter **mParticleEmitters;
    int mCurrentIndex;
    void createParticleSystem(int index);
public:
    SpecialEffectManager();
    SpecialEffectManager(
        SceneManager *sceneMgr,
        int numParticleSystems);

    void init();
    int getNumParticleSystems() const { return mNumParticleSystems; }
    int setOffParticleSystem(const Ogre::Vector3 &pos);
    void setOffParticleSystem(int pIndex, const Ogre::Vector3 &pos);
    void disableAllParticleSystems();
    void enableAllParticleSystems();
};

#endif
