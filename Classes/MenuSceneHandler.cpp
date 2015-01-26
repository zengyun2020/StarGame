#include "MenuSceneHandler.h"
#include "ui/UIText.h"
#include "MenuLayer.h"
#include "HelloWorldScene.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
MenuSceneHandler::MenuSceneHandler()
{}
Widget::ccWidgetTouchCallback MenuSceneHandler::onLocateTouchCallback(const string &callBackName)
{
	if(callBackName == "startGame"){
		return CC_CALLBACK_2(MenuSceneHandler::startGame, this);
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

void MenuSceneHandler::startGame(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("startGame");
	auto layer = MenuLayer::create();
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
//		layer->startGame();
	}
}

void MenuSceneHandler::onClick(cocos2d::Ref* sender){
	
}

void MenuSceneHandler::onEvent(cocos2d::Ref* sender, int eventType){
	
}
