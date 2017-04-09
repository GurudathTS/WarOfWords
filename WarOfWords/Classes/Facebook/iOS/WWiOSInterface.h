//
//  WWiOSInterface.h
//  War of Words
//
//  Created by Gurudath on 21/10/15.
//
//

#ifndef WWiOSInterface_h
#define WWiOSInterface_h

#include "cocos2d.h"
using namespace cocos2d;

#define ZI_DLL
#define WWiOSInterfaceRef   WWiOSInterface::getInstance()

class ZI_DLL WWiOSInterface
{
     
public:
     static WWiOSInterface* getInstance();
     WWiOSInterface();
    
    /*
     * Version read from info.Plist
     */
    
    std::string getAppVersion();
    
     /*
      * Network Related Functions.
      */
     void checkNetworkForDevice();
    
     /*
      *Network Manager interface
      */
     void initializeNetworkNotifier();
     

    /*
     Facebook
     */
    bool checkFacebookLoggedIn();
    bool checkFacebookDeclined();
    
    void initializeFacebook();
    void logIn();
    void logOutFacebook();
    void getTotalFreindCount();
    void updateScore(int pScore);
    
    //Current User
    void getCurrentUser();
    
    void shareFacebookMessage(std::string pMessageStr);
    void sharePhotoOnFacebook(std::string pImageName);
    void inviteFreinds();
    void getInvitableFriendsList(int pTotalFriendsCount);
    void getGameFriendsList(int pTotalFriendsCount);
    void collectUserId(std::string pUserId);
    void inviteFriends();
};

#endif /* WWiOSInterface_h */
