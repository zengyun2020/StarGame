#ifndef _MENU_SCENE_PAY_HANDLER_H_
#define _MENU_SCENE_PAY_HANDLER_H_
#include "cocos2d.h"

class MenuScenePayHandler
{       
    public:
        MenuScenePayHandler() {};
        ~MenuScenePayHandler() {};  
        void payCallback(jclass jcl,int requestId,int resultId);
        bool getResult();
        static MenuScenePayHandler* getInstance();
    private:
    	bool result;
};
#endif

