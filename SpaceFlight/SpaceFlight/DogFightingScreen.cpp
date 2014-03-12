#include "StdAfx.h"
#include "DogFightingScreen.h"

using namespace std;
using namespace Ogre;

DogFightingScreen::DogFightingScreen(void)
{
}


DogFightingScreen::~DogFightingScreen(void)
{
}

void DogFightingScreen::Load()
{
	this->mSceneManager = this->mWindow->_obj_root->createSceneManager(ST_GENERIC, "DogFightManager");
	this->mSceneManager->setAmbientLight(Ogre::ColourValue(0.2f, 0.2f, 0.2f));

	int i = this->mWindow->controllingGamepadID;
	int max = this->mWindow->controllingGamepadID + 1;

	if(this->IsMultiplayer)
	{
		i = 0;
		max = 4;
	}

	for(i = i; i < max; i++)
	{
		if(this->mWindow->activePlayers[i])
		{
			this->mActiveCamera[i] = this->mSceneManager->createCamera("PlayerCam_" + i);
			this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 0.0f));

			this->mActiveCamera[i]->setPosition(Ogre::Vector3(i * 1000,0,50));
			this->mActiveCamera[i]->lookAt(Ogre::Vector3(i * 1000,0,0));
			this->mActiveCamera[i]->setNearClipDistance(0.01);
			this->mActiveCamera[i]->setFarClipDistance(1000);
			this->mActiveCamera[i]->setAspectRatio(Ogre::Real(this->mWindow->_obj_viewport[i]->getActualWidth()) / Ogre::Real(this->mWindow->_obj_viewport[i]->getActualHeight()));
			this->mWindow->_obj_viewport[i]->setCamera(this->mActiveCamera[i]);
		}
	}
}

void DogFightingScreen::Unload()
{

}

void DogFightingScreen::Update(Ogre::Real elapsedTime)
{

}