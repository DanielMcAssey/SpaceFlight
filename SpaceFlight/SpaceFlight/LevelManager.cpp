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

void LevelManager::LoadLevel(bool IsMultiplayer, Ogre::SceneNode* sceneNode)
{
	this->mNode = sceneNode->createChildSceneNode("level"); //Create the level manager node.
	int i = this->mWindow->controllingGamepadID;
	int max = this->mWindow->controllingGamepadID + 1;

	if(IsMultiplayer)
	{
		i = 0;
		max = 4;
	}

	for(i = i; i < max; i++)
	{
		if(this->mWindow->activePlayers[i])
		{
			this->mPlayers[i] = new PlayerObject(this->mSceneManager, this->mWindow, this->mNode, i);
			this->mWindow->_obj_viewport[i]->setCamera(this->mPlayers[i]->LoadCamera(i));
			this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 0.0f));
		}
	}
}

void LevelManager::UnloadLevel()
{

}

void LevelManager::Update(Ogre::Real elapsedTime)
{
	for(int i = 0; i < 4; i++)
	{
		if(this->mPlayers[i] != nullptr)
		{
			this->mPlayers[i]->Update(elapsedTime);
		}
	}
}

void LevelManager::ResetPlayerCameras()
{
	for(int i = 0; i < 4; i++)
	{
		if(this->mPlayers[i] != nullptr)
		{
			//Reset Camera
		}
	}
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
