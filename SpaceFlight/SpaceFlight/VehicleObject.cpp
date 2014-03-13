#include "StdAfx.h"
#include "VehicleObject.h"


VehicleObject::VehicleObject(Ogre::String meshFile, int playerID)
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
}