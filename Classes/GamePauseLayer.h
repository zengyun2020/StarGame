#ifndef _GAMEPAUSELAYER_H_
#define _GAMEPAUSELAYER_H_
#include "cocos2d.h"

using namespace cocos2d;

class GamePauseLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GamePauseLayer);
};

#endif // !_GAMEPAUSELAYER_H_
