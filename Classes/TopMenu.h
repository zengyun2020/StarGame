#ifndef _TOPMENU_H_
#define _TOPMENU_H_
#include <string>
#include "cocos2d.h"
using namespace cocos2d;
class TopMenu : public Node{
public:
	virtual bool init();
	CREATE_FUNC(TopMenu);
	void refresh();
	void usePropsBomb();
	void usePropsTime();
	void PauseGame();
	void ResumeGame();

private:
	Label* highestScore;
	//Label* level;
	//Label* targetScore;
	Label* curScore;
	Layer* gamePause;
};
#endif