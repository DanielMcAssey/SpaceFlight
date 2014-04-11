#include "StdAfx.h"
#include "PlayerObject.h"


PlayerObject::PlayerObject(SceneManager* sceneManager, WindowData* window, Ogre::SceneNode* sceneNode, int playerID)
{
	this->mSceneManager = sceneManager;
	this->mWindow = window;
	this->mPlayerID = playerID;
	this->mNode = sceneNode->createChildSceneNode("player_" + playerID);
	this->mNode->setPosition(Ogre::Vector3(0,0,0));
	this->mGunCooldownTime = 3.0f;
	this->mGunMaxFireTime = 5.0f;
	this->mGunCooldownWait = false;
	this->mBulletManager = new BulletManager(this, sceneManager);
	this->isPlayerDead = false;
}


PlayerObject::~PlayerObject(void)
{
}


Ogre::Camera* PlayerObject::LoadCamera(int id)
{
	this->mCamera = this->mSceneManager->createCamera("PlayerCam_" + id);
	this->mCamera->setPosition(Ogre::Vector3(this->GetPosition().x,this->GetPosition().y + 5,25)); //Need to fix
	this->mCamera->lookAt(Ogre::Vector3(this->GetPosition().x,this->GetPosition().y + 5,this->GetPosition().z));
	this->mCamera->setNearClipDistance(0.01);
	this->mCamera->setFarClipDistance(this->mWindow->maxViewDistance);
	this->mCamera->setAspectRatio(Real(this->mWindow->_obj_viewport[id]->getActualWidth()) / Real(this->mWindow->_obj_viewport[id]->getActualHeight()));
	this->mCameraNode = this->mNode->createChildSceneNode("player_camera_" + id); //Create camera node.
	this->mCameraNode->attachObject(this->mCamera); //Attach camera to the scene node.
	return this->mCamera;
}


void PlayerObject::Update(Real elapsedTime)
{
	if(!this->isPlayerDead)
	{
		this->HandleInput(elapsedTime); //Deal with Input
		this->mBulletManager->Update(elapsedTime);
	}
}


void PlayerObject::SetPosition(Vector3 newPos)
{
	this->mNode->setPosition(newPos);
}


Vector3 PlayerObject::GetPosition()
{
	return this->mNode->getPosition();
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
	this->mCameraNode->setPosition(Ogre::Vector3(this->GetPosition().x,this->GetPosition().y,50));
	this->mCamera->lookAt(this->GetPosition());
}


void PlayerObject::KillPlayer()
{
	this->isPlayerDead = true;

	//TODO: EXPLODE
}


Ogre::SceneNode* PlayerObject::GetSceneNode(void)
{
	if(this->mNode != nullptr)
		return this->mNode;
}


void PlayerObject::HandleInput(Real elapsedTime)
{
	this->mDirection = this->mNode->_getDerivedOrientation() * Vector3::NEGATIVE_UNIT_Z;
	Real _Speed = this->mVehicle->GetStats()->Speed * 0.3f;

	if(this->mWindow->_obj_input->GetState(this->mPlayerID).RTrigger != 0.0f)
		this->mNode->translate((this->mDirection * (this->mWindow->_obj_input->GetState(this->mPlayerID).RTrigger * (_Speed * 1.5))) * elapsedTime); //Accelerate
	else if(this->mWindow->_obj_input->GetState(this->mPlayerID).LTrigger != 0.0f)
		this->mNode->translate((this->mDirection * (_Speed / 2)) * elapsedTime); //Brake
	else
		this->mNode->translate((this->mDirection * _Speed) * elapsedTime); //Normal Speed

	if(this->mWindow->_obj_input->GetState(this->mPlayerID).LStick.X != 0.0f)
		this->mNode->roll(Ogre::Degree(-this->mWindow->_obj_input->GetState(this->mPlayerID).LStick.X  * elapsedTime * (this->mVehicle->GetStats()->Handling / 2000)), Ogre::Node::TS_LOCAL);

	if(this->mWindow->_obj_input->GetState(this->mPlayerID).LStick.Y != 0.0f)
		this->mNode->pitch(Ogre::Degree(-this->mWindow->_obj_input->GetState(this->mPlayerID).LStick.Y  * elapsedTime * (this->mVehicle->GetStats()->Handling / 2000)), Ogre::Node::TS_LOCAL);

	if(this->mWindow->_obj_input->GetState(this->mPlayerID).Buttons.LShoulder == false && this->mGunCooldownWait == false)
		this->mGunCooldown = 0.0f;

	if(this->mWindow->_obj_input->GetState(this->mPlayerID).Buttons.LShoulder) //Automatic MG
	{
		this->mGunCooldown += elapsedTime;
		if(!this->mGunCooldownWait)
		{
			this->mBulletManager->CreateBullet(this->GetPosition(), this->mDirection);
			if(this->mGunCooldown >= this->mGunMaxFireTime)
			{
				this->mGunCooldownWait = true;
				this->mGunCooldown = 0.0f;
			}
		}
		else
		{
			if(this->mGunCooldown >= this->mGunCooldownTime)
			{
				this->mGunCooldownWait = false;
				this->mGunCooldown = 0.0f;
			}
		}
	}
	
	if(this->mWindow->_obj_input->GetState(this->mPlayerID).ButtonsSingle.RShoulder) //Missile
	{
		if(this->mCurrentMissiles > 0)
		{
			this->mBulletManager->CreateMissile(this->GetPosition(), this->mDirection);
			this->mCurrentMissiles -= 1;
		}
	}
}

