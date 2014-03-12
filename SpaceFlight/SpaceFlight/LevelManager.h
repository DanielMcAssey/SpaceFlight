#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

class LevelManager
{
public:
	LevelManager(WindowData* window, Ogre::SceneManager* sceneManager);
	~LevelManager(void);
	void LoadLevel();
	void ResetPlayerCameras();
	PlayerObject* GetPlayer(int id);
protected:
	WindowData* mWindow;
	Ogre::SceneManager* mSceneManager;
	PlayerObject* mPlayers[4];
};

#endif // LEVELMANAGER_H