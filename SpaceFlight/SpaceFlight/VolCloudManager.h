#ifndef VOLCLOUD_MANAGER_H
#define VOLCLOUD_MANAGER_H

#include "VolClouds.h"

class VolCloudManager
{
public:
	VolCloudManager(Ogre::SceneManager *_sceneManager);
	~VolCloudManager(void);

	void Load(const Ogre::Real& radius = -1);
	void Update(Ogre::Real elapsedTime);

	inline void setHeight(const Ogre::Vector2& Height){ mHeight = Height;}
	inline const Ogre::Vector2& getHeight() const {return mHeight;}
	inline void setWindSpeed(const Ogre::Real& WindSpeed) {mWindSpeed = WindSpeed; updateWindSpeedConfig();}
	inline const Ogre::Real& getWindSpeed() const{return mWindSpeed;}
	inline VolClouds* getVClouds(){return mVolClouds;}
	inline const bool& isCreated() const{return mCreated;}
protected:
	void updateWindSpeedConfig(void);
private:
	Ogre::SceneManager* mSceneManager;
	VolClouds* mVolClouds;
	Ogre::Vector2 mHeight;
	Ogre::Real mWindSpeed;
	bool mCreated;
};

#endif // VOLCLOUD_MANAGER_H

