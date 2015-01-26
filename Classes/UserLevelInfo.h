#ifndef _USERLEVELINFO_H_
#define _USERLEVELINFO_H_
#include <string>
#include "cocos2d.h"
#include "FloatWord.h"
using namespace cocos2d;
class UserLevelInfo : public Node{
public:
	static UserLevelInfo* getInstance();
	virtual bool init();
	CREATE_FUNC(UserLevelInfo);
	bool hideSelf(Touch* touch,Event* event);

private:
	static UserLevelInfo* _instance;
private:
	UserLevelInfo();

};
#endif
