#ifndef BASESCREEN_H
#define BASESCREEN_H

#include "stdafx.h"
#include "ScreenListener.h"

class BaseScreen
{
public:
	static void CreateScreen(ScreenListener *_listener, const Ogre::String _screenName) {};
	void destroy(void) { delete this; }
	void Initialize(WindowData *_window) { this->mWindow = _window; }

	//Screen Load and Unload
	virtual void Load(void) = 0;
	virtual void Unload(void) = 0;
	
	//Pause un-pause
	virtual bool Pause(void) { return false; }
	virtual void Resume(void) {};
	virtual void Update(Ogre::Real elapsedTime) = 0;

protected:
	BaseScreen(void) {};
	virtual ~BaseScreen(void) {};

	ScreenListener *mListenerParent;
	WindowData *mWindow;

	Ogre::ColourValue _gpu_clear_colour;
	Ogre::FrameEvent mFrameEvent;
	Ogre::SceneManager* mSceneManager;

	Ogre::Camera* mActiveCamera[4];
	Ogre::Real mCamSpeed[4];
	Ogre::Real mCamRotSpeed[4];
	Ogre::Real mCamRotate[4];
	Ogre::Real mCamMovement[4];
	Ogre::SceneNode *mCamNode[4];
	Ogre::Vector3 mCamDirection[4];

	bool IsMultiplayer;

	BaseScreen *FindScreen(Ogre::String _screenName) { return this->mListenerParent->FindScreen(_screenName); }
	void ChangeScreen(BaseScreen *_newScreen) { return this->mListenerParent->ChangeScreen(_newScreen); }
	bool PushScreen(BaseScreen *_newScreen) { return this->mListenerParent->PushScreen(_newScreen); }
	void PopScreen(void) { this->mListenerParent->PopScreen(); }
	void GameShutdown(void) { this->mListenerParent->GameShutdown(); }
};

#define DECLARE_SCREENSTATE_CLASS(T) static void CreateScreen(ScreenListener *_listener,const Ogre::String _screenName)    {                        T *screenState=new T();                    screenState->mListenerParent=_listener;                _listener->StoreScreen(_screenName,screenState);        }

#endif // BASESCREEN_H