#ifndef _MENULAYER_H_
#define _MENULAYER_H_

#include "cocos2d.h"
#include "SignIn.h"
#include "BlinkTitle.h"

using namespace cocos2d;

class MenuLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(MenuLayer);
	bool startGame(Touch* touch,Event* event);
	void autoStartGame(float dt);
	void showAbout();
	void getSoudState(CCObject* pSender);
	void getMusicState(CCObject* pSender);
	void quit();
	void cancel();
	void showQuit();
	void setSignIn(bool signIn);
	void pay();
	void refreshGold();
private:
	Menu* menuBgMusic;
	Menu* menuSoundEffect;
	Sprite* quitBg;
	Sprite* quitDesc;
	Menu* confirmMenu;
	Menu* cancelMenu;
	SignIn* signIn;
	BlinkTitle* title;
	bool hasShowQuitPay;
	Node* aboutLayer;
	LabelAtlas* gold;
};
#endif
