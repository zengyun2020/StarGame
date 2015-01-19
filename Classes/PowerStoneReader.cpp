#include "PowerStoneReader.h"
#include "PowerStone.h"
USING_NS_CC;

static PowerStoneReader* _instance = nullptr;
PowerStoneReader* PowerStoneReader::getInstance()
{
    if (!_instance)
    {
        _instance = new PowerStoneReader();
    }
    return _instance;
}
void PowerStoneReader::purge()
{
    CC_SAFE_DELETE(_instance);
}
Node* PowerStoneReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
    PowerStone* node = PowerStone::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    return node;
}
