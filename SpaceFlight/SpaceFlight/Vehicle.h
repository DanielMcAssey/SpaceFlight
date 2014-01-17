#ifndef ENT_VEHICLE_H
#define ENT_VEHICLE_H

class Vehicle : public GameObject
{
public:
	Vehicle(Ogre::SceneManager *_sceneManager);
	~Vehicle(void);
};

#endif // ENT_VEHICLE_H