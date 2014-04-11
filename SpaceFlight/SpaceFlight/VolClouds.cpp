#include "StdAfx.h"
#include "VolClouds.h"


VolClouds::VolClouds(Ogre::SceneManager* _sceneManager)
{
	this->mSceneManager = _sceneManager;
}


VolClouds::~VolClouds(void)
{
}


void VolClouds::Load(const Ogre::Vector2& _Height, const float& _Radius)
{
	this->mHeight = _Height;
	this->mRadius = _Radius;

	this->mVolCloudsMaterial = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("ExtClouds"));

	if(this->mVolCloudsMaterial.isNull())
		return;

	this->mVolCloudsMaterial->getTechnique(0)->getPass(0)->getVertexProgramParameters()->setNamedConstant("uRadius", this->mRadius);
	this->mCreated = true;
	this->setSunColor(this->mSunColor);
	this->setAmbientColor(this->mAmbientColor);
	this->setLightResponse(this->mLightResponse);
	this->setAmbientFactors(this->mAmbientFactors);
	this->setWheater(this->mWheater.x, this->mWheater.y, this->mDelayedResponse);
}


void VolClouds::Update(Ogre::Real elapsedTime)
{
	if(!this->mCreated)
		return;

	this->mVolCloudsMaterial->getTechnique(0)->getPass(0)->getFragmentProgramParameters()->setNamedConstant("uInterpolation", elapsedTime);
	this->mVolCloudsMaterial->getTechnique(0)->getPass(0)->getFragmentProgramParameters()->setNamedConstant("uSunDirection", -this->mSunDirection);
}


void VolClouds::setSunColor(const Ogre::Vector3& SunColor)
{
	this->mSunColor = SunColor;

	if (!this->mCreated)
		return;

	this->mVolCloudsMaterial->getTechnique(0)->getPass(0)->getFragmentProgramParameters()->setNamedConstant("uSunColor", this->mSunColor);
}


void VolClouds::setAmbientColor(const Ogre::Vector3& AmbientColor)
{
	this->mAmbientColor = AmbientColor;

	if (!this->mCreated)
		return;

	this->mVolCloudsMaterial->getTechnique(0)->getPass(0)->getFragmentProgramParameters()->setNamedConstant("uAmbientColor", this->mAmbientColor);
}


void VolClouds::setLightResponse(const Ogre::Vector4& LightResponse)
{
	this->mLightResponse = LightResponse;

	if (!this->mCreated)
		return;

	this->mVolCloudsMaterial->getTechnique(0)->getPass(0)->getFragmentProgramParameters()->setNamedConstant("uLightResponse", this->mLightResponse);
}


void VolClouds::setAmbientFactors(const Ogre::Vector4& AmbientFactors)
{
	this->mAmbientFactors = AmbientFactors;

	if (!this->mCreated)
		return;

	this->mVolCloudsMaterial->getTechnique(0)->getPass(0)->getFragmentProgramParameters()->setNamedConstant("uAmbientFactors", this->mAmbientFactors);
}


void VolClouds::setWheater(const float& Humidity, const float& AverageCloudsSize, const bool& DelayedResponse)
{
	this->mWheater = Ogre::Vector2(Humidity, AverageCloudsSize);
	this->mDelayedResponse = DelayedResponse;

	if (!this->mCreated)
		return;
}

