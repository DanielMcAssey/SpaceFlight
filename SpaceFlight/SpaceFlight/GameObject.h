#ifndef ENT_GAMEOBJECT_H
#define ENT_GAMEOBJECT_H

class GameObject
{
protected:
	Ogre::SceneNode *mLocalNode;
	Ogre::SceneNode *mVisionNode;
	Ogre::SceneNode *mCameraNode;
	Ogre::Entity *mEntity;
	Ogre::SceneManager *mSceneManager;
	//Input manager here

public:
	Ogre::Vector3 getPosition();
	Ogre::SceneNode *getVisionNode();
	Ogre::SceneNode *getCameraNode();
	void setLocalNode(Ogre::SceneNode *_node);
	void setVisionNode(Ogre::SceneNode *_node);
	void setCameraNode(Ogre::SceneNode *_node);

	virtual void Update(Ogre::Real elapsedTime) = 0;
};

#endif // ENT_GAMEOBJECT_H
