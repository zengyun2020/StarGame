#ifndef _GAME_OVER_READER_H_
#define _GAME_OVER_READER_H_
#include "cocos2d.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class GameOverReader : public cocostudio::NodeReader
{       
    public:
        GameOverReader() {};
        ~GameOverReader() {};   
        static GameOverReader* getInstance();
        static void purge();
        cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};
#endif

