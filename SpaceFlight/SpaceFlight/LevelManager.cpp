#include "StdAfx.h"
#include "LevelManager.h"


LevelManager::LevelManager(WindowData* window, Ogre::SceneManager* sceneManager)
{
	this->mWindow = window;
	this->mSceneManager = sceneManager;
	this->mCloudManager = new VolCloudManager(this->mSceneManager);
}


LevelManager::~LevelManager(void)
{

}


void LevelManager::LoadLevel(bool IsMultiplayer, Ogre::SceneNode* sceneNode)
{
	this->mNode = sceneNode->createChildSceneNode("level"); //Create the level manager node.
	int i = this->mWindow->controllingGamepadID;
	int max = this->mWindow->controllingGamepadID + 1;

	if(IsMultiplayer)
	{
		i = 0;
		max = 4;
	}

	for(i = i; i < max; i++)
	{
		if(this->mWindow->activePlayers[i])
		{
			this->mPlayers[i] = new PlayerObject(this->mSceneManager, this->mWindow, this->mNode, i);
			this->mPlayers[i]->SetVehicle(this->mWindow->playerData[i]->_player_vehicle);
			this->mPlayers[i]->SetPosition(Ogre::Vector3(0.0f, 0.0f, -100.0f));
			this->mWindow->_obj_viewport[i]->setCamera(this->mPlayers[i]->LoadCamera(i));
			this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 0.0f)); //Reset BG Colour
			this->mStatusText[i] = new Ogre::MovableText("PLAYER_STATUS_" + i, "NullString", "BlueHighway-64", 2.0f, Ogre::ColourValue::White);
			this->mStatusText[i]->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_CENTER);
			this->mDebugText[i] = new Ogre::MovableText("PLAYER_DEBUG_" + i, "DEBUGTEXT", "BlueHighway-64", 1.0f, Ogre::ColourValue::White);
			this->mDebugText[i]->setTextAlignment(Ogre::MovableText::H_LEFT, Ogre::MovableText::V_CENTER);
			this->mPlayerScenes[i] = this->mPlayers[i]->GetSceneNode()->createChildSceneNode("PLAYER_HUD_" + i);
			this->mPlayerScenes[i]->translate(0.0f, 5.0f, 0.0f);
			this->mStatusHUD[i] = this->mPlayerScenes[i]->createChildSceneNode("HUD_STATUS_" + i);
			this->mDebugHUD[i] = this->mPlayerScenes[i]->createChildSceneNode("HUD_DEBUG_" + i);
			this->mStatusHUD[i]->attachObject(this->mStatusText[i]);
			this->mStatusHUD[i]->setVisible(false);
			this->mDebugHUD[i]->attachObject(this->mDebugText[i]);
			this->mDebugHUD[i]->translate(-((this->mWindow->_obj_viewport[i]->getWidth() / 2.0f)), -(this->mWindow->_obj_viewport[i]->getHeight() / 2.0f), 0.0f);
		}
	}

	Vector3 _tmpLightDir(0.55, -0.3, 0.75);
	_tmpLightDir.normalise();

	this->mLevelLight = this->mSceneManager->createLight("LevelLight");
	this->mLevelLight->setType(Ogre::Light::LT_DIRECTIONAL);
	this->mLevelLight->setDirection(_tmpLightDir);
	this->mLevelLight->setDiffuseColour(Ogre::ColourValue::White);
	this->mLevelLight->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
	this->mSceneManager->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
	this->GenerateTerrain();
	this->mSceneManager->setSkyDome(true, "Examples/CloudySky", 64, 8);

	for(int i = 0; i < 4; i++)
	{
		if(this->mWindow->activePlayers[i])
		{
			this->mPlayers[i]->SetPosition(Vector3(50.0f * i, 600.0f, 0.0f));
		}
	}

	this->mCloudManager->Load(-1); // Load Volumetric Cloud Manager
}


void LevelManager::UnloadLevel()
{
	OGRE_DELETE this->mTerrainGroup;
    OGRE_DELETE this->mTerrainGlobals;
}


void LevelManager::Update(Ogre::Real elapsedTime)
{
	for(int i = 0; i < 4; i++)
	{
		if(this->mWindow->activePlayers[i])
		{
			Vector3 tmpVector = this->mPlayers[i]->GetPosition();
			this->mDebugText[i]->setCaption("POSITION X[" + Ogre::StringConverter::toString(tmpVector.x) + "] Y[" + Ogre::StringConverter::toString(tmpVector.y) + "] Z[" + Ogre::StringConverter::toString(tmpVector.z) + "]");

			this->mPlayers[i]->Update(elapsedTime);

			if(this->mPlayers[i]->GetHealth() <= 0.0f)
			{
				this->mPlayers[i]->KillPlayer();
				this->mStatusText[i]->setCaption("GAME OVER");
				this->mStatusHUD[i]->setVisible(true);
				this->mWindow->_obj_viewport[i]->setBackgroundColour(Ogre::ColourValue::Black);
			}
		}
	}

	if (!mTerrainGroup->isDerivedDataUpdateInProgress())
    {
        if (mTerrainsImported)
        {
            mTerrainGroup->saveAllTerrains(true); //Save Terrain
            mTerrainsImported = false;
        }
    }
}


