#include "StdAfx.h"
#include "ScreenManager.h"
#include <OgreWindowEventUtilities.h>

using namespace std;
using namespace Ogre;

ScreenManager::ScreenManager(WindowData *_window)
{
	this->mWindow = _window;
	this->mGameShutdown = false;
}

ScreenManager::~ScreenManager(void)
{
	while(!this->mScreenStack.empty())
	{
		this->mScreenStack.back()->Unload();
		this->mScreenStack.pop_back();
	}

	while(!this->mScreenData.empty())
	{
		this->mScreenData.back().Screen->destroy();
		this->mScreenData.pop_back();
	}
}

void ScreenManager::StoreScreen(String _screenName, BaseScreen *_screen)
{
	ScreenData _tmpData;
	_tmpData.Name = _screenName;
	_tmpData.Screen = _screen;
	_tmpData.Screen->Initialize(this->mWindow);
	this->mScreenData.push_back(_tmpData);
}

BaseScreen *ScreenManager::FindScreen(String _screenName)
{
	std::vector<ScreenData>::iterator i;

	for(i = mScreenData.begin(); i != mScreenData.end(); i++)
		if(i->Name == _screenName)
			return i->Screen;

	return 0;
}

void ScreenManager::LoadScreen(BaseScreen *_screen)
{
	this->ChangeScreen(_screen);

	Ogre::Real timeSinceLastFrame = 1;
	Ogre::Real startTime = 0;

	while(!mGameShutdown)
	{
		if(this->mWindow->_obj_rdr_window->isClosed())
			this->GameShutdown();

		Ogre::WindowEventUtilities::messagePump();

		if(this->mWindow->_obj_rdr_window->isActive())
		{
			startTime = this->mWindow->_obj_timer->getMillisecondsCPU();
			this->mWindow->_obj_input->Update();

			if(!this->mWindow->controllingGamepadSet)
				for(int i = 0; i < 4; i++)
				{
					if(!this->mWindow->_obj_input->GetState(i).Disconnected && this->mWindow->_obj_input->GetState(i).ButtonsSingle.Start)
					{
						this->mWindow->controllingGamepadID = i;
						this->mWindow->controllingGamepadSet = true;
					}
				}
			else
				if(this->mWindow->_obj_input->GetState(this->mWindow->controllingGamepadID).Disconnected)
					this->mWindow->controllingGamepadSet = false;

			this->mScreenStack.back()->Update(timeSinceLastFrame);
			this->mWindow->_obj_root->renderOneFrame();
			timeSinceLastFrame = this->mWindow->_obj_timer->getMillisecondsCPU() - startTime;
		}
		else
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			Sleep(1000);
#else
			sleep(1);
#endif
		}
	}
}

void ScreenManager::ChangeScreen(BaseScreen* _newScreen)
{
	if(!this->mScreenStack.empty())
	{
		this->mScreenStack.back()->Unload();
		this->mScreenStack.pop_back();
	}

	this->mScreenStack.push_back(_newScreen);
	this->Initialize(_newScreen);
	this->mScreenStack.back()->Load();
}

bool ScreenManager::PushScreen(BaseScreen* _newScreen)
{
	if(!this->mScreenStack.empty())
		if(!this->mScreenStack.back()->Pause())
			return false;

	this->mScreenStack.push_back(_newScreen);
	this->Initialize(_newScreen);
	this->mScreenStack.back()->Load();

	return true;
}

void ScreenManager::PopScreen()
{
	if(!this->mScreenStack.empty())
	{
		this->mScreenStack.back()->Unload();
		this->mScreenStack.pop_back();
	}

	if(!this->mScreenStack.empty())
	{
		this->Initialize(this->mScreenStack.back());
		this->mScreenStack.back()->Resume();
	}
	else
		this->GameShutdown();
}

void ScreenManager::GameShutdown()
{
	this->mGameShutdown = true;
}

void ScreenManager::Initialize(BaseScreen *_newScreen)
{
	this->mWindow->_obj_rdr_window->resetStatistics();
}