#ifndef _POWERSTONEREADER_H_
#define _POWERSTONEREADER_H_
#include "cocos2d.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class PowerStoneReader : public cocostudio::NodeReader
{       
    public:
        PowerStoneReader() {};
        ~PowerStoneReader() {};   
        static PowerStoneReader* getInstance();
        static void purge();
        cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};
#endif

