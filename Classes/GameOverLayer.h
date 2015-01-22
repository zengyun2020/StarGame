#ifndef _GAMEOVERLAYER_H_
#define _GAMEOVERLAYER_H_

#include "cocos2d.h"

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
	void showRank(float dt);
	void showBeat(float dt);
	GameOverLayer getInstance();
private:
	float scoreNum;
	float animTime;
	int curScore;
	int rankNumTemp;
	float scale;
	LabelAtlas* labelScore;
	Sprite* currentRoundScore;
	LabelAtlas* rankNum;
	Sprite* rank;
	LabelAtlas* beatNum;
	Sprite* beatPer;
	MenuItemImage* startBtn;
};
#endif
