#include "StdAfx.h"
#include "BulletManager.h"

BulletManager::BulletManager(PlayerObject *_player, Ogre::SceneManager *_sceneManager)
{
	this->mPlayer = _player;
	this->mSceneManager = _sceneManager;
	this->mBulletsBillboard = this->mSceneManager->createBillboardSet();
}


BulletManager::~BulletManager(void)
{
}


void BulletManager::Update(Ogre::Real elapsedTime)
{

}


void BulletManager::CreateBullet(Ogre::Vector3 &_startPos, Ogre::Vector3 &_direction)
{

}


void BulletManager::CreateMissile(Ogre::Vector3 &_startPos, Ogre::Vector3 &_direction)
{

}

