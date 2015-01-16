#include "GameOver.h"
#include "ui/UIText.h"
#include "GameOverLayer.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
GameOver::GameOver()
{}
Widget::ccWidgetTouchCallback GameOver::onLocateTouchCallback(const string &callBackName)
{
    if (callBackName == "upgrade")//判断事件名，返回对应的函数。下同
    {
           return CC_CALLBACK_2(GameOver::onTouch, this);
    }
    return nullptr;
}
Widget::ccWidgetClickCallback GameOver::onLocateClickCallback(const string &callBackName)
{
    if (callBackName == "upgrade")
    {
        return CC_CALLBACK_1(GameOver::upgrade, this);
    }
	else if(callBackName == "continueGame"){
		return CC_CALLBACK_1(GameOver::continueGame, this);
	}
	else if(callBackName == "back"){
		return CC_CALLBACK_1(GameOver::back, this);
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
void GameOver::upgrade(cocos2d::Ref* sender)
{
    CCLOG("upgrade");
}

void GameOver::continueGame(cocos2d::Ref* sender)
{
    CCLOG("continueGame");
	GameOverLayer *layer = GameOverLayer::create();
	layer->continueGame();
}

void GameOver::back(cocos2d::Ref* sender)
{
    CCLOG("back");
	GameOverLayer *layer = GameOverLayer::create();
	layer->back();
}

void GameOver::onTouch(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("onTouch");
}
void GameOver::onEvent(cocos2d::Ref* sender, int eventType)
{
    CCLOG("onEvent");
}
