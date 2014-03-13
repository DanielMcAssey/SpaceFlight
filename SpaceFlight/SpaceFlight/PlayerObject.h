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
protected:
	int mPlayerID;
	Ogre::SceneNode* mNode;
	WindowData* mWindow;
	Ogre::SceneManager* mSceneManager;
	Ogre::Camera* mCamera;
	Ogre::Vector3 mPosition;
	Ogre::Real mHealth;
	VehicleObject* mVehicle;
};

#endif // PLAYEROBJECT_H
