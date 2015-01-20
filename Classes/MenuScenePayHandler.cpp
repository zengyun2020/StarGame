#include "MenuScenePayHandler.h"

static MenuScenePayHandler* _instance = nullptr;
MenuScenePayHandler* MenuScenePayHandler::getInstance()
{
    if (!_instance)
    {
        _instance = new MenuScenePayHandler();
    }
    return _instance;
}

void MenuScenePayHandler::payCallback(int requestId,int resultId){
	if(resultId == 0){
		result = false;
	}else{
		result = true;
	}
}

bool MenuScenePayHandler::getResult(){
	return result;
}
