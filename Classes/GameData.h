#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

class GAMEDATA{
public:
	static GAMEDATA* getInstance();
	/*��ǰ�ȼ�*/
	void setCurLevel(int level);
	inline int getCurLevel(){return cur_level;}
	/*��һ�ȼ�*/
	inline int getNextLevel(){return next_level;}
	/*��߷�*/
	inline void setHistoryScore(int score){history_score = score;}
	inline int getHistoryScore(){return history_score;}
	/*��ǰ����*/
	inline void setCurScore(int score){cur_score = score;}
	inline int getCurScore(){return cur_score;}
	/*ͨ�ط���*/
	inline int getNextScore(){return next_score;}
	inline int getScoreByLevel(int level);
	/*�������*/
	inline void setGoldNum(int goldNum){gold_num = goldNum;}
	inline int getGoldNum(){return gold_num;}
	/*����ʯ����*/
	inline void setPowerStoneNum(int powerStoneNum){power_stone_num = powerStoneNum;}
	inline int getPowerStoneNum(){return power_stone_num;}
	/*��ҵȼ�*/
	inline void setUserLevel(int userLevel){user_level = userLevel;}
	inline int getUserLevel(){return user_level;}
	/*ʣ��齱����*/
	inline void setPrizeTimes(int prizeTimes){prize_times = prizeTimes;}
	inline int getPrizeTimes(){return prize_times;}

	inline void setAddTimeNum(int addTimeNum){add_time_num = addTimeNum;}
	inline int getAddTimeNum(){return add_time_num;}

	inline void setBombNum(int bombNum){bomb_num = bombNum;}
	inline int getBombNum(){return bomb_num;}

	inline void setReviveNum(int reviveNum){revive_num = reviveNum;}
	inline int getReviveNum(){return revive_num;}

	inline void setHasShowRegisterPay(bool showRegisterPay){show_register_pay = showRegisterPay;}
	inline bool hasShowRegisterPay(){return show_register_pay;}

	/*��������*/
	int getJiangli(int size);

	void saveHighestScore();
	void saveGoldNum();
	void savePowerStoneNum();
	void saveUserLevel();
	void savePrizeTimes();
	void saveAddTimeNum();
	void saveBombNum();
	void saveReviveNum();
	void saveShowRegisterPay();
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
	int add_time_num;
	int bomb_num;
	int revive_num;
	bool show_register_pay;
	friend class MenuLayer;
	friend class GameOverLayer;
};
#endif