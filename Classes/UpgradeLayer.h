#ifndef _UPGRADELAYER_H_
#define _UPGRADELAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class UpgradeLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(UpgradeLayer);
	void back();
	void buyGold();
	void buyTip();
	void addTime();
	void refresh();
	void bomb();
};
#endif