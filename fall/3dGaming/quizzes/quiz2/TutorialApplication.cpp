//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
// Date: 2019/10/28
//
#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace Ogre;

const float PI = 3.141592654;

#define mMoveDirection_NONE 0
#define mMoveDirection_DOWN (1 << 0)
#define mMoveDirection_UP   (1 << 1)
#define mMoveDirection_LEFT (1 << 2)
#define mMoveDirection_RIGHT (1<<3)


BasicTutorial_00::BasicTutorial_00(void)
    : 
mMoveDirection(mMoveDirection_NONE)
{
	mSceneNodeIndex = 0;
	mNumSpheres = 500;
	prevNumSpheres = mNumSpheres;
	barrelsBound = 650;
	isMovingUp = false;
	isMovingDown = false;
	isMovingRight = false;
	isMovingLeft  = false;
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
}
void BasicTutorial_00::resolveBoundaryCollision(
	SceneNode* nodeA)
{
	int currentRadius = (nodeA->getName() =="LargeSphereSN")?100:15;

	Vector3 posA = nodeA->getPosition();
	int putaBound = barrelsBound-100;
	if(posA.x + currentRadius >= (putaBound-20)){
		posA.x = (putaBound-20) - currentRadius + 1 ;
	}
	if(posA.x - currentRadius <= (-barrelsBound + 20)){
		posA.x = -barrelsBound + 20 +currentRadius + 1;
	}
	if(posA.z + currentRadius >= putaBound-20){
		posA.z = (putaBound - 20 - currentRadius -1);
	}
	if(posA.z -currentRadius <= (-barrelsBound + 20 )){
		posA.z = -barrelsBound + 20 + currentRadius + 1;
	}
	nodeA->setPosition(posA);
}
void BasicTutorial_00::resolveCollision(
    SceneNode *nodeA, SceneNode *nodeB,
    float rA, float rB, float wA, float wB)
	//what is wA and wB?
{
    Vector3 posA = nodeA->getPosition();
    Vector3 posB = nodeB->getPosition();
    int R = rA + rB;
    ///////////////////////
    // add your own stuff
    ///////////////////////
	R*=R;
	int x = abs(posA.x - posB.x), z = abs(posA.z - posB.z);
	int distanceSquared = (x*x) + (z*z);
	if(R > distanceSquared){
		Vector3 n = posA-posB;
		n.normalise();
		nodeB->translate(-n);

	}

}

void BasicTutorial_00::resolveCollisionLargeSphere()
{
    float smallR = 15; // small sphere radius

    float largeR = 1.0/0.15*smallR; // large sphere radius
	for(int i =0; i<mNumSpheres; i++){
		resolveCollision(mLargeSphereSceneNode, mSphereSceneNode[i],
						largeR, smallR, 10.0f, 10.0f);
		resolveBoundaryCollision(mLargeSphereSceneNode);
		resolveBoundaryCollision(mSphereSceneNode[i]);
	}
}

// perform collision handling for all pairs
void BasicTutorial_00::resolveCollisionSmallSpheres()
{
	//std::cout<<"or maybe for the small spheres only?"<<std::endl;
    float ri = 15; // sphere radius
    float rj = 15; // sphere radius
	for(int i =0; i<mNumSpheres; i++){
		for(int j =i+1; j<mNumSpheres; j++){
			resolveCollision(mSphereSceneNode[i], mSphereSceneNode[j],
							ri, rj, 10.0f, 10.0f);
			resolveBoundaryCollision(mSphereSceneNode[j]);
		}
		resolveBoundaryCollision(mSphereSceneNode[i]);
	}
}
//how do we resolve collisions efficiently?
void BasicTutorial_00::resolveCollision()
{
	//std::cout<<"calling the main resolveCollision function"<<std::endl;
    int num = 10;
    for (int i = 0; i < num;++i) {
        resolveCollisionSmallSpheres();
        resolveCollisionLargeSphere();
    }
	//std::cout<<"returning from the main resolveCollision function"<<std::endl;
}

// reset positions of all small spheres
void BasicTutorial_00::reset()
{
	int x, z;
    for (int i = 0; i < mNumSpheres; ++i ) {
        ///////////////////////
        // add your own stuff
        ///////////////////////
		//do we just need to reset the position of each sphere?
		SceneNode* sNode = mSphereSceneNode[i];
		//Entity* ent = mEntity[i];

		x = rand()%barrelsBound-100;
		z =rand()%barrelsBound-100;
		
		if(x%3==0){x = -x;}
		if(z%5==0){z = -z;}
		sNode->setPosition(x, 0, z);
    }
	resolveCollision();
}

