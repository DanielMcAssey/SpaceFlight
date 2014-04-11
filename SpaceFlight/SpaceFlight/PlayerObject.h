#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

class PlayerObject
{
public:
	PlayerObject(Ogre::SceneManager* sceneManager, WindowData* window, Ogre::SceneNode* sceneNode, int playerID);
	~PlayerObject(void);
	Ogre::Camera* LoadCamera(int id);
	void Update(Ogre::Real elapsedTime);
	void SetPosition(Ogre::Vector3 newPos);
	Ogre::Vector3 GetPosition();
	void SetHealth(Ogre::Real newHealth);
	Ogre::Real GetHealth();
	void SetVehicle(VehicleObject* vehicle);
	VehicleObject* GetVehicle();
	void ResetCamera(void);
	void KillPlayer(void);
protected:
	void HandleInput(Ogre::Real elapsedTime);
	int mPlayerID;

	//Scene Nodes
	Ogre::SceneNode* mNode;
	Ogre::SceneNode* mCameraNode;
	//--SceneNodes

	WindowData* mWindow;
	Ogre::SceneManager* mSceneManager;
	Ogre::Camera* mCamera;
	Ogre::Vector3 mPosition;
	Ogre::Vector3 mDirection;
	Ogre::Real mHealth;
	VehicleObject* mVehicle;

	bool mGunCooldownWait;
	Ogre::Real mGunCooldown;
	Ogre::Real mGunCooldownTime;
	Ogre::Real mGunMaxFireTime;
	BulletManager* mBulletManager;

	int mMaxMissiles;
	int mCurrentMissiles;
};

#endif // PLAYEROBJECT_H
