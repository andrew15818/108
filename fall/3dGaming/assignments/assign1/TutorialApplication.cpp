////////////////////////////////////////
//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
// Date: 2019/09/20
////////////////////////////////////////
// Student Name: Andres Ponce
// Student ID: 0616110
// Student Email: andreseeponce@gmail.com
//
////////////////////////////////////////
// You can delete or add some functions to do the assignment.
////////////////////////////////////////

#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace Ogre;

const float PI = 3.141592654;

BasicTutorial_00::BasicTutorial_00(void) {
	inMotion = false; /*The two penguins are not in motion when we begin*/ 
}

void BasicTutorial_00::chooseSceneManager()
{
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_GENERIC, "primary");
	mSceneMgrArr[1] = mRoot
		->createSceneManager(ST_GENERIC, "secondary");
    //
    // add your own stuff
    //

}

void BasicTutorial_00::createCamera_00(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(120,300,600));
	mCamera->lookAt(Ogre::Vector3(0,0,0.001));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createCamera_01(void)
{
	// add your own stuff
	mSceneMgr2 = mSceneMgrArr[1];
	mCamera2 = mCameraArr[1] = mSceneMgr2->createCamera("SecondaryCam");
	mCamera2->setPosition(Ogre::Vector3(0,350,0.001));
	mCamera2->lookAt(0,0,0);
	mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera2);
}

void BasicTutorial_00::createViewport_00(void)
{
	Viewport *vp =mWindow->addViewport(mCamera,0); //It's working now :D
	//std::cout<<"THE FIRST VIEWPORT HAS ZORDER: "<<vp->getZOrder()<<std::endl;											 //just had to delete and reinstall
	vp->setBackgroundColour(ColourValue(0,0,1));
	mViewportArr[0] = vp;
	
}

