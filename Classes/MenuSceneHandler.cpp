#include "MenuSceneHandler.h"
#include "ui/UIText.h"
#include "MenuLayer.h"
#include "UpgradeScene.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
MenuSceneHandler::MenuSceneHandler()
{}
Widget::ccWidgetTouchCallback MenuSceneHandler::onLocateTouchCallback(const string &callBackName)
{
    if (callBackName == "buyGold")//判断事件名，返回对应的函数。下同
    {
           return CC_CALLBACK_2(MenuSceneHandler::onTouch, this);
    }
    return nullptr;
}
Widget::ccWidgetClickCallback MenuSceneHandler::onLocateClickCallback(const string &callBackName)
{
    if (callBackName == "buyGold")
    {
        return CC_CALLBACK_1(MenuSceneHandler::buyGold, this);
    }
	else if(callBackName == "buyTip"){
		return CC_CALLBACK_1(MenuSceneHandler::buyTip, this);
	}
	else if(callBackName == "upgrade"){
		return CC_CALLBACK_1(MenuSceneHandler::upgrade, this);
	}
	else if(callBackName == "startGame"){
		return CC_CALLBACK_1(MenuSceneHandler::startGame, this);
	}
	else if(callBackName == "getPackage"){
		return CC_CALLBACK_1(MenuSceneHandler::getPackage, this);
	}
	else if(callBackName == "set"){
		return CC_CALLBACK_1(MenuSceneHandler::set, this);
	}
	else if(callBackName == "moreGame"){
		return CC_CALLBACK_1(MenuSceneHandler::moreGame, this);
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
void MenuSceneHandler::buyGold(cocos2d::Ref* sender)
{
    CCLOG("buyGold");
}

void MenuSceneHandler::buyTip(cocos2d::Ref* sender)
{
    CCLOG("buyTip");
}

void MenuSceneHandler::startGame(cocos2d::Ref* sender)
{
    CCLOG("startGame");
	MenuLayer *layer = MenuLayer::create();
	layer->startGame();
}

void MenuSceneHandler::upgrade(cocos2d::Ref* sender)
{
    CCLOG("upgrade");
	Director::getInstance()->replaceScene(UpgradeScene::create());
}

void MenuSceneHandler::getPackage(cocos2d::Ref* sender)
{
    CCLOG("getPackage");
}

void MenuSceneHandler::set(cocos2d::Ref* sender)
{
    CCLOG("set");
}

void MenuSceneHandler::moreGame(cocos2d::Ref* sender)
{
    CCLOG("moreGame");
}

void MenuSceneHandler::onTouch(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("onTouch");
}
void MenuSceneHandler::onEvent(cocos2d::Ref* sender, int eventType)
{
    CCLOG("onEvent");
}
