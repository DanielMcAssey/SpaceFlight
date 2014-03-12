#include "StdAfx.h"
#include "PlayerObject.h"


PlayerObject::PlayerObject(SceneManager* sceneManager, WindowData* window)
{
	this->mSceneManager = sceneManager;
	this->mWindow = window;
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