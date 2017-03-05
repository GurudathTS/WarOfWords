//
//  WWFacebookShare.h
//  WWFacebookShare
//
//  Created by Gurudath.
//
//

#import <UIKit/UIKit.h>
#import <FBSDKLoginKit/FBSDKLoginKit.h>
#import <FBSDKShareKit/FBSDKShareKit.h>
#import <FBSDKCoreKit/FBSDKCoreKit.h>

#define ZIFBShare [WWFacebookShare getInstance]
@interface WWFacebookShare : NSObject
{
    NSString *_mShareDiscription, *_mShareImage;
}
@property(assign,readwrite)NSMutableArray* mCollectUserIdArray;

+(WWFacebookShare *)getInstance;
-(bool)checkForLoggedIn;
-(bool)checkForDeclined;

-(void)initializeFacebook;
-(void)loginFacebook;
-(void)loginPublishPermission;
-(void)logOut;

-(void)updateScore:(int)pScore;
-(void)getTotalFreindCount;

-(void)shareMessageOnFacebook:(NSString*) shareMessage;
-(void)sharePhotoOnFacebook:(NSString *)imageName;

//Fetch
-(void)getInvitableFriendsList:(int)pTotalFriendsCount;
-(void)getGameFriendsList:(int)pTotalFriendsCount;
-(void)inviteFriends;

@end

