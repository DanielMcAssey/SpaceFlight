#ifndef TARGETPRACTICE_H
#define TARGETPRACTICE_H

#include "MovableText.h"

class TargetPracticeScreen : public BaseScreen
{
public:
	TargetPracticeScreen(void);
	~TargetPracticeScreen(void);

	DECLARE_SCREENSTATE_CLASS(TargetPracticeScreen);

	void Load();
	void Unload();
	void Update(Ogre::Real elapsedTime);
	bool mShutdown;
protected:
	Ogre::SceneNode* mGameNode;
	Ogre::SceneNode* mLevelNode;
	LevelManager* mLevelManager;
};

#endif // TARGETPRACTICE_H