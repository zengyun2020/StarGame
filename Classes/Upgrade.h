#ifndef _UPGRADE_H_
#define _UPGRADE_H_
#include <string>
#include "cocos2d.h"
#include "FloatWord.h"
using namespace cocos2d;
class Upgrade : public Node{
public:
	static Upgrade* getInstance();
	virtual bool init();
	CREATE_FUNC(Upgrade);
	bool hideSelf(Touch* touch,Event* event);

private:
	static Upgrade* _instance;
	int signDay;
private:
	Upgrade();

};
#endif
