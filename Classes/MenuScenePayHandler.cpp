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
		//�������
		GameLayer::_PauseTime=false;
		GAMEDATA::getInstance()->setAddTimeNum(5+GAMEDATA::getInstance()->getAddTimeNum());
		GAMEDATA::getInstance()->saveAddTimeNum();
		GAMEDATA::getInstance()->setBombNum(5+GAMEDATA::getInstance()->getBombNum());
		GAMEDATA::getInstance()->saveBombNum();
		TopMenu::getInstance()->updatePropsNum();
		break;
	case 2:
		//��ʱ
		break;
	case 3:
		//ը��
		break;
	case 4:
		//��ͣ�������
		break;
	case 5:
		//����
		break;
	case 6:
		//��Ѹ���
		break;
	default:
		break;
	}
}

