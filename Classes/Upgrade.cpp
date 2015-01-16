#include "Upgrade.h"
#include "ui/UIText.h"
#include "MenuLayer.h"
#include "UpgradeLayer.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
Upgrade::Upgrade()
{}
Widget::ccWidgetTouchCallback Upgrade::onLocateTouchCallback(const string &callBackName)
{
    if (callBackName == "buyGold")//判断事件名，返回对应的函数。下同
    {
           return CC_CALLBACK_2(Upgrade::onTouch, this);
    }
    return nullptr;
}
Widget::ccWidgetClickCallback Upgrade::onLocateClickCallback(const string &callBackName)
{
	CCLOG(">>>>>>>>>>>>on click");
    if (callBackName == "buyGold")
    {
        return CC_CALLBACK_1(Upgrade::buyGold, this);
    }
	else if(callBackName == "buyTip"){
		return CC_CALLBACK_1(Upgrade::buyTip, this);
	}
	else if(callBackName == "addTime"){
		return CC_CALLBACK_1(Upgrade::addTime, this);
	}
	else if(callBackName == "refresh"){
		return CC_CALLBACK_1(Upgrade::refresh, this);
	}
	else if(callBackName == "bomb"){
		return CC_CALLBACK_1(Upgrade::bomb, this);
	}
	else if(callBackName == "back"){
		return CC_CALLBACK_1(Upgrade::back, this);
	}
    return nullptr;
}
Widget::ccWidgetEventCallback Upgrade::onLocateEventCallback(const string &callBackName)
{
    if (callBackName == "onEvent")
    {
        return CC_CALLBACK_2(Upgrade::onEvent, this);
    }
    return nullptr;
}
void Upgrade::buyGold(cocos2d::Ref* sender)
{
    CCLOG("buyGold");
}

void Upgrade::buyTip(cocos2d::Ref* sender)
{
    CCLOG("buyTip");
}

void Upgrade::addTime(cocos2d::Ref* sender)
{
    CCLOG("addTime");
}

void Upgrade::refresh(cocos2d::Ref* sender)
{
    CCLOG("refresh");
}

void Upgrade::bomb(cocos2d::Ref* sender)
{
    CCLOG("bomb");
}

void Upgrade::back(cocos2d::Ref* sender)
{
    CCLOG("back");
	UpgradeLayer *layer = UpgradeLayer::create();
	layer->back();
}

void Upgrade::onTouch(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("onTouch");
}
void Upgrade::onEvent(cocos2d::Ref* sender, int eventType)
{
    CCLOG("onEvent");
}
