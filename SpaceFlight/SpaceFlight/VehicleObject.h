#ifndef VEHICLEOBJECT_H
#define VEHICLEOBJECT_H

struct VehicleStats
{
	Ogre::Real Speed;
	Ogre::Real Acceleration;
	Ogre::Real Handling;
	Ogre::Real MissileRange;
	Ogre::Real GunRange;
	Ogre::Real Armor;
};

class VehicleObject
{
public:
	VehicleObject(Ogre::String meshFile, int vehicleIndex, int playerID);
	~VehicleObject(void);
	void LoadVehicle(Ogre::SceneManager* sceneManager, Ogre::SceneNode* sceneNode);
	VehicleStats* GetStats();
protected:
	int mPlayerID;
	int mVehicleIndex;
	VehicleStats* mStats;
	Ogre::String mMeshFile;
	Ogre::Entity* mModel;
	Ogre::SceneNode* mNode;
};

#endif // VEHICLEOBJECT_H