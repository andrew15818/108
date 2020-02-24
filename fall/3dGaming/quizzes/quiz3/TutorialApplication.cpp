//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
// Date: 2019/12/11
//Student Name: Andres Ponce
//Student ID: 0616110
#include "TutorialApplication.h"
#include "BasicTools.h"
#include <queue>
#include <vector>
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

#define MOVABLE 1
#define BARREL 2
#define SOLUTION_PART 3

BasicTutorial_00::BasicTutorial_00(void)
    : 
mMoveDirection(mMoveDirection_NONE)
{
	barrelDelta = 130;//original scene  is 1500, leaving 100 units gap on either side / barrels per side
	totalBarrels = 60;
	barrelsBound = 650;
	totalSpheres = 20;
	sideBarrels = 10;
	
	for(int i= 0; i < sideBarrels; i++){
		for(int j=0; j< sideBarrels; j++){
			map[i][j].type = MOVABLE;
			map[i][j].f  = map[i][j].g = map[i][j].h = -1;
			//map[i][j].parent = NULL;
			map[i][j].parentX = -1;
			map[i][j].parentZ = -1;
		}
	}
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


// reset positions of all small spheres
void BasicTutorial_00::reset()
{

}
double BasicTutorial_00::manDist(int startX, int startY, int destX, int destY)
{
	return abs(destX-startX) + abs((destY-startY));
}
int BasicTutorial_00::getWorldCoordinatesFromIndex(int index)
{
	return -barrelsBound + barrelDelta * index;
}
//returns the correct coordinates
int BasicTutorial_00::getIndexFromWorldCoordinates(int index)
{
	/*return the absolute value because originally we start
	measuring from -650, so always returns negative value*/
	return abs((-barrelsBound - index)/barrelDelta);
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
	planito = plane;
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

    

    ///////////////////////
        // add your own stuff
        ///////////////////////

		//see if we can figure out how to to make the node actually appear?
		robotSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("robotSceneNode");
		robotEntity = mSceneMgr->createEntity("robotEnt", "Robot.mesh");
		robotSceneNode->attachObject(robotEntity);
		mAnimationState = robotEntity->getAnimationState("Idle");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
		
		
		setBarrels();
		search(5, 5, 4, 4);
}
void BasicTutorial_00::setBarrels()
{
	

	int startingX = -barrelsBound, startingY = -barrelsBound;
		String barrelEntName, barrelSNname;
		Entity *barrelEnt;
		SceneNode* barrelSn;
		int objectCounter =0;
	//creating the main outer barrels
	for(int i = 0; i< 40; i++, objectCounter++){
		genNameUsingIndex("barrelEnt", i, barrelEntName);
		genNameUsingIndex("barrelSn", i, barrelSNname);
		barrelEnt = mSceneMgr->createEntity(barrelEntName, "barrel.mesh");
		barrelSn = mSceneMgr->getRootSceneNode()->createChildSceneNode(barrelSNname);
		
		if(i < 10){
			startingX += barrelDelta;
			map[i%10][0].type = BARREL;
			std::cout<<"map["<<i%10<<"][0]=false"<<std::endl;
		}
		else if(i>=10 && i< 20){
			startingY += barrelDelta;
			map[0][i%10].type = BARREL;
			std::cout<<"map[0"<<"]["<< i%10<<"]=false"<<std::endl;
		}
		else if(i>=20 && i< 30){
			startingX -= barrelDelta;
			map[9][i%10].type = BARREL;
			std::cout<<"map[9]["<<i%10<<"]=false"<<std::endl;
		}
		else if( i>=30 && i<40){
			startingY -= barrelDelta;
			map[i%10][9].type = BARREL;
			std::cout<<"map["<<i%10<<"][9]=false"<<std::endl;
		}
		barrelSn->scale(10.0f, 10.0f, 10.0f);
		barrelSn->setPosition(startingX, 0, startingY);
		if(i == 16){
			barrelSn->setPosition(startingX - barrelDelta, 0, startingY);
			map[5][8].type = BARREL; // not so sure about this coord
		}
		else if( i== 35){
			barrelSn->setPosition(startingX + barrelDelta, 0, startingY);
			map[4][1].type = BARREL;
		}
		
		barrelSn->attachObject(barrelEnt);
		mBarrelEnts[objectCounter] = barrelEnt;
		mBarrelSceneNodes[objectCounter] = barrelSn;
	}

	//creating the horizontal barrels
	for(int i =0; i< 6; i++, objectCounter++){
		genNameUsingIndex("crossBarrelEnt", i, barrelEntName);
		genNameUsingIndex("crossBarrelSn", i, barrelSNname);
		barrelEnt = mSceneMgr->createEntity(barrelEntName, "barrel.mesh");
		barrelSn = mSceneMgr->getRootSceneNode()->createChildSceneNode(barrelSNname);

		startingX = -barrelsBound + (i+2)*barrelDelta;
		startingY = -barrelsBound+ 2* barrelDelta;
		map[7][i+2].type = BARREL;
		barrelSn->scale(10.0f, 10.0f, 10.0f);
		barrelSn->setPosition(startingX, 0, startingY);
		barrelSn->attachObject(barrelEnt);
		mBarrelEnts[objectCounter] = barrelEnt;
		mBarrelSceneNodes[objectCounter] = barrelSn;
	}

	//creating the second row of  horizontal barrels
	for(int i =0; i< 6; i++, objectCounter++){
		genNameUsingIndex("crossBarrelEnt2", i, barrelEntName);
		genNameUsingIndex("crossBarrelSn2", i, barrelSNname);
		barrelEnt = mSceneMgr->createEntity(barrelEntName, "barrel.mesh");
		barrelSn = mSceneMgr->getRootSceneNode()->createChildSceneNode(barrelSNname);
		map[2][i+2].type = BARREL;

		startingX = barrelsBound - (i+2)*barrelDelta;
		startingY = barrelsBound- 2* barrelDelta;
		barrelSn->scale(10.0f, 10.0f, 10.0f);
		barrelSn->setPosition(startingX, 0, startingY);
		barrelSn->attachObject(barrelEnt);
		mBarrelEnts[objectCounter] = barrelEnt;
		mBarrelSceneNodes[objectCounter] = barrelSn;
	}
	/*TODO: get the last two items into position*/
	//creating the last two barrels to go in the scene
	barrelEnt = mSceneMgr->createEntity("centerBarrel1Ent","barrel.mesh");
	barrelSn = mSceneMgr->getRootSceneNode()->createChildSceneNode("centerBarrel1Sn");
	startingX = getWorldCoordinatesFromIndex(5);
	startingY = getWorldCoordinatesFromIndex(4);
	map[5][4].type = BARREL;
	barrelSn->setPosition(startingX, 0, startingY);
	std::cout<<"setting the coordinates at: "<<startingX<<" "<<startingY<<std::endl;
	barrelSn->scale(10.0f, 10.0f, 10.0f);
	barrelSn->attachObject(barrelEnt);
	

	barrelEnt = mSceneMgr->createEntity("centerBarrel2Ent","barrel.mesh");
	barrelSn = mSceneMgr->getRootSceneNode()->createChildSceneNode("centerBarrel2Sn");
	startingX = getWorldCoordinatesFromIndex(4);
	startingY = getWorldCoordinatesFromIndex(5);
	map[4][5].type = BARREL;
	barrelSn->scale(10.0f, 10.0f, 10.0f);
	barrelSn->setPosition(startingX, 0, startingY);
	barrelSn->attachObject(barrelEnt);

	//printMatrix();
}
bool BasicTutorial_00::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	//maybe use the intersects method with a ray 
	//getting the window height and Width
	Ogre::Real screenWidth = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
	Ogre::Real screenHeight = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();

	//get the coords as a fraction of the window size 
	Ogre::Real offsetX = arg.state.X.abs / screenWidth;
	Ogre::Real offsetY = arg.state.Y.abs / screenHeight;
	

	Ray mMouseRay = mCamera->getCameraToViewportRay(offsetX, offsetY);
	std::pair<bool, Real> result = mMouseRay.intersects(planito);
	//if the click goes through the plane
	if(result.first){

		Vector3 vectorino = mMouseRay.getPoint(result.second);
		std::cout<<vectorino<<std::endl;
		clickX = getIndexFromWorldCoordinates(vectorino.x);
		clickZ = getIndexFromWorldCoordinates(vectorino.z);
		
		robotX = getIndexFromWorldCoordinates(robotSceneNode->getPosition().x);
		robotZ = getIndexFromWorldCoordinates(robotSceneNode->getPosition().z);
		
		//TODO: check if the robot's coordinates are correct, remember we had to switch the order of the
		std::cout<<"going from : ("<<robotX<<","<<robotZ<<") to ("<<clickX<<","<<clickZ<<std::endl;
		search(robotX, robotZ, clickZ, clickX);
	}
	return true;
}
void BasicTutorial_00::printMatrix()
{
	std::cout<<"format: (g, h, f)"<<std::endl;
	for(int i =0; i< 10; i++){
		for(int j=0; j<10; j++){
			std::cout<<i<<","<<j<<":("<<map[i][j].parentX<<","<<map[i][j].parentZ<<")\t";
			if(j == sideBarrels-1)std::cout<<std::endl;
		}
	}
}
bool compare(const aStarNode& n1, const aStarNode& n2){

	return n1.f <= n2.f;
}
/*TODO: we need to initialize the values in aStarNode*/
aStarNode& getMin(std::list<aStarNode>& Open){
	aStarNode& min = Open.front();
	std::cout<<"the minimum f"<<min.f<<" with "<<min.x<<","<<min.z<<std::endl;
	std::list<aStarNode>::iterator it;
	for(it; it != Open.end(); it++){
		min = (min.f < it->f)?min:*(it);
	}
	return min;
}
bool BasicTutorial_00::findNode( std::list<aStarNode> Open, const aStarNode& node){
	
	std::list<aStarNode>::iterator it = Open.begin();
	while(it != Open.end()){
		if( (*it).x == node.x && (*it).z == node.z){
			return true;
		}
		it++;
	}
	
	return false;
}
bool BasicTutorial_00::isValid(int x, int z)
{
	if( x<0 || z < 0 || x >=10 || z >=10){
		return false;
	}
	if(map[x][z].type != MOVABLE){
		return false;
	}
	return true;
}
bool BasicTutorial_00::isDestination(int currentX, int currentZ, int endX, int endZ)
{
	return (currentX == endX && currentZ == endZ)?true:false;
}
int BasicTutorial_00::getIndexToDelete( std::list<aStarNode&>&listo, aStarNode& nodo)
{
	/*
	std::list<aStarNode&>::iterator it = listo.begin();
	int counter=0;
	for(it; it!= listo.end(); it++){
		if((*it).x == nodo.x && (*it).z == nodo.z){
			return counter;
		}
	}
	*/
	return -1;
}
void BasicTutorial_00::printPath(int startX, int startZ, int endX, int endZ)
{
	aStarNode tmp = map[endX][endZ];
	while(tmp.x != -1 && tmp.z != -1){
		std::cout<<"("<<tmp.x<<","<<tmp.z<<")->";
		tmp.x = tmp.parentX;
		tmp.z = tmp.parentZ;
	}
}
void BasicTutorial_00::printF()
{
	for(int i=0; i<sideBarrels; i++){
		for(int j=0; j<sideBarrels; j++){
			std::cout<<map[i][j].f<<" ";
			if(j==sideBarrels-1)std::cout<<std::endl;
		}
	}
}
void BasicTutorial_00::drawSpheres(int startX, int startZ, int endX, int endZ)
{
	int next, prev, sphereCounter=0;
	String entName, entSN;
	while(1){
		prev = startX, next = startZ;

		genNameUsingIndex("pathSphereEnt", sphereCounter, entName);
		genNameUsingIndex("pathSphereSN", sphereCounter, entSN);
		Entity* tmpEnt = mPathSphereEnts[sphereCounter] = mSceneMgr->createEntity(entName, "sphere.mesh");
		SceneNode* tmpSN  = mPathSceneNodes[sphereCounter] = mSceneMgr->getRootSceneNode()->createChildSceneNode(entSN);
		
		Vector3 pos = Ogre::Vector3(getWorldCoordinatesFromIndex(startX), 0, getWorldCoordinatesFromIndex(startZ));
		tmpSN->setPosition(pos);

		tmpSN->attachObject(tmpEnt);
		startX = map[startX][startZ].parentX;
		startZ = map[startX][startZ].parentZ;
		if(prev == startX && next == startZ){return;}
		sphereCounter++;
	}
}
/*Like any hope, the algorithm evades me :(*/
void BasicTutorial_00::search(int startX, int startZ, int endX, int endZ)
{
	//first we do some preprocessing
	//will need these values to choose the best ones
	std::list<aStarNode> Open;
	std::list<aStarNode> Closed;
	std::list<aStarNode> result;

	for(int i=0; i<sideBarrels; i++){
		for(int j=0; j<sideBarrels; j++){
			if(map[i][j].type == MOVABLE){
				//map[i][j].g = manDist(startX, startZ, i, j);
				map[i][j].h = manDist(i,j,endX, endZ);
				map[i][j].f = map[i][j].g + map[i][j].h;
				map[i][j].x = i;
				map[i][j].z = j;
			}
		}
	}

	
	//map[startX][startZ].f = map[startX][startZ].g = map[startX][startZ].h = 0;
	map[startX][startZ].g = 0;
	map[startX][startZ].h = manDist(startX, startZ, endX, endZ);
	map[startX][startZ].f = map[startX][startZ].g + map[startX][startZ].h;
	map[startX][startZ].parentX = startX;
	map[startX][startZ].parentZ = startZ;
	Open.push_back(map[startX][startZ]);
	result.push_back(map[startX][startZ]);
	
	std::cout<<"going from ("<<startX<<","<<startZ<<")->("<<endX<<","<<endZ<<")"<<std::endl;
	while(!Open.empty()){
		Open.sort(compare);
		aStarNode& currMin = Open.front();
		std::cout<<"testing: "<<currMin.x<<","<<currMin.z<<"\t sizeof Open: "<<Open.size()<<"\t size of closed:"<<Closed.size()<<std::endl;

		Open.pop_front();
		//Closed.push_back(currMin);
		if(isDestination(currMin.x, currMin.z, endX, endZ)){
			std::cout<<"llegamos!"<<std::endl;
			printMatrix();
			//printPath(startX, startZ, endX, endZ);
			return;
		}
		//std::cout<<"starting with:"<<map[startX][startZ].x<<","<<map[startX][startZ].z<<std::endl;
		for(int k=0; k<4; k++){
			int i,j;
			//to decide which node from among the ones we can move to 
			switch(k){
				case 0:
					i=0;
					j=-1;
					break;
				case 1:
					i=-1;
					j=0;
					break;
				case 2:
					i=0;
					j=1;
					break;
				case 3:
					i=1;
					j=0;
					break;
			}
			if(isValid(currMin.x+i,currMin.z+j)){
				aStarNode& testCurrent = map[currMin.x+i][currMin.z+j];
				testCurrent.g = currMin.g + 1;
				testCurrent.f = testCurrent.g + testCurrent.h;
				std::cout<<"\twhile testing: ("<<currMin.x<<","<<currMin.z<<"), testing("<<testCurrent.x<<","<<testCurrent.z<<")"<<std::endl;
				if(findNode(Open,testCurrent) && testCurrent.f > currMin.f){
					continue;
				}
				else if(findNode(Closed, testCurrent) && testCurrent.f > currMin.f){
					continue;
				}
				//removing possible duplicates from the lists
				if(testCurrent.f <= currMin.f){
					std::list<aStarNode>::iterator it = Open.begin();
					std::list<aStarNode>::iterator Closedit = Closed.begin();
					for(it; it != Open.end(); it++){
						if(it->x == testCurrent.x && it->z == testCurrent.z){
							continue;
							//Open.erase(it);
						}
					}
					for(Closedit; Closedit != Closed.end(); Closedit++){
						if(Closedit->x == testCurrent.x && Closedit->z == testCurrent.z){
							Closed.erase(Closedit);
						}
					}
					std::cout<<"\t\t From("<<currMin.x<<","<<currMin.z<<") to ("<<testCurrent.x<<","<<testCurrent.z<<std::endl;
					std::cout<<"\t\t(f,g,h)("<<currMin.f<<","<<currMin.g<<","<<currMin.h<<"),("<<testCurrent.f<<","<<testCurrent.g<<","<<testCurrent.h<<std::endl;
					testCurrent.parentX = currMin.x;
					testCurrent.parentZ = currMin.z;
					Open.push_back(testCurrent);
				}
				/*
				if(!findNode(Open, testCurrent) && !findNode(Closed, testCurrent)){
					Open.push_back(testCurrent);
						
					if(testCurrent.f <= currMin.f){
						std::cout<<"\tmaybe ("<<testCurrent.x<<","<<testCurrent.z<<")is a better option?"<<std::endl;						
						testCurrent.parentX = currMin.x; 
						testCurrent.parentZ = currMin.z;
						std::cout<<"\t\tfrom "<<testCurrent.x<<","<<testCurrent.z<<" we go to "<<testCurrent.parentX<<","<<testCurrent.parentZ<<std::endl;
					}
					
				}
				*/
				/*
				std::cout<<"Comparing: "<<std::endl;
				std::cout<<"("<<currMin.x<<","<<currMin.z<<")"<<"\t("<<testCurrent.x<<","<<testCurrent.z<<")"<<std::endl;
				std::cout<<"f:"<<currMin.f<<"\t"<<testCurrent.f<<std::endl;
				std::cout<<"g:"<<currMin.g<<"\t"<<testCurrent.g<<std::endl;
				std::cout<<"h:"<<currMin.h<<"\t"<<testCurrent.h<<std::endl;
				*/
				
	
			}
		}
		std::cout<<"\tpushing ("<<currMin.x<<","<<currMin.z<<")to Closed"<<std::endl;
		Closed.push_back(currMin);
	}
	//printPath(endX, endZ);
	//printMatrix();
	drawSpheres(startX, startZ, endX, endZ);
	
	std::cout<<std::endl;
	return;
}
void BasicTutorial_00::setSphereAlongPath(int clickX, int ClickZ)
{
	String sphereEnt, sphereSN;
	SceneNode* pathSphereSN;
	Entity* pathSphereEnt;
		
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
            ->setPosition(Vector3(-22.30,	409.24,	816.74));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.02,	-0.23,	-0.97));

    }

    if (arg.key == OIS::KC_2 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(-824.52,	468.58,	68.45));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.94,	-0.31,	-0.11));

        //-1463.00	606.45	-513.24
        //0.88	-0.47	0.10
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

    if (arg.key == OIS::KC_B ) {
    }


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
    //
    Vector3 mdir;
    if (mMoveDirection & mMoveDirection_UP ) {
        mdir += Vector3(0.0, 0.0, -1.0);
    }
	mAnimationState->addTime(evt.timeSinceLastFrame);
    ///////////////////////
    // add your own stuff
    ///////////////////////


    //
    return flg;
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
