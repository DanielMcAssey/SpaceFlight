#include "StdAfx.h"
#include "RaceScreen.h"


RaceScreen::RaceScreen(void)
{
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
	}
	else
	{
		throw new Exception(Ogre::Exception::ERR_RT_ASSERTION_FAILED, "LevelManager was not created, no level could be loaded.", "LevelManager");
	}

	//Load Stuff
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
	if(this->mLevelManager != nullptr)
		this->mLevelManager->Update(elapsedTime);

	//Update Stuff
}