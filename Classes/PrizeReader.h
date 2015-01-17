#ifndef _PRIZE_READER_H_
#define _PRIZE_READER_H_
#include "cocos2d.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class PrizeReader : public cocostudio::NodeReader
{       
    public:
        PrizeReader() {};
        ~PrizeReader() {};   
        static PrizeReader* getInstance();
        static void purge();
        cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};
#endif

