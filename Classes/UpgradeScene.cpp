#include "UpgradeScene.h"
#include "UpgradeLayer.h"

bool UpgradeScene::init(){
	if(!Scene::init()){
		return false;
	}
	this->addChild(UpgradeLayer::create());
	return true;
} 