#include "Audio.h"
#include "SimpleAudioEngine.h"

Audio* Audio::m_instance = nullptr;
Audio* Audio::getInstance(){
	if(m_instance == nullptr){
		m_instance = new Audio();
	}
	return m_instance;
}

void Audio::playBGM(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/music.ogg",true);
}

void Audio::playReadyGo(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/readygo.ogg",false);
}

void Audio::playPop(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/pop.ogg",false);
}

void Audio::playClick(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/select.ogg",false);
}


void Audio::playCombo(int size){
	if(size < 5)
		return;
	if(size >= 10){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_3.ogg",false);
	}else if(size >= 7){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_2.ogg",false);
	}else {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_1.ogg",false);
	}
}

void Audio::playCoin(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/coin.ogg",false);
}

void Audio::playCoinsIn(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/coinsin.ogg",false);
}

void Audio::playNextGameRound(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/NextGameRound.ogg",false);
}

void Audio::playPropBomb(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/Props_Bomb.ogg",false);
}

void Audio::playPropRainbow(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/Props_Rainbow.ogg",false);
}

void Audio::playPropPlusTime(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/Props_Paint.ogg",false);
}

void Audio::playClear(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/clear.ogg",false);
}

void Audio::playBeep(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/beep.ogg",false);
}

void Audio::playLanding(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/landing.ogg",false);
}

void Audio::playFireWorks(int type){
	if(type%3==0){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/fireworks_01.ogg",false);
	}else if(type%3==1){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/fireworks_02.ogg",false);
	}else if(type%3==2){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/fireworks_03.ogg",false);
	}
}

void Audio::prepare(){
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/music.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/readygo.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/pop.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_1.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_2.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_3.ogg");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/coin.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/coinsin.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/NextGameRound.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/Props_Bomb.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/Props_Rainbow.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/Props_Paint.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/clear.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/beep.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/landing.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/fireworks_01.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/fireworks_02.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/fireworks_03.ogg");
}