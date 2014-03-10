#ifndef DOGFIGHT_H
#define DOGFIGHT_H

#include "MovableText.h"

class DogFightingScreen : public BaseScreen
{
public:
	DogFightingScreen(void);
	~DogFightingScreen(void);

	DECLARE_SCREENSTATE_CLASS(DogFightingScreen);

	void Load();
	void Unload();

	void Update(Ogre::Real elapsedTime);

	bool mShutdown;
protected:
	PlayerData players[4];
	Ogre::SceneNode* vehicleDisplayNode[4];
	Ogre::SceneNode* cameraNode[4];
	Ogre::SceneNode* overlayNode[4];
	Ogre::MovableText* hudData[4];
};

#endif // DOGFIGHT_H