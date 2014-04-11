#include "StdAfx.h"
#include "VolClouds.h"


VolClouds::VolClouds(Ogre::SceneManager* _sceneManager)
{
	this->mSceneManager = _sceneManager;
	this->mCreated = false;
	this->mWindDirection = Ogre::Degree(0);
	this->mWindSpeed = 80.0f;
	this->mWeather = Ogre::Vector2(0.5f, 1.0f);
	this->mSunDirection = Ogre::Vector3(0,-1,0);
	this->mSunColour = Ogre::Vector3(1,1,1);
	this->mAmbientColour = Ogre::Vector3(0.63f,0.63f,0.7f);
	this->mLightResponse = Ogre::Vector4(0.25f,0.2f,1.0f,0.1f);
	this->mAmbientFactors = Ogre::Vector4(0.45f,0.3f,0.6f,1);
	this->mNoiseScale = 4.2f;
	this->mVisible = true;
	this->mGeometryManager = new GeometryManager(this);
	this->mVolCloudsMaterial = Ogre::MeshPtr();
}


VolClouds::~VolClouds(void)
{
}


void VolClouds::Load(const Ogre::Vector2& _Height, const float& _Radius)
{
	this->mHeight = _Height;
	this->mRadius = _Radius;

	this->mVolCloudsMaterial = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("VolClouds", "Content"));

	if(this->mVolCloudsMaterial.isNull())
		return;

	this->mGeometryManager->Load(this->mHeight, this->mRadius, Ogre::Degree(12), Ogre::Degree(40), 12, 10, 8, 6);
	this->mGeometryManager->getSceneNode()->setVisible(mVisible);

	this->mVolCloudsMaterial->getTechnique(0)->getPass(0)->getVertexProgramParameters()->setNamedConstant("uRadius", this->mRadius);
	this->mCreated = true;
	this->setSunColour(this->mSunColour);
	this->setAmbientColour(this->mAmbientColour);
	this->setLightResponse(this->mLightResponse);
	this->setAmbientFactors(this->mAmbientFactors);
	this->setWheater(this->mWeather.x, this->mWeather.y, this->mDelayedResponse);
}


void VolClouds::Update(Ogre::Real elapsedTime)
{
	if(!this->mCreated)
		return;

	this->mGeometryManager->Update(elapsedTime);
	this->mVolCloudsMaterial->getTechnique(0)->getPass(0)->getFragmentProgramParameters()->setNamedConstant("uInterpolation", elapsedTime);
	this->mVolCloudsMaterial->getTechnique(0)->getPass(0)->getFragmentProgramParameters()->setNamedConstant("uSunDirection", -this->mSunDirection);
}


void VolClouds::setSunColour(const Ogre::Vector3& SunColour)
{
	this->mSunColour = SunColour;

	if (!this->mCreated)
		return;

	this->mVolCloudsMaterial->getTechnique(0)->getPass(0)->getFragmentProgramParameters()->setNamedConstant("uSunColour", this->mSunColour);
}


void VolClouds::setAmbientColour(const Ogre::Vector3& AmbientColour)
{
	this->mAmbientColour = AmbientColour;

	if (!this->mCreated)
		return;

	this->mVolCloudsMaterial->getTechnique(0)->getPass(0)->getFragmentProgramParameters()->setNamedConstant("uAmbientColour", this->mAmbientColour);
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
	this->mWeather = Ogre::Vector2(Humidity, AverageCloudsSize);
	this->mDelayedResponse = DelayedResponse;

	if (!this->mCreated)
		return;
}

