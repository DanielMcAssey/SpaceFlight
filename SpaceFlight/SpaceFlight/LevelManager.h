#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <OGRE\Terrain\OgreTerrain.h>
#include <OGRE\Terrain\OgreTerrainGroup.h>
#include "VolCloudManager.h"

class LevelManager
{
public:
	LevelManager(WindowData* window, Ogre::SceneManager* sceneManager);
	~LevelManager(void);
	void LoadLevel(bool IsMultiplayer, Ogre::SceneNode* sceneNode);
	void UnloadLevel(void);
	void Update(Ogre::Real elapsedTime);
	void ResetPlayerCameras(void);
	PlayerObject* GetPlayer(int id);
	Ogre::SceneNode* GetLevelNode(void);
private:
	Ogre::TerrainGlobalOptions* mTerrainGlobals;
    Ogre::TerrainGroup* mTerrainGroup;
    bool mTerrainsImported;

	void GetTerrainImage(bool flipX, bool flipY, Ogre::Image& img);
	void DefineTerrain(long x, long y);
    void InitBlendMaps(Ogre::Terrain* _terrain);
    void ConfigTerrainDefaults(Ogre::Light* _light);
protected:
	WindowData* mWindow;
	Ogre::SceneManager* mSceneManager;
	Ogre::SceneNode* mNode;
	PlayerObject* mPlayers[4];
	Ogre::Light* mLevelLight;
	VolCloudManager* mCloudManager;

	Ogre::MovableText* mStatusText[4];
	Ogre::MovableText* mDebugText[4];
	Ogre::SceneNode* mPlayerScenes[4];

	Ogre::SceneNode* mStatusHUD[4];
	Ogre::SceneNode* mDebugHUD[4];

	void GenerateTerrain(void);
};

#endif // LEVELMANAGER_H