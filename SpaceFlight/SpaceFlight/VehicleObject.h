#ifndef VEHICLEOBJECT_H
#define VEHICLEOBJECT_H

class VehicleObject
{
public:
	VehicleObject(Ogre::String meshFile, int playerID);
	~VehicleObject(void);
	void LoadVehicle(Ogre::SceneManager* sceneManager, Ogre::SceneNode* sceneNode);
protected:
	int mPlayerID;
	Ogre::String mMeshFile;
	Ogre::Entity* mModel;
	Ogre::SceneNode* mNode;
};

#endif // VEHICLEOBJECT_H