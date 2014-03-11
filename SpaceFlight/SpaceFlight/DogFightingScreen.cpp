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
}

void DogFightingScreen::Unload()
{

}

void DogFightingScreen::Update(Ogre::Real elapsedTime)
{

}