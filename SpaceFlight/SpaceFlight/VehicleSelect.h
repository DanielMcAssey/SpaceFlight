#ifndef VEHICLESCREEN_H
#define VEHICLESCREEN_H

#include "MovableText.h"

class VehicleSelect : public BaseScreen
{
public:
	VehicleSelect(void);
	~VehicleSelect(void);

	DECLARE_SCREENSTATE_CLASS(VehicleSelect);

	void Load();
	void Unload();

	void Update(Ogre::Real elapsedTime);

	bool mShutdown;
protected:
	std::vector<Ogre::Entity*> mAvailableVehicles_p1;
	std::vector<Ogre::Entity*> mAvailableVehicles_p2;
	std::vector<Ogre::Entity*> mAvailableVehicles_p3;
	std::vector<Ogre::Entity*> mAvailableVehicles_p4;
	int vehicleIndexID[4];
	int maxVehicles;

	Ogre::SceneNode* vehicleDisplayNode[4];
	Ogre::SceneNode* cameraNode[4];
	Ogre::SceneNode* overlayNode[4];

	Ogre::MovableText* userInstructions[4];
};

#endif // VEHICLESCREEN_H