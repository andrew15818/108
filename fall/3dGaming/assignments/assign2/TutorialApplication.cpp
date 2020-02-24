////////////////////////////////////////
//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
// Date: 2019/09/20
////////////////////////////////////////
// Student Name:Andres Ponce
// Student ID: 0616110
// Student Email: andreseeponce@gmail.com
//
////////////////////////////////////////
// You can delete or add some functions to do the assignment.
////////////////////////////////////////

#include "TutorialApplication.h"
#include "BasicTools.h"
//#include "selection_rectangle.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace Ogre;

const float PI = 3.141592654;

BasicTutorial_00::BasicTutorial_00(void) {
	lightSpeed = 0;
	lightAngle = 0;
	numRobots = 30;
	isParticleSystemActive = false;
	for(int i=0; i<60; i++){
		isRobotMoving[i] = false;
	}
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
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createCamera_01(void)
{
	// add your own stuff
	//Ogre::Camera* mCamera2;
	mSceneMgr = mSceneMgrArr[0];
	mCamera2 = mCameraArr[1] = mSceneMgr->createCamera("SecondCam");
	mCamera2->setPosition(Ogre::Vector3(0,1400,1));
	mCamera2->lookAt(Ogre::Vector3(0,0,0));

	mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera2);
}
/*! To create a special aspect ratio, we first position the 
viewport wherever we want it, and then we change the aspect ratio
of the camera, to the desired specifications, and then we 
set the background color to yellow.*/
void BasicTutorial_00::createViewport_00(void)
{
	Viewport* vp = mWindow->addViewport(mCamera, 0);
	vp->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.0f));
	//vp->setDimensions(1,0, 0.25, 0.25);
	mViewportArr[0] = vp;
}

