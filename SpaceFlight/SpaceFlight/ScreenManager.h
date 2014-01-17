#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "BaseScreen.h"

class ScreenManager : public ScreenListener
{
public:
	typedef struct
	{
		Ogre::String Name;
		BaseScreen *Screen;
	} ScreenData;

	ScreenManager(WindowData *_window);
	~ScreenManager();

	void StoreScreen(Ogre::String _screenName, BaseScreen *_screen);
	BaseScreen *FindScreen(Ogre::String _screenName);
	void LoadScreen(BaseScreen *_screen);
	void ChangeScreen(BaseScreen *_newScreen);
	bool PushScreen(BaseScreen* _newScreen);
	void PopScreen(void);
	void GameShutdown(void);
protected:
	void Initialize(BaseScreen *_newScreen);

	std::vector<BaseScreen*> mScreenStack;
	std::vector<ScreenData> mScreenData;
	WindowData *mWindow;
	bool mGameShutdown;
};

#endif // SCREENMANAGER_H