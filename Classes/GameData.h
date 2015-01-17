#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

class GAMEDATA{
public:
	static GAMEDATA* getInstance();
	/*当前等级*/
	void setCurLevel(int level);
	inline int getCurLevel(){return cur_level;}
	/*下一等级*/
	inline int getNextLevel(){return next_level;}
	/*最高分*/
	inline void setHistoryScore(int score){history_score = score;}
	inline int getHistoryScore(){return history_score;}
	/*当前分数*/
	inline void setCurScore(int score){cur_score = score;}
	inline int getCurScore(){return cur_score;}
	/*通关分数*/
	inline int getNextScore(){return next_score;}
	inline int getScoreByLevel(int level);
	/*金币数量*/
	inline void setGoldNum(int goldNum){gold_num = goldNum;}
	inline int getGoldNum(){return gold_num;}
	/*能量石数量*/
	inline void setPowerStoneNum(int powerStoneNum){power_stone_num = powerStoneNum;}
	inline int getPowerStoneNum(){return power_stone_num;}
	/*玩家等级*/
	inline void setUserLevel(int userLevel){user_level = userLevel;}
	inline int getUserLevel(){return user_level;}
	/*剩余抽奖次数*/
	inline void setPrizeTimes(int prizeTimes){prize_times = prizeTimes;}
	inline int getPrizeTimes(){return prize_times;}

	/*奖励分数*/
	int getJiangli(int size);

	void saveHighestScore();
	void saveGoldNum();
	void savePowerStoneNum();
	void saveUserLevel();
	void savePrizeTimes();
private:
	GAMEDATA();
	void init();
private:
	static GAMEDATA* _instance;
	int cur_level;
	int next_level;
	int history_score;
	int cur_score;
	int next_score;
	int gold_num;
	int power_stone_num;
	int user_level;
	int prize_times;
	friend class MenuLayer;
	friend class GameOverLayer;
};
#endif