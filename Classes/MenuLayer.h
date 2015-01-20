#ifndef _MENULAYER_H_
#define _MENULAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class MenuLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(MenuLayer);
	void startGame();
	void stopAction();
	void startAction();
	void setGoldNum();
	void clickGetPrize();
	void showPowerStone();
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
private:
	Menu* menuBgMusic;
	Menu* menuSoundEffect;
};
#endif