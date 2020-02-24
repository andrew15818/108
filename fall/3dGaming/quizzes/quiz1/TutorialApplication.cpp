//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
//
// Date: 2019/10/28
//
#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>
using namespace Ogre;

const float PI = 3.141592654;

BasicTutorial_00::BasicTutorial_00(void)
    : 
mFlg_Root(false), mFlg_Root_Dir(true)

, mFlg_Arm(false), mFlg_Arm_Dir(true)
, mPitchAngle(0)      
{
	//set the maximum height that the penguin can move from
	//its starting position
	maxPenguinHeightOffset = 100;
}

void BasicTutorial_00::chooseSceneManager()
{
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_GENERIC, "primary");
	mSceneMgrArr[1] = mRoot
		->createSceneManager(ST_GENERIC, "secondary");
}

void BasicTutorial_00::createCamera_00(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(120,300,600));
	mCamera->lookAt(Ogre::Vector3(120,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createCamera_01(void)
{
	mSceneMgr = mSceneMgrArr[1];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(0,350,0.0));
	mCamera->lookAt(Ogre::Vector3(0.00001,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller

}



void BasicTutorial_00::createViewport_00(void)
{
	mCamera = mCameraArr[0];
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0.0,1.0));
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    mViewportArr[0] = vp;
}

void BasicTutorial_00::createViewport_01(void)
{
	mCamera = mCameraArr[1];

	Ogre::Viewport* vp = mWindow->addViewport(
		mCamera,
		1,
		0.75,
		0.0,
		0.25,
		0.25
		);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,1));
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	vp->setOverlaysEnabled(false);
    //
    mViewportArr[1] = vp;
}
/*! 
	\In this function, we just create an entity that is
	\attached to mSceneNode[root_index] instead of doing it 
	\twice in the regular function
*/
void BasicTutorial_00::createLowerLevelEntity(int index, int root_index, const String& meshName){
	String name_en, name_sn;
	genNameUsingIndex("R1", index, name_en);
	genNameUsingIndex("S1", index, name_sn);
	mEntity[index] = mSceneMgr->createEntity(name_en, meshName);
}
void BasicTutorial_00::createHierarchyStructure()
{
    String name_en;
    String name_sn;
	

    int index = 0;

    genNameUsingIndex("R1", index, name_en);
    genNameUsingIndex("S1", index, name_sn);
    mEntity[index] = mSceneMgr
		->createEntity( name_en, "sphere.mesh" ); ;
    mSceneNode[index] = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode( 
		name_sn, Vector3( 0, 0, 0 ) ); 

    mSceneNode[index]->attachObject(mEntity[index]);
    //
    mSphere = mSceneNode[index];
    int root_index = index;
    //
    ++index;
	//create the columns, changed the angle from 20 to 30
    int num = 12;
    double angle = 30;
    for (int i =0; i < num; ++i, ++index) {
        genNameUsingIndex("R1", index, name_en);
        genNameUsingIndex("S1", index, name_sn);
        mEntity[index] = mSceneMgr
            ->createEntity( name_en, "column.mesh" ); ;
        mSceneNode[index] = mSceneNode[root_index]
        ->createChildSceneNode( 
            name_sn, Vector3( 0, 100, 0 ) ); 
        mSceneNode[index]->scale(0.25, 1.0, 0.25);
        mSceneNode[index]->translate(Vector3(0.0, 0.0, 0.0),
            Node::TS_PARENT);
        mSceneNode[index]->attachObject(mEntity[index]);
        mSceneNode[index]->pitch(Degree(30), Node::TS_PARENT);
        mSceneNode[index]->yaw(Degree(i*angle), Node::TS_PARENT);
    }

    ++index;
    genNameUsingIndex("R1", index, name_en);
    genNameUsingIndex("S1", index, name_sn);
	
    mEntity[index] = mSceneMgr
		->createEntity( name_en, "cube.mesh" ); 
    mSceneNode[index] = mSceneNode[root_index]
		->createChildSceneNode( 
		name_sn, Vector3( 0, 350, 0 ) ); 
    mSceneNode[index]->scale(1.3/0.35, 0.1, 1.3/0.35);
    mSceneNode[index]->attachObject(mEntity[index]);
	
    //this is the white platform that needs to support the black cube
    mPlatform = mSceneNode[index];

    //creating the black cube
    ++index;
	//we will attach the penguin object to the column object later
	genNameUsingIndex("R1", index, name_en);
	genNameUsingIndex("S1", index, name_sn);
	mEntity[index] = mSceneMgr->createEntity(name_en, "column.mesh");
	mSceneNode[index] = mSceneNode[root_index]->createChildSceneNode(name_sn, Vector3(0,351,0));
	mSceneNode[index]->scale(1.0f, 0.1f, 1.0f);
	std::cout<<"LOOK HERE name_en:"<<mSceneNode[index]->getPosition().y<<std::endl;
	mSceneNode[index]->attachObject(mEntity[index]);
	mColumn = mSceneNode[index];
	
	//creating the penguin
	//need to adjust the penguin position so it moves up and down
	int column_index = index; 
	++index;
	genNameUsingIndex("R1", index, name_en);
	genNameUsingIndex("S1", index, name_sn);
	mEntity[index] = mSceneMgr->createEntity(name_en,"penguin.mesh");
	mSceneNode[index] = mSceneNode[column_index]->createChildSceneNode(name_sn, Vector3(0, 600, 0));
	mSceneNode[index]->scale(1.0f, 10.1f, 1.0f);
	mSceneNode[index]->attachObject(mEntity[index]);
	penguinOriginalHeight = mSceneNode[index]->getPosition().y;
    mPenguin = mSceneNode[index];
}

