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
	void usePropsBomb();
	void usePropsTime();
	void PauseGame();
	void ResumeGame();
	void getSoudState(CCObject* pSender);
	void getMusicState(CCObject* pSender);
	void updatePropsNum();
	void goBack();
	void stopScaleAction();
	void cleanScore();

private:
	static TopMenu* _instance;
	Label* highestScore;
	//Label* level;
	//Label* targetScore;
	Label* curScore;
	Layer* gamePause;
	Label* propBombNum;
	Label* propTimeNum;
	MenuItemImage* BombBtn;
	MenuItemImage* TimeBtn;
	FloatWord* plusTimeWord;
private:
	TopMenu();

};
#endif