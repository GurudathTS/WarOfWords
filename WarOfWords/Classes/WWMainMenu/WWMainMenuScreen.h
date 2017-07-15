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
using namespace cocos2d::network;
using namespace cocos2d::ui;

#include "json/rapidjson.h"
#include "json/filestream.h"
#include "json/document.h"

#include "WWSettingPageLayer.h"
#include "WWmainMenuPlayConfirmation.h"
#include "WWPlayerInfo.h"
#include "WWGameUtility.h"

template<typename T> std::string NumToString(T t) {
    // to_string() prints different numbers of digits for floats depending on
    // platform and isn't available on Android, so we use stringstream
    std::stringstream ss;
    ss << t;
    return ss.str();
}

class WWMainMenu : public cocos2d::Layer
{
private:
    MenuItemImage* settingButton, *inappbtn, *quickMatchBtn, *howtoPlaybtn, *createbuildbtn;
    Sprite* profileBackground, *profileCircleSpr, *CommonPoupBg;
    Label* userNameLabel, *userDescriptionLabel;
    ScrollView *activeGameListScrollView;
     WWSettingsPannel* settingPannelLayer;
    WWmainMenuPlayConfirmation* playConfirmationPopup;
    std::string lastUpdatedStr;
    
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
    
    
    //connecting server functions
    void getRamdomUserAPI();
    void onGetRamdomUserAPIRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    
    //connecting server functions
    void getUserDetailsAPI();
    void onGetUserDetailsAPIRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    
    void requestForPlayAPI();
    void onRequestForPlayAPIRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    void getGamesAPI();
    void onGetGamesAPIRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    void getAllActiveGamesDetail();
    void onGetAllActiveGamesDetail(HttpClient *sender, HttpResponse *response);

    //Player Accept STatus
    void updatePlayerAcceptStatus(bool pIsAccepted);
    void onGetUpdateAPIRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    void sendPushNotificationToUserAPI();
    void onSendPushNotificationToUserAPIRequestCompleted(HttpClient *sender, HttpResponse *response);

    //Confirmation Popup
    void addConfirmationPlayPopUp();

public:
    static cocos2d::Scene* createScene();
    virtual bool init()override;
    void onEnter()override;
    void onExit()override;
    
    //UI
    void addUI();
    
    void callbackFromConfirmationPopup(bool pIsConfirmed);
    
    // implement the "static create()" method manually
    CREATE_FUNC(WWMainMenu);
};



#endif /* WWMainMenuScreen_h */
