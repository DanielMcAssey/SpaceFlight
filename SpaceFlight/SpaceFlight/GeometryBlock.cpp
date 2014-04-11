#include "StdAfx.h"
#include "GeometryBlock.h"

GeometryBlock::GeometryBlock(VolClouds* _vc, const float& Height, const Ogre::Radian& Alpha, const Ogre::Radian& Beta, const float& Radius, const Ogre::Radian& Phi, const int& Na, const int& Nb, const int& Nc, const int& A, const int& B, const int& C, const int& Position)
{
	this->mVolClouds = _vc;
	this->mCreated = false;
	this->mSubMesh = 0;
	this->mEntity = 0;
	this->mVertices = 0;
	this->mNumberOfTriangles = 0;
	this->mVertexCount = 0;
	this->mHeight = Height;
	this->mAlpha = Alpha;
	this->mBeta = Beta;
	this->mRadius = Radius;
	this->mPhi = Phi;
	this->mNa = Na;
	this->mNb = Nb;
	this->mNc = Nc;
	this->mA = A;
	this->mB = B;
	this->mC = C;
	this->mPosition = Position;
	this->CalculateDataSize();
}


GeometryBlock::~GeometryBlock(void)
{
}


void GeometryBlock::CalculateDataSize(void)
{
	this->mVertexCount = 7*this->mNa + 6*this->mNb + 4*this->mNc;
	this->mNumberOfTriangles = 5*this->mNa + 4*this->mNb + 2*this->mNc;

	this->mV2Cos = Ogre::Vector2(Ogre::Math::Cos(this->mPosition*this->mPhi), Ogre::Math::Cos((this->mPosition+1)*this->mPhi));
	this->mV2Sin = Ogre::Vector2(Ogre::Math::Sin(this->mPosition*this->mPhi), Ogre::Math::Sin((this->mPosition+1)*this->mPhi));

	this->mBetaSin  = Ogre::Math::Sin(Ogre::Math::PI-this->mBeta.valueRadians());
	this->mAlphaSin = Ogre::Math::Sin(Ogre::Math::PI-this->mAlpha.valueRadians());
}


void GeometryBlock::Load(void)
{
	this->mMesh = Ogre::MeshManager::getSingleton().createManual("VolClouds_Block" + Ogre::StringConverter::toString(mPosition), "Content");
	this->mSubMesh = this->mMesh->createSubMesh();
	this->mSubMesh->useSharedVertices = false;

	this->CreateGeometry();

	this->mMesh->buildEdgeList();

	this->mMesh->load();
	this->mMesh->touch();

	this->mEntity = this->mVolClouds->getSceneManager()->createEntity("VolClouds_BlockEnt" + Ogre::StringConverter::toString(mPosition), "VolClouds_Block" + Ogre::StringConverter::toString(mPosition));
	this->mEntity->setMaterialName("ExtClouds");
	this->mEntity->setCastShadows(false);

	this->mCreated = true;
}

void GeometryBlock::CreateGeometry(void)
{
		this->mSubMesh->vertexData = new Ogre::VertexData();
		this->mSubMesh->vertexData->vertexStart = 0;
		this->mSubMesh->vertexData->vertexCount = this->mVertexCount;

		Ogre::VertexDeclaration* vdecl = this->mSubMesh->vertexData->vertexDeclaration;
		Ogre::VertexBufferBinding* vbind = this->mSubMesh->vertexData->vertexBufferBinding;

		size_t offset = 0;
		vdecl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
		offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
		vdecl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_TEXTURE_COORDINATES, 0);
		offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
		vdecl->addElement(0, offset, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES, 1);
		offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);
		vdecl->addElement(0, offset, Ogre::VET_FLOAT1, Ogre::VES_TEXTURE_COORDINATES, 2);

		this->mVertexBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(sizeof(VERTEX), this->mVertexCount, Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY);
		vbind->setBinding(0, this->mVertexBuffer);

		unsigned short *indexbuffer = new unsigned short[this->mNumberOfTriangles*3];

		int IndexOffset = 0;
		int VertexOffset = 0;

		// C
		for (int k = 0; k < this->mNc; k++)
		{
			// First triangle
			indexbuffer[IndexOffset]   = VertexOffset;
			indexbuffer[IndexOffset+1] = VertexOffset+1;
			indexbuffer[IndexOffset+2] = VertexOffset+3;

			// Second triangle
			indexbuffer[IndexOffset+3] = VertexOffset;
			indexbuffer[IndexOffset+4] = VertexOffset+3;
			indexbuffer[IndexOffset+5] = VertexOffset+2;

			IndexOffset  += 6;
			VertexOffset += 4;
		}

		// B
		for (int k = 0; k < this->mNb; k++)
		{
			// First triangle
			indexbuffer[IndexOffset]   = VertexOffset;
			indexbuffer[IndexOffset+1] = VertexOffset+1;
			indexbuffer[IndexOffset+2] = VertexOffset+3;

			// Second triangle
			indexbuffer[IndexOffset+3] = VertexOffset;
			indexbuffer[IndexOffset+4] = VertexOffset+3;
			indexbuffer[IndexOffset+5] = VertexOffset+2;

			// Third triangle
			indexbuffer[IndexOffset+6] = VertexOffset+2;
			indexbuffer[IndexOffset+7] = VertexOffset+3;
			indexbuffer[IndexOffset+8] = VertexOffset+5;

			// Fourth triangle
			indexbuffer[IndexOffset+9] = VertexOffset+2;
			indexbuffer[IndexOffset+10] = VertexOffset+5;
			indexbuffer[IndexOffset+11] = VertexOffset+4;

			IndexOffset  += 12;
			VertexOffset += 6;
		}

		// A
		for (int k = 0; k < this->mNa; k++)
		{
			// First triangle
			indexbuffer[IndexOffset]   = VertexOffset;
			indexbuffer[IndexOffset+1] = VertexOffset+1;
			indexbuffer[IndexOffset+2] = VertexOffset+3;

			// Second triangle
			indexbuffer[IndexOffset+3] = VertexOffset;
			indexbuffer[IndexOffset+4] = VertexOffset+3;
			indexbuffer[IndexOffset+5] = VertexOffset+2;

			// Third triangle
			indexbuffer[IndexOffset+6]   = VertexOffset+2;
			indexbuffer[IndexOffset+7] = VertexOffset+3;
			indexbuffer[IndexOffset+8] = VertexOffset+5;

			// Fourth triangle
			indexbuffer[IndexOffset+9] = VertexOffset+2;
			indexbuffer[IndexOffset+10] = VertexOffset+5;
			indexbuffer[IndexOffset+11] = VertexOffset+4;

			// Fifth triangle
			indexbuffer[IndexOffset+12] = VertexOffset+4;
			indexbuffer[IndexOffset+13] = VertexOffset+5;
			indexbuffer[IndexOffset+14] = VertexOffset+6;

			IndexOffset  += 15;
			VertexOffset += 7;
		}

		this->mIndexBuffer =Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT, this->mNumberOfTriangles*3, Ogre::HardwareBuffer::HBU_STATIC, true);
		this->mIndexBuffer->writeData(0, this->mIndexBuffer->getSizeInBytes(), indexbuffer,true);
		delete []indexbuffer;

		this->mSubMesh->indexData->indexBuffer = this->mIndexBuffer;
		this->mSubMesh->indexData->indexStart = 0;
		this->mSubMesh->indexData->indexCount = this->mNumberOfTriangles*3;

		this->mVertices = new VERTEX[this->mVertexCount];
}

