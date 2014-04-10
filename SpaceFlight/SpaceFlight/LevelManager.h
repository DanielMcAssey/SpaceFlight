#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <OGRE\Terrain\OgreTerrain.h>
#include <OGRE\Terrain\OgreTerrainGroup.h>

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
private:
	Ogre::TerrainGlobalOptions* mTerrainGlobals;
    Ogre::TerrainGroup* mTerrainGroup;
    bool mTerrainsImported;

	void GetTerrainImage(bool flipX, bool flipY, Ogre::Image& img);
	void DefineTerrain(long x, long y);
    void InitBlendMaps(Ogre::Terrain* _terrain);
    void ConfigTerrainDefaults(Ogre::Light* _light);
protected:
	void GenerateTerrain(void);
	WindowData* mWindow;
	Ogre::SceneManager* mSceneManager;
	Ogre::SceneNode* mNode;
	PlayerObject* mPlayers[4];
	Ogre::Light* mLevelLight;
};

#endif // LEVELMANAGER_H