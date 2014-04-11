#ifndef VOLCLOUD_H
#define VOLCLOUD_H


class VolClouds
{
public:
	VolClouds(Ogre::SceneManager* _sceneManager);
	~VolClouds(void);

	Ogre::Vector2 mHeight;
	float mRadius;

	void Load(const Ogre::Vector2& _Height, const float& _Radius);
	void Update(Ogre::Real elapsedTime);

	inline const bool& isCreated() const{return mCreated;}

	inline const Ogre::Radian& getWindDirection() const {return mWindDirection;}
	inline const Ogre::Vector2 getWindDirectionV2() const {return Ogre::Vector2(Ogre::Math::Cos(mWindDirection), Ogre::Math::Sin(mWindDirection));}

	inline void setWindSpeed(const float& WindSpeed){mWindSpeed = WindSpeed;}
	inline const float& getWindSpeed() const{return mWindSpeed;}

	inline void setSunDirection(const Ogre::Vector3& SunDirection){mSunDirection = SunDirection;}
	inline const Ogre::Vector3& getSunDirection() const{return mSunDirection;}

	void setSunColor(const Ogre::Vector3& SunColor);
	inline const Ogre::Vector3& getSunColor() const {return mSunColor;}

	void setAmbientColor(const Ogre::Vector3& AmbientColor);
	inline const Ogre::Vector3& getAmbientColor() const {return mAmbientColor;}

	void setLightResponse(const Ogre::Vector4& LightResponse);
	inline const Ogre::Vector4& getLightResponse() const {return mLightResponse;}

	void setAmbientFactors(const Ogre::Vector4& AmbientFactors);
	inline const Ogre::Vector4& getAmbientFactors() const {return mAmbientFactors;}

	inline void setGlobalOpacity(const Ogre::Real& GlobalOpacity) {mGlobalOpacity = GlobalOpacity;}
	inline const Ogre::Real& getGlobalOpacity() const {return mGlobalOpacity;}

	inline void setCloudFieldScale(const Ogre::Real& CloudFieldScale) { mCloudFieldScale = CloudFieldScale; }
	inline const Ogre::Real& getCloudFieldScale() const {return mCloudFieldScale;}

	inline void setNoiseScale(const Ogre::Real& NoiseScale){mNoiseScale = NoiseScale;}
	inline const Ogre::Real& getNoiseScale() const {return mNoiseScale;}

	void setWheater(const float& Humidity, const float& AverageCloudsSize, const bool& DelayedResponse);
	inline const Ogre::Vector2& getWheater() const {return mWheater;}

	void setVisible(const bool& visible);
	inline const bool& isVisible() const {return mVisible;}
private:
	bool mCreated;
	Ogre::Radian mWindDirection;
	float mWindSpeed;
	Ogre::Vector2 mWheater;
	bool mDelayedResponse;
	Ogre::Vector3 mSunDirection;
	Ogre::Vector3 mSunColor;
	Ogre::Vector3 mAmbientColor;
	Ogre::Vector4 mLightResponse;
	Ogre::Vector4 mAmbientFactors;

	float mGlobalOpacity;
	float mCloudFieldScale;
	float mNoiseScale;
	bool mVisible;

	Ogre::SceneManager* mSceneManager;
	Ogre::MaterialPtr mVolCloudsMaterial;
};

#endif // VOLCLOUD_H

