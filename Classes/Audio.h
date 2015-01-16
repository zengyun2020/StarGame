#ifndef _AUDIO_H_
#define _AUDIO_H_
class Audio{
public:
	static Audio* getInstance();
	void playBGM();
	void playReadyGo();
	void playClick();
	void playPop();
	void playCombo(int size);
	void playClear();
	void playCoin();
	void playCoinsIn();
	void playNextGameRound();
	void playPropBomb();
	void playPropRainbow();
	void playPropPlusTime();
	void playBeep();
	void playLanding();
	void playFireWorks(int type);
	void prepare();
private:
	static Audio* m_instance;
};
#endif