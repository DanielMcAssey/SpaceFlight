#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "MovableText.h"

class MenuScreen : public BaseScreen
{
public:
	MenuScreen(void);
	~MenuScreen(void);

	DECLARE_SCREENSTATE_CLASS(MenuScreen);

	void Load();
	void Unload();

	void Update(Ogre::Real elapsedTime);

	bool mShutdown;
protected:
	Ogre::MaterialPtr mBGMaterial;
	Ogre::Rectangle2D* mBGRect;
	Ogre::Vector2 mLogoPos;

	Ogre::SceneNode* menuNode;

	Ogre::MovableText* startupMsg;
	Ogre::MovableText* menuText;

	Ogre::SceneNode* startupTextNode;
	Ogre::SceneNode* menuTextNode;

	bool startPressed;
	int menuIndex;
	int maxMenuItems;
	std::vector<Ogre::MovableText*> textStorage;
};

#endif // MENUSCREEN_H