#include "stdafx.h"

typedef struct PlayerData
{
	Ogre::Entity*		_player_vehicle;
};

typedef struct WindowData
{
	Ogre::Root*			_obj_root;						//Pointer to the root of our scene graph
	Ogre::RenderWindow* _obj_rdr_window;				//Pointer to our application's render window
	Ogre::String		_fname_cfg_res;					//Stores the File Name of our Resources Configurations
	Ogre::String		_fname_cfg_plugins;				//Stores the File Name of our Plugin Configurations
	Ogre::String		_prop_app_windowname;			//Property to store the Application Window Name
	Ogre::Timer*		_obj_timer;						//Timer for frame updates.
	Ogre::Viewport*		_obj_viewport[4];					//Viewport
	Ogre::Log*			_obj_log;						//Log
	InputManager*		_obj_input;						//XInput Controller

	int controllingGamepadID;							//Controlling Gamepad ID
	bool controllingGamepadSet;							//If controlling gamepad has been set
	bool activePlayers[4];
	bool playerReady[4];
	int totalPlayers;
	int playersReady;
};