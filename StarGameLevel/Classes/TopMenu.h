#ifndef _TOPMENU_H_
#define _TOPMENU_H_
#include <string>
#include "cocos2d.h"
#include "FloatWord.h"
using namespace cocos2d;
class TopMenu : public Node{
public:
	static TopMenu* getInstance();
	virtual bool init();
	CREATE_FUNC(TopMenu);
	void refresh(int score);
	void PauseGame();
	void cleanScore();
	void refreshGold();
	void pay();
	void payGift();
	void refreshTargetScore();
	void usePropsBomb();//ʹ��ը��
	void usePropsHammer();//ʹ�ô���
	void usePropsRainBow();//ʹ������
	void usePropsMagic();//ʹ��Ⱦɫ
	void cancelUseProp();
	void hideProps();//�������е���
	void showProps();
	void hideMenuGift();
	void showRePaly();
	void rePlayResultSuccess();
	void rePlayResultFail();
private:
	static TopMenu* _instance;
	//Label* highestScore;
	Label* level;
	Label* targetScore;
	Label* curScore;
	Layer* gamePause;
	Label* playerGold;
	MenuItemImage* hammerBtn;
	MenuItemImage* magicBtn;
	MenuItemImage* rainbowBtn;
	MenuItemImage* bombBtn;
	Label* propInfo;
	Menu* cancel;
	Menu* props;
	Label* price_hammer;
	Label* price_magic;
	Label* price_rainbow;
	Label* price_bomb;
	Menu* menuGift;
    Sprite* rePlay;
private:
	TopMenu();

};
#endif
