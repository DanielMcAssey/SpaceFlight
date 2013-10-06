#include "StdAfx.h"
#include "GameApp.h"


GameApp::GameApp(void)
{
}


GameApp::~GameApp(void)
{
}


void GameApp::initSceneGraph(void)
{
	//-------SCENE LIGHTING AND CAMERA SETUP------------------------------------------------------------
	
}

bool GameApp::frameRenderingQueued(const Ogre::FrameEvent& pframe_event)
{
	//Boolean to store our True/false return value
	bool tresult;

	//Call the Superclass update, so that we still doing all the process which 
	//our default game template does - (see the frameRenderingQueued Implementation
	// in ILJMUGameApp for more information).
	tresult = App::frameRenderingQueued(pframe_event);
	
	//If our game is still active.
	if (tresult) 
	{

	}

	//Return whether our game is active.
	return tresult;
}