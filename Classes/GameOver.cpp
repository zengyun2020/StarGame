#include "GameOver.h"
#include "ui/UIText.h"
#include "GameOverLayer.h"
#include "UpgradeLayer.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
GameOver::GameOver()
{}
Widget::ccWidgetTouchCallback GameOver::onLocateTouchCallback(const string &callBackName)
{
    if (callBackName == "upgrade")
    {
        return CC_CALLBACK_2(GameOver::upgrade, this);
    }
	else if(callBackName == "continueGame"){
		return CC_CALLBACK_2(GameOver::continueGame, this);
	}
	else if(callBackName == "back"){
		return CC_CALLBACK_2(GameOver::back, this);
	}
    return nullptr;
}
Widget::ccWidgetClickCallback GameOver::onLocateClickCallback(const string &callBackName)
{
    if (callBackName == "onClick")
    {
        return CC_CALLBACK_1(GameOver::onClick, this);
    }
    return nullptr;
}
Widget::ccWidgetEventCallback GameOver::onLocateEventCallback(const string &callBackName)
{
    if (callBackName == "onEvent")
    {
        return CC_CALLBACK_2(GameOver::onEvent, this);
    }
    return nullptr;
}
void GameOver::upgrade(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("upgrade");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		
	}
}

void GameOver::continueGame(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("continueGame");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		GameOverLayer *layer = GameOverLayer::create();
		layer->continueGame();
	}
}

void GameOver::back(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("back");
	if(type == cocos2d::ui::Widget::TouchEventType::BEGAN){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::CANCELED){
		
	}
	else if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
		GameOverLayer *layer = GameOverLayer::create();
		layer->back();
	}
}

void GameOver::onClick(cocos2d::Ref* sender)
{
    CCLOG("onClick");
}

void GameOver::onEvent(cocos2d::Ref* sender, int eventType)
{
    CCLOG("onEvent");
}