void BasicTutorial_00::createViewport_01(void)
{
    // add your own stuff
	Viewport *vp2 = mWindow->addViewport(mCamera2,1,0,0,.25,.25);
	std::cout<<"PROCESSING ANOTHER VIEWOPRT "<<vp2->getZOrder()<<std::endl;
	vp2->setBackgroundColour(ColourValue(0,0,1));
	vp2->setOverlaysEnabled(false);
	mViewportArr[1] = vp2;
}
/*!
	For this function, we create the first and most populated scene. We first
	create the scene nodes, which will include the lights, penguins, and the ground
	plane.

	Next, we create the plane object, which is done through a plane object.

	We then create the three entities present in the scene: the two penguins and the 
	ground. We attach them to their respective scene nodes and translate/scale them 
	accordingly. We then attach the entities to the previously created sceneNodes.

	Finally, we create and set the array of entities that surround the alrgest penguin
	and the line of objects in front of the two penguins. We do this with two loops:
	one for the circular set of cubes and one for the horizontal line. We set their 
	heights accordingly.

	We also edit the diffuse and specular attributes of both lights so that they give the 
	scene a green/white contrast. The light coming in from the right side (viewed from the initial
	frame) shines green and the other one is set to white. This gives the scene a mix of the two.
*/
void BasicTutorial_00::createScene_00(void) 
{
	/*Creating the scene, lights, and shadows*/
	mSceneMgr = mSceneMgrArr[0];
	mSceneMgr->setAmbientLight(ColourValue(0,1,0));//ambient light
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);//shadows
    // add your own stuff

	
	/*=====Creating the actual objects of the scene: SceneNodes=====*/
    SceneNode *pNode1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("Penguin1"); //Create a new Scene Node, nod to pingu
	SceneNode *pNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("Penguin2"); //second penguin scene node
	SceneNode *fNode  = mSceneMgr->getRootSceneNode()->createChildSceneNode("ground");
	SceneNode *lnode1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("light");
	SceneNode *lnode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("light2");
	
	//creating the plane object and making mesh from the plane object
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"ground",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500,1500,
		20,20,
		true,
		1,
		5,5,
		Vector3::UNIT_Z
	);
	
	//creating the entities
	Entity *pengu1 = mSceneMgr->createEntity("Pingu","penguin.mesh"); //first penguin
	Entity *pengu2 = mSceneMgr->createEntity("Pingu2","penguin.mesh");//second penguin
	Entity *floor = mSceneMgr->createEntity("floor","ground");//ground
	
	//enabling shadows
	pengu1->setCastShadows(true);
	pengu2->setCastShadows(true);
	
	/*======Lights =====*/	
	//first light
	
	Light *light1=mSceneMgr->createLight("Light1");
	light1->setType(Light::LT_POINT);
	light1->setPosition(Vector3(150,250,100));
	light1->setDiffuseColour(ColourValue(0, .1,0));
	light1->setSpecularColour(ColourValue(0, .1,0 ));
	
	//second light
	Light *light2=mSceneMgr->createLight("Light2");
	light2->setType(Light::LT_POINT);
	light2->setPosition(Vector3(-150,300,250));
	light2->setDiffuseColour(ColourValue(1,1,1));
	light2->setSpecularColour(ColourValue(1,1,1));
	
	/*=====attaching the objects to their respective sceneNodes=====*/
	pNode1->attachObject(pengu1);
	pNode2->attachObject(pengu2);
	fNode->attachObject(floor);
	lnode1->attachObject(light1);
	lnode2->attachObject(light2);
	
	/*===== scaling and translating the penguins respectively, pengu2 facing pengu1 =====*/
	pNode1->scale(Vector3(2,3,2));
	pNode1->translate(Vector3(0,50,0));
	pNode2->translate(Vector3(0,20,100));
	pNode2->rotate(Quaternion(0,0,180));
	
	//  Going to create the circles around the penguin and the row
	int numCubes = 72, circle_radius=100, L = 255;
	double h, fx, x1, z1, unitF, cubeSize;
	for(int i =0; i<numCubes;i++){
		/*Creating the object and placing it in the scene*/
		String name;
		genNameUsingIndex("c", i, name);
		Entity *ent = mSceneMgr->createEntity(name, "cube.mesh");
		ent->setMaterialName("Examples/SphereMappedRustySteel");
		ent->setCastShadows(true);
		AxisAlignedBox bb = ent->getBoundingBox();
		cubeSize = bb.getMaximum().x - bb.getMinimum().x;
		SceneNode *snode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		
		/*Setting things like the position and height of the object*/
		 fx = i/(double)(numCubes-1);
		 h = (1+sin(fx*PI*4))*50;
		 //circle_radius = 100;
		  x1= circle_radius*cos(fx*PI*2);
		  z1 = circle_radius*sin(fx*PI*2);
		  unitF = 1.0/cubeSize/numCubes*L*0.8;
		  snode->scale(unitF, h/cubeSize, unitF);
		  snode->setPosition(x1, 50, z1);
		  snode->attachObject(ent);
	}
	// going to model the row of objects
	for(int i=0; i<numCubes;i++){
		//first setting up the object again
		String name;
		
		genNameUsingIndex("row", i, name);
		//std::cout<<"Here's the value of the stringo: "<<name<<std::endl;
		Entity *ent2 = mSceneMgr->createEntity(name, "cube.mesh");
		ent2->setMaterialName("Examples/Chrome");
		ent2->setCastShadows(true);
		SceneNode *snode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		
		//height and position calculations
		fx = 2*i/(double)(numCubes-1);	
		x1 = fx*L - L/2.0;				//x value for every object
		h = (1+cos(fx*PI*2.0))*20;		//height
		Real unitF = 1.0/cubeSize/numCubes*L*0.8;
		z1 = 20;// x asis value
		
		//scaling and attaching the object
		/*The row is not in a straight line, still need to figure out x position well*/
		snode2->scale(unitF, h/cubeSize, unitF);
		snode2->setPosition(x1, 20, 200);
		snode2->attachObject(ent2);	
	}
}
/*!
	For the next scene in the assignment, we create a cube and a plane, and we 
	place the camera directly above them. This is a simpler scene, where we only have 
	a cube, a plane, and a light source. The light source is located so that it shines 
	on the cube from the back.

	We create the plane and set it at the back of the scene, and place the cube on top of it.
	We scale the cube a little bit and move it away from the center a little bit.
*/
void BasicTutorial_00::createScene_01(void) 
{
    // add your own stuff	
	//setting up the basic lighting for the scene
	mSceneMgr2 = mSceneMgrArr[1];
	mSceneMgr2->setAmbientLight(ColourValue(0,0,1)); //ambient light
	mSceneMgr2->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);//shadows
	
	/*===== SceneNode objects  =====*/
	SceneNode *fnode = mSceneMgr2->getRootSceneNode()->createChildSceneNode("PlaneNode");//Not so sure bout this one 
	SceneNode *lnode = mSceneMgr2->getRootSceneNode()->createChildSceneNode("SecondLight");
	SceneNode *cnode = mSceneMgr2->getRootSceneNode()->createChildSceneNode("SecondCube");
	Entity    *floor2 = mSceneMgr->createEntity("SecondFloor","ground");//ground
	
	/*=====Creating a plane=====*/

	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"Plane1",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1,1,
		1,1,
		true,
		1,
		5,5,
		Vector3::UNIT_Z
	);	
	floor2->setMaterialName("Examples/Rockwall");

	/*===== Creating the light =====*/
	
	Light *light = mSceneMgr2->createLight("SmallVPLight");
	light->setType(Light::LT_POINT);
	light->setPosition(Vector3(100,150,250));
	light->setDiffuseColour(0.0,1.0,1.0);
	light->setSpecularColour(0.0,1.0,1.0);
	//maybe try to fix the scaling issues
	/*===== Creating a Cube =====*/
	//The material doesn't look uniform in the texture, so I'm not sure it's correct
	Entity *ent = mSceneMgr->createEntity("cube", "cube.mesh");
	ent->setMaterialName("Examples/Green");
	ent->setCastShadows(true);
	cnode->setPosition(100,0,0);
	cnode->scale(Vector3(0.5,2.0,0.5));
	cnode->rotate(Ogre::Vector3(0.0,0.0,.02), Ogre::Radian(1.0f));
	
	
	/*===== Attaching all the objects to the SceneManager=====*/
	//lnode->attachObject(light);
	cnode->attachObject(ent);
	fnode->attachObject(floor2);
}
/*!
	The viewports specify how the scene will look at the screen. We assign a camera to each 
	one when created, set their ambient color, etc... 
	
	We also specify which viewport is to be on the top and which one is to be beneath by specifying
	its ZOrder. With a ZOrder of 0 we have the main viewport which (initially) contains the two penguins
	on the plane, which means it will cover the entire screen and be beneath any other viewports.

	Next, the second viewport which we use for the simpler scene will remain on top of the first
	one. However, this order can then be switched around. 
*/
void BasicTutorial_00::createViewports(void)
{
    //Do not modify
	createViewport_00();
	createViewport_01();
}

