#ifndef _STARMATRIX_H_
#define _STARMATRIX_H_
#include "cocos2d.h"
#include "Star.h"
#include "GameLayer.h"
#include <deque>
using namespace cocos2d;
using namespace std;
class GameLayer;
class StarMatrix : public Node{
public:
	static StarMatrix* create(GameLayer* layer);
	virtual bool init(GameLayer* layer);
	void updateStar(float delta);
	void onTouch(const Point& p);
	void setNeedClear(bool b);
	void setAcceptTouch(bool b);
	void initMatrix();
	void useBombAuto(Star* s);
	Animation* createAnimation(std::string prefixName, int framesNum, float delay);
	void update(float dt);
private:

	Point getPositionByIndex(int i,int j);
	Star* getStarByTouch(const Point& p);
	void genSelectedList(Star* s);
	void genBombList(Star* s);//��������ը����Ҫ�����Ķ���
	void deleteSelectedList();
	void deleteBombList();
	void doHammer(Star* s);
	void doMagic(Star* s);
	void doRainbow();
	void adjustMatrix();
	bool isEnded();
	void clearMatrixOneByOne();
	int getLeftStarNum();
	void showHammerAnim();
	void showMagicAnim();
	void showRainbowAnim();
	void showBombAnim();
	void setHammerPosition(Star* s);
	void setMagicposition(Star* s);
	void setBombPosition(Star* s);
	void removeAnimSprite();
	Star* getHammerStar();//ʹ�õ���ʱĬ����ʾλ��
public:
	const static int ROW_NUM = 10;
	const static int COL_NUM = 10;
private:
	Star* stars[ROW_NUM][COL_NUM];
	deque<Star*> selectedList;
	GameLayer* m_layer;
	bool needClear;
	bool clearOneByOne;
	bool acceptTouch;
	bool touchLeft;
	Sprite* animSprite;
	float clearSumTime;
	int selectedListSize;
	bool isShowAnim;
public :
	static bool BombClick;//ʹ��ը��
	static bool MagicClick;//ʹ��ħ��
	static bool RainBowClick;//ʹ������
	static bool HammerClick;//ʹ�ô���
	static float ONE_CLEAR_TIME;
	static bool removeAnim;
};
#endif