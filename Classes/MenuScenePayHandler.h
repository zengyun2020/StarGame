#ifndef _MENU_SCENE_PAY_HANDLER_H_
#define _MENU_SCENE_PAY_HANDLER_H_
#include "cocos2d.h"

class MenuScenePayHandler
{       
    public:
        MenuScenePayHandler() {};
        ~MenuScenePayHandler() {};  
        void payCallback(int requestId,int resultId);
        bool getResult();
        static MenuScenePayHandler* getInstance();
		inline void setRequestId(int requestId){request_id = requestId;}
		inline int getRequestId(){return request_id;}
    private:
    	bool result;
		int request_id;
};
#endif

