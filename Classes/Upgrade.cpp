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
   if (callBackName == "buyGold")
    {
        return CC_CALLBACK_2(Upgrade::buyGold, this);
    }
	else if(callBackName == "buyTip"){
		return CC_CALLBACK_2(Upgrade::buyTip, this);
	}
	else if(callBackName == "addTime"){
		return CC_CALLBACK_2(Upgrade::addTime, this);
	}
	else if(callBackName == "refresh"){
		return CC_CALLBACK_2(Upgrade::refresh, this);
	}
	else if(callBackName == "bomb"){
		return CC_CALLBACK_2(Upgrade::bomb, this);
	}
	else if(callBackName == "back"){
		return CC_CALLBACK_2(Upgrade::back, this);
	}
    return nullptr;
}
Widget::ccWidgetClickCallback Upgrade::onLocateClickCallback(const string &callBackName)
{
	CCLOG(">>>>>>>>>>>>on click");
    if (callBackName == "onClick")
    {
        return CC_CALLBACK_1(Upgrade::onClick, this);
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
void Upgrade::buyGold(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("buyGold");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){

	}
}

void Upgrade::buyTip(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("buyTip");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){

	}
}

void Upgrade::addTime(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("addTime");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){

	}
}

void Upgrade::refresh(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("refresh");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){

	}
}

void Upgrade::bomb(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("bomb");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){

	}
}

void Upgrade::back(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("back");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		UpgradeLayer *layer = UpgradeLayer::create();
		layer->back();
	}
}

void Upgrade::onClick(cocos2d::Ref* sender)
{
    CCLOG("onClick");
}


void Upgrade::onEvent(cocos2d::Ref* sender, int eventType)
{
    CCLOG("onEvent");
}
