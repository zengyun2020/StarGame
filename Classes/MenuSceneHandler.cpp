#include "MenuSceneHandler.h"
#include "ui/UIText.h"
#include "MenuLayer.h"
#include "UpgradeScene.h"
#include "HelloWorldScene.h"
#include "PrizeLayer.h"
#include "PrizeScene.h"
#include "CallAndroidMethod.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
MenuSceneHandler::MenuSceneHandler()
{}
Widget::ccWidgetTouchCallback MenuSceneHandler::onLocateTouchCallback(const string &callBackName)
{
     if (callBackName == "buyGold")
    {
        return CC_CALLBACK_2(MenuSceneHandler::buyGold, this);
    }
	else if(callBackName == "buyTip"){
		return CC_CALLBACK_2(MenuSceneHandler::buyTip, this);
	}
	else if(callBackName == "upgrade"){
		return CC_CALLBACK_2(MenuSceneHandler::upgrade, this);
	}
	else if(callBackName == "startGame"){
		return CC_CALLBACK_2(MenuSceneHandler::startGame, this);
	}
	else if(callBackName == "getPackage"){
		return CC_CALLBACK_2(MenuSceneHandler::getPackage, this);
	}
	else if(callBackName == "set"){
		return CC_CALLBACK_2(MenuSceneHandler::set, this);
	}
	else if(callBackName == "moreGame"){
		return CC_CALLBACK_2(MenuSceneHandler::moreGame, this);
	}
    return nullptr;
}
Widget::ccWidgetClickCallback MenuSceneHandler::onLocateClickCallback(const string &callBackName)
{
    if (callBackName == "onClick")
    {
		return CC_CALLBACK_1(MenuSceneHandler::onClick, this);
    }
    return nullptr;
}
Widget::ccWidgetEventCallback MenuSceneHandler::onLocateEventCallback(const string &callBackName)
{
    if (callBackName == "onEvent")
    {
        return CC_CALLBACK_2(MenuSceneHandler::onEvent, this);
    }
    return nullptr;
}
void MenuSceneHandler::buyGold(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("buyGold");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		
	}
}

void MenuSceneHandler::buyTip(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("buyTip");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		auto layer = MenuLayer::create();
		layer->showPowerStone();
	}
}

void MenuSceneHandler::startGame(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("startGame");
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

void MenuSceneHandler::upgrade(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("upgrade");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){		
		Director::getInstance()->replaceScene(TransitionShrinkGrow::create(2.5,UpgradeScene::create()));
	}
}

void MenuSceneHandler::getPackage(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("getPackage");	
	auto layer = MenuLayer::create();
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		layer->clickGetPrize();
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		Director::getInstance()->replaceScene(TransitionShrinkGrow::create(2.5,PrizeScene::create()));
	}
}

void MenuSceneHandler::set(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("set");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		
	}
}

void MenuSceneHandler::moreGame(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("moreGame");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		CallAndroidMethod::getInstance()->showMoreGame();
	}
}

void MenuSceneHandler::onClick(cocos2d::Ref* sender){
	
}

void MenuSceneHandler::onEvent(cocos2d::Ref* sender, int eventType){
	
}
