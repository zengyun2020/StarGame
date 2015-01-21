#include "MenuScenePayHandler.h"
#include "GameLayer.h"
#include "GameData.h"

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
	//request_id = requestId;
	switch (requestId)
	{
	case 1:
		//新手礼包
		GameLayer::_PauseTime=false;
		GAMEDATA::getInstance()->setAddTimeNum(5+GAMEDATA::getInstance()->getAddTimeNum());
		GAMEDATA::getInstance()->saveAddTimeNum();
		GAMEDATA::getInstance()->setBombNum(5+GAMEDATA::getInstance()->getBombNum());
		GAMEDATA::getInstance()->saveBombNum();
		TopMenu::getInstance()->updatePropsNum();
		break;
	case 2:
		//加时
		break;
	case 3:
		//炸弹
		break;
	case 4:
		//暂停界面礼包
		break;
	case 5:
		//复活
		break;
	case 6:
		//免费复活
		break;
	default:
		break;
	}
}

