#ifndef _CALLANDROIDMETHOD_H_
#define _CALLANDROIDMETHOD_H_

#include "cocos2d.h"

using namespace cocos2d;

class CallAndroidMethod{
public:
	void showMoreGame();
	void pay(int payPoint);
	void markPersonInfo(const char tag1,const char tag2);
	static CallAndroidMethod* getInstance();
private:
	CallAndroidMethod();
	static CallAndroidMethod* _instance;
};
#endif