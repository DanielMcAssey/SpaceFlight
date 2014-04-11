#ifndef GEOMETRY_MANAGER_H
#define GEOMETRY_MANAGER_H

class VolClouds;

#include "VolClouds.h"
#include "GeometryBlock.h"

class GeometryManager
{
public:
	GeometryManager(VolClouds* _vc);
	~GeometryManager(void);

	void Load(const Ogre::Vector2& Height, const float& Radius, const Ogre::Radian& Alpha, const Ogre::Radian& Beta, const int& NumberOfBlocks, const int& Na, const int& Nb, const int& Nc);
	void Update(Ogre::Real elapsedTime);

	inline const bool& isCreated() const {return mCreated;}
	inline Ogre::SceneNode* getSceneNode() {return mSceneNode;}
protected:
	void CreateGeometry();

	bool mCreated;
	Ogre::Vector2 mHeight;
	Ogre::Radian mAlpha, mBeta;
	float mRadius;
	Ogre::Radian mPhi;
	int mNumberOfBlocks;
	int mNa, mNb, mNc;
	float mA, mB, mC;

	Ogre::Vector2 mWorldOffset;
	Ogre::SceneNode* mSceneNode;
	VolClouds* mVolClouds;
	std::vector<GeometryBlock*> mGeometryBlocks;
};


#endif // GEOMETRY_MANAGER_H
