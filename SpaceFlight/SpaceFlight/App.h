#ifndef _APP_H
#define _APP_H

class App : public Ogre::FrameListener
{
public:
	App(void);
	virtual ~App(void);

	virtual void startApp(void); //Starts Game

	//----------INHERITED INTERFACE IMPLEMENTATION-----------------------------------------
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& pevt);					//Event Handler for Frame Rendering (Game Loop)
	virtual void windowResized(Ogre::RenderWindow* prw);								//Event Handler for Window Resizing Actions
    virtual void windowClosed(Ogre::RenderWindow* prw);									//Event Handler for Window Closing Actions

protected:
	//----------INHERITABLE CUSTOM METHODS-------------------------------------------------
    virtual bool internAppSetup();						//Method to Start the Configuration of Our Application 
    virtual bool internConfigureScreen(void);			//Method to configure our application screen output (OM Stage in DirectX 11)
    virtual void internSelectSceneManager(void);		//Method to specify the type of scene graph manager used
    virtual void internCreateDefaultCamera(void);		//Method to create our default camera system
    virtual void internCreateFrameListener(void);		//Method to constructor our application frame listener
    virtual void internDestroyScene(void);				//Method to destroy our Scene 
    virtual void internCreateViewports(void);			//Method to construct our Viewport
	virtual void internTuneDataManagers(void);			//Method to tune our application data managers
    virtual void internSetupDefaultResources(void);		//Method to setup of default resource locations and files
    virtual void internCreateResListener(void);			//Method to Create a Resource Listener (ADVANCED TECHNIQUE)
    virtual void internImportResources(void);			//Method to import our Application External Resources

	//----------ABSTRACT CLASS (PURE VIRTUAL) FUNCTION-------------------------------------
	virtual void initSceneGraph(void) = 0; // Abstract Method to be implemented by our sub class, which sets up the scene.

	//----------INHERITABLE FIELDS---------------------------------------------------------
    Ogre::Root*			_obj_root;						//Pointer to the root of our scene graph
    Ogre::Camera*		_obj_camera;					//Pointer to our default camera object
    Ogre::SceneManager* _obj_mgr_scene;					//Pointer to our application's scene manager
    Ogre::RenderWindow* _obj_rdr_window;				//Pointer to our application's render window
    Ogre::String		_fname_cfg_res;					//Stores the File Name of our Resources Configurations
    Ogre::String		_fname_cfg_plugins;				//Stores the File Name of our Plugin Configurations
	Ogre::String		_prop_app_windowname;			//Property to store the Application Window Name
	Ogre::ColourValue	_prop_bg_colour;				//Property to store the render target clear colour
    bool				_flg_shutdown;					//Flag to tell us when our game is exiting
};

#endif

