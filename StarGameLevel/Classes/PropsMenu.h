#ifndef _PROPSMENU_H_
#define _PROPSMENU_H_
#include <string>
#include "cocos2d.h"
using namespace cocos2d;
class PropsMenu : public Node{
public:
	static PropsMenu* getInstance();
	virtual bool init();
	CREATE_FUNC(PropsMenu);
	void pay();
	void usePropsBomb();
	void usePropsTime();
private:
	static PropsMenu* _instance;
private:
	PropsMenu();
};
#endif
