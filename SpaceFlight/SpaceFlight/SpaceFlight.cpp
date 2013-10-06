#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	#define WIN32_LEAN_AND_MEAN
	#include "windows.h"
#endif

#include "stdafx.h"
#include "GameApp.h"

#ifdef __cplusplus
extern "C"{
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
		GameApp tapp;

        try
		{
			//Make a call to Start App to Start our game loop.
			tapp.startApp();
        } 
		catch(Ogre::Exception& texception)
		{
			#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
				MessageBox(nullptr, texception.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
			#else
				std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
			#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

