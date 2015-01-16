#ifndef _GAMEOVERLAYER_H_
#define _GAMEOVERLAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class GameOverLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameOverLayer);
	void continueGame();
	void back();
	void upgrade();
	GameOverLayer getInstance();
};
#endif