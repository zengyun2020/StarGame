#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include "cocos2d.h"
#include "FloatWord.h"
#include "TopMenu.h"
#include "StarMatrix.h"

using namespace cocos2d;
class StarMatrix;

class GameLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	
	void floatLevelWord();
	//void floatTargetScoreWord();
	void removeFloatWord();
	void showStarMatrix();
	virtual void update(float delta);
	virtual bool onTouchBegan(Touch* touch,Event* event);
	void refreshMenu();
	void showLinkNum(int size);
	void showGameTime(int time);
	void hideLinkNum();
	void floatLeftStarMsg(int leftNum);
	void gotoNextLevel();
	void gotoGameOver();

	void updateCustom(float dt);
	void initTime();  //重置游戏时间
	int getTime();
	void plusTime(int time);
	
private:
	FloatWord* _levelMsg;
	//FloatWord* _targetScore;
	TopMenu* menu;
	StarMatrix* matrix;
	Label* linkNum;
	Label* gameTime;//游戏时间显示
	int totalTime;//游戏时间
};
#endif