#ifndef RACE_H
#define RACE_H

#include "MovableText.h"

class RaceScreen : public BaseScreen
{
public:
	RaceScreen(void);
	~RaceScreen(void);
	DECLARE_SCREENSTATE_CLASS(RaceScreen);

	void Load();
	void Unload();

	void Update(Ogre::Real elapsedTime);

	bool mShutdown;
protected:
	PlayerData players[4];
};

#endif // RACE_H