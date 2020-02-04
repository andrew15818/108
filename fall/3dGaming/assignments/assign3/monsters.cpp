#include "monsters.h"
#include "BasicTools.h"

MONSTER::MONSTER(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
	mSceneNode = a_SceneMgr->getRootSceneNode()->createChildSceneNode();
	mVelocity= Vector3::ZERO;
	mTime = rand() %2;
}

//
// Make the monster look at mTarget
//
void MONSTER::updateViewDirection()
{
	if (mTarget == 0) return;
	Vector3 pos = mTarget->getPosition();
	Vector3 target_pos = mSceneNode->getPosition();
    //
    // Add your own stuff
    // 
	Vector3 lookAtPos(mTarget->getPosition().x, mSceneNode->getPosition().y, mTarget->getPosition().z);
	mSceneNode->lookAt(lookAtPos, Ogre::Node::TransformSpace::TS_WORLD);
	mSceneNode->yaw(Radian(3.1415));
}

//
// Update the position of the monster.
//
void MONSTER::update(const Ogre::FrameEvent& evt)
{
	/*
	float radius = 15;
	Vector3 mv = mInitPosition - mTarget->getPosition();
	Real d = mv.length();
	mv.normalise();
	mv.y =0;
	Real dt = evt.timeSinceLastFrame;
	
	if(d < radius){
		mVelocity += dt * mv * 1500/(d+1);
	}
	else if(d > radius){
		mVelocity -= dt * mv * 10;
	}
	mTime += dt +dt*(5*mRandSpeed);
	Vector3 offset=Vector3::ZERO;
	offset.y = mAmplitude*sin(mTime);
	if(mTime > 2*3.14159){
		mTime -= 3.14159;
	}
	//Vector3 new_pos = mSceneNode->getPosition() + mVelocity*dt + offset;
	mSceneNode->setPosition(mSceneNode->getPosition() + mVelocity * dt);
	std::cout<<"pos; "<<mSceneNode->getPosition()<<std::endl;
	*/
		double totalRadius = 15;
	Vector3 mv = mSceneNode->getPosition() - mTarget->getPosition();
	Real d = mv.length();
	mv.normalise();
	Real dt = evt.timeSinceLastFrame;
	Vector3 mVelocity(0.0f, 0.0f, 0.0f);
	mv.y = 0;
	if( d < totalRadius){
		mVelocity += dt * mv * 1500/(d+1);
	}
	else if( d > 300){
		mVelocity -= dt * mv * 100;
	}
	
	 mTime += dt + dt*(5*mRandSpeed);
	Vector3 offset(0,0,0);
	 offset.y = mAmplitude* sin(mTime);
	if( mTime > 3.14159 * 2){
		mTime -= 3.14159* 2;
	}
	
	Vector3 p0 = mSceneNode->getPosition();
	//p0.y = offsetY + 100;
	
	
	mSceneNode->setPosition(mVelocity + p0 + offset*dt);
	//std::cout<<mSceneNode->getPosition()<<std::endl;
	updateViewDirection();
	
}
