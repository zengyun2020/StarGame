#ifndef _PRIZELAYER_H_
#define _PRIZELAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class PrizeLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(PrizeLayer);
	void getPrize();
	void back();
	void startPrizeAction();
	void stopPrizeAction();
	void startBtnAction();
	void stopBtnAction();
	PrizeLayer getInstance();

private:
	Label *labelPrize;
	Node *rootNode2;
};
#endif