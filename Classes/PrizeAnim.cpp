#include "PrizeAnim.h"
#include "ui/UIText.h"
#include "GameOverLayer.h"
#include "PrizeLayer.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
PrizeAnim::PrizeAnim()
{}
Widget::ccWidgetTouchCallback PrizeAnim::onLocateTouchCallback(const string &callBackName)
{
    if (callBackName == "getPrize")
    {
        return CC_CALLBACK_2(PrizeAnim::getPrize, this);
    }
	else if(callBackName == "back"){
		return CC_CALLBACK_2(PrizeAnim::back, this);
	}
    return nullptr;
}
Widget::ccWidgetClickCallback PrizeAnim::onLocateClickCallback(const string &callBackName)
{
    if (callBackName == "onClick")
    {
        return CC_CALLBACK_1(PrizeAnim::onClick, this);
    }
    return nullptr;
}
Widget::ccWidgetEventCallback PrizeAnim::onLocateEventCallback(const string &callBackName)
{
    if (callBackName == "onEvent")
    {
        return CC_CALLBACK_2(PrizeAnim::onEvent, this);
    }
    return nullptr;
}
void PrizeAnim::getPrize(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
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

void PrizeAnim::back(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
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

void PrizeAnim::onClick(cocos2d::Ref* sender)
{
    CCLOG("onClick");
}

void PrizeAnim::onEvent(cocos2d::Ref* sender, int eventType)
{
    CCLOG("onEvent");
}
