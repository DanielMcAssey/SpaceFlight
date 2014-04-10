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
			this->mPlayers[i]->SetVehicle(this->mWindow->playerData[i]->_player_vehicle);
			this->mPlayers[i]->SetPosition(Ogre::Vector3(0.0f, 0.0f, -100.0f));
			this->mWindow->_obj_viewport[i]->setCamera(this->mPlayers[i]->LoadCamera(i));
			this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 0.0f)); //Reset BG Colour
		}
	}

	//Test Entity
	Entity* tmpEntity = this->mSceneManager->createEntity("Sphere", SceneManager::PT_SPHERE);
	tmpEntity->setMaterialName("Examples/BumpyMetal");
	this->mNode->attachObject(tmpEntity);
}


void LevelManager::UnloadLevel()
{

}


void LevelManager::Update(Ogre::Real elapsedTime)
{
	for(int i = 0; i < 4; i++)
	{
		if(this->mWindow->activePlayers[i])
		{
			this->mPlayers[i]->Update(elapsedTime);

			if(this->mPlayers[i]->GetHealth() <= 0.0f)
			{
				//Kill
			}
		}
	}
}


void LevelManager::GenerateTerrain()
{
	//generate terrain

}


#pragma region Helper_Functions

void LevelManager::ResetPlayerCameras()
{
	for(int i = 0; i < 4; i++)
	{
		if(this->mPlayers[i] != nullptr)
		{
			this->mPlayers[i]->ResetCamera();
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


Ogre::SceneNode* LevelManager::GetLevelNode()
{
	if(this->mNode != nullptr)
		return this->mNode;
}
#pragma endregion