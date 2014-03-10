#ifndef TARGETPRACTICE_H
#define TARGETPRACTICE_H

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
	PlayerData players[4];
};

#endif // TARGETPRACTICE_H