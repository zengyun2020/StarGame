#ifndef _PRIZE_ANIM_READER_H_
#define _PRIZE_ANIM_READER_H_
#include "cocos2d.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class PrizeAnimReader : public cocostudio::NodeReader
{       
    public:
        PrizeAnimReader() {};
        ~PrizeAnimReader() {};   
        static PrizeAnimReader* getInstance();
        static void purge();
        cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};
#endif