// create all spheres
// "Examples/red"
// "Examples/green"
// "Examples/blue":
// "Examples/yellow"
//create and place the spheres in the scene
void BasicTutorial_00::createSpace(int startingIndex)
{
    String name_en;
    String name_sn;
	
	int index = 1;
	int  boxedAreaDimensions = 400;
	double x, z;
   
    for (int i = startingIndex; i < mNumSpheres; ++i ) {
	
			index = i;
			genNameUsingIndex("SphereEnt", index, name_en);
		genNameUsingIndex("SphereSceneNode", index, name_sn);
		mSphereEntity[index] = mSceneMgr
			->createEntity( name_en, "sphere.mesh" );
		mSphereSceneNode[index] = mSceneMgr
			->getRootSceneNode()->createChildSceneNode(name_sn);
			 ///////////////////////
			// add your own stuff
			///////////////////////

		//radomly set the colors of the spheres
		switch(rand()%3) {
		case 0:
			mSphereEntity[index]->setMaterialName("Examples/red");
			break;
		case 1:
			mSphereEntity[index]->setMaterialName("Examples/green");
			break;
		case 2:
			mSphereEntity[index]->setMaterialName("Examples/blue");
			break;
		case 3:
			mSphereEntity[index]->setMaterialName("Examples/yellow");
		}
		//setting the position to the bounded area height and width
		x = rand()%barrelsBound-100;
		z = rand()%barrelsBound-100;
		if(i%2==0){x=-x;}
		if(i%3==0){z=-z;}
		mSphereSceneNode[index]->setPosition(x, 0, z);
		
		//scale the small spheres
		mSphereSceneNode[index]->scale(0.15, 0.15, 0.15);
		mSphereSceneNode[index]->attachObject(mSphereEntity[index]);
		std::cout<<"set sphere at "<<x<<" 0 "<<z<<std::endl;
    }
	resolveCollision();

}

