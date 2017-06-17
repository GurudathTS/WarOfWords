//
//  WWMainMenuScreen.h
//  WarOfWords
//
//  Created by Gurudath on 5/2/17.
//
//

#ifndef WWMainMenuScreen_h
#define WWMainMenuScreen_h

#include <stdio.h>

#include "cocos2d.h"
using namespace cocos2d;

#include "extensions/cocos-ext.h"
using namespace cocos2d::extension;

#include "WWSettingPageLayer.h"
#include "WWPlayerInfo.h"

class WWMainMenu : public cocos2d::Layer
{
private:
    MenuItemImage* settingButton, *inappbtn, *quickMatchBtn, *howtoPlaybtn, *createbuildbtn;
    Sprite* profileBackground, *profileCircleSpr, *CommonPoupBg;
    Label* userNameLabel, *userDescriptionLabel;
    ScrollView *activeGameListScrollView;
     WWSettingsPannel* settingPannelLayer;
    
    //Variable
    Size visibleSize;
    Vec2 origin;
    
    //Button
    void onClickOnQuickmatchBtn(Ref* pSender);
    void onClickOnSettingBtn(Ref* pSender);
    void onClickOnHowToPlaybtnBtn(Ref* pSender);
    void onClickOnInAppBtn(Ref* pSender);
    void onClickOnGuildbtnBtn(Ref* pSender);
    
    void addActiveGamesList();
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init()override;
    void onEnter()override;
    void onExit()override;
    
    //UI
    void addUI();
    
    // implement the "static create()" method manually
    CREATE_FUNC(WWMainMenu);
};



#endif /* WWMainMenuScreen_h */
