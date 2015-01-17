#include "PrizeScene.h"
#include "PrizeLayer.h"

bool PrizeScene::init(){
	if(!Scene::init()){
		return false;
	}
	this->addChild(PrizeLayer::create());
	return true;
} 