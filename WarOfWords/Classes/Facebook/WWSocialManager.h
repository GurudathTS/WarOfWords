//
//  WWSocialManager.h
//  
//
//  Created by Gurudath.
//
//

#ifndef WWSocialManager_h
#define WWSocialManager_h

#include "cocos2d.h"
using namespace cocos2d;

enum enumSocialSharingType {
    kFacebook,
    kTwitter
};

#define WWSocialManagerRef     WWSocialManager::getInstance()
class WWSocialFriendDetail;

class WWSocialManager : public cocos2d::Ref
{
     bool            _mHasLoadingPopup;
public:
    
    ~WWSocialManager();
    static  WWSocialManager* getInstance(void);
    
    //Callback
    void executeCallback(bool);
    void setCallback(const std::function<void(bool)> pCallback);
    
    //Facebook
    void initWithEnum(enumSocialSharingType shareType);
    void logIn(enumSocialSharingType pShareType);
    void checkForPermissions();
    void setTotalUserCount(int pTotalUserCount);
    void logOut(enumSocialSharingType pShareType);
    
    //Current login User
    void getCurrentUserInfo(enumSocialSharingType pShareType);
    void readCurrentUserInfo(std::string pId, std::string pUserName, std::string pUrl, int pScore);
    
    //Share Message with Enum Type
    void shareSocialMessageWithEnum(enumSocialSharingType shareType,std::string pMessageStr);
    void shareSocialPhotoeWithEnum(enumSocialSharingType shareType,std::string imageName);
    void inviteFreinds(enumSocialSharingType shareType);
    
    //Friend List
    void getInvitableFriendsList(enumSocialSharingType pShareType);
    void readInvitableFreindList(std::string pId, std::string pUserName, std::string pUrl);

    void getGameFriendsList(enumSocialSharingType pShareType);
    void readGameFreindList(std::string pId, std::string pUserName, std::string pUrl, int pScore);
    void sortgameFriendList();
    void quickSort(std::vector<WWSocialFriendDetail*> arr, int left, int right);
    
    void inviteFriends(enumSocialSharingType pShareType,std::vector<std::string>pInviteList);
    void updateScore(enumSocialSharingType pShareType, int pScore);

public:
    WWSocialManager();
    
    CC_SYNTHESIZE_READONLY(bool, _mIsShareOpened, ShareOpened);
    CC_SYNTHESIZE_READONLY(bool, _mIsFacebookLoggedIn, FacebookLoggedIn);
    CC_SYNTHESIZE_READONLY(bool, _mIsFacebookDeclined, FacebookDeclined);
    CC_SYNTHESIZE_READONLY(int, _mTotalFbFriendsCount, TotalFbFriendsCount);
        
    //User Detail Array
     CC_SYNTHESIZE_READONLY(std::vector<WWSocialFriendDetail*>, _mFbInviteUserInfo, FbInviteUserInfo);
    WWSocialFriendDetail* currentLoginUserDetail;

    //Call Backs
    std::function<void(bool)> _mDelegate;
};


#endif /* WWSocialManager_h */
