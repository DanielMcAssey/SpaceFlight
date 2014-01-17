#ifndef SCREENLISTENER_H
#define SCREENLISTENER_H

#include "stdafx.h"

class BaseScreen;

class ScreenListener
{
public:
	ScreenListener(void) {};
	virtual ~ScreenListener(void) {};
	virtual void StoreScreen(Ogre::String _screenName, BaseScreen *_screen) = 0;
	virtual BaseScreen *FindScreen(Ogre::String _screenName) = 0;
	virtual void ChangeScreen(BaseScreen *_newScreen) = 0;
	virtual bool PushScreen(BaseScreen* _newScreen) = 0;
	virtual void PopScreen() = 0;
	virtual void GameShutdown() = 0;
};

#endif // SCREENLISTENER_H