void BasicTutorial_00::createCamera(void) {
    //Do not modify
	createCamera_00();
	createCamera_01();
	mCameraMan = mCameraManArr[0];
	//mCameraMan = mCameraManArr[1];
}

void BasicTutorial_00::createScene( void ) {
    //Do not modify
	createScene_00();
	createScene_01();
	//mSceneMgr = mSceneMgrArr[0]; // active SceneManager
	mSceneMgr = mSceneMgrArr[1]; // active SceneManager
    //
    mCamera = mCameraArr[0];
    //mCamera = mCameraArr[1];
}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
//
// To find out the answer:
// Go to see the definition of KeyEvent
//
/*!
We take a look at what key is pressed, and we can update
the viewport or the cameras.
When the user presses a number 1-5, we switch the camera
to different coordinates.

When the user presses 'n', we switch the zOrder
of the two viewports.

When the user presses 'm', we also swap the viewports, but
set them to different coordinates than with 'n'.

*/
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
            ->setPosition(Vector3(98.14,	450.69,	964.20));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.01,	-0.30,	-0.95));

        //98.14	450.69	964.20
        //-0.01	-0.30	-0.95
    }

    if (arg.key == OIS::KC_2 ) {
        // add your own stuff
		mCameraMan->getCamera()
			->setPosition(-1463.00, 606.45, -513.24);
		mCameraMan->getCamera()
			->setDirection(0.88, -0.47, .10);
        //-1463.00	606.45	-513.24
        //0.88	-0.47	0.10
    }

    if (arg.key == OIS::KC_3 ) {
        // add your own stuff
		mCameraMan->getCamera()
			->setPosition(-1356.16, 634.32, -964.51);
		mCameraMan->getCamera()
			->setDirection(0.71, -0.44, 0.55);
		//-1356.16	634.32	-964.51
        //0.71	-0.44	0.55
    }

    if (arg.key == OIS::KC_4 ) {
         // add your own stuff
		mCameraMan->getCamera()
			->setPosition(40.39, 155.23, 251.20);
		mCameraMan->getCamera()
			->setDirection(-0.02, -0.41, -0.91);
        //40.39	155.23	251.20
        //-0.02	-0.41	-0.91
    }

    if (arg.key == OIS::KC_5 ) {
        // add your own stuff
		mCameraMan->getCamera()
			->setPosition(19.94, 822.63, 30.79);
		mCameraMan->getCamera()
			->setDirection(0.00, -0.99, -0.11);
        //19.94	822.63	30.79
        //0.00	-0.99	-0.11
    }
	/*!
		Here, we swap two of the viewports that we created previously. When we do so,
		we first create two new ones and then change the aspect ratio and the top,
		left, height and width values.
	*/
    if (arg.key == OIS::KC_M ) { 
		/*Create two new viewports with different dimensions, and just swap the 
		ones we already created to the large or small spot, repsectively*/
	   Camera *c_ptr = mCameraArr[0];
	   Camera *c2_ptr = mCameraArr[1];

		mWindow->removeViewport(mViewportArr[0]->getZOrder()); 
		mWindow->removeViewport(mViewportArr[1]->getZOrder());

		//Ogre::Viewport* vp2 = mWindow->addViewport(c2_ptr, 1);
		
		//The two new viewports
		Ogre::Viewport* vp = mWindow->addViewport(
        c_ptr,
        1,
        0.0,
        0.0,
        0.45,
        0.3
        );

		Ogre::Viewport* vp2 = mWindow->addViewport(
		c2_ptr,
		0,
		0.0,
		0.0,
		1.0,
		1.0
		);

	vp->setBackgroundColour(Ogre::ColourValue(0,0.5,0.0));
	//vp->setOverlaysEnabled(false);
	c_ptr->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	c2_ptr->setAspectRatio(
		Ogre::Real(vp->getActualWidth())/ Ogre::Real(vp->getActualHeight()));
	vp2->setOverlaysEnabled(false);

	 mViewportArr[0] = vp;// make sure to save the new pointer
	 mViewportArr[1] = vp2; 

	}

    if (arg.key == OIS::KC_N ) {
		/*Let's maybe try the same strategy that worked on the previous entry? */
        // add your own stuff
		Camera* c_ptr = mCameraArr[0];
		Camera* c2_ptr = mCameraArr[1];

		mWindow->removeViewport(mViewportArr[0]->getZOrder());
		mWindow->removeViewport(mViewportArr[1]->getZOrder());

		Ogre::Viewport* vp = mWindow->addViewport(
		c_ptr,
		0,
		0.0,
		0.0,
		1.0,
		1.0
		);
		Ogre::Viewport* vp2 = mWindow->addViewport(
		c2_ptr,
		1,
		0.55,
		0.3,
		1.0,
		0.45
		);
		vp->setBackgroundColour(ColourValue(1,0,0));
		vp2->setOverlaysEnabled(false);
		c_ptr->setAspectRatio(
			(Ogre::Real(vp->getActualWidth())/ Ogre::Real(vp->getActualHeight())));
		c2_ptr->setAspectRatio(
			(Ogre::Real(vp2->getActualWidth())/ Ogre::Real(vp2->getActualHeight())));
		mViewportArr[0] = vp;
		mViewportArr[1] = vp2;

    }

	if(arg.key == OIS::KC_P){
	
		inMotion = !inMotion; //the ->isKeyDown() meth. requires the key to be pressed continually, this will just act as a trigger
		acceleration = 1.2; //mess around with the acceleration
		angle = 0;
		Ogre::Vector3 pengu1 = mSceneMgrArr[0]->getSceneNode("Penguin2")->getPosition(); //big penguin
		Ogre::Vector3 pengu2 = mSceneMgrArr[0]->getSceneNode("Penguin1")->getPosition();
		radius = pengu1.distance(pengu2);
		//angle = 45.0; //check to see if this is correct
		
	}

    // Do not delete this line
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

bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
	mKeyboard->capture();
	mMouse->capture();
    //
    // add your own stuff
    //
	//If we're supposed to be moving, after key P has been pressed
	if(!inMotion){
		acceleration =0;
		speed=0;
		angle=0;
	}
	if(/*mKeyboard->isKeyDown(OIS::KC_P)*/ inMotion){
		std::cout<<"were supposed to be moving "<<std::endl;
		

		//Will this make the two penguins look at each other? 
		//We need to make it so that the sceneNodes get found regardless of viewport order ///////7
		Ogre::SceneNode *pNode1 = mSceneMgrArr[0]->getSceneNode("Penguin1"); //the scene nodes that contain the two penguins
		Ogre::SceneNode *pNode2 = mSceneMgrArr[0]->getSceneNode("Penguin2");
		
		//std::cout<<pNode1->getName()<<std::endl;
		//std::cout<<pNode2->getName()<<std::endl;
		Ogre::Vector3  pVec1 = pNode1->getPosition();
		Ogre::Vector3  pVec2 = pNode2->getPosition();

		speed +=(evt.timeSinceLastFrame*acceleration);
		angle +=(speed*evt.timeSinceLastFrame);
		if(angle> 6.28){
			angle =0;
			speed = -speed;
		}
		//std::cout<<"The speed and angle should be: "<<speed<<" "<<angle<<std::endl;
	

		//std::cout<<"This is the distance between two pengus :"<<radius<<std::endl;

		/*The two penguins just rotate around their own axes too? I think it's a small mistake :'(*/	
		pVec2.x = radius*cos(angle);
		pVec2.z = radius*sin(angle);
	
		std::cout<<"pengu2's position: "<<pVec2.x<<" "<<pVec2.y<<" "<<pVec2.z<<std::endl;
	
		pNode2->lookAt(pVec1, Ogre::Node::TransformSpace::TS_WORLD);
		pNode1->lookAt(-pVec2, Ogre::Node::TransformSpace::TS_WORLD);
		pNode2->setPosition(pVec2);
		
	}
	
	return flg;
}
int main(int argc, char *argv[]) {
	std::cout<<"Hola"<<std::endl;
	BasicTutorial_00 app;
	app.go();  
	return 0;
}

////////////////////////////////////////
// DO NOT DELETE THIS LINE: 2018/09/20. 3D Game Programming
////////////////////////////////////////