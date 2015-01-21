#ifndef _TOPMENU_H_
#define _TOPMENU_H_
#include <string>
#include "cocos2d.h"
using namespace cocos2d;
class TopMenu : public Node{
public:
	static TopMenu* getInstance();
	virtual bool init();
	CREATE_FUNC(TopMenu);
	void refresh();
	void usePropsBomb();
	void usePropsTime();
	void PauseGame();
	void ResumeGame();
	void getSoudState(CCObject* pSender);
	void getMusicState(CCObject* pSender);
	void updatePropsNum();
	void goBack();

private:
	Label* highestScore;
	//Label* level;
	//Label* targetScore;
	Label* curScore;
	Layer* gamePause;
	Label* propBombNum;
	Label* propTimeNum;
	static TopMenu* _instance;
private:
	TopMenu();

};
#endif