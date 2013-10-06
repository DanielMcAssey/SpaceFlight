#include "StdAfx.h"
#include "App.h"


App::App(void):
		_obj_root(nullptr),
		_obj_camera(nullptr),
		_obj_mgr_scene(nullptr),
		_obj_rdr_window(nullptr),
		_fname_cfg_res(Ogre::StringUtil::BLANK),
		_fname_cfg_plugins(Ogre::StringUtil::BLANK),
		_prop_bg_colour(0.0f,0.0f,0.0f,1.0f),
		_prop_app_windowname("SpaceFlight - Development Revision: 1"),

		_flg_shutdown(false)
{
}

App::~App(void)
{
    //Handle the Window Closing Event
	this->windowClosed(this->_obj_rdr_window);
    //Destroy our Scene Graph
	delete this->_obj_root;
}

bool App::internAppSetup(void)
{
	//Construct an OGRE Scene Root, specifying our Plugins Configuration File
    this->_obj_root = new Ogre::Root(this->_fname_cfg_plugins);

	//Setup our Default Resource Locations for External Content
    this->internSetupDefaultResources();

	//Configure our Application Screen
    bool tscreencreated = internConfigureScreen();

	//If we have no screen, there is no point in continuing the setup!!
	if (!tscreencreated)
		return false;

	//Create the Scene Graph Manager, Default Camera and Window Render Viewports/
    this->internSelectSceneManager();
    this->internCreateDefaultCamera();
    this->internCreateViewports();

	this->internTuneDataManagers();

    //Create an Resource Listeners
    this->internCreateResListener();

	//Call our Internal Default Resource Import Function
    this->internImportResources();

    // Create the scene - Abstract - Calls our Concrete Sub Class
    this->initSceneGraph();

	//Call our Internal Frame Listener Creation Method
    this->internCreateFrameListener();

	return true;
}

bool App::frameRenderingQueued(const Ogre::FrameEvent& pframe_event)
{
    if(this->_obj_rdr_window->isClosed())
        return false;

    if(this->_flg_shutdown)
        return false;

    //Need to capture/update each device
    //this->_obj_kbd->capture();
    //this->_obj_mouse->capture();


    return true;
}

void App::windowResized(Ogre::RenderWindow* pobjrdrwindow)
{
	//Setup our temporary variables
    unsigned int twidth, theight, tdepth;
    int tleft, ttop;

	//Store our Screen Metrics in our Temp Variables
    pobjrdrwindow->getMetrics(twidth, theight, tdepth, tleft, ttop);
}

void App::windowClosed(Ogre::RenderWindow* pobjrdrwindow)
{
    //Only close for window that created OIS (the main window in these demos)
    if(pobjrdrwindow == this->_obj_rdr_window)
    {

    }
}

bool App::internConfigureScreen(void)
{
	//If we have returned from our Configuration Window.
    if(this->_obj_root->showConfigDialog())
    {
		//Construct Our Window From Our Scene Root
		this->_obj_rdr_window = this->_obj_root->initialise(true,this->_prop_app_windowname);

        // Let's add a nice window icon if we are on Windows
		#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			//HWND hwnd;
			//this->_obj_rdr_window->getCustomAttribute("WINDOW", (void*)&hwnd);
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

void App::internSelectSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    this->_obj_mgr_scene = this->_obj_root->createSceneManager(Ogre::ST_GENERIC);
}

void App::internTuneDataManagers()
{
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
}

void App::internCreateDefaultCamera(void)
{
	//Setup our Default Camera
    this->_obj_camera = this->_obj_mgr_scene->createCamera("PlayerCam");
    this->_obj_camera->setPosition(Ogre::Vector3(0,30,20));
    this->_obj_camera->lookAt(Ogre::Vector3(0,0,-5));
    this->_obj_camera->setNearClipDistance(5);

	//Use the SDK's Camera Manager to Manager our Camera.
    //this->_obj_mgr_camera = new MyFPSCameraMan(this->_obj_camera);
}

void App::internCreateFrameListener(void)
{
	//Write a Message to our Default Application Log Manager
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

	//----------------INPUT CREATION------------------------------------------------
	//Create an Input
    size_t				thwnd_handle = 0;
    std::ostringstream	twindowconfigstring;

	//Obtain our HWND Identity String and write it to our string stream
	this->_obj_rdr_window->getCustomAttribute("WINDOW", &thwnd_handle);
    twindowconfigstring << thwnd_handle;


	//---------------WINDOW HANDLERS------------------------------------------------
    windowResized(this->_obj_rdr_window);


	//Register this Class as the Game Loop Frame Listener for our Game App.
    this->_obj_root->addFrameListener(this);
}

void App::internDestroyScene(void)
{
	//No Scene to Destroy by default.
}

void App::internCreateViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* tviewport = this->_obj_rdr_window->addViewport(this->_obj_camera);
	tviewport->setBackgroundColour(this->_prop_bg_colour);

    // Alter the camera aspect ratio to match the viewport
    this->_obj_camera->setAspectRatio(Ogre::Real(tviewport->getActualWidth()) / Ogre::Real(tviewport->getActualHeight()));
}

void App::internSetupDefaultResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile tconfigfile_resources;
    tconfigfile_resources.load(_fname_cfg_res);

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
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(tarch_name, ttype_name, tsection_name);
        }
    }
}

void App::internCreateResListener(void)
{
	//No Resource Handler to create by Default
}

void App::internImportResources(void)
{
	//Invoke the Resource groups.
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void App::startApp(void)
{
	//Preprocessor Directives
	#ifdef _DEBUG
		this->_fname_cfg_res = "./resources_d.cfg";
		this->_fname_cfg_plugins = "./plugins_d.cfg";
	#else
		this->_fname_cfg_res = "./resources.cfg";
		this->_fname_cfg_plugins = "./plugins.cfg";
	#endif

    //Setup the Base ogre system.
    if (!this->internAppSetup())
        return;

	//Start the Game Loop Process - Look at the definition to
	//identify the ogre calls.
    this->_obj_root->startRendering();

    // clean up the scene and exit out of the game.
    this->internDestroyScene();
}

