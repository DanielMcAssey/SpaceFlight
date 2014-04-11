#include "StdAfx.h"
#include "DogFightingScreen.h"

DogFightingScreen::DogFightingScreen(void)
{
	this->mShutdown = false;
}


DogFightingScreen::~DogFightingScreen(void)
{
	this->Unload();
}


void DogFightingScreen::Load()
{
	this->mSceneManager = this->mWindow->_obj_root->createSceneManager(ST_GENERIC, "DogFightManager");
	this->mSceneManager->setAmbientLight(Ogre::ColourValue(0.2f, 0.2f, 0.2f));
	this->mGameNode = this->mSceneManager->getRootSceneNode()->createChildSceneNode("DogFightScene");
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
}


void DogFightingScreen::Unload()
{
	if(this->mLevelManager != nullptr)
	{
		this->mLevelManager->UnloadLevel();
		delete this->mLevelManager;
	}

}


void DogFightingScreen::Update(Ogre::Real elapsedTime)
{
	this->mFrameEvent.timeSinceLastFrame = elapsedTime;
	if(this->mShutdown)
	{
		this->GameShutdown();
		return;
	}
	if(this->mLevelManager != nullptr)
		this->mLevelManager->Update(elapsedTime);


}