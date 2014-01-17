#include "StdAfx.h"
#include "GameObject.h"

using namespace std;
using namespace Ogre;

SceneNode *GameObject::getVisionNode()
{
	return this->mVisionNode;
}

SceneNode *GameObject::getCameraNode()
{
	return this->mCameraNode;
}

Vector3 GameObject::getPosition()
{
	return this->mLocalNode->_getDerivedPosition();
}