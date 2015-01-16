#ifndef _MENU_SCENE_HANDLER_H_
#define _MENU_SCENE_HANDLER_H_
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetCallBackHandlerProtocol.h"

class MenuSceneHandler: public cocos2d::Node, public cocostudio::WidgetCallBackHandlerProtocol
{
    public:
        CREATE_FUNC(MenuSceneHandler)
        MenuSceneHandler();
        virtual cocos2d::ui::Widget::ccWidgetTouchCallback
        onLocateTouchCallback(const std::string &callBackName);
        virtual cocos2d::ui::Widget::ccWidgetClickCallback
        onLocateClickCallback(const std::string &callBackName);
        virtual cocos2d::ui::Widget::ccWidgetEventCallback
        onLocateEventCallback(const std::string &callBackName);
		void onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
        void buyGold(cocos2d::Ref* sender);
        void buyTip(cocos2d::Ref* sender);
        void upgrade(cocos2d::Ref* sender);
        void startGame(cocos2d::Ref* sender);
        void getPackage(cocos2d::Ref* sender);
        void set(cocos2d::Ref* sender);
        void moreGame(cocos2d::Ref* sender);
        void onEvent(cocos2d::Ref* sender, int eventType);
    private:
        std::vector<std::string> _touchTypes;
        std::string _click;
        std::vector<std::string> _eventTypes;
 };
#endif

