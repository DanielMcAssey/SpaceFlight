#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

class PlayerObject;

class BulletManager
{
public:
	BulletManager(PlayerObject *_player, Ogre::SceneManager *_sceneManager);
	~BulletManager(void);
	void CreateBullet(Ogre::Vector3 &_startPos, Ogre::Vector3 &_direction);
	void CreateMissile(Ogre::Vector3 &_startPos, Ogre::Vector3 &_direction);
	void Update(Ogre::Real elapsedTime);
protected:
	PlayerObject* mPlayer;
	Ogre::SceneManager* mSceneManager;

	Ogre::BillboardSet* mBulletsBillboard;
};

#endif // BULLET_MANAGER_H

