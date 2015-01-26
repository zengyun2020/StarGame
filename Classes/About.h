#ifndef _ABOUT_H_
#define _ABOUT_H_
#include <string>
#include "cocos2d.h"
#include "FloatWord.h"
using namespace cocos2d;
class About : public Node{
public:
	static About* getInstance();
	virtual bool init();
	CREATE_FUNC(About);
	bool hideSelf(Touch* touch,Event* event);

private:
	static About* _instance;
private:
	About();

};
#endif
