#include "StdAfx.h"
#include "RaceScreen.h"
#include <random>
#include <time.h>

RaceScreen::RaceScreen(void)
{
	this->mShutdown = false;
}


RaceScreen::~RaceScreen(void)
{
	this->Unload();
}


void RaceScreen::Load()
{
	this->mSceneManager = this->mWindow->_obj_root->createSceneManager(ST_GENERIC, "RaceManager");
	this->mSceneManager->setAmbientLight(Ogre::ColourValue(0.2f, 0.2f, 0.2f));
	this->mGameNode = this->mSceneManager->getRootSceneNode()->createChildSceneNode("RaceScene");
	this->mLevelManager = new LevelManager(this->mWindow, this->mSceneManager);

	if(this->mLevelManager != nullptr)
	{
		this->mLevelManager->LoadLevel(this->IsMultiplayer, this->mGameNode);
		this->mLevelNode = this->mLevelManager->GetLevelNode();
	}
	else
	{
		throw new Exception(Ogre::Exception::ERR_RT_ASSERTION_FAILED, "LevelManager was not created, no level could be loaded.", "LevelManager");
	}

	//Load Stuff
	CreateCheckpoints();
	//load checkpoints spheres
	//load hud

}

void RaceScreen::Unload()
{
	if(this->mLevelManager != nullptr)
	{
		this->mLevelManager->UnloadLevel();
		delete this->mLevelManager;
	}

	//Unload Stuff
}

void RaceScreen::Update(Ogre::Real elapsedTime)
{
	this->mFrameEvent.timeSinceLastFrame = elapsedTime;
	if(this->mShutdown)
	{
		this->GameShutdown();
		return;
	}
	if(this->mLevelManager != nullptr)
		this->mLevelManager->Update(elapsedTime);

	//Update Stuff
}

void RaceScreen::CreateCheckpoints()
{
	//srand(time(0)); //making it random number
	//int RandomMax = rand()%20+10;
	//int i = 0;



	//list of checkpoints

	mCheckpoints = this->mSceneManager->getRootSceneNode()->createChildSceneNode("StaticNode");

	Entity* mTempEntity = nullptr;

	//minimum height has to be greater than 200

	//x -6000
	//x +17000
	//z +6000
	//z -17000

	this->mTempNode = mGameNode->createChildSceneNode("Checkpoints");
	Ogre::String mNodeName = "CheckpointNode";
	mNodeName.append("_").append(Ogre::StringConverter::toString(1));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	Ogre::String mEntityName = "Checkpoint";
	mEntityName.append("_").append(Ogre::StringConverter::toString(1));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(2500,735,100);

	mNodeName.append("_").append(Ogre::StringConverter::toString(2));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	mEntityName.append("_").append(Ogre::StringConverter::toString(2));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(400,952,65);

	mNodeName.append("_").append(Ogre::StringConverter::toString(3));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	mEntityName.append("_").append(Ogre::StringConverter::toString(3));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(-400,498,-100);

	mNodeName.append("_").append(Ogre::StringConverter::toString(4));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	mEntityName.append("_").append(Ogre::StringConverter::toString(4));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(-896,1789,-894);

	mNodeName.append("_").append(Ogre::StringConverter::toString(5));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	mEntityName.append("_").append(Ogre::StringConverter::toString(5));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(-1834,2000,957);

	mNodeName.append("_").append(Ogre::StringConverter::toString(6));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	mEntityName.append("_").append(Ogre::StringConverter::toString(6));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(-1834,2000,957);

	mNodeName.append("_").append(Ogre::StringConverter::toString(7));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	mEntityName.append("_").append(Ogre::StringConverter::toString(7));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(2000,198,-1943);

	mNodeName.append("_").append(Ogre::StringConverter::toString(8));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	mEntityName.append("_").append(Ogre::StringConverter::toString(8));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(-1100,1842,1868);

	mNodeName.append("_").append(Ogre::StringConverter::toString(9));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	mEntityName.append("_").append(Ogre::StringConverter::toString(9));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(-1847,234,1023);

	mNodeName.append("_").append(Ogre::StringConverter::toString(10));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	mEntityName.append("_").append(Ogre::StringConverter::toString(10));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(1285,578,-964);

	mNodeName.append("_").append(Ogre::StringConverter::toString(11));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	mEntityName.append("_").append(Ogre::StringConverter::toString(11));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(10000,2000,-10000);

	mNodeName.append("_").append(Ogre::StringConverter::toString(12));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	mEntityName.append("_").append(Ogre::StringConverter::toString(12));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(-5468,569,2435);

	mNodeName.append("_").append(Ogre::StringConverter::toString(13));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	mEntityName.append("_").append(Ogre::StringConverter::toString(13));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(-5788,335,-14523);

	mNodeName.append("_").append(Ogre::StringConverter::toString(14));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	mEntityName.append("_").append(Ogre::StringConverter::toString(14));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(-3764,789,-6789);

	mNodeName.append("_").append(Ogre::StringConverter::toString(15));
	mTempNode = this->mCheckpoints->createChildSceneNode(mNodeName);
	mEntityName.append("_").append(Ogre::StringConverter::toString(15));
	mTempEntity = this->mSceneManager->createEntity(mEntityName,SceneManager::PT_SPHERE);
	mTempEntity->setMaterialName("Examples/BumpyMetal");
	mTempNode->attachObject(mTempEntity);
	mTempNode->setPosition(12986,1478,+4523);






	//Entity* tmpEntity = this->mSceneManager->createEntity("Sphere", SceneManager::PT_SPHERE);
	//tmpEntity->

	//while (i<RandomMax)
	//{
	//	
	//	//get position of player
	//	//generate new checkpoint
	//		//check it not near player within 200 units so -100 & +100
	//		//check if no other spheres are within 200 units
	//				//sphere position will be given by the middle of sphere so they all have 100 radius
	//				//this will change according to how everything scales. 
	//		//if check fails generate new position
	//	//if check succeds add it to list
	//}


}

// functions to do
	//hud
	//	timer
	//	lap counter
	//	position
	//  minimap
	//  health
	//  weapon counters
//
	//lapcontrol/racecontrol system
	//	check whos in lead
	//	check which checkpoints each player needs to go to
	