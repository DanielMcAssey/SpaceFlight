#include "StdAfx.h"
#include "VehicleObject.h"


VehicleObject::VehicleObject(Ogre::String meshFile, int vehicleIndex, int playerID)
{
	this->mMeshFile =  meshFile;
	this->mPlayerID = playerID;
}


VehicleObject::~VehicleObject(void)
{
}


void VehicleObject::LoadVehicle(Ogre::SceneManager* sceneManager, Ogre::SceneNode* sceneNode)
{
	this->mModel = sceneManager->createEntity("player_vehicle_" + this->mPlayerID, this->mMeshFile);
	this->mNode = sceneNode->createChildSceneNode("vehicle_node_" + this->mPlayerID);
	this->mNode->attachObject(this->mModel);

	this->mStats = new VehicleStats();
	switch(this->mVehicleIndex)
	{
	case 0: // F15_Active
		this->mStats->Acceleration = 1.0f;
		this->mStats->Speed = 1.0f;
		this->mStats->Handling = 0.8f;
		this->mStats->Armor = 1.5f;
		this->mStats->GunRange = 0.0f;
		this->mStats->MissileRange = 0.0f;
		break;
	case 1: // F-35_Lightning
		this->mStats->Acceleration = 0.8f;
		this->mStats->Speed = 0.65f;
		this->mStats->Handling = 0.7f;
		this->mStats->Armor = 1.25f;
		this->mStats->GunRange = 0.0f;
		this->mStats->MissileRange = 0.0f;
		break;
	case 2: // F-117_Nighthawk
		this->mStats->Acceleration = 0.75f;
		this->mStats->Speed = 0.5f;
		this->mStats->Handling = 0.5f;
		this->mStats->Armor = 1.0f;
		this->mStats->GunRange = 0.0f;
		this->mStats->MissileRange = 0.0f;
		break;
	case 3: // Su32
		this->mStats->Acceleration = 0.5f;
		this->mStats->Speed = 0.80f;
		this->mStats->Handling = 0.6f;
		this->mStats->Armor = 1.25f;
		this->mStats->GunRange = 0.0f;
		this->mStats->MissileRange = 0.0f;
		break;
	}
}


VehicleStats* VehicleObject::GetStats()
{
	if(this->mStats != nullptr)
		return this->mStats;
}

