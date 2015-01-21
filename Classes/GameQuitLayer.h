#ifndef _GAMEQUITLAYER_H_
#define _GAMEQUITLAYER_H_
#include "cocos2d.h"

using namespace cocos2d;

class GameQuitLayer : public Node{
public:
	static GameQuitLayer* getInstance();
	virtual bool init();
	CREATE_FUNC(GameQuitLayer);
	void quit();
	void cancel();
private:
	static GameQuitLayer* _instance;
private:
	GameQuitLayer();
};

#endif // 