void BasicTutorial_00::createViewport_01(void)
{
    // add your own stuff
	Viewport* vp2 = mWindow->addViewport(mCamera2,1, 0, 0, 0.25, 0.25);
	vp2->setBackgroundColour(ColourValue(255, 255, 0));
	vp2->setOverlaysEnabled(false);
	vp2->setSkiesEnabled(false);
	mCamera2->setAspectRatio(4* vp2->getWidth()/vp2->getHeight());
	mViewportArr[1] = vp2;
}
/*!
Here, we delegate the responsibility of creating all the objects to their own
separate functions. We create the light entity in this function.
*/
void BasicTutorial_00::createScene_00(void) 
{
	PlaneBoundedVolumeList volList;
	mVolQuery = mSceneMgr->createPlaneBoundedVolumeQuery(volList);
	
	mSceneMgr = mSceneMgrArr[0];
	mSceneMgr->setAmbientLight(ColourValue(1.0,1.0,1.0));
	//setting fog and shadows
    mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	
	//creating the elements in the scene
	sc0_createFog();
	sc0_createPlane();
	sc0_createRobots(0,200);
	sc0_createRobots(30,300);
	sc0_createSphere();
	
	//sceneNode declartions
	SceneNode *fNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("groundNode");

	//entity declarations
	Entity* gEnt = mSceneMgr->createEntity("groundEntity", "ground");
	gEnt->setQueryFlags(0);
	//attaching entities
	fNode->attachObject(gEnt);

	gEnt->setCastShadows(false);
	gEnt->setMaterialName("Examples/Rockwall");

	//selection rectangle used for volume selection later on
	mSelectionRect = new SelectionRectangle("selectionRect");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(mSelectionRect);
	mSelectionRect->setLightMask(0);
	mSelectionRect->setCastShadows(false);
	
	// need to create the lights
	Light* light = mSceneMgr->createLight("rotatingLight");
	light->setType(Light::LT_POINT);
	light->setPosition(Vector3(0, 300, 0));
	light->setDiffuseColour(1.0,1.0,1.0);
	light->setSpecularColour(1.0, 1.0, 1.0);

	/*mSceneMgr->getRootSceneNode()
		->createChildSceneNode()
		->attachObject(ground);
		*/
    
    Radian angle(3.141952654/2.0);

    Vector3 axis(1.0, 0.0, 0.0);
    mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(
            Vector3(0.0, 0.0, -750.0),
            Quaternion( angle, axis))
		->attachObject(light);
    
}
/*! Simply create the plane with the same dimensions that we had
it before.*/
void BasicTutorial_00::sc0_createPlane(){
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
			"ground",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			plane,
			1500, 1500,
			20,20,
			true,
			1,
			5,5,
			Vector3::UNIT_Z
		);
}
/*!
	Create fog effects that set after
	a certain distance.
*/
void BasicTutorial_00::sc0_createFog(){
	mSceneMgr = mSceneMgrArr[0];
	ColourValue fade(0.9, 0.9, 0.9);
	mWindow->getViewport(0)->setBackgroundColour(fade);
	mSceneMgr->setFog(Ogre::FOG_LINEAR, fade, 0, 1400, 1600);
}
/*!We create a sphere and place it in the center of the map.
The sphere should not be selectable, the robots will need to move around 
it in order to  get around it.*/
void BasicTutorial_00::sc0_createSphere(){
	mSceneMgr = mSceneMgrArr[0];
	Entity* sphereEnt = mSceneMgr->createEntity("centerSphere", "sphere.mesh");
	sphereEnt->setQueryFlags(0);
	SceneNode* sphereNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	sphereNode->setPosition(Vector3(0,0,0));
	sphereNode->setScale(0.7, 0.7, 0.7);
	sphereNode->showBoundingBox(false);
	sphereEnt->setCastShadows(true);
	sphereEnt->setMaterialName("Examples/SphereMappedRustySteel");

	sphereNode->attachObject(sphereEnt);
}
/*! When we create the robots, we set their position using the
formulas for circular rotation from the previous assignment, then
we create the particles that go on them. We also set their idle 
animations.*/
void BasicTutorial_00::sc0_createRobots(int startingIndex, double radius){
	String sname,ename;
	String sname2, ename2;
	double angle = 30.0, fx, h;
	int  circleRadius = 300;

	for(int i=0, animationIndex =0; i<30; i++, startingIndex++){
		//getting required names and scene/entity objects
		genNameUsingIndex(std::to_string((long double)startingIndex)+"s", i, sname);
		genNameUsingIndex(std::to_string((long double)startingIndex)+"e", i, ename);
		
		
		SceneNode*rNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		Entity* rEnt = mSceneMgr->createEntity(ename, "Robot.mesh");
		rEnt->setCastShadows(true);
	
		//rEnt->setQueryFlags(QMASK);
		rNode->showBoundingBox(false); //does this need to be true or false?

		//calculating the robot's position
		double x1, z1;
		fx = i/(double)(numRobots-1);
		h = (1+sin(fx*PI*4));
		x1 = radius*cos(fx*PI*2);
		z1 = radius*sin(fx*PI*2);
		if(i==1){
			rNode->scale(2,2,2);
		}
		rNode->setPosition(x1, 0,z1);
		rNode->attachObject(rEnt);
		
		//setting the animation state
		mAnimationState[startingIndex] = rEnt->getAnimationState("Idle");
		mAnimationState[startingIndex]->setLoop(true);
		mAnimationState[startingIndex]->setEnabled(true);
		mSceneNodeArr[startingIndex]=rNode;
		mEntityArr[startingIndex]=rEnt;
		
		//attaching the particle system to each robot Node
		String psName, peName;
		genNameUsingIndex(std::to_string((long double)startingIndex)+"pNode", i, psName);
		genNameUsingIndex(std::to_string((long double)startingIndex)+"pEnt", i, peName);
		
		ParticleSystem* rParticle = mSceneMgr->createParticleSystem(peName, "Examples/Smoke");
		SceneNode* rParticleNode = mSceneNodeArr[startingIndex]->createChildSceneNode(psName);
		rParticleNode->attachObject(rParticle);
		mParticleArr[startingIndex] = rParticle;
	}
}
void BasicTutorial_00::createScene_01(void) 
{
    // add your own stuff
}

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
        //-1463.00	606.45	-513.24
        //0.88	-0.47	0.10
    }

    if (arg.key == OIS::KC_3 ) {
        // add your own stuff
        //-1356.16	634.32	-964.51
        //0.71	-0.44	0.55
    }

    if (arg.key == OIS::KC_4 ) {
         // add your own stuff
        //40.39	155.23	251.20
        //-0.02	-0.41	-0.91
    }

    if (arg.key == OIS::KC_5 ) {
        // add your own stuff
        //19.94	822.63	30.79
        //0.00	-0.99	-0.11
    }

    if (arg.key == OIS::KC_M ) {
		toggleParticleEffects();
    }

    if (arg.key == OIS::KC_N ) {
        // add your own stuff
    }

    // Do not delete this line
    BaseApplication::keyPressed(arg);

    return flg;
}
/*! Once the 'M' key is pressed, we just loop 
through all the objects and switch their animations
off with the setEmitting() method.*/
void BasicTutorial_00::toggleParticleEffects()
{
	for(int i =0; i<60; i++){
		bool pState = !mParticleArr[i]->getEmitting();
		mParticleArr[i]->setEmitting(pState); 
	}
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
//how do we get the light to move around the scene correctly? :(
/*!
	We have to create and update the position of the lights every frame.
	There are still some problems with the position of the light source.
	The light calculations are still wrong, but it moves in somewhat of 
	a circle, although only around a different axis. 

	Then we call the function to handle the operation on the robots.
*/
bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
    //
    // add your own stuff
    //
	//trying to set the lights?
	Vector3 tmp = mSceneMgrArr[0]->getLight("rotatingLight")->getPosition();
	double circleRadius = 100;
	lightSpeed += (evt.timeSinceLastFrame * 20);
	lightAngle += (lightSpeed* evt.timeSinceLastFrame);
	/*if(lightAngle > 6.28){
		lightAngle = 0;
		lightSpeed -= lightSpeed;
	}
	*/
	tmp.x = circleRadius * cos(lightAngle);
	tmp.z = circleRadius * sin(lightAngle);
	mSceneMgrArr[0]->getLight("rotatingLight")->setPosition(tmp);
	//std::cout<<"coords "<<tmp.x<<" "<<tmp.y<<" "<<tmp.z<<std::endl;
	updateRobotAnimationState(evt);
	return flg;
}
/*!
	Here, every frame we loop through every entity in the scene nodes and check if 
	it is moving. If it is, we then have to calculate the distance between it and 
	the target, check for collisions between it and the sphere, or between the robot
	and other robots.

	We also have to ensure that the animation is maintained all the way through, so that 
	it is a smooth transition. Also, we need to use a quaternion to ensure that the robot
	keeps facing in the direction it wants to go. We do this by rotating around the y axis.

	Once the robot reaches its destination(when the distance vector is <=0 for x,y,z), we change
	it's animation state and stop it. We have to make sure that it doesn't run into the sphere
	or other robots.

	If the robot is not moving, we just update it's normal animation.
*/
void BasicTutorial_00::updateRobotAnimationState(const Ogre::FrameEvent& evt){
	int speed = 30;
	double distanceMoved = speed*evt.timeSinceLastFrame;
	for(int i=0; i<60; i++){
		
		if(isRobotMoving[i]){
			//std::cout<<"robot "<<i<<" should def be moving"<<std::endl;
			//calculate the distance we have to move
			mAnimationState[i] =  mEntityArr[i]->getAnimationState("Walk");
			
			
			distances[i] -= distanceMoved; //b/c we're getting closer to our target
			std::cout<<"distance between "<<i<<" and point: "<<distances[i]<<std::endl;
			//maybe not the best way to check if we arrived
			if(distances[i].x <= 0 && distances[i].y <= 0.0f && distances[i].z <= 0.0f){ 
				
				std::cout<<"reached the point"<<std::endl;
				//when we arrive at the destination
				mAnimationState[i] = mEntityArr[i]->getAnimationState("Idle");
				isRobotMoving[i] = false;
				mSceneNodeArr[i]->setPosition(targetPoint);
				mSceneNodeArr[i]->showBoundingBox(false);
				//check to see how many robots are moving later
			}

			else{
				//checking for collisions
				float maxDistance = 20;
				
				Real distanceToSphere = 
					 mSceneNodeArr[i]->getPosition().distance(Vector3(0,0,0));
				if(distanceToSphere < maxDistance ){
					//this is probably very wrong
					mSceneNodeArr[i]->translate(directions[i] * evt.timeSinceLastFrame);
				}
				else{
					//just keep swimming
					mSceneNodeArr[i]->translate(directions[i] * distanceMoved);
				}
				
			}
			mAnimationState[i] =  mEntityArr[i]->getAnimationState("Walk");
			mAnimationState[i]->addTime(evt.timeSinceLastFrame);
		}
		
		//if robot isn't supposed to be moving, just continue the animation
		else{
			mAnimationState[i]->addTime(evt.timeSinceLastFrame); 
		}
	}
}
/*!
In this function, we draw a ray from the mouse to the scene and select the first item
that we intersect.
*/
bool BasicTutorial_00::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id){
	Ray mRay = mTrayMgr->getCursorRay(mCamera);
	Vector2 scn = mTrayMgr->sceneToScreen(mCamera, mRay.getOrigin());
	
	left = scn.x;
	top = scn.y;
	right = scn.x;
	bottom = scn.y;
	mSelectionRect->setCorners(left, top, right, bottom);

	return BaseApplication::mousePressed(arg, id);
}
/*!
	Here, we continue tracking the coordinates of the mouse ray.
*/
bool BasicTutorial_00::mouseMoved(const OIS::MouseEvent& arg){
	Ray mRay = mTrayMgr->getCursorRay(mCamera);

	Vector2 scn = mTrayMgr->sceneToScreen(mCamera, mRay.getOrigin());
	left = scn.x;
	//top = scn.y;
	//right = scn.x;
	bottom = scn.y;
	mSelectionRect->setCorners(left, top, right, bottom);
	mSelectionRect->setVisible(true);

	return BaseApplication::mouseMoved( arg);
}
/*!
	We have two different processes for the right and
	left mouse buttons, respectively. If the right button is
	released, then we have to record the mouse ray that tells us
	the desired target coordinates.
	
	Else if the left button is the one that is released, we have to
	make the query to see which entities are selected, and then change 
	their status to moving. Then in the next frame their state will 
	be updated.
*/
bool BasicTutorial_00::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id){
	//for moving the items
	if(id == OIS::MB_Right){
		Real x  = arg.state.X.abs;
		Real y = arg.state.Y.abs;

		Real width = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
		Real height = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();

		Real offsetx = x/width;
		Real offsety= y/width;

		Ray destRay = mCamera->getCameraToViewportRay(offsetx, offsety);
		Plane plane(Vector3::UNIT_Y, 0);

		std::pair<bool, Real> queryResult = destRay.intersects(plane);
		//if the query from the destRay intersects the plane, first is true, and we have the distance
		if(queryResult.first){
			targetPoint = destRay.getPoint(queryResult.second);
			for(int i=0; i<60; i++){
				SceneNode* mCurrentObject = mSceneNodeArr[i];
				//changing the animation state from idle to walking
				//if the node was in the selection rectangle
				if(mSceneNodeArr[i]->getShowBoundingBox()){
					mAnimationState[i] = mEntityArr[i]->getAnimationState("Walk");
					mAnimationState[i]->setLoop(true);
					mAnimationState[i]->setEnabled(true);

					isRobotMoving[i]=true;
					directions[i] = targetPoint - mSceneNodeArr[i]->getPosition();
					distances[i] = directions[i].normalise();
				}
				
			}
		}
	}
	//for selecting the items we want to move
	else if(id == OIS::MB_Left){
		if( left==right && top ==bottom){
			return BaseApplication::mouseReleased(arg, id);
		}
		/* This is used to work with CEGUI
		Ray topLeft = mCamera->getCameraToViewportRay(left, top);
		Ray topRight = mCamera->getCameraToViewportRay(right, top);
		Ray bottomLeft = mCamera->getCameraToViewportRay(left, bottom);
		Ray bottomRight = mCamera->getCameraToViewportRay(right, bottom);
		*/
		mSelectionRect->clear();
		Real nleft = left;
		Real nright = right;
		Real ntop = 1+top;
		Real nbottom = 1+bottom;
		Ray topLeft = mTrayMgr->screenToScene(mCamera, Vector2(nleft, ntop));
		Ray topRight = mTrayMgr->screenToScene(mCamera, Vector2(nright, ntop));
		Ray bottomLeft = mTrayMgr->screenToScene(mCamera, Vector2(nleft, nbottom));
		Ray bottomRight = mTrayMgr->screenToScene(mCamera, Vector2(nright, nbottom));

		PlaneBoundedVolume vol;
		int np = 100;
		vol.planes.push_back(Plane(topLeft.getPoint(3), topRight.getPoint(3), bottomRight.getPoint(3))); //front plane
		vol.planes.push_back(Plane(topLeft.getOrigin(), topLeft.getPoint(np), topRight.getPoint(np))); //top plane
		vol.planes.push_back(Plane(topLeft.getOrigin(), bottomLeft.getPoint(np), topLeft.getPoint(np)));//left plane
		vol.planes.push_back(Plane(bottomLeft.getOrigin(), bottomRight.getPoint(np), bottomLeft.getPoint(np)));//bottom plane
		vol.planes.push_back(Plane(bottomRight.getOrigin(), topRight.getPoint(np), bottomRight.getPoint(np))); //right plane
	
		PlaneBoundedVolumeList volList;
		volList.push_back(vol);
		mVolQuery->setVolumes(volList);

		SceneQueryResult result = mVolQuery->execute();
		SceneQueryResultMovableList::iterator itr = result.movables.begin();
	

		//we only care about the first intersection, so we set the camera
		for(itr = result.movables.begin(); itr != result.movables.end(); ++itr){
			if(*itr){
				SceneNode* mCurrentObject = (*itr)->getParentSceneNode();
				std::cout<<mCurrentObject->getName()<<std::endl;
				bool flgShow = mCurrentObject->getShowBoundingBox();
				std::cout<<"\t should we be seeing bounding box: "<<flgShow<<std::endl;
				mCurrentObject->showBoundingBox(!flgShow);
			}
		}
	}
	return BaseApplication::mouseReleased(arg, id);
}
int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}

////////////////////////////////////////
// DO NOT DELETE THIS LINE: 2018/09/20. 3D Game Programming
////////////////////////////////////////