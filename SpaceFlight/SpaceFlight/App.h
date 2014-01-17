#ifndef _APP_H
#define _APP_H

#include "ScreenManager.h"

class App
{
public:
	App(void);
	~App(void);

	void startApp(void); //Starts Game
protected:
	//----------INHERITABLE CUSTOM METHODS-------------------------------------------------
    bool internAppSetup();						//Method to Start the Configuration of Our Application 
    bool internConfigureScreen(void);			//Method to configure our application screen output (OM Stage in DirectX 11)
    void internSetupDefaultResources(void);		//Method to setup of default resource locations and files

	//----------MEMBER FIELDS---------------------------------------------------------
    WindowData _obj_window;
	ScreenManager* _obj_screenmanager;
};

#endif

