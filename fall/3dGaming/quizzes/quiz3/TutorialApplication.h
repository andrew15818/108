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
\n Date:2019/12/11

This is an assignment of 3D Game Programming

*/

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"
#include "aStar.h"
#include <queue>
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
    bool keyPressed(  const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    void createSpace();

    void resolveCollisionSmallSpheres();
    void resolveCollisionLargeSphere();
	void setBarrels();
    void reset();
protected:
    Ogre::Viewport* mViewportArr[8];
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
    //

	int getWorldCoordinatesFromIndex(int index); //function mapping coordinates from map[][] to game world
	int getIndexFromWorldCoordinates(int index);
	void printMatrix();
    void setSphereAlongPath(int clickX, int ClickZ);
	bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
	int getIndexToDelete(  std::list<aStarNode&>& listo, aStarNode& nodo);
	
	//utility functions related to a*
	void search(int startX, int startZ, int endX, int endZ);
	double manDist(int startX, int startY, int destX, int destY); //distance from the start indices to the end ones
	bool isValid(int x, int y); //tests for boundary collisions
	bool isDestination(int currentX, int currentZ, int endX, int endZ);
	
	bool findNode( std::list<aStarNode>Open, const aStarNode& node);
	void printF(); //paying respects
	void printPath(int startX, int startZ, int endX, int endZ); //print the path for debugging purposes

	//aiding in moving and animating the robot
	void drawSpheres(int startX, int startZ, int endX, int endZ);
	//
	int clickX, clickZ; //when we perfrom a ray query, these are the x, y coordinates
	int robotX, robotZ; //the robot's locations when we perform the search
	
	int sideBarrels; //number of barrels per side
	int totalBarrels;
	int totalSpheres;
	int barrelDelta;
	int barrelsBound; //where the barrels are arranged in a square in our scene
	// hopefully upper bound for the amount of spheres possible along the path?

	bool isValid();

	aStarNode map[10][10]; //new place where we store the node values
	int mMoveDirection;
	
	
    Entity *robotEntity;
    SceneNode *robotSceneNode;

	Entity* mBarrelEnts[54];
	SceneNode* mBarrelSceneNodes[54];

	Entity* mPathSphereEnts[20];
	SceneNode* mPathSceneNodes[20]; 
	
	Plane planito;
	AnimationState* mAnimationState;
};

#endif // #ifndef __BasicTutorial_00_h_