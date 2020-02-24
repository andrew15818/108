//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
//
// Date: 2019/10/28
//
/*!
\brief 3D Game Programming
\n
My Name: Andres Ponce
\n
My ID: 0616110
\n
My Email: andreseponce.cs06@nctu.edu.tw
\n Date: 2019/10/28

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
	void createLowerLevelEntity(int index, int root_index, const String& meshName);
	void createViewport_00(void);
	void createViewport_01(void);
	//
	void createCamera_00();
	void createCamera_01();

	void createScene_00();
	void createScene_01();
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );

    void createHierarchyStructure();
protected:
    Ogre::Viewport* mViewportArr[8];
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
    //
	
    bool mFlg_Penguin_Jump;
    bool mFlg_Penguin_Dir;
    //
    bool mFlg_Root; //are these for scene Node A, the sphere?
    bool mFlg_Root_Dir;
    bool mFlg_Arm; //are these for the column holding the penguin?
    bool mFlg_Arm_Dir;
    //
	bool mFlg_Column_Is_Moving; //penguin supporting column movement
	bool mFlg_Platform_Is_Moving; //platform supporting the penguin
    SceneNode *mSceneNode[128];
    Entity *mEntity[128];

    SceneNode *mPlatform; //black cubic platform
    SceneNode *mColumn; //black column on which the penguin rests

    SceneNode *mPenguin;
    SceneNode *mSphere;
	
    double mPitchAngle;
	double penguinOriginalHeight;
	double maxPenguinHeightOffset;
    void HandleKeyEventAndUpdateObjects(const Ogre::FrameEvent& evt);

};

#endif // #ifndef __BasicTutorial_00_h_