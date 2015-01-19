#ifndef _POWERSTONE_H_
#define _POWERSTONE_H_
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetCallBackHandlerProtocol.h"
#include "MenuLayer.h"

class PowerStone: public cocos2d::Node, public cocostudio::WidgetCallBackHandlerProtocol
{
    public:
        CREATE_FUNC(PowerStone)
        PowerStone();
        virtual cocos2d::ui::Widget::ccWidgetTouchCallback
        onLocateTouchCallback(const std::string &callBackName);
        virtual cocos2d::ui::Widget::ccWidgetClickCallback
        onLocateClickCallback(const std::string &callBackName);
        virtual cocos2d::ui::Widget::ccWidgetEventCallback
        onLocateEventCallback(const std::string &callBackName);
		void back(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
        void buy1(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
        void buy2(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
        void buy3(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
        void buy4(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
		void onClick(cocos2d::Ref* sender);
        void onEvent(cocos2d::Ref* sender, int eventType);
    private:
        std::vector<std::string> _touchTypes;
        std::string _click;
        std::vector<std::string> _eventTypes;
 };
#endif

