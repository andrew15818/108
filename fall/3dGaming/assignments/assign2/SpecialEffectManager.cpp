#include <string>
#include "SpecialEffectManager.h"
#include "BasicTools.h"

const std::string pNames[] = {
    "Examples/GreenyNimbus",
    //"Examples/Rain",
    "Examples/Aureola",
    "Examples/Snow",
    //"Examples/Smoke"
};

SpecialEffectManager::SpecialEffectManager()
{
    mSceneMgr = 0;
    mCurrentIndex = 0;
}

    SpecialEffectManager::SpecialEffectManager(
        SceneManager *sceneMgr,
        int numParticleSystems
        )
    {
        mSceneMgr = sceneMgr;
        mNumParticleSystems = numParticleSystems;
        mParticleNodes = new SceneNode*[mNumParticleSystems];
        mParticleEmitters  = new ParticleEmitter*[mNumParticleSystems];
    }


void SpecialEffectManager::createParticleSystem(int index)
{
    int i = index;
    int numPNames = sizeof(pNames)/sizeof(std::string);
    int pTypeIndex = index%numPNames;		// particle system type

    // add your own stuff
}

void SpecialEffectManager::init()
{
    for (int i =0; i < mNumParticleSystems; ++i) {
        createParticleSystem(i);
    }
}

void SpecialEffectManager::setOffParticleSystem(
    int pIndex, 
    const Ogre::Vector3 &pos)
{
    int index = pIndex;
    SceneNode *fNode = mParticleNodes[index];

    //add your own stuff
    
}

int SpecialEffectManager::setOffParticleSystem(const Ogre::Vector3 &pos)
{
    int index = mCurrentIndex;
    // 
    // add your own stuff
    //
    mCurrentIndex = (mCurrentIndex+1)%mNumParticleSystems;
    return index;
}

void SpecialEffectManager::disableAllParticleSystems()
{
    for (int i =0; i < mNumParticleSystems; ++i) {
             mParticleNodes[i]->setVisible(false);
        ParticleEmitter *e = mParticleEmitters[i];
	e->setEnabled(false);
    }
}

    void SpecialEffectManager::enableAllParticleSystems() {
         for (int i =0; i < mNumParticleSystems; ++i) {
       // 
       // add your own stuff
       //
    }
    }
