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
	Ogre::SceneNode* mGameNode;
	Ogre::SceneNode* mLevelNode;
	LevelManager* mLevelManager;
};

#endif // DOGFIGHT_H