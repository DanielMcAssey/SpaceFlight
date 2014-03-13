#include "StdAfx.h"
#include "TargetPracticeScreen.h"


TargetPracticeScreen::TargetPracticeScreen(void)
{
	this->mShutdown = false;
}


TargetPracticeScreen::~TargetPracticeScreen(void)
{
	this->Unload();
}


void TargetPracticeScreen::Load()
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
}

void TargetPracticeScreen::Unload()
{
	if(this->mLevelManager != nullptr)
	{
		this->mLevelManager->UnloadLevel();
		delete this->mLevelManager;
	}

	//Unload Stuff
}

void TargetPracticeScreen::Update(Ogre::Real elapsedTime)
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