void BasicTutorial_00::createScene_00(void) 
{
	std::cout<<"hola"<<std::endl;
	mSceneMgr = mSceneMgrArr[0];
	mSceneMgr->setAmbientLight( ColourValue( 0.5, 0.5, 0.5 ) ); 
	//mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );  
	mSceneMgr->setShadowTechnique(
		SHADOWTYPE_STENCIL_ADDITIVE); 

	Light *light;
	light = mSceneMgr->createLight("Light1"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(150, 250, 100)); 
	light->setDiffuseColour(0.0, 1.0, 0.0);		
	light->setSpecularColour(0.0, 1.0, 0.0);	

	light = mSceneMgr->createLight("Light2"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(-150, 300, 250)); 
	light->setDiffuseColour(0.5, 0.5, 0.5);		
	light->setSpecularColour(0.5, 0.5, 0.5);	

    light = mSceneMgr->createLight("Light3"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(-150, 400, 250)); 
	light->setDiffuseColour(0.5, 0.5, 0.5);		
	light->setSpecularColour(0.0, 0.0, 0.5);	

	//
	Plane plane(Vector3::UNIT_Y, 0); 
	MeshManager::getSingleton().createPlane(
		"ground", 						ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
		plane, 
		1500,1500, 	// width, height
		20,20, 		// x- and y-segments
		true, 		// normal
		1, 			// num texture sets
		5,5, 		// x- and y-tiles
		Vector3::UNIT_Z	// upward vector
		); 

	Entity *ent = mSceneMgr->createEntity(
		"GroundEntity", "ground"); 
	//ent->setMaterialName("Examples/BeachStones");
	//ent->setMaterialName("Examples/Rockwall");


	mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode()
		->attachObject(ent); 

    ent = mSceneMgr->createEntity(
		"Background", "ground"); 
	//ent->setMaterialName("Examples/BeachStones");
	ent->setMaterialName("Examples/Rockwall");

    //Radian angle((45/180.0)*3.141592654);
    Radian angle(3.141952654/2.0);

    Vector3 axis(1.0, 0.0, 0.0);
    mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(
            Vector3(0.0, 0.0, -750.0),
            Quaternion( angle, axis))
		->attachObject(ent);

    createHierarchyStructure();
}

