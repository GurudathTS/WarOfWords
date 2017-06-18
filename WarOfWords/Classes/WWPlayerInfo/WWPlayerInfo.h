//
//  WWPlayerInfo.h
//  WarOfWords
//
//  Created by Gurudath on 6/17/17.
//
//

#ifndef WWPlayerInfo_h
#define WWPlayerInfo_h

#include "cocos2d.h"
using namespace cocos2d;
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
using namespace cocos2d::network;

#include <fstream>
#include <string>
using namespace std;

#define WWPlayerInfoRef     WWPlayerInfo::getInstance()

class WWPlayerInfo : public cocos2d::Ref
{
public:
    
    ~WWPlayerInfo();
    static  WWPlayerInfo* getInstance(void);
    
    //Callback
    void executeCallback(bool);
    void setCallback(const std::function<void(bool)> pCallback);
    
    std::string fileNameFromUrl(std::string url);
    void loadUserProfileURL();
    void onHttpRequestCompletedUser(HttpClient *sender, HttpResponse *response);
    
    void loadOpponentProfileURL();
    void onHttpRequestCompletedOpponent(HttpClient *sender, HttpResponse *response);
    
public:
    WWPlayerInfo();
    
    void initializeUserInfo(std::string pUserName,std::string pUserId ,std::string pUserProfilePicture, std::string pUserHealthBar);
    void updateUserName(std::string pUserName);
    void updateProfilePicture(std::string pProfilePictureUrl);
    void updateHealthBar(std::string pHealthBar);
    
    void initializeOpponentinfo(std::string pOpponentName,std::string pUserId, std::string pOpponentProfilePicture, std::string pOpponentHealthBar);
    void updateOpponentUserName(std::string pUserName);
    void updateOpponentProfilePicture(std::string pProfilePictureUrl);
    void updateOpponentHealthBar(std::string pHealthBar);
    
    //Current User
    CC_SYNTHESIZE_READONLY(std::string, _mCurrentUserName, CurrentUserName);
    CC_SYNTHESIZE_READONLY(std::string, _mCurrentUserProfilePtcture, CurrentUserProfilePtcture);
    CC_SYNTHESIZE_READONLY(std::string, _mCurrentUserHealthBar, CurrentUserHealthBar);
    CC_SYNTHESIZE_READONLY(std::string, _mCurrentId, CurrentUserID);

    CC_SYNTHESIZE_READONLY(Texture2D*, _mCurrentProfilePictureTexture, CurrentProfilePictureTexture);
    
    //Opponemt User
    CC_SYNTHESIZE_READONLY(std::string, _mOpponentUserName, OpponentUserName);
    CC_SYNTHESIZE_READONLY(std::string, _mOpponentUserProfilePtcture, OpponentUserProfilePtcture);
    CC_SYNTHESIZE_READONLY(std::string, _mOpponentUserHealthBar, OpponentUserHealthBar);
    CC_SYNTHESIZE_READONLY(std::string, _mOpponentUserId, OpponentUserID);

    CC_SYNTHESIZE_READONLY(Texture2D*, _mOpponentProfilePictureTexture, OpponentProfilePictureTexture);
    
    //Call Backs
    std::function<void(bool)> _mDelegate;
};

#endif /* WWPlayerInfo_h */
