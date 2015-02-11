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
private:

	Point getPositionByIndex(int i,int j);
	Star* getStarByTouch(const Point& p);
	void genSelectedList(Star* s);
	void genBombList(Star* s);//��������ը����Ҫ�����Ķ���
	void deleteSelectedList();
	void deleteBombList();
	void doHammer(Star* s);
	void adjustMatrix();
	bool isEnded();
	void clearMatrixOneByOne();
	int getLeftStarNum();
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
public :
	static bool BombClick;
	static float ONE_CLEAR_TIME;
};
#endif