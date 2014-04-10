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
	srand(time(0)); //making it random number
	int RandomMax = rand()%20+10;
	int i = 0;
	//list of checkpoints

	while (i<RandomMax)
	{
		//get position of player
		//generate new checkpoint
			//check it not near player within 200 units so -100 & +100
			//check if no other spheres are within 200 units
					//sphere position will be given by the middle of sphere so they all have 100 radius
					//this will change according to how everything scales. 
			//if check fails generate new position
		//if check succeds add it to list
	}


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
	