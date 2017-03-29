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

class WWSocialManager : public cocos2d::Node
{
     bool            _mHasLoadingPopup;
public:
    
    ~WWSocialManager();
    static  WWSocialManager* getInstance(void);
    
    
    //TransparentLayer
    void addTransparentLayer();
    void removeTransparentLayer();

    
    //Callback
    void executeCallback(bool);
    void setCallback(const std::function<void(bool)> pCallback);
    
    //Facebook
    void initWithEnum(enumSocialSharingType shareType);
    void logIn(enumSocialSharingType pShareType);
    void checkForPermissions();
    void setTotalUserCount(int pTotalUserCount);
    void logOut(enumSocialSharingType pShareType);
    
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
    
    //Transparent Layer
    LayerColor*    _mBGLayer;
    
    //User Detail Array
     CC_SYNTHESIZE_READONLY(std::vector<WWSocialFriendDetail*>, _mFbInviteUserInfo, FbInviteUserInfo);

    //Call Backs
    std::function<void(bool)> _mDelegate;
};


#endif /* WWSocialManager_h */
