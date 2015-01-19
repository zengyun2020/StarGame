#include "PowerStone.h"
#include "ui/UIText.h"
#include "MenuLayer.h"
#include "UpgradeScene.h"
#include "HelloWorldScene.h"
#include "PrizeLayer.h"
#include "PrizeScene.h"
#include "CallAndroidMethod.h"
#include "PowerStoneLayer.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
PowerStone::PowerStone()
{}
Widget::ccWidgetTouchCallback PowerStone::onLocateTouchCallback(const string &callBackName)
{
     if (callBackName == "back")
    {
        return CC_CALLBACK_2(PowerStone::back, this);
    }
	else if(callBackName == "buy1"){
		return CC_CALLBACK_2(PowerStone::buy1, this);
	}
	else if(callBackName == "buy2"){
		return CC_CALLBACK_2(PowerStone::buy2, this);
	}
	else if(callBackName == "buy3"){
		return CC_CALLBACK_2(PowerStone::buy3, this);
	}
	else if(callBackName == "buy4"){
		return CC_CALLBACK_2(PowerStone::buy4, this);
	}
    return nullptr;
}
Widget::ccWidgetClickCallback PowerStone::onLocateClickCallback(const string &callBackName)
{
    if (callBackName == "onClick")
    {
		return CC_CALLBACK_1(PowerStone::onClick, this);
    }
    return nullptr;
}
Widget::ccWidgetEventCallback PowerStone::onLocateEventCallback(const string &callBackName)
{
    if (callBackName == "onEvent")
    {
        return CC_CALLBACK_2(PowerStone::onEvent, this);
    }
    return nullptr;
}

void PowerStone::back(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("back");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		auto layer = PowerStoneLayer::create();
		layer->back();
	}
}

void PowerStone::buy1(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("buy1");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		
	}
}

void PowerStone::buy2(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("buy2");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		
	}
}

void PowerStone::buy3(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("buy3");
	auto layer = MenuLayer::create();
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		//layer->stopAction();
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		//layer->startAction();
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		layer->startGame();
	}
}

void PowerStone::buy4(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("buy4");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){		
		Director::getInstance()->replaceScene(TransitionShrinkGrow::create(2.5,UpgradeScene::create()));
	}
}

void PowerStone::onClick(cocos2d::Ref* sender){
	
}

void PowerStone::onEvent(cocos2d::Ref* sender, int eventType){
	
}
