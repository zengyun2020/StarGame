#include "PrizeReader.h"
#include "Prize.h"
USING_NS_CC;

static PrizeReader* _instance = nullptr;
PrizeReader* PrizeReader::getInstance()
{
    if (!_instance)
    {
        _instance = new PrizeReader();
    }
    return _instance;
}
void PrizeReader::purge()
{
    CC_SAFE_DELETE(_instance);
}
Node* PrizeReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
	Prize* node = Prize::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    return node;
}
