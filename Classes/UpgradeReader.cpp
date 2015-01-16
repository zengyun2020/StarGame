#include "UpgradeReader.h"
#include "Upgrade.h"
USING_NS_CC;

static UpgradeReader* _instance = nullptr;
UpgradeReader* UpgradeReader::getInstance()
{
    if (!_instance)
    {
        _instance = new UpgradeReader();
    }
    return _instance;
}
void UpgradeReader::purge()
{
    CC_SAFE_DELETE(_instance);
}
Node* UpgradeReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
    Upgrade* node = Upgrade::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    return node;
}