#pragma region Terrain_Functions
void LevelManager::GenerateTerrain(void)
{
	this->mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
	this->mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(this->mSceneManager, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);
	this->mTerrainGroup->setFilenameConvention(Ogre::String("DefaultTerrain"), Ogre::String("dat"));
	this->mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);
	this->ConfigTerrainDefaults(this->mLevelLight);

	for(long x = 0; x <= 1; ++x)
		for(long y = 0; y <= 1; ++y)
			this->DefineTerrain(x, y);

	this->mTerrainGroup->loadAllTerrains(true);

	if(this->mTerrainsImported)
	{
		Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
        while(ti.hasMoreElements())
        {
            Ogre::Terrain* t = ti.getNext()->instance;
            this->InitBlendMaps(t);
        }
	}

	this->mTerrainGroup->freeTemporaryResources();
}


void LevelManager::GetTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
	img.load("Terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	if (flipX)
		img.flipAroundY();
	if (flipY)
		img.flipAroundX();
}


void LevelManager::DefineTerrain(long x, long y)
{
	Ogre::String filename = mTerrainGroup->generateFilename(x, y);
    if (Ogre::ResourceGroupManager::getSingleton().resourceExists(this->mTerrainGroup->getResourceGroup(), filename))
    {
        this->mTerrainGroup->defineTerrain(x, y);
    }
    else
    {
        Ogre::Image img;
        this->GetTerrainImage(x % 2 != 0, y % 2 != 0, img);
        this->mTerrainGroup->defineTerrain(x, y, &img);
        this->mTerrainsImported = true;
    }
}


void LevelManager::InitBlendMaps(Terrain* _terrain)
{
	Ogre::TerrainLayerBlendMap* blendMap0 = _terrain->getLayerBlendMap(1);
    Ogre::TerrainLayerBlendMap* blendMap1 = _terrain->getLayerBlendMap(2);
    Ogre::Real minHeight0 = 70;
    Ogre::Real fadeDist0 = 40;
    Ogre::Real minHeight1 = 70;
    Ogre::Real fadeDist1 = 15;
    float* pBlend0 = blendMap0->getBlendPointer();
    float* pBlend1 = blendMap1->getBlendPointer();
    for (Ogre::uint16 y = 0; y < _terrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < _terrain->getLayerBlendMapSize(); ++x)
        {
            Ogre::Real tx, ty;
            blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
            Ogre::Real height = _terrain->getHeightAtTerrainPosition(tx, ty);
            Ogre::Real val = (height - minHeight0) / fadeDist0;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend0++ = val;
            val = (height - minHeight1) / fadeDist1;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend1++ = val;
        }
    }

    blendMap0->dirty();
    blendMap1->dirty();
    blendMap0->update();
    blendMap1->update();
}


void LevelManager::ConfigTerrainDefaults(Light* _light)
{
	this->mTerrainGlobals->setMaxPixelError(8);
    this->mTerrainGlobals->setCompositeMapDistance(3000);
	this->mTerrainGlobals->setLightMapDirection(_light->getDerivedDirection());
    this->mTerrainGlobals->setCompositeMapAmbient(this->mSceneManager->getAmbientLight());
    this->mTerrainGlobals->setCompositeMapDiffuse(_light->getDiffuseColour());

	Ogre::Terrain::ImportData& defaultimp = this->mTerrainGroup->getDefaultImportSettings();
    defaultimp.terrainSize = 513;
    defaultimp.worldSize = 12000.0f;
    defaultimp.inputScale = 600;
    defaultimp.minBatchSize = 33;
    defaultimp.maxBatchSize = 65;

	defaultimp.layerList.resize(3);
    defaultimp.layerList[0].worldSize = 100;
    defaultimp.layerList[0].textureNames.push_back("dirt_diffuse.dds");
    defaultimp.layerList[0].textureNames.push_back("dirt_normal.dds");
    defaultimp.layerList[1].worldSize = 30;
    defaultimp.layerList[1].textureNames.push_back("grass_diffuse.dds");
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
    defaultimp.layerList[2].worldSize = 200;
    defaultimp.layerList[2].textureNames.push_back("fungus_diffuse.dds");
    defaultimp.layerList[2].textureNames.push_back("fungus_normal.dds");
}
#pragma endregion Terrain_Functions


#pragma region Helper_Functions
void LevelManager::ResetPlayerCameras()
{
	for(int i = 0; i < 4; i++)
	{
		if(this->mPlayers[i] != nullptr)
		{
			this->mPlayers[i]->ResetCamera();
		}
	}
}


PlayerObject* LevelManager::GetPlayer(int id)
{
	if(id < 4)
	{
		if(this->mPlayers[id] != nullptr)
		{
			return this->mPlayers[id];
		}
	}

	return nullptr;
}


Ogre::SceneNode* LevelManager::GetLevelNode()
{
	if(this->mNode != nullptr)
		return this->mNode;
}
#pragma endregion