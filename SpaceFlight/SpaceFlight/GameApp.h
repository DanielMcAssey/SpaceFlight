#ifndef _GAME_APP_H
#define _GAME_APP_H

#include "App.h"

class GameApp : public App
{
public:
	GameApp(void);
	virtual ~GameApp(void);
protected:
	//----------INHERITABLE METHODS---------------------------------------
	virtual void initSceneGraph(void);												    //Our customised version of our game's initialisation method.
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& pframe_event);			//Our customised version of our game's update method.

	//----------OGRE DYNAMIC POINTERS-------------------------------------
	Ogre::Light*					_light_dynamic;		//Pointer to our Scene's Main Light
	std::vector<Ogre::SceneNode*>	_scene_nodes;		//List of Pointers to the key objects in our Scene (See Init function for scene structure).
};

#endif 