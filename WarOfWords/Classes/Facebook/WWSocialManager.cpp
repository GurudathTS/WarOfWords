//
//  WWSocialManager.cpp
//
//
//  Created by Gurudath
//
//

#include "WWSocialManager.h"
#include "WWSocialFriendDetail.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "WWiOSInterface.h"
#endif

using namespace cocos2d;

static WWSocialManager *_mInstance = nullptr;
WWSocialManager* WWSocialManager::getInstance()
{    
    if (!_mInstance)
    {
        _mInstance = new (std::nothrow) WWSocialManager();
        _mInstance->retain();
    }
    
    return _mInstance;
}
WWSocialManager::WWSocialManager()
:_mDelegate(nullptr)
{
     _mHasLoadingPopup = false;
    currentLoginUserDetail = nullptr;
}

WWSocialManager::~WWSocialManager()
{
    
}

#pragma mark - Call Backs
void WWSocialManager::setCallback(const std::function<void(bool)> pCallback)
{
    _mDelegate = pCallback;
}

void WWSocialManager::executeCallback(bool pResult)
{
    if (_mDelegate)
        _mDelegate(pResult);
    
     _mDelegate = nullptr;
     _mHasLoadingPopup = false;
}

#pragma mark - Facebook
void WWSocialManager::initWithEnum(enumSocialSharingType pShareType)
{
    if (pShareType==kFacebook) {
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        WWiOSInterfaceRef->initializeFacebook();
#endif
         checkForPermissions();
    }
}

void WWSocialManager::logIn(enumSocialSharingType pShareType)
{
    log("Start Log In");

    _mHasLoadingPopup = true;
     
    if (pShareType == kFacebook) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        WWiOSInterfaceRef->logIn();
#endif
        
    }
}

void WWSocialManager::checkForPermissions()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
     //For Facebook
     _mIsFacebookLoggedIn = WWiOSInterfaceRef->checkFacebookLoggedIn();
     if (!_mIsFacebookLoggedIn)
          _mIsFacebookDeclined = WWiOSInterfaceRef->checkFacebookDeclined();
     else
          _mIsFacebookDeclined = false;
#endif
    
    if (_mIsFacebookLoggedIn && !_mIsFacebookDeclined) {
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        WWiOSInterfaceRef->getTotalFreindCount();
#endif
    
    }
    
}

void WWSocialManager::setTotalUserCount(int pTotalUserCount)
{
    _mTotalFbFriendsCount = pTotalUserCount;
    
    this->getCurrentUserInfo(enumSocialSharingType::kFacebook);
    //this->executeCallback(true);
}

void WWSocialManager::logOut(enumSocialSharingType pShareType)
{
    if (pShareType == kFacebook) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        WWiOSInterfaceRef->logOutFacebook();
#endif
        
    }
     _mIsFacebookLoggedIn = false;
     _mIsFacebookDeclined = false;
}

//Invitable - Enum & Callback
void WWSocialManager::getInvitableFriendsList(enumSocialSharingType pShareType)
{
     _mHasLoadingPopup = true;
     
    if (pShareType==kFacebook) {
        _mFbInviteUserInfo.clear();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        WWiOSInterfaceRef->getInvitableFriendsList(_mTotalFbFriendsCount);
#endif
        
    }
}

void WWSocialManager::readInvitableFreindList(std::string pId, std::string pUserName, std::string pUrl)
{
    WWSocialFriendDetail* _tUserInfo = new WWSocialFriendDetail(pUserName,pUrl,pId,0,"");
    _mFbInviteUserInfo.push_back(_tUserInfo);
}

//Game freinds list
void WWSocialManager::getGameFriendsList(enumSocialSharingType pShareType)
{
    if (pShareType==kFacebook) {
        _mFbInviteUserInfo.clear();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        WWiOSInterfaceRef->getGameFriendsList(_mTotalFbFriendsCount);
#endif
        
    }
}
void WWSocialManager::readGameFreindList(std::string pId, std::string pUserName, std::string pUrl, int pScore)
{
    WWSocialFriendDetail* _tUserPlayedInfo = new WWSocialFriendDetail(pUserName, pUrl, pId,pScore,"");
    _mFbInviteUserInfo.push_back(_tUserPlayedInfo);
}

void WWSocialManager::sortgameFriendList()
{
    //std::sort(_mFbInviteUserInfo.begin(), _mFbInviteUserInfo.end());
    
     if (_mFbInviteUserInfo.size() > 1)
     {
          this->quickSort(_mFbInviteUserInfo,0,(int)_mFbInviteUserInfo.size()-1);
//          for (int i=0; i<_mFbInviteUserInfo.size(); i++) {
//               
//               log("Sorted Score  %d",_mFbInviteUserInfo.at(i)->getScore());
//          }
     }
    
    this->executeCallback(true);
}

void WWSocialManager::quickSort(std::vector<WWSocialFriendDetail*> arr, int left, int right)
{
    
    int i = left, j = right;
    WWSocialFriendDetail* tmp;
    int pivot = arr[(left + right) / 2]->getScore();
    
    while (i <= j)
    {
        while (arr[i]->getScore() > pivot)
            i++;
        while (arr[j]->getScore() < pivot)
            j--;
        if (arr[i]->getScore() <= arr[j]->getScore())
        {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
    
}

#pragma mark - Get Current User Detail
void WWSocialManager::getCurrentUserInfo(enumSocialSharingType pShareType)
{
    if (pShareType==kFacebook) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        WWiOSInterfaceRef->getCurrentUser();
#endif
        
    }
}

void WWSocialManager::readCurrentUserInfo(std::string pId, std::string pUserName, std::string pUrl, int pScore,std::string eMailStr)
{
    WWSocialFriendDetail* _tUserPlayedInfo = new WWSocialFriendDetail(pUserName, pUrl, pId,pScore,eMailStr);
    currentLoginUserDetail = _tUserPlayedInfo;
    
    this->executeCallback(true);
}

//Invite Freinds Callback - Enum & Callbackas
void WWSocialManager::inviteFriends(enumSocialSharingType pShareType,  std::vector<std::string>pInviteList)
{
    if (pShareType==kFacebook) {
        
        //Loop Array
        for(std::string _tInviteList : pInviteList) {
            
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            WWiOSInterfaceRef->collectUserId(_tInviteList);
#endif
        }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
         WWiOSInterfaceRef->inviteFriends();
#endif
    }
}

void WWSocialManager::updateScore(enumSocialSharingType pShareType, int pScore)
{
    if (pShareType==kFacebook) {
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        WWiOSInterfaceRef->updateScore(pScore);
#endif
    }

}

#pragma mark - Share Message
void WWSocialManager::shareSocialMessageWithEnum(enumSocialSharingType pShareType, std::string pMessageStr)
{
    if (pShareType==kFacebook) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        WWiOSInterfaceRef->shareFacebookMessage(pMessageStr);
#endif
    }
}


void WWSocialManager::shareSocialPhotoeWithEnum(enumSocialSharingType pShareType,std::string pImageName)
{
    if (pShareType==kFacebook) {
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        WWiOSInterfaceRef->sharePhotoOnFacebook(pImageName);
#endif
    }
}

void WWSocialManager::inviteFreinds(enumSocialSharingType pShareType)
{
    if (pShareType==kFacebook) {
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        WWiOSInterfaceRef->inviteFreinds();
#endif
    }
}

