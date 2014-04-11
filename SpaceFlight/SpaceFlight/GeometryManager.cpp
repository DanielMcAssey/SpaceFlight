#include "StdAfx.h"
#include "GeometryManager.h"

GeometryManager::GeometryManager(VolClouds* _vc)
{
	this->mVolClouds = _vc;
	this->mCreated = false;
	this->mHeight = Ogre::Vector2();
	this->mRadius = 0;
	this->mAlpha = 0;
	this->mBeta = 0;
	this->mPhi = 0;
	this->mNumberOfBlocks = 0;
	this->mNa = 0;
	this->mNb = 0;
	this->mNc = 0;
	this->mA = 0;
	this->mB = 0;
	this->mC = 0;
	this->mWorldOffset = Ogre::Vector2(0,0);
}


GeometryManager::~GeometryManager(void)
{
}


void GeometryManager::Load(const Ogre::Vector2& Height, const float& Radius, const Ogre::Radian& Alpha, const Ogre::Radian& Beta, const int& NumberOfBlocks, const int& Na, const int& Nb, const int& Nc)
{
	this->mHeight = Height;
	this->mRadius = Radius;
	this->mAlpha = Alpha;
	this->mBeta = Beta;
	this->mPhi = Ogre::Math::TWO_PI / NumberOfBlocks;
	this->mNumberOfBlocks = NumberOfBlocks;
	this->mNa = Na;
	this->mNb = Nb;
	this->mNc = Nc;

	this->mSceneNode = this->mVolClouds->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	this->CreateGeometry();

	this->mCreated = true;
}


void GeometryManager::Update(Ogre::Real elapsedTime)
{
	if (!this->mCreated)
		return;

	this->mWorldOffset += this->mVolClouds->getWindDirectionV2() * this->mVolClouds->getWindSpeed() * elapsedTime;
}


void GeometryManager::CreateGeometry()
{
	this->mA = mHeight.y / Ogre::Math::Cos(Ogre::Math::PI/2-mBeta.valueRadians());
	this->mB = mHeight.y / Ogre::Math::Cos(Ogre::Math::PI/2-mAlpha.valueRadians());
	this->mC = mRadius;

	for (int k = 0; k < mNumberOfBlocks; k++)
	{
		this->mGeometryBlocks.push_back(new GeometryBlock(this->mVolClouds, this->mHeight.y, this->mAlpha, this->mBeta, this->mRadius, this->mPhi, this->mNa, this->mNb, this->mNc, this->mA, this->mB, this->mC, k));
		this->mGeometryBlocks.at(k)->Load();
		Ogre::SceneNode *sn = this->mSceneNode->createChildSceneNode();
		sn->attachObject(this->mGeometryBlocks.at(k)->getEntity());
	}
}

