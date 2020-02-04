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
\n Date: 10/26/19

This is an assignment of 3D Game Programming
*/

////////////////////////////////////////
// You can delete or add some functions to do the assignment.
////////////////////////////////////////

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"
#include "selection_rectangle.h"

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
	virtual void createViewports(void);
	virtual void createScene(void);
	
	
    //
    virtual bool frameStarted(const Ogre::FrameEvent& evt);
    //
    // Add your own stuff.
    //
protected:
	/*!
	\brief Create a viewport

	Create a viewport for the entire screen.

	\return The sum of two integers.
	*/
	//SceneNode* mSceneNode;
	void createViewport_00(void);
	void createViewport_01(void);
	//
	void createCamera_00();
	void createCamera_01();

	void createScene_00();
	void createScene_01();
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    //
    // Add your own stuff.
    //
	//functions for dealing with the mouse input7
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseMoved(const OIS::MouseEvent& arg);
	
	//functions for creating the different scenes
	void sc0_createPlane();
	void sc0_createFog();
	void sc0_createRobots(int startingIndex, double radius);
	void sc0_createSphere();
	
	//handling the animation state of the robots
	void updateRobotAnimationState(const Ogre::FrameEvent& evt);
	void toggleParticleEffects();

protected:
	/*! We keep track of the sceneNodes, particleNodes, Entities, cameras, 
	and viewports, to ensure easy access later on*/
    Ogre::Viewport* mViewportArr[8];
	Ogre::Camera* mCameraArr[8];
	Ogre::Camera* mCamera2;
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
	//
    // Add your own stuff.
	/*!The light speed and angle serve to calculate the trajectory of the light as 
	it surrounds the scene. The next two items deal with the selection of the items
	on the screen.*/
	SceneNode* mSceneNodeArr[60];
	ParticleSystem* mParticleArr[60];

	Entity* mEntityArr[60];
    Ogre::Real left, top, right, bottom;
	double lightAngle;
	double lightSpeed;
	int numRobots;
	AnimationState* mAnimationState[60]; //remember to change this if the num of Robots changes later
	bool isRobotMoving[60]; //set if a robot is targeted in a query
	bool isParticleSystemActive;
	Vector3 directions[60];
	Vector3 distances[60]; //distance each robot has to move
	Vector3 targetPoint; //where we want to move
	
	SelectionRectangle *mSelectionRect;
	PlaneBoundedVolumeListSceneQuery *mVolQuery;
};


#endif // #ifndef __BasicTutorial_00_h_