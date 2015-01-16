#include "GameOverReader.h"
#include "GameOver.h"
USING_NS_CC;

static GameOverReader* _instance = nullptr;
GameOverReader* GameOverReader::getInstance()
{
    if (!_instance)
    {
        _instance = new GameOverReader();
    }
    return _instance;
}
void GameOverReader::purge()
{
    CC_SAFE_DELETE(_instance);
}
Node* GameOverReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
	GameOver* node = GameOver::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    return node;
}
