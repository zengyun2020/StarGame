#ifndef _GAMEQUITHANDLER_H_
#define _GAMEQUITHANDLER_H_
#include "GameQuitLayer.h"

class GameQuitHandler
{       
    public:
        GameQuitHandler() {};
        ~GameQuitHandler() {};  
        void quitGame();
        void quit();
		void cancel();
        static GameQuitHandler* getInstance();
    private:
    	GameQuitLayer* layer;
};
#endif

