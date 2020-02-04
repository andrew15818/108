#include "BasicTools.h"

void genNameUsingIndex(const Ogre::String & prefix, int index, Ogre::String &out_name)
{
	out_name= prefix + Ogre::StringConverter::toString(static_cast<int>(index));
}

void resolveCollision(
    SceneNode *nodeA, SceneNode *nodeB,
    float rA, float rB, float wA, float wB)
{
	
	Vector3 p0 = nodeA->getPosition();
	Vector3 p1 = nodeB->getPosition();
	float totalRadius = (rA + rB) *(rA  + rB);
	if(p0.squaredDistance(p1) > totalRadius ){
		Vector3 p0p1 = p1-p0;
		p0p1.normalise();
		nodeB->translate(-p0p1);
	}
}
