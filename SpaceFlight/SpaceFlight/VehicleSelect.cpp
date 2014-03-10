#include "StdAfx.h"
#include "VehicleSelect.h"

using namespace std;
using namespace Ogre;

VehicleSelect::VehicleSelect(void)
{
	this->mShutdown = false;
	this->mFrameEvent = Ogre::FrameEvent();
}


VehicleSelect::~VehicleSelect(void)
{
}

void VehicleSelect::Load()
{
	this->mSceneManager = this->mWindow->_obj_root->createSceneManager(ST_GENERIC, "VehicleSelectManager");
	this->mSceneManager->setAmbientLight(Ogre::ColourValue(0.2f, 0.2f, 0.2f));

	this->mWindow->playersReady = 0;
	this->mWindow->totalPlayers = 0;
	int i = this->mWindow->controllingGamepadID;
	int max = this->mWindow->controllingGamepadID + 1;

	if(this->IsMultiplayer)
	{
		i = 0;
		max = 4;
	}

	for(int j = i; j < max; j++)
	{
		if(!this->mWindow->_obj_input->GetState(j).Disconnected)
		{
			this->mWindow->activePlayers[j] = true;
			this->mWindow->totalPlayers += 1;
		}
	}

	int viewPortsSetup = 0;
	this->mWindow->_obj_rdr_window->removeAllViewports();

	for(i = i; i < max; i++)
	{
		if(this->mWindow->activePlayers[i])
		{
			this->vehicleIndexID[i] = 0;

			std::vector<Ogre::Entity*> tmpVector;
			tmpVector.push_back(this->mSceneManager->createEntity("F15_Active_" + i,"F15_Active.mesh"));
			tmpVector.push_back(this->mSceneManager->createEntity("F35_Lightning_" + i,"F-35_Lightning.mesh"));
			tmpVector.push_back(this->mSceneManager->createEntity("F117_Nighthawk_" + i,"F-117_Nighthawk.mesh"));
			tmpVector.push_back(this->mSceneManager->createEntity("Su32_Flanker_" + i,"Su32.mesh"));

			this->maxVehicles = 4;
			

			if(i == 0)
				this->mAvailableVehicles_p1 = tmpVector;
			else if(i == 1)
				this->mAvailableVehicles_p2 = tmpVector;
			else if(i == 2)
				this->mAvailableVehicles_p3 = tmpVector;
			else if(i == 3)
				this->mAvailableVehicles_p4 = tmpVector;

			this->mActiveCamera[i] = this->mSceneManager->createCamera("VehicleSelectCam_" + i);

			if(this->mWindow->totalPlayers == 1)
			{
				this->mWindow->_obj_viewport[i] = this->mWindow->_obj_rdr_window->addViewport(this->mActiveCamera[i], 0, 0.0, 0.0, 1.0, 1.0);
				this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue(0.5f, 0.5f, 1.0f));
			}
			else if(this->mWindow->totalPlayers == 2)
			{
				if(viewPortsSetup == 0)
				{
					this->mWindow->_obj_viewport[i] = this->mWindow->_obj_rdr_window->addViewport(this->mActiveCamera[i], 0, 0.0, 0.0, 0.5, 1.0);
					this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue(0.6f, 0.0f, 0.0f));
				}
				else if(viewPortsSetup == 1)
				{
					this->mWindow->_obj_viewport[i] = this->mWindow->_obj_rdr_window->addViewport(this->mActiveCamera[i], 1, 0.5, 0.0, 0.5, 1.0);
					this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.6f));
				}
			}
			else if(this->mWindow->totalPlayers == 3)
			{
				if(viewPortsSetup == 0)
				{
					this->mWindow->_obj_viewport[i] = this->mWindow->_obj_rdr_window->addViewport(this->mActiveCamera[i], 0, 0.0, 0.0, 0.5, 0.5);
					this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue(0.6f, 0.0f, 0.0f));
				}
				else if(viewPortsSetup == 1)
				{
					this->mWindow->_obj_viewport[i] = this->mWindow->_obj_rdr_window->addViewport(this->mActiveCamera[i], 1, 0.5, 0.0, 0.5, 0.5);
					this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.6f));
				}
				else if(viewPortsSetup == 2)
				{
					this->mWindow->_obj_viewport[i] = this->mWindow->_obj_rdr_window->addViewport(this->mActiveCamera[i], 2, 0.0, 0.5, 1.0, 0.5);
					this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue(0.0f, 0.6f, 0.0f));
				}
			}
			else if(this->mWindow->totalPlayers == 4)
			{
				if(viewPortsSetup == 0)
				{
					this->mWindow->_obj_viewport[i] = this->mWindow->_obj_rdr_window->addViewport(this->mActiveCamera[i], 0, 0.0, 0.0, 0.5, 0.5);
					this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue(0.6f, 0.0f, 0.0f));
				}
				else if(viewPortsSetup == 1)
				{
					this->mWindow->_obj_viewport[i] = this->mWindow->_obj_rdr_window->addViewport(this->mActiveCamera[i], 1, 0.5, 0.0, 0.5, 0.5);
					this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.6f));
				}
				else if(viewPortsSetup == 2)
				{
					this->mWindow->_obj_viewport[i] = this->mWindow->_obj_rdr_window->addViewport(this->mActiveCamera[i], 2, 0.0, 0.5, 0.5, 0.5);
					this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue(0.0f, 0.6f, 0.0f));
				}
				else if(viewPortsSetup == 3)
				{
					this->mWindow->_obj_viewport[i] = this->mWindow->_obj_rdr_window->addViewport(this->mActiveCamera[i], 3, 0.5, 0.5, 0.5, 0.5);
					this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue(6.0f, 0.6f, 6.0f));
				}
			}

			viewPortsSetup += 1;

			this->mActiveCamera[i]->setPosition(Ogre::Vector3(i * 1000,0,50));
			this->mActiveCamera[i]->lookAt(Ogre::Vector3(i * 1000,0,0));
			this->mActiveCamera[i]->setNearClipDistance(0.01);
			this->mActiveCamera[i]->setFarClipDistance(1000);
			this->mActiveCamera[i]->setAspectRatio(Ogre::Real(this->mWindow->_obj_viewport[i]->getActualWidth()) / Ogre::Real(this->mWindow->_obj_viewport[i]->getActualHeight()));
			this->mWindow->_obj_viewport[i]->setCamera(this->mActiveCamera[i]);

			this->vehicleDisplayNode[i] = this->mSceneManager->getRootSceneNode()->createChildSceneNode("VehicleDisplayNode_" + i);
			this->vehicleDisplayNode[i]->setPosition(Ogre::Vector3(i * 1000,0,0));

			this->vehicleDisplayNode[i]->yaw(Ogre::Degree(180.0));
			this->vehicleDisplayNode[i]->pitch(Ogre::Degree(-20.0));

			if(i == 0)
				this->vehicleDisplayNode[i]->attachObject(this->mAvailableVehicles_p1.back());
			else if(i == 1)
				this->vehicleDisplayNode[i]->attachObject(this->mAvailableVehicles_p2.back());
			else if(i == 2)
				this->vehicleDisplayNode[i]->attachObject(this->mAvailableVehicles_p3.back());
			else if(i == 3)
				this->vehicleDisplayNode[i]->attachObject(this->mAvailableVehicles_p4.back());

			this->cameraNode[i] = this->mSceneManager->getRootSceneNode()->createChildSceneNode("CameraNode_" + i);
			this->cameraNode[i]->attachObject(this->mActiveCamera[i]);

			this->overlayNode[i] = this->mSceneManager->getRootSceneNode()->createChildSceneNode("Overlay_" + i);

			this->mCamNode[i] = this->mActiveCamera[i]->getParentSceneNode();
			this->mCamRotate[i] = 0.13;
			this->mCamMovement[i] = 250;
			this->mCamDirection[i] = Ogre::Vector3::ZERO;
			this->mCamSpeed[i] = 0.0001f;
			this->mCamRotSpeed[i] = 0.01f;
		}
	}	

	Ogre::Light* light = this->mSceneManager->createLight("MainLight");
	light->setType(Ogre::Light::LT_POINT);
	light->setPosition(Ogre::Vector3(250, 150, 250));
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue::White);

	for(int j = 0; j < 4; j++)
	{
		if(this->mWindow->activePlayers[j])
		{
			this->userInstructions[j] = new Ogre::MovableText("INSTRUCTIONS_001", "Use the Left and Right Bumpers to select a vehicle.\nPress 'A' to be Ready.", "BlueHighway-64", 2.0f, Ogre::ColourValue::White);
			this->userInstructions[j]->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_BELOW);
			this->overlayNode[j]->attachObject(this->userInstructions[j]);
			this->overlayNode[j]->setPosition(Ogre::Vector3(j * 1000,-20,-20));
		}
	}
}

