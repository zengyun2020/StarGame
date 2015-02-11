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
private:
	static TopMenu* _instance;
	//Label* highestScore;
	Label* level;
	Label* targetScore;
	Label* curScore;
	Layer* gamePause;
	Label* playerGold;
private:
	TopMenu();

};
#endif
