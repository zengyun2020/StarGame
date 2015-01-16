#include "MenuSceneHandlerReader.h"
#include "MenuSceneHandler.h"
USING_NS_CC;

static MenuSceneHandlerReader* _instance = nullptr;
MenuSceneHandlerReader* MenuSceneHandlerReader::getInstance()
{
    if (!_instance)
    {
        _instance = new MenuSceneHandlerReader();
    }
    return _instance;
}
void MenuSceneHandlerReader::purge()
{
    CC_SAFE_DELETE(_instance);
}
Node* MenuSceneHandlerReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
    MenuSceneHandler* node = MenuSceneHandler::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    return node;
}
