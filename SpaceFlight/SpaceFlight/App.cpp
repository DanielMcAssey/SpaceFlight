#include "StdAfx.h"
#include "App.h"

using namespace std;
using namespace Ogre;

App::App(void)
{
	this->_obj_window._obj_root = nullptr;
	this->_obj_window._obj_rdr_window = nullptr;
	this->_obj_window._fname_cfg_res = Ogre::StringUtil::BLANK;
	this->_obj_window._fname_cfg_plugins = Ogre::StringUtil::BLANK;
	this->_obj_window._prop_app_windowname = "SpaceFlight - Version: 0.1-dev";
	this->_obj_window._obj_log = nullptr;
	this->_obj_window._obj_timer = nullptr;
}

App::~App(void)
{
	//Destroy our Scene Graph
	delete this->_obj_window._obj_root;
}

bool App::internAppSetup(void)
{
	Ogre::LogManager* logManager = new Ogre::LogManager();

	this->_obj_window._obj_log = Ogre::LogManager::getSingleton().createLog("OgreLogFile.log", true, true, false);
	this->_obj_window._obj_log->setDebugOutputEnabled(true);

	this->_obj_window.controllingGamepadID = 0;
	this->_obj_window.controllingGamepadSet = false;

	//Construct an OGRE Scene Root, specifying our Plugins Configuration File
	this->_obj_window._obj_root = new Ogre::Root(this->_obj_window._fname_cfg_plugins);

	//Setup our Default Resource Locations for External Content
	this->internSetupDefaultResources();

	//Configure our Application Screen
	bool tscreencreated = internConfigureScreen();

	//If we have no screen, there is no point in continuing the setup!!
	if (!tscreencreated)
		return false;

	this->_obj_window._obj_viewport[0] = this->_obj_window._obj_rdr_window->addViewport(0);
	this->_obj_window._obj_viewport[0]->setBackgroundColour(Ogre::ColourValue(0.5f, 0.5f, 0.5f, 1.0f));
	this->_obj_window._obj_viewport[0]->setCamera(0);

	this->_obj_window._obj_input = new InputManager();

	//Create the Scene Graph Manager, Default Camera and Window Render Viewports/
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	//Call our Internal Default Resource Import Function
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	this->_obj_window._obj_timer = new Ogre::Timer();
	this->_obj_window._obj_timer->reset();

	//Start the Game Loop Process - Look at the definition to
	//identify the ogre calls.
	this->_obj_window._obj_rdr_window->setActive(true);

	this->_obj_window.totalPlayers = 0;
	this->_obj_window.playersReady = 0;

	for(int i = 0; i < 4; i++)
	{
		this->_obj_window.activePlayers[i] = false;
		this->_obj_window.playerReady[i] = false;
	}

	this->_obj_window.maxViewDistance = 1000.0f;
	//Create the screen manager
	this->_obj_screenmanager = new ScreenManager(&this->_obj_window);
	MenuScreen::CreateScreen(this->_obj_screenmanager, "MenuScreen");
	VehicleSelect::CreateScreen(this->_obj_screenmanager, "VehicleSelect");
	DogFightingScreen::CreateScreen(this->_obj_screenmanager, "DogFightingScreen");
	RaceScreen::CreateScreen(this->_obj_screenmanager, "RaceScreen");
	TargetPracticeScreen::CreateScreen(this->_obj_screenmanager, "TargetPracticeScreen");
	this->_obj_screenmanager->LoadScreen(this->_obj_screenmanager->FindScreen("MenuScreen"));

	return true;
}

bool App::internConfigureScreen(void)
{
	//If we have returned from our Configuration Window.
	if(this->_obj_window._obj_root->showConfigDialog())
	{
		//Construct Our Window From Our Scene Root
		this->_obj_window._obj_rdr_window = this->_obj_window._obj_root->initialise(true,this->_obj_window._prop_app_windowname);

		// Let's add a nice window icon if we are on Windows
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		//HWND hwnd;
		//this->_obj_window._obj_rdr_window->getCustomAttribute("WINDOW", (void*)&hwnd);
		//LONG iconID = (LONG)LoadIcon( GetModuleHandle(0), MAKEINTRESOURCE(IDI_APPICON) );
		//SetClassLong( hwnd, GCL_HICON, iconID );
#endif

		return true;
	}
	else
	{
		return false;
	}
}

void App::internSetupDefaultResources(void)
{
	// Load resource paths from config file
	Ogre::ConfigFile tconfigfile_resources;
	tconfigfile_resources.load(this->_obj_window._fname_cfg_res);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator tsiter = tconfigfile_resources.getSectionIterator();

	Ogre::String tsection_name, ttype_name, tarch_name;

	//Loop over our Configuration File and Strip Out the Properties
	while (tsiter.hasMoreElements())
	{
		tsection_name = tsiter.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *tsettings = tsiter.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator tpropertyiterator;
		for (tpropertyiterator = tsettings->begin(); tpropertyiterator != tsettings->end(); ++tpropertyiterator)
		{
			ttype_name = tpropertyiterator->first;
			tarch_name = tpropertyiterator->second;

			if(tsection_name == "Content" && ttype_name == "FileSystem")
			{
				ResourceGroupManager::getSingleton().addResourceLocation(tarch_name, ttype_name, tsection_name, true);
			}
			else
			{
				ResourceGroupManager::getSingleton().addResourceLocation(tarch_name, ttype_name, tsection_name);
			}

			OutputDebugString(tarch_name.c_str());
			OutputDebugString("\n");
		}
	}
}

void App::startApp(void)
{
	//Preprocessor Directives
#ifdef _DEBUG
	this->_obj_window._fname_cfg_res = "./resources_d.cfg";
	this->_obj_window._fname_cfg_plugins = "./plugins_d.cfg";
#else
	this->_obj_window._fname_cfg_res = "./resources.cfg";
	this->_obj_window._fname_cfg_plugins = "./plugins.cfg";
#endif

	//Setup the Base ogre system.
	if (!this->internAppSetup())
		return;
}

