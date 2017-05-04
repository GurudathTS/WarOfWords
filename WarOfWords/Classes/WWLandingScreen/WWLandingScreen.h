//
//  WWLandingScreen.h
//  WarOfWords
//
//  Created by Gurudath on 5/1/17.
//
//

#ifndef WWLandingScreen_h
#define WWLandingScreen_h

#include <stdio.h>
#include "WWGameUtility.h"

#include "cocos2d.h"
using namespace cocos2d;
using namespace cocos2d::network;
using namespace cocos2d::ui;

class WWLandingScreen : public cocos2d::Layer
{
private:
    
    //Variable
    Size visibleSize;
    Vec2 origin;
    
    MenuItemImage* loginFacebookBtn, *signUpBtn, *loginBtn;
    MenuItemToggle* musinBtn, *soundbtn;
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    //UI
    void addUI();
    
    //Button
    void onClickOnLoginFacebook(Ref* sender);
    void afterLoginCompleted(bool pIsDone);

    
    void onClickOnLoginbtn(Ref* pSender);
    void onClickOnSinUpbtn(Ref* pSender);
    void onClickOnMusicbtn(Ref* pSender);
    void onClickOnSoundbtn(Ref* pSender);
    
    //API
    void loginToServer();
    void onLoginRequestCompleted(HttpClient *sender, HttpResponse *response);


    // implement the "static create()" method manually
    CREATE_FUNC(WWLandingScreen);
};


#endif /* WWLandingScreen_hpp */