void BasicTutorial_00::createScene_00(void) 
{
	mSceneMgr = mSceneMgrArr[0];
	//mSceneMgr->setAmbientLight( ColourValue( 0.25, 0.25, 0.25 ) ); 

	mSceneMgr->setAmbientLight( ColourValue( 0.5, 0.5, 0.5 ) ); 
	//mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );  
	mSceneMgr->setShadowTechnique(
		SHADOWTYPE_STENCIL_ADDITIVE); 

	Light *light;
	light = mSceneMgr->createLight("Light1"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(150, 250, 100)); 
	light->setDiffuseColour(0.3, 0.3, 0.3);		
	light->setSpecularColour(0.5, 0.5, 0.5);	

	light = mSceneMgr->createLight("Light2"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(-150, 300, 250)); 
	light->setDiffuseColour(0.25, 0.25, 0.25);		
	light->setSpecularColour(0.35, 0.35, 0.35);	

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

	Scene_00CreateBarrels();
	
	mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode()
		->attachObject(ent); 

    ent = mSceneMgr->createEntity(
		"Background", "ground"); 
	ent->setCastShadows(true);
	SceneNode* mSceneNode = mSceneMgr->getRootSceneNode()
		->createChildSceneNode("backgroundSN");
	mSceneNode->attachObject(ent);
	mSceneNode->rotate(Vector3(1,0,0), Degree(90), Ogre::Node::TS_LOCAL);
	mSceneNode->translate(Vector3(0,0,-750));
	ent->setMaterialName("Examples/Rockwall");
	
	

    Radian angle(3.141952654/2.0);
	//creating the large sphere
	mLargeSphereEntity = mSceneMgr->createEntity("LargeSphereEnt", "sphere.mesh");
	mLargeSphereEntity->setMaterialName("Examples/yellow");
	mLargeSphereEntity->setCastShadows(true);
	mLargeSphereSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("LargeSphereSN");
	mLargeSphereSceneNode->attachObject(mLargeSphereEntity);
	
	createSpace(0);

    ///////////////////////
        // add your own stuff
        ///////////////////////
    
    resolveCollision();
}
//place 20 barrles per side, depending on i size
//distance between all barrels should be about 65 units
void BasicTutorial_00::Scene_00CreateBarrels(){
	int numBarrels = 80;
	int separation = 60;
	String entName, snName;
	int x= -barrelsBound, z =-barrelsBound; //positions of our barrels
	for(int i =0; i<numBarrels; mSceneNodeIndex++, i++){
		int index = i+mSceneNodeIndex;

		genNameUsingIndex("barrelEnt", i, entName);
		genNameUsingIndex("barrelSn", i, snName);

		Entity* mEntityTmp = mSceneMgr->createEntity(entName, "Barrel.mesh");
		SceneNode* mSceneNodeTmp = mSceneMgr->getRootSceneNode()->createChildSceneNode(snName);
		
		//topmost barrels
		if(i>=0 && i<20){
			x+=separation;
		}
		//rightmost barrels
		if(i>=20 && i<40){
			z+=separation;
		}
		//bottom barrels
		if(i>=40 && i<60){
			x-=separation;
		}
		//leftmost barrels
		if(i>=60){
			z-=separation;
		}
		mSceneNodeTmp->setPosition(x, 0, z);
		mSceneNodeTmp->scale(10,10,10);

		mSceneNodeTmp->attachObject(mEntityTmp);	
		mSceneNode[index] = mSceneNodeTmp;
		mEntity[index] = mEntityTmp;
		
	}
}
void BasicTutorial_00::handleSphereDifference(bool increasing){
	std::cout<<"we need to go from "<<prevNumSpheres<<" to "<<mNumSpheres<<std::endl;
	if(increasing){
		for(int i=prevNumSpheres-1; i<mNumSpheres; i++){
			
			mSphereSceneNode[i]->setVisible(true);
	
		}
	}
	else{
		for(int i = prevNumSpheres-1; i> mNumSpheres; i--){

			mSphereSceneNode[i]->setVisible(false);
			
		}
	}

}
void BasicTutorial_00::createScene_01(void) 
{

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
            ->setPosition(Vector3(-77.89, 169.11, 1996.70));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.05, -0.25, -0.97));
    }

    if (arg.key == OIS::KC_3 ) {

		 mCameraMan->getCamera()
            ->setPosition(Vector3(0.0, 1608.68, 0.0));

		mCameraMan->getCamera()->lookAt(0.0, 0.0, -0.01);

    }
	if(arg.key == OIS::KC_2){
		mCameraMan->getCamera()
			->setPosition(Vector3(-1000, 500, 10));
		mCameraMan->getCamera()->lookAt(0.0, 0.0, -0.01);
	}


    if (arg.key == OIS::KC_3 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(19.94,	822.63,	30.79));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.00,	-0.99,	-0.11));
        //19.94	822.63	30.79
        //0.00	-0.99	-0.11
    }

    ///////////////////////
    // add your own stuff
    ///////////////////////
	//check whether the key bindings are accurate to the demo


	if(arg.key == OIS::KC_U){
		isMovingUp = true;
	}
	if(arg.key == OIS::KC_J){
		isMovingDown = true;
	}
	if(arg.key == OIS::KC_H){
		isMovingLeft = true;
	}
	if(arg.key == OIS::KC_K){
		isMovingRight = true;
	}
	
	prevNumSpheres = mNumSpheres;
	if(arg.key == OIS::KC_7){
		mNumSpheres = 100;
		std::cout<<"changed the sphereNum to "<<mNumSpheres<<std::endl;
	
	}
	if(arg.key == OIS::KC_8){
		mNumSpheres = 200;
		std::cout<<"changed the sphereNum to "<<mNumSpheres<<std::endl;
	}
	if(arg.key == OIS::KC_9){
		mNumSpheres = 300;
		std::cout<<"changed the sphereNum to "<<mNumSpheres<<std::endl;
	}
	if(arg.key == OIS::KC_0){
		mNumSpheres = 500;
		std::cout<<"changed the sphereNum to "<<mNumSpheres<<std::endl;
	}
	if(prevNumSpheres != mNumSpheres){
		bool increasing = (prevNumSpheres>mNumSpheres)?true:false;
		std::cout<<"need to change the amount of balls"<<std::endl;
		handleSphereDifference(increasing);
	}
	if(arg.key == OIS::KC_B){
		reset();
	}

	//mLargeSphereSceneNode->setPosition(mLargeSpherePos);
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
    
	if(isMovingUp){isMovingUp = false;}
	if(isMovingDown){isMovingDown = false;}
	if(isMovingRight){isMovingRight= false;}
	if(isMovingLeft){isMovingLeft = false;}
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    BaseApplication::keyReleased(arg);

    return flg;
}

bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
    //
    Vector3 mdir;
    if (mMoveDirection & mMoveDirection_UP ) {
        mdir += Vector3(0.0, 0.0, -1.0);
    }

    ///////////////////////
    // add your own stuff
    ///////////////////////
	//setting the position based on the directions in which we're moving
	int move = 5;
	Vector3 tmp = mLargeSphereSceneNode->getPosition();
	if(isMovingUp){tmp.z+=move;}
	if(isMovingDown){tmp.z-=move;}
	if(isMovingRight){tmp.x+=move;}
	if(isMovingLeft){tmp.x-=move;}
	mLargeSphereSceneNode->setPosition(tmp);
	resolveCollision();
    //
    return flg;
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
