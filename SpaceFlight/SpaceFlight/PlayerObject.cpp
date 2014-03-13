#include "StdAfx.h"
#include "PlayerObject.h"


PlayerObject::PlayerObject(SceneManager* sceneManager, WindowData* window, Ogre::SceneNode* sceneNode, int playerID)
{
	this->mSceneManager = sceneManager;
	this->mWindow = window;
	this->mPlayerID = playerID;
	this->mNode = sceneNode->createChildSceneNode("player_" + playerID);
	this->mPosition = Ogre::Vector3(0,0,0);
}


PlayerObject::~PlayerObject(void)
{
}


Ogre::Camera* PlayerObject::LoadCamera(int id)
{
	this->mCamera = this->mSceneManager->createCamera("PlayerCam_" + id);
	this->mCamera->setPosition(Ogre::Vector3(0,0,50)); //Need to fix
	this->mCamera->lookAt(this->mPosition);
	this->mCamera->setNearClipDistance(0.01);
	this->mCamera->setFarClipDistance(this->mWindow->maxViewDistance);
	this->mCamera->setAspectRatio(Real(this->mWindow->_obj_viewport[id]->getActualWidth()) / Real(this->mWindow->_obj_viewport[id]->getActualHeight()));
	this->mCameraNode = this->mNode->createChildSceneNode("player_camera"); //Create camera node.
	this->mCameraNode->attachObject(this->mCamera); //Attach camera to the scene node.
	return this->mCamera;
}


void PlayerObject::Update(Real elapsedTime)
{
	this->HandleInput(); //Deal with Input
}


void PlayerObject::SetPosition(Vector3 newPos)
{
	this->mPosition = newPos;
}


Vector3 PlayerObject::GetPosition()
{
	return this->mPosition;
}


void PlayerObject::SetHealth(Ogre::Real newHealth)
{
	if(newHealth <= 100.0f)
		this->mHealth = newHealth;
}


Real PlayerObject::GetHealth()
{
	return this->mHealth;
}


void PlayerObject::SetVehicle(VehicleObject* vehicle)
{
	this->mVehicle = vehicle;
	this->mVehicle->LoadVehicle(this->mSceneManager, this->mNode);
}


VehicleObject* PlayerObject::GetVehicle()
{
	if(this->mVehicle != nullptr)
		return this->mVehicle;
}


void PlayerObject::ResetCamera()
{
	//Do stuff
}


void PlayerObject::HandleInput()
{

}