void BasicTutorial_00::createScene_01(void) 
{
	mSceneMgr = mSceneMgrArr[1];
	//mSceneMgr->setAmbientLight( ColourValue( 1.0,1.0, 1.0 ) ); 
	mSceneMgr->setAmbientLight( ColourValue( 0.0,0.0, 0.0 ) );  
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE); 
//mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);

	Light *light = mSceneMgr->createLight("Light1"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(100, 150, 250)); 
	light->setDiffuseColour(0.0, 0.0, 1.0);		
	light->setSpecularColour(0.0, 0.0, 1.0);	

	Entity *ent3 
		= mSceneMgr
		->createEntity( "Robot3", "cube.mesh" ); 
	//ent2->setCastShadows(true);
	SceneNode *node3 
		= mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode( 
		"RobotNode3", Vector3( 50, 0, 0 ) ); 
	node3->attachObject( ent3 );
	node3->translate(0, 30, 0);
	node3->scale(0.4, 0.2, 0.2);
	ent3->setMaterialName("Examples/green");
	//
	Plane plane(Vector3::UNIT_Y, 0); 
	MeshManager::getSingleton().createPlane(
		"ground", 						ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
		plane, 
		1500,1500, 	// width, height
		20,20, 		// x- and y-segments
		true, 		// normal
		1, 		// num texture sets
		5,5, 		// x- and y-tiles
		Vector3::UNIT_Z	// upward vector
		); 

	Entity *ent = mSceneMgr->createEntity(
		"GroundEntity", "ground"); 
	//ent->setMaterialName("Examples/RustySteel");
	mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode()
		->attachObject(ent); 


}

void BasicTutorial_00::createViewports(void)
{
	createViewport_00();
	createViewport_01();
}

void BasicTutorial_00::createCamera(void) {
	createCamera_00();
	createCamera_01();
	mCameraMan = mCameraManArr[0];
	//mCameraMan = mCameraManArr[1];
}

