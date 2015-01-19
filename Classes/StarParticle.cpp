#include "StarParticle.h"
#include "Star.h"

void showStarParticleEffect(int color,Point position,Node* node){
	CCLOG("Particle Particle Particle");
	ParticleExplosion* effect = ParticleExplosion::create();
	effect->setTexture(Director::getInstance()->getTextureCache()->addImage("star.png"));
	effect->setTotalParticles(200);//参数从15上调到200,15的时候没有效果
	effect->setStartColor(getColor4F(color));
	effect->setStartColorVar(Color4F(0,0,0,1));
	effect->setEndColor(getColor4F(color));
	effect->setEndColorVar(Color4F(0,0,0,1));
	effect->setStartSize(25.0f);
	effect->setGravity(Point(0,-300));
	effect->setDuration(0.2f);
	effect->setLife(2.0f);
	effect->setSpeed(100);
	effect->setSpeedVar(10);
	effect->setPosition(position);
	node->addChild(effect);
}

Color4F getColor4F(int color){
	switch(color){
	case Star::Color::PURPLE:
		return Color4F(0.74,0.30,0.99,1);
	case Star::Color::BLUE:
		return Color4F(84/255.0f,203/255.0f,254/255.0f,1);
	case Star::Color::RED:
		return Color4F(253/255.0f,80/255.0f,126/255.0f,1);
	case Star::Color::YELLOW:
		return Color4F(253/255.0f,234/255.0f,84/255.0f,1);
	case Star::Color::GREEN:
		return Color4F(132/255.0f,226/255.0f,111/255.0f,1);
	}
	return Color4F(1,1,1,0);
}