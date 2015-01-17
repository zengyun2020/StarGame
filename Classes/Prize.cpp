#include "Prize.h"
#include "ui/UIText.h"
#include "GameOverLayer.h"
#include "PrizeLayer.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
Prize::Prize()
{}
Widget::ccWidgetTouchCallback Prize::onLocateTouchCallback(const string &callBackName)
{
    if (callBackName == "getPrize")
    {
        return CC_CALLBACK_2(Prize::getPrize, this);
    }
	else if(callBackName == "back"){
		return CC_CALLBACK_2(Prize::back, this);
	}
    return nullptr;
}
Widget::ccWidgetClickCallback Prize::onLocateClickCallback(const string &callBackName)
{
    if (callBackName == "onClick")
    {
        return CC_CALLBACK_1(Prize::onClick, this);
    }
    return nullptr;
}
Widget::ccWidgetEventCallback Prize::onLocateEventCallback(const string &callBackName)
{
    if (callBackName == "onEvent")
    {
        return CC_CALLBACK_2(Prize::onEvent, this);
    }
    return nullptr;
}
void Prize::getPrize(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("getPrize");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		auto layer = PrizeLayer::create();
		layer->getPrize();
	}
}

void Prize::back(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("back");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		auto layer = PrizeLayer::create();
		layer->back();
	}
}

void Prize::onClick(cocos2d::Ref* sender)
{
    CCLOG("onClick");
}

void Prize::onEvent(cocos2d::Ref* sender, int eventType)
{
    CCLOG("onEvent");
}