void BasicTutorial_00::createScene( void ) {
	createScene_00();
	createScene_01();
	//mSceneMgr = mSceneMgrArr[0]; // active SceneManager
	mSceneMgr = mSceneMgrArr[1]; // active SceneManager
    //
    mCamera = mCameraArr[0];
    //mCamera = mCameraArr[1];
    //
    mCameraMan->getCamera()
            ->setPosition(Vector3(-22.30,	409.24,	816.74));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.02,	-0.23,	-0.97));

}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
//
// To find out the answer:
// Go to see the definition of KeyEvent
//
bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyPressed ***\n";
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    
    if (arg.key == OIS::KC_C ) {
        
        //How to clear ss?
        ss.str("");
        ss.clear();
        
        //stringstream ss; // Second way

        // Third way?
        //=============

        // How to get camerea position?
        //-----------------------------
        //This is incorrect.
        //Vector3 pos = mCamera->getPosition();
        //-----------------------------
        Vector3 pos = mCameraMan->getCamera()->getPosition(); //Correct
        ss << std::fixed << std::setprecision(2) 
            << "CameraPosition:" 
            << pos.x << "\t" 
            << pos.y << "\t" 
            << pos.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
        //
        ss.str("");
        ss.clear();
        Vector3 dir = mCameraMan->getCamera()->getDirection();
        ss << std::fixed << std::setprecision(2) 
            << "CameraDirection:" 
            << dir.x << "\t" 
            << dir.y << "\t" 
            << dir.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
        //
    }

    if (arg.key == OIS::KC_1 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(-22.30,	409.24,	816.74));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.02,	-0.23,	-0.97));

    }

    if (arg.key == OIS::KC_2 ) {
        //mCameraMan->getCamera()
        //    ->setPosition(Vector3(-824.52,	468.58,	68.45));
        //mCameraMan->getCamera()
        //    ->setDirection(Vector3(0.94,	-0.31,	-0.11));

        //-824.52,	468.58,	68.45
        //0.94,	-0.31,	-0.11
		mCameraMan->getCamera()
			->setPosition(Vector3(-824.52, 468.58, 68.45));
		mCameraMan->getCamera()
			->setDirection(Vector3(0.94, -0.31, -0.11));
    }


    if (arg.key == OIS::KC_3 ) {
        //19.94	822.63	30.79
        //0.00	-0.99	-0.11
		mCameraMan->getCamera()
			->setPosition(Vector3(19.94, 822.63, 30.79));
		mCameraMan->getCamera()
			->setDirection(Vector3(0.00, -0.99, -0.11));
    }

	if (arg.key == OIS::KC_7){
		mFlg_Arm = (mFlg_Arm)?false:true;
		mFlg_Arm_Dir = !mFlg_Arm_Dir;
	}

	if(arg.key == OIS::KC_8){
		mFlg_Arm = (mFlg_Arm)?false:true;
		mFlg_Arm_Dir = mFlg_Arm_Dir;

	}

	if(arg.key == OIS::KC_9){
		mFlg_Root = (mFlg_Root)?false:true;
		mFlg_Root_Dir = !mFlg_Root_Dir;
	}

	if(arg.key == OIS::KC_0){
		mFlg_Root = (mFlg_Root)?false:true;
		std::cout<<"hola"<<std::endl;
		mFlg_Root_Dir = !mFlg_Root_Dir;
	}
    //
    // Add your own stuff
    //
    BaseApplication::keyPressed(arg);

    return flg;
}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
// 
// To find out the answer:
// Go to see the definition of KeyEvent
//
bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg )
{
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyReleased ***\n";
    
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    BaseApplication::keyReleased(arg);

    return flg;
}
/*When rotating the platform, the penguin and the column aren't moving with it, so I need to check the
assignment of a child scene node attached to the platform*/
/*The penguin isn't attached to the platform, it's attached to the sphere */
void BasicTutorial_00::HandleKeyEventAndUpdateObjects(const Ogre::FrameEvent& evt)
{
    //
    // Add your own stuff
    //   
	float a = 20.0*evt.timeSinceLastFrame;
	//changing the position of the penguin

		Vector3 tmp = mPenguin->getPosition();
		if( mFlg_Penguin_Dir){		
			tmp.y+=2*a;
			if(tmp.y > penguinOriginalHeight + maxPenguinHeightOffset){
				mFlg_Penguin_Dir = !mFlg_Penguin_Dir;
				tmp.y -= 10*a;
			}
		}
		else if(!mFlg_Penguin_Dir){
			tmp.y-=2*a;
			if(tmp.y<penguinOriginalHeight){
				tmp.y+=10*a;
				mFlg_Penguin_Dir = !mFlg_Penguin_Dir;
			}
		}
		mPenguin->setPosition(tmp);
	//changing the pitch of the central column
	if(mFlg_Arm){
		if ( mFlg_Arm_Dir ) {
			mPitchAngle += a;
			//std::cout<<"the current pitch angle: "<<mPitchAngle<<std::endl;
			if ( mPitchAngle > 30) {
				 mPitchAngle -= a;
				 mFlg_Arm_Dir = !mFlg_Arm_Dir;
				 a = -a;
			}
			mColumn->pitch(Degree(a));
		}
		else if(!mFlg_Arm_Dir){
			mPitchAngle -= a;
		
			if(mPitchAngle < -30){
				mFlg_Arm_Dir = !mFlg_Arm_Dir;
				mPitchAngle += a;
			}
			mColumn->pitch(Degree(-a));
		}
	}

	//moving the cube platform
	if(mFlg_Root){
		std::cout<<"direction we're supposed to be going in: "<<mFlg_Root_Dir<<std::endl;
		//std::cout<<"IM TRIGERED "<<std::endl;
		Vector3 tmp_platform = mSphere->getPosition();
		if (mFlg_Root_Dir){
			mSphere->rotate(Vector3(0,1,0), Degree(a));
			//tmp_platform.z +=20*sin(18.0f);
		}
		//need to figure out how to rotate in the negative direction.
		else if(!mFlg_Root_Dir){
			mSphere->rotate(Vector3(0,1,0), Degree(-a)); //def change this
			//tmp_platform.z -= 20*sin(18.0f);
		}
		//mSphere->setPosition(tmp_platform);

	}
	std::cout<<"the current pitch angle: "<<mPitchAngle<<std::endl;
}

bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
    //
    HandleKeyEventAndUpdateObjects(evt);
    //
    return flg;
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
