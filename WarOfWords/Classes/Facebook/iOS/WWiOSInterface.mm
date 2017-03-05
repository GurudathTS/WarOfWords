//
//  WWiOSInterface.cpp
//
//
//  Created by Gurudath.
//
//

#include "WWiOSInterface.h"

//#include "WWSocialManager.h"
#import   "Reachability.h"
#include "WWFacebookShare.h"

static WWiOSInterface* _mInstance = nullptr;

WWiOSInterface* WWiOSInterface::getInstance()
{
     if (!_mInstance)
          _mInstance = new (std::nothrow) WWiOSInterface;
     
     return _mInstance;
}

WWiOSInterface::WWiOSInterface()
{
    
}

/*********************************************************************************/
#pragma mark - Version read from info.Plist
std::string WWiOSInterface::getAppVersion()
{
    NSString *_tAppVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    return std::string([_tAppVersion UTF8String]);
}



/*********************************************************************************/
#pragma mark - Network Related Functions.
/**
 * Network Related Functions.
 */
void WWiOSInterface::checkNetworkForDevice()
{
//     [ZICheckNetwork checkNetwork];
}

void WWiOSInterface::initializeNetworkNotifier()
{
     [[Reachability getInstance] checkNetwork];
}

#pragma mark - Facebook

bool WWiOSInterface::checkFacebookLoggedIn()
{
    return [ZIFBShare checkForLoggedIn];
}
bool WWiOSInterface::checkFacebookDeclined()
{
    return [ZIFBShare checkForDeclined];
}

void WWiOSInterface::initializeFacebook()
{
    [ZIFBShare initializeFacebook];
}

void WWiOSInterface::logIn()
{
    [ZIFBShare loginFacebook];
}
void WWiOSInterface::logOutFacebook()
{
    [ZIFBShare logOut];
}
void WWiOSInterface::getTotalFreindCount()
{
    [ZIFBShare getTotalFreindCount];
}
void WWiOSInterface::updateScore(int pScore)
{
    [ZIFBShare updateScore:pScore];
}

//Invite Friends
void WWiOSInterface::getInvitableFriendsList(int pTotalFriendsCount)
{
    [ZIFBShare getInvitableFriendsList:pTotalFriendsCount];
}
void WWiOSInterface::getGameFriendsList(int pTotalFriendsCount)
{
    [ZIFBShare getGameFriendsList:pTotalFriendsCount];
}

void WWiOSInterface::collectUserId(std::string pUserId)
{
    NSString* _tUserId= [NSString stringWithCString:pUserId.c_str()
                                           encoding:[NSString defaultCStringEncoding]];
    [ZIFBShare.mCollectUserIdArray addObject:_tUserId];
}
void WWiOSInterface::inviteFriends()
{
    [ZIFBShare inviteFriends];
    [ZIFBShare.mCollectUserIdArray removeAllObjects];
}

void WWiOSInterface::shareFacebookMessage(std::string pMessageStr)
{
    NSString *_tShareMessage = [NSString stringWithCString:pMessageStr.c_str()
                                                   encoding:[NSString defaultCStringEncoding]];
    [ZIFBShare shareMessageOnFacebook:_tShareMessage];
}
void WWiOSInterface::sharePhotoOnFacebook(std::string pImageName)
{
    NSString *_tImagePath = [NSString stringWithCString:pImageName.c_str()
                                                   encoding:[NSString defaultCStringEncoding]];
    [ZIFBShare sharePhotoOnFacebook:_tImagePath];
}
void WWiOSInterface::inviteFreinds()
{
   //[ZIFBShare inviteFreinds];
}

