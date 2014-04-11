#ifndef GEOMETRY_BLOCK_H
#define GEOMETRY_BLOCK_H

#include "VolClouds.h"

class GeometryBlock
{
public:
	struct VERTEX {float x,y,z,xc, yc, zc,u, v,o;};
	GeometryBlock(VolClouds* _vc, const float& Height, const Ogre::Radian& Alpha, const Ogre::Radian& Beta, const float& Radius, const Ogre::Radian& Phi, const int& Na, const int& Nb, const int& Nc, const int& A, const int& B, const int& C, const int& Position);
	~GeometryBlock(void);

	void Load(void);
	inline Ogre::Entity* getEntity(){return mEntity;}

protected:
	void CalculateDataSize(void);
	void CreateGeometry(void);

	Ogre::HardwareVertexBufferSharedPtr mVertexBuffer;
	Ogre::HardwareIndexBufferSharedPtr  mIndexBuffer;
	VERTEX *mVertices;
	int mNumberOfTriangles;
	int mVertexCount;

	float mHeight;
	Ogre::Radian mAlpha, mBeta;
	float mRadius;
	Ogre::Radian mPhi;
	int mNa, mNb, mNc;
	float mA, mB, mC;
	int mPosition;

	Ogre::Vector2 mV2Cos;
	Ogre::Vector2 mV2Sin;
	float mBetaSin;
	float mAlphaSin;

	bool mCreated;
	Ogre::MeshPtr mMesh;
	Ogre::SubMesh* mSubMesh;
	Ogre::Entity* mEntity;
	VolClouds* mVolClouds;
};

#endif // GEOMETRY_BLOCK_H

