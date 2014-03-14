#include "StdAfx.h"
#include "PlayerObject.h"


PlayerObject::PlayerObject(SceneManager* sceneManager, WindowData* window, Ogre::SceneNode* sceneNode, int playerID)
{
	this->mSceneManager = sceneManager;
	this->mWindow = window;
	this->mPlayerID = playerID;
	this->mNode = sceneNode->createChildSceneNode("player_" + playerID);
	this->mPosition = Ogre::Vector3(0,0,0);
	this->mNode->setPosition(this->mPosition);

}


PlayerObject::~PlayerObject(void)
{
}


Ogre::Camera* PlayerObject::LoadCamera(int id)
{
	this->mCamera = this->mSceneManager->createCamera("PlayerCam_" + id);
	this->mCamera->setPosition(Ogre::Vector3(this->mPosition.x,this->mPosition.y,50)); //Need to fix
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
	this->HandleInput(elapsedTime); //Deal with Input
}


void PlayerObject::SetPosition(Vector3 newPos)
{
	this->mPosition = newPos;
	this->mNode->setPosition(this->mPosition);
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
	this->mCameraNode->setPosition(Ogre::Vector3(this->mPosition.x,this->mPosition.y,50));
	this->mCamera->lookAt(this->mPosition);
}


void PlayerObject::HandleInput(Real elapsedTime)
{
	if(this->mWindow->_obj_input->GetState(this->mPlayerID).RTrigger > 0.0f)
	{
		this->SetPosition(Ogre::Vector3(0.0f, 0.0f, this->mPosition.z + this->mWindow->_obj_input->GetState(this->mPlayerID).RTrigger));
	}

	if(this->mWindow->_obj_input->GetState(this->mPlayerID).LStick.X != 0.0f)
	{
		this->mNode->roll(Ogre::Degree(-this->mWindow->_obj_input->GetState(this->mPlayerID).LStick.X  * elapsedTime * (this->mVehicle->GetStats()->Handling * 100)), Ogre::Node::TS_WORLD);
	}

	if(this->mWindow->_obj_input->GetState(this->mPlayerID).LStick.Y != 0.0f)
	{
		this->mNode->pitch(Ogre::Degree(-this->mWindow->_obj_input->GetState(this->mPlayerID).LStick.Y  * elapsedTime * (this->mVehicle->GetStats()->Handling * 100)), Ogre::Node::TS_WORLD);
	}

	if(this->mWindow->_obj_input->GetState(this->mPlayerID).Buttons.LShoulder)
	{
		this->mNode->yaw(Ogre::Degree((this->mVehicle->GetStats()->Handling * 100) * elapsedTime), Ogre::Node::TS_WORLD);
	}
	else if(this->mWindow->_obj_input->GetState(this->mPlayerID).Buttons.RShoulder)
	{
		this->mNode->yaw(Ogre::Degree((this->mVehicle->GetStats()->Handling * 100) * elapsedTime), Ogre::Node::TS_WORLD);
	}
}