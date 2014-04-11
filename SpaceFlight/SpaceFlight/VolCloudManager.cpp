#include "StdAfx.h"
#include "VolCloudManager.h"


VolCloudManager::VolCloudManager(Ogre::SceneManager *_sceneManager)
{
	this->mSceneManager = _sceneManager;
	this->mVolClouds = new VolClouds(this->mSceneManager);
}


VolCloudManager::~VolCloudManager(void)
{
}


void VolCloudManager::Load(const Ogre::Real& radius)
{
	if(this->mCreated)
		return;

	Ogre::Real selectedRadius = radius < 0 ? this->mVolClouds->mRadius : radius;
	Ogre::Vector2 defaultheight = Ogre::Vector2(selectedRadius*0.025f, selectedRadius*0.1f); 
	Ogre::Vector2 height = (this->mHeight.x == -1 || this->mHeight.y == -1) ? defaultheight : this->mHeight;

	this->mVolClouds->Load(height, selectedRadius);
	this->mCreated = true;
	this->updateWindSpeedConfig();
}


void VolCloudManager::Update(Ogre::Real elapsedTime)
{
	if(!this->mCreated)
		return;

	this->mVolClouds->Update(elapsedTime);
}


void VolCloudManager::updateWindSpeedConfig(void)
{
	if(!this->mCreated)
		return;

	this->mVolClouds->setWindSpeed(this->mWindSpeed);
}

