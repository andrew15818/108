//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
/*!
\brief 3D Game Programming
\n
My Name: Andres Ponce
\n
My ID: 0616110
\n
My Email: andreseeponce@gmail.com
\n Date: 2019/11/11

This is an assignment of 3D Game Programming

*/

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"

using namespace Ogre;

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
	virtual void createViewports(void);
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void chooseSceneManager(void);
    //
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
    //
protected:
	/*!
	\brief Create a viewport

	Create a viewport for the entire screen.

	\return The sum of two integers.
	*/
	void createViewport_00(void);
	void createViewport_01(void);
	//
	void createCamera_00();
	void createCamera_01();

	void createScene_00();
	void createScene_01();
	void Scene_00CreateBarrels();
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    void createSpace(int startingIndex);

    void resolveCollisionSmallSpheres();
    void resolveCollisionLargeSphere();
    void resolveCollision(
    SceneNode *nodeA, SceneNode *nodeB,
    float rA, float rB);
    void resolveCollision(
    SceneNode *nodeA, SceneNode *nodeB,
    float rA, float rB, float wA, float wB);
    void resolveCollision();
	void resolveBoundaryCollision(SceneNode *nodeA);
	void handleSphereDifference(bool increasing);

    void reset();
protected:
    Ogre::Viewport* mViewportArr[8];
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
    //
	bool isMovingUp;
	bool isMovingDown;
	bool isMovingRight;
	bool isMovingLeft;
    //
	bool switchedSphereCount;
    //
    int mMoveDirection;
    SceneNode *mLargeSphereSceneNode;
    Entity *mLargeSphereEntity;
	//
	int barrelsBound; // we need the positive and negative values of the barrel squares
    int mNumSpheres;
	int prevNumSpheres;
	int mSceneNodeIndex;
	SceneNode* mSphereSceneNode[500];
	Entity* mSphereEntity[500];
    SceneNode *mSceneNode[1024];
    Entity *mEntity[1024];


};

#endif // #ifndef __BasicTutorial_00_h_