//
//  WWLoginScreen.hpp
//  WarOfWords
//
//  Created by Gurudath on 3/17/17.
//
//

#ifndef WWLoginScreen_h
#define WWLoginScreen_h

#include "WWSocialManager.h"
#include <stdio.h>
#include "WWGameUtility.h"

#include "cocos2d.h"
using namespace cocos2d;
using namespace cocos2d::network;

class WWLoginScreen : public cocos2d::Layer
{
private:
    MenuItemLabel* loginBtn;
    
public:
    static cocos2d::Scene* createScene();
    void afterLoginCompleted(bool pIsDone);    
    virtual bool init();
    
    void onClickOnLogin(Ref* pSender);
    
    //connecting server functions
    void loginToServer();
    void onLoginRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(WWLoginScreen);
};


#endif /* WWLoginScreen_hpp */
