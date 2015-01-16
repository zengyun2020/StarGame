#ifndef _MENU_SCENE_HANDLER_READER_H_
#define _MENU_SCENE_HANDLER_READER_H_
#include "cocos2d.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class MenuSceneHandlerReader : public cocostudio::NodeReader
{       
    public:
        MenuSceneHandlerReader() {};
        ~MenuSceneHandlerReader() {};   
        static MenuSceneHandlerReader* getInstance();
        static void purge();
        cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};
#endif

