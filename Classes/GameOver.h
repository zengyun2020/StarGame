#ifndef _GAME_OVER_H_
#define _GAME_OVER_H_
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetCallBackHandlerProtocol.h"

class GameOver: public cocos2d::Node, public cocostudio::WidgetCallBackHandlerProtocol
{
    public:
        CREATE_FUNC(GameOver)
        GameOver();
        virtual cocos2d::ui::Widget::ccWidgetTouchCallback
        onLocateTouchCallback(const std::string &callBackName);
        virtual cocos2d::ui::Widget::ccWidgetClickCallback
        onLocateClickCallback(const std::string &callBackName);
        virtual cocos2d::ui::Widget::ccWidgetEventCallback
        onLocateEventCallback(const std::string &callBackName);
		void onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
        void upgrade(cocos2d::Ref* sender);
        void continueGame(cocos2d::Ref* sender);
        void back(cocos2d::Ref* sender);
        void onEvent(cocos2d::Ref* sender, int eventType);
    private:
        std::vector<std::string> _touchTypes;
        std::string _click;
        std::vector<std::string> _eventTypes;
 };
#endif

