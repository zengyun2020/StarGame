#include "PrizeAnimReader.h"
#include "PrizeAnim.h"
USING_NS_CC;

static PrizeAnimReader* _instance = nullptr;
PrizeAnimReader* PrizeAnimReader::getInstance()
{
    if (!_instance)
    {
        _instance = new PrizeAnimReader();
    }
    return _instance;
}
void PrizeAnimReader::purge()
{
    CC_SAFE_DELETE(_instance);
}
Node* PrizeAnimReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
	PrizeAnim* node = PrizeAnim::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    return node;
}
