#ifndef __SelectionRectangle_h__
#define __SelectionRectangle_h__

#include<OgreCamera.h>
#include<OgreEntity.h>
#include<OgreLogManager.h>
#include<OgreRoot.h>
#include<OgreViewport.h>
#include<OgreSceneManager.h>
#include<OgreRenderWindow.h>
#include<OgreConfigFile.h>

using namespace Ogre;
class SelectionRectangle: public ManualObject
{
public:
	SelectionRectangle(const String& name):ManualObject(name){
		setUseIdentityProjection(true);
		setUseIdentityView(true);
		setRenderQueueGroup(RENDER_QUEUE_OVERLAY);
		setQueryFlags(0);
	}
	void setCorners(float left, float top, float right, float bottom){
		left = left*2-1;
		right = right * 2 -1;
		top = -1 - top*2;
		bottom = -1 -bottom *2;
		
		Real z = -1;
		clear();

		begin("Examples/Hilite/Yellow", RenderOperation::OT_TRIANGLE_STRIP);
		position(right, top, z);
		position(left, top, z);
		position(right, bottom, z);
		position(left, bottom, z);

		end();
		AxisAlignedBox box;
		box.setInfinite();
		setBoundingBox(box);
	}
};
#endif