#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "MovableText.h"

class GameScreen : public BaseScreen
{
public:
	GameScreen(void);
	~GameScreen(void);

	DECLARE_SCREENSTATE_CLASS(GameScreen);

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

#endif // GAMESCREEN_H