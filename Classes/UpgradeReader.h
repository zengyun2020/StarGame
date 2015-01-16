#ifndef _UPGRADE_READER_H_
#define _UPGRADE_READER_H_
#include "cocos2d.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class UpgradeReader : public cocostudio::NodeReader
{       
    public:
        UpgradeReader() {};
        ~UpgradeReader() {};   
        static UpgradeReader* getInstance();
        static void purge();
        cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};
#endif

