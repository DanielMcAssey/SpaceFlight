#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

class LevelManager
{
public:
	LevelManager(WindowData* window, Ogre::SceneManager* sceneManager);
	~LevelManager(void);
	void LoadLevel(bool IsMultiplayer, Ogre::SceneNode* sceneNode);
	void UnloadLevel();
	void Update(Ogre::Real elapsedTime);
	void ResetPlayerCameras();
	PlayerObject* GetPlayer(int id);
	Ogre::SceneNode* GetLevelNode();
protected:
	WindowData* mWindow;
	Ogre::SceneManager* mSceneManager;
	Ogre::SceneNode* mNode;
	PlayerObject* mPlayers[4];
};

#endif // LEVELMANAGER_H