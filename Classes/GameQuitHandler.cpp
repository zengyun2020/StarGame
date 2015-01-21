#include "GameQuitHandler.h"
#include "GameQuitLayer.h"

static GameQuitHandler* _instance = nullptr;
GameQuitHandler* GameQuitHandler::getInstance()
{
    if (!_instance)
    {
        _instance = new GameQuitHandler();
    }
    return _instance;
}

void GameQuitHandler::quitGame(){
	//layer = GameQuitLayer::create();
}

void GameQuitHandler::quit(){
	Director::getInstance()->end();
}

void GameQuitHandler::cancel(){
	layer->removeFromParentAndCleanup(true);
}
