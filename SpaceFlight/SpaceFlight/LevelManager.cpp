#include "StdAfx.h"
#include "LevelManager.h"


LevelManager::LevelManager(WindowData* window, Ogre::SceneManager* sceneManager)
{
	this->mWindow = window;
	this->mSceneManager = sceneManager;
}


LevelManager::~LevelManager(void)
{

}

void LevelManager::LoadLevel()
{

}

void LevelManager::ResetPlayerCameras()
{

}

PlayerObject* LevelManager::GetPlayer(int id)
{
	if(id < 4)
	{
		if(this->mPlayers[id] != nullptr)
		{
			return this->mPlayers[id];
		}
	}

	return nullptr;
}
