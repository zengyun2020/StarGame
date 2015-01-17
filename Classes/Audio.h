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

	void playClear();//���
	void playCoin();//�������
	void playCoinsIn();//��ҽ��뱳��
	void playNextGameRound();//������һ�غ�
	void playPropBomb();//����ը��
	void playPropRainbow();//���߲ʺ�
	void playPropPlusTime();//���߼�ʱ
	void playBeep();//����ʱ
	void playLanding();//����
	void playFireWorks(int type);//����Ч��
	void prepare();
private:
	static Audio* m_instance;
};
#endif