void VehicleSelect::Unload()
{

}

void VehicleSelect::Update(Ogre::Real elapsedTime)
{
	this->mFrameEvent.timeSinceLastFrame = elapsedTime;

	if(this->mShutdown)
	{
		this->GameShutdown();
		return;
	}

	if(this->mWindow->playersReady == this->mWindow->totalPlayers)
		this->ChangeScreen(this->FindScreen("DogFightingScreen"));

	for(int i = 0; i < 4; i++)
	{
		if(!this->mWindow->_obj_input->GetState(i).Disconnected)
		{
			if(this->mWindow->_obj_input->GetState(this->mWindow->controllingGamepadID).ButtonsSingle.B)
				this->ChangeScreen(this->FindScreen("MenuScreen"));

			if(this->mWindow->_obj_input->GetState(i).ButtonsSingle.A)
				if(this->mWindow->playerReady[i])
				{
					this->mWindow->playerReady[i] = false;
					this->userInstructions[i]->setCaption("Use the Left and Right Bumpers to select a vehicle.\nPress 'A' to be Ready.");
					this->mWindow->playersReady -= 1;
				}
				else
				{
					this->mWindow->playerReady[i] = true;
					this->userInstructions[i]->setCaption("PLAYER IS READY / Press 'A' to un-ready");
					this->mWindow->playersReady += 1;
				}

				if(this->mWindow->_obj_input->GetState(i).ButtonsSingle.LShoulder)
				{
					if(this->vehicleIndexID[i] - 1 < 0)
						this->vehicleIndexID[i] = this->maxVehicles - 1;
					else
						this->vehicleIndexID[i] -= 1;

					this->vehicleDisplayNode[i]->detachAllObjects();

					if(i == 0)
						this->vehicleDisplayNode[i]->attachObject(this->mAvailableVehicles_p1.at(this->vehicleIndexID[i]));
					else if(i == 1)
						this->vehicleDisplayNode[i]->attachObject(this->mAvailableVehicles_p2.at(this->vehicleIndexID[i]));
					else if(i == 2)
						this->vehicleDisplayNode[i]->attachObject(this->mAvailableVehicles_p3.at(this->vehicleIndexID[i]));
					else if(i == 3)
						this->vehicleDisplayNode[i]->attachObject(this->mAvailableVehicles_p4.at(this->vehicleIndexID[i]));

				}

				if(this->mWindow->_obj_input->GetState(i).ButtonsSingle.RShoulder)
				{
					if(this->vehicleIndexID[i] + 1 > (this->maxVehicles - 1))
						this->vehicleIndexID[i] = 0;
					else
						this->vehicleIndexID[i] += 1;

					this->vehicleDisplayNode[i]->detachAllObjects();
					
					if(i == 0)
						this->vehicleDisplayNode[i]->attachObject(this->mAvailableVehicles_p1.at(this->vehicleIndexID[i]));
					else if(i == 1)
						this->vehicleDisplayNode[i]->attachObject(this->mAvailableVehicles_p2.at(this->vehicleIndexID[i]));
					else if(i == 2)
						this->vehicleDisplayNode[i]->attachObject(this->mAvailableVehicles_p3.at(this->vehicleIndexID[i]));
					else if(i == 3)
						this->vehicleDisplayNode[i]->attachObject(this->mAvailableVehicles_p4.at(this->vehicleIndexID[i]));

				}

				this->vehicleDisplayNode[i]->yaw(Ogre::Degree(-this->mCamRotate[i] * -this->mWindow->_obj_input->GetState(i).RStick.X  * this->mFrameEvent.timeSinceLastFrame * this->mCamRotSpeed[i]), Ogre::Node::TS_WORLD);
				this->vehicleDisplayNode[i]->pitch(Ogre::Degree(-this->mCamRotate[i] * this->mWindow->_obj_input->GetState(i).RStick.Y  * this->mFrameEvent.timeSinceLastFrame * this->mCamRotSpeed[i]), Ogre::Node::TS_LOCAL);

				this->mCamDirection[i] = Ogre::Vector3::ZERO;
		}
	}
}