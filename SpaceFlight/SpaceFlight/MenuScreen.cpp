#include "StdAfx.h"
#include "MenuScreen.h"

using namespace std;
using namespace Ogre;

MenuScreen::MenuScreen(void)
{
	this->mShutdown = false;
	this->mFrameEvent = Ogre::FrameEvent();
}


MenuScreen::~MenuScreen(void)
{
}

void MenuScreen::Load()
{
	this->mSceneManager = this->mWindow->_obj_root->createSceneManager(ST_GENERIC, "MenuRoot");

	this->mWindow->_obj_rdr_window->removeAllViewports();
	this->mActiveCamera[0] = this->mSceneManager->createCamera("MenuCamera");
	this->mWindow->_obj_viewport[0] = this->mWindow->_obj_rdr_window->addViewport(this->mActiveCamera[0], 0, 0.0f, 0.0f, 1.0f, 1.0f);
	this->mActiveCamera[0]->setPosition(Ogre::Vector3(0,0,50));
	this->mActiveCamera[0]->lookAt(Ogre::Vector3(0,0,0));
	this->mActiveCamera[0]->setNearClipDistance(0.01);
	this->mActiveCamera[0]->setFarClipDistance(1000);
	this->mActiveCamera[0]->setAspectRatio(Ogre::Real(this->mWindow->_obj_viewport[0]->getActualWidth()) / Ogre::Real(this->mWindow->_obj_viewport[0]->getActualHeight()));
	this->mWindow->_obj_viewport[0]->setCamera(this->mActiveCamera[0]);

	//Create BG
	this->mBGMaterial = Ogre::MaterialManager::getSingleton().create("MENU_Background", "Content");
	this->mBGMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("menu_bg.png");
	this->mBGMaterial->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	this->mBGMaterial->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	this->mBGMaterial->getTechnique(0)->getPass(0)->setLightingEnabled(false);

	this->mBGRect = new Rectangle2D(true);
	this->mBGRect->setCorners(-1.0, 1.0, 1.0, -1.0);
	this->mBGRect->setMaterial("MENU_Background");
	this->mBGRect->setRenderQueueGroup(RENDER_QUEUE_BACKGROUND);

	AxisAlignedBox aabInf;
	aabInf.setInfinite();
	this->mBGRect->setBoundingBox(aabInf);

	this->mBGMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setScrollAnimation(-0.05, 0.0);

	this->menuNode = this->mSceneManager->getRootSceneNode()->createChildSceneNode("MainMenu");
	this->menuNode->setPosition(Ogre::Vector3(0,0,0));

	this->menuNode->attachObject(this->mBGRect);
	this->menuNode->attachObject(this->mActiveCamera[0]);

	this->startupMsg = new Ogre::MovableText("ALERT_001", "Press Start", "BlueHighway-64", 5.0f, Ogre::ColourValue::Black);
	this->startupMsg->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_ABOVE);
	this->menuNode->attachObject(this->startupMsg);
}

void MenuScreen::Unload()
{
	if(this->mActiveCamera[0] != nullptr)
		this->mSceneManager->destroyCamera(this->mActiveCamera[0]);

	if(this->mSceneManager)
		this->mWindow->_obj_root->destroySceneManager(this->mSceneManager);

	if(this->mBGRect != nullptr)
		delete this->mBGRect;
}

void MenuScreen::Update(Ogre::Real elapsedTime)
{
	this->mFrameEvent.timeSinceLastFrame = elapsedTime;

	if(this->mShutdown)
	{
		this->GameShutdown();
		return;
	}

	if(!this->mWindow->_obj_input->GetState(this->mWindow->controllingGamepadID).Disconnected && this->mWindow->controllingGamepadSet)
	{
		if(this->mWindow->_obj_input->GetState(this->mWindow->controllingGamepadID).ButtonsSingle.B)
			this->mShutdown = true;

		if(this->mWindow->_obj_input->GetState(this->mWindow->controllingGamepadID).ButtonsSingle.Start)
			this->startupMsg->setCaption("Press A to Continue");

		if(this->mWindow->_obj_input->GetState(this->mWindow->controllingGamepadID).ButtonsSingle.A)
			this->ChangeScreen(this->FindScreen("VehicleSelect"));
	}
}