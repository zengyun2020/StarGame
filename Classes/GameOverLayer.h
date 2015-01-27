#ifndef _GAMEOVERLAYER_H_
#define _GAMEOVERLAYER_H_

#include "cocos2d.h"
#include "Upgrade.h"

using namespace cocos2d;

class GameOverLayer : public Layer{
public:
	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(GameOverLayer);
	void continueGame();
	void back();
	void getSoudState(CCObject* pSender);
	void getMusicState(CCObject* pSender);
	GameOverLayer getInstance();
private:
	float scoreNum;
	float animTime;
	int curScore;
	int rankNumTemp;
	float rotation;
	bool hasShowUpgrade;
	bool canClick;
	LabelAtlas* labelScore;
	MenuItemImage* startBtn;
	Upgrade* upgrade;
};
#endif
