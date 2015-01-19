#ifndef _POWERSTONELAYER_H_
#define _POWERSTONELAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class PowerStoneLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(PowerStoneLayer);
	void back();
	static PowerStoneLayer* getInstance();
private:
	static PowerStoneLayer* layer;
};
#endif