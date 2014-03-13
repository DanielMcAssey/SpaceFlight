#include "StdAfx.h"
#include "PlayerObject.h"


PlayerObject::PlayerObject(SceneManager* sceneManager, WindowData* window, Ogre::SceneNode* sceneNode, int playerID)
{
	this->mSceneManager = sceneManager;
	this->mWindow = window;
	this->mPlayerID = playerID;
	this->mNode = sceneNode->createChildSceneNode("player_" + playerID);
}


PlayerObject::~PlayerObject(void)
{
}

Ogre::Camera* PlayerObject::LoadCamera(int id)
{
	this->mCamera = this->mSceneManager->createCamera("PlayerCam_" + id);
	this->mCamera->setPosition(this->mPosition); //Need to fix
	this->mCamera->lookAt(this->mPosition);
	this->mCamera->setNearClipDistance(0.01);
	this->mCamera->setFarClipDistance(this->mWindow->maxViewDistance);
	this->mCamera->setAspectRatio(Real(this->mWindow->_obj_viewport[id]->getActualWidth()) / Real(this->mWindow->_obj_viewport[id]->getActualHeight()));
	this->mNode->attachObject(this->mCamera); //Attach camera to the scene node.
	return this->mCamera;
}

void PlayerObject::Update(Real elapsedTime)
{

}

void PlayerObject::SetPosition(Vector3 newPos)
{
	this->mPosition = newPos;
}

Vector3 PlayerObject::GetPosition()
{
	return this->mPosition;
}