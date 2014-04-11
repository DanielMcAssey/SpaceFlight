#include "StdAfx.h"
#include "MenuScreen.h"

using namespace std;
using namespace Ogre;

MenuScreen::MenuScreen(void)
{
}


MenuScreen::~MenuScreen(void)
{
}

void MenuScreen::Load()
{
	this->mShutdown = false;
	this->mFrameEvent = Ogre::FrameEvent();
	this->menuIndex = 0;
	this->maxMenuItems = 3;
	this->startPressed = false;
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
	this->startupTextNode = this->menuNode->createChildSceneNode("ALERT_001_NODE");
	this->startupTextNode->attachObject(this->startupMsg);

	this->menuText = new Ogre::MovableText("MENU_01", "Game Modes", "BlueHighway-64", 3.0f, Ogre::ColourValue::Black);
	this->menuText->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_ABOVE);
	this->menuTextNode = this->menuNode->createChildSceneNode("MENU_01_NODE");
	this->menuTextNode->translate(0.0f, 2.5f, 0.0f);
	this->menuTextNode->detachAllObjects();
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

		if(this->startPressed) //Menu Screen
		{
			if(this->mWindow->_obj_input->GetState(this->mWindow->controllingGamepadID).DPadSingle.Right)
			{
				if(this->menuIndex + 1 >= this->maxMenuItems)
				{
					this->menuIndex = 0;
				}
				else
				{
					this->menuIndex += 1;
				}

			}
			else if(this->mWindow->_obj_input->GetState(this->mWindow->controllingGamepadID).DPadSingle.Left)
			{
				if(this->menuIndex - 1 < 0)
				{
					this->menuIndex = this->maxMenuItems - 1;
				}
				else
				{
					this->menuIndex -= 1;
				}
			}

			if(this->mWindow->_obj_input->GetState(this->mWindow->controllingGamepadID).DPadSingle.Left || this->mWindow->_obj_input->GetState(this->mWindow->controllingGamepadID).DPadSingle.Right)
			{
				switch(this->menuIndex)
				{
				case 0: //Practice
					this->startupMsg->setCaption("<-  Practice Mode  ->");
					break;
				case 1: //Race
					this->startupMsg->setCaption("<-  Race Mode  ->");
					break;
				case 2: //Dog Fight
					this->startupMsg->setCaption("<-  VS Mode  ->");
					break;
				}
			}

			if(this->mWindow->_obj_input->GetState(this->mWindow->controllingGamepadID).ButtonsSingle.A)
			{
				switch(this->menuIndex)
				{
				case 0: //Practice
					this->mWindow->gameMode = this->menuIndex;
					this->ChangeScreen(this->FindScreen("VehicleSelect"));
					break;
				case 1: //Race
					this->mWindow->gameMode = this->menuIndex;
					this->ChangeScreen(this->FindScreen("VehicleSelect"));
					break;
				case 2: //Dog Fight
					this->mWindow->gameMode = this->menuIndex;
					this->ChangeScreen(this->FindScreen("VehicleSelect"));
					break;
				}
			}
		}
		else //Press Start Screen
		{
			if(this->mWindow->_obj_input->GetState(this->mWindow->controllingGamepadID).ButtonsSingle.Start)
			{
				this->menuTextNode->attachObject(this->menuText);
				switch(this->menuIndex)
				{
				case 0: //Practice
					this->startupMsg->setCaption("<-  Practice Mode  ->");
					break;
				case 1: //Race
					this->startupMsg->setCaption("<-  Race Mode  ->");
					break;
				case 2: //Dog Fight
					this->startupMsg->setCaption("<-  VS Mode  ->");
					break;
				}
				this->startupMsg->setCharacterHeight(2.0f);
				this->startupMsg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE);
				this->startPressed = true;
			}
		}
	}
}