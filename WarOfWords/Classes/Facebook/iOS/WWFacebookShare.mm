//
//  WWFacebookShare.cpp
//  WWFacebookShare
//
//  Created by Gurudath on 05/05/16.
//
//

#include "WWFacebookShare.h"
#include "WWSocialManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AppController.h"
#endif

#import <FBSDKCoreKit/FBSDKCoreKit.h>
#import <FBSDKLoginKit/FBSDKLoginKit.h>
#import <FBSDKShareKit/FBSDKShareKit.h>

@interface WWFacebookShare () <FBSDKSharingDelegate,FBSDKAppInviteDialogDelegate,FBSDKGameRequestDialogDelegate>
@end

@implementation WWFacebookShare

+(WWFacebookShare *)getInstance
{
    static WWFacebookShare *mSharedInstance = nil;
    static dispatch_once_t once = 0;
    dispatch_once(&once, ^{mSharedInstance = [[self alloc] init];});
    return mSharedInstance;
}
-(id)init
{
    self = [super init];
    if (self)
    {
        _mCollectUserIdArray = [[NSMutableArray alloc] init];
    }
    
    return  self;
}

#pragma mark - Init
-(void)initializeFacebook
{
    
    UIApplication* application = [UIApplication sharedApplication];
    //Facebook
    [[FBSDKApplicationDelegate sharedInstance] application:application
                             didFinishLaunchingWithOptions:nil];
    
    [FBSDKAppEvents activateApp];
    
    
}

-(bool)checkForLoggedIn
{
    if ([[FBSDKAccessToken currentAccessToken] hasGranted:@"public_profile"]
        && [[FBSDKAccessToken currentAccessToken] hasGranted:@"user_friends"]
        && [[FBSDKAccessToken currentAccessToken] hasGranted:@"publish_actions"])
        return true;
    
    return false;
}

-(bool)checkForDeclined
{
    
    if ([[[FBSDKAccessToken currentAccessToken] declinedPermissions] containsObject:@"public_profile"]
        || [[[FBSDKAccessToken currentAccessToken] declinedPermissions] containsObject:@"user_friends"]
        || [[[FBSDKAccessToken currentAccessToken] declinedPermissions] containsObject:@"publish_actions"])
        return true;
    return false;
}

#pragma mark - Login
-(void)loginFacebook
{
    //Check for Read action
    if ([[FBSDKAccessToken currentAccessToken] hasGranted:@"public_profile"]
        && [[FBSDKAccessToken currentAccessToken] hasGranted:@"user_friends"])
    {
        [self loginPublishPermission];
    }
    else
    {
        AppController *controller = (AppController *) [UIApplication sharedApplication].delegate;
        FBSDKLoginManager *loginManager = [[FBSDKLoginManager alloc] init];
        
        [loginManager logInWithReadPermissions:@[@"user_friends",@"public_profile"]
                            fromViewController:(UIViewController*)controller.viewController
                                       handler:^(FBSDKLoginManagerLoginResult *result, NSError *error)
                                       {
                                           if (!error && !result.isCancelled)
                                           {
                                               //Publish
                                               [self loginPublishPermission];
                                           }
                                           else if (!result.isCancelled)
                                           {
                                               //Facebook Error Pop Up
                                                WWSocialManagerRef->checkForPermissions();
                                           }
                                           
                                           
                                       }];
    }

}

-(void)loginPublishPermission
{
    //Check for Publish action
    if ([[FBSDKAccessToken currentAccessToken] hasGranted:@"publish_actions"])
    {
         WWSocialManagerRef->checkForPermissions();
    }
    else
    {
        //
        AppController *controller = (AppController *) [UIApplication sharedApplication].delegate;
        FBSDKLoginManager *loginManager = [[FBSDKLoginManager alloc] init];
        [loginManager logInWithPublishPermissions:@[@"publish_actions"]
                               fromViewController:(UIViewController*)controller.viewController
                                          handler:^(FBSDKLoginManagerLoginResult *result, NSError *error) {
                                              if (!error && !result.isCancelled)
                                              {
                                                   WWSocialManagerRef->checkForPermissions();
                                              }
                                              else if (!result.isCancelled) {
                                                  //Facebook Error Pop Up
                                                  WWSocialManagerRef->checkForPermissions();
                                              }
                                          }];
    }
}

-(void)logOut
{
    //Log out
    FBSDKLoginManager *loginManager = [[FBSDKLoginManager alloc] init];
    [loginManager logOut];
}

#pragma mark -
-(void)updateScore:(int)pScore
{
    //Fetch Current Score
    // Handle the result
    NSString *_tScoreStr = [NSString stringWithFormat:@"%d", pScore];
    NSDictionary *params = @{
                             @"score": _tScoreStr,
                             };
    
    NSMutableString *facebookRequest = [NSMutableString new];
    [facebookRequest appendString:@"/"];
    [facebookRequest appendString:[FBSDKAccessToken currentAccessToken].userID];
    [facebookRequest appendString:@"/scores"];
    
    /* make the API call */
    FBSDKGraphRequest *request = [[FBSDKGraphRequest alloc]
                                  initWithGraphPath:facebookRequest
                                  parameters:params
                                  HTTPMethod:@"POST"];
    [request startWithCompletionHandler:^(FBSDKGraphRequestConnection *connection,
                                          id result,
                                          NSError *error)
     {
        

     }];

}

-(void)getTotalFreindCount
{
    NSDictionary *params = @{@"fields": @"",};
    
    NSMutableString *facebookRequest = [NSMutableString new];
    [facebookRequest appendString:@"/"];
    [facebookRequest appendString:[FBSDKAccessToken currentAccessToken].userID];
    [facebookRequest appendString:@"/friends"];
    
    FBSDKGraphRequest *request = [[FBSDKGraphRequest alloc]
                                  initWithGraphPath:facebookRequest
                                  parameters:params
                                  HTTPMethod:@"GET"];
    [request startWithCompletionHandler:^(FBSDKGraphRequestConnection *connection,
                                          id result,
                                          NSError *error) {
        // Handle the result
        if (error) {
     
        }
        else
        {
            NSDictionary* _fbSummaryDict = [result objectForKey:@"summary"];
            NSNumber* _tCountStr = [_fbSummaryDict objectForKey:@"total_count"];
            int _tTotalCount = _tCountStr.intValue;
            WWSocialManagerRef->setTotalUserCount(_tTotalCount);
            
        }
        
    }];
    
}

-(void)getUserDetail
{
    //Get Freind List
    NSMutableString *facebookRequest = [NSMutableString new];
    [facebookRequest appendString:@"/"];
    [facebookRequest appendString:[FBSDKAccessToken currentAccessToken].userID];
    
    NSDictionary *params1 = @{
                              @"fields": @"id,name,picture,score",
                              };
    //Get Freind List
    
    FBSDKGraphRequest *request3 = [[FBSDKGraphRequest alloc]
                                   initWithGraphPath:facebookRequest
                                   parameters:params1
                                   HTTPMethod:@"GET"];
    [request3 startWithCompletionHandler:^(FBSDKGraphRequestConnection *connection,
                                           id result,
                                           NSError *error) {
        
        if (error) {
            
            //Error pop up
        }
        else
        {
            
            //Get Root Array
            
            //Loop Data  Array
                NSString* _tFbId = [result objectForKey:@"id"];
                NSString* _tFbName = [result objectForKey:@"name"];
                
                //Profile Picture
                NSString* _tFbUrl = [[[result objectForKey:@"picture"] objectForKey:@"data"] objectForKey:@"url"];
                
                NSNumber *_tFbScore = [NSNumber numberWithInt:0];
                if ([result objectForKey:@"score"])
                {
                    _tFbScore = [[[[result objectForKey:@"score"] objectForKey:@"data"] objectAtIndex:0] objectForKey:@"score"];
                }
                
                WWSocialManagerRef->readCurrentUserInfo(std::string([_tFbId UTF8String]), std::string([_tFbName UTF8String]), std::string([_tFbUrl UTF8String]),[_tFbScore intValue]);
            //
        }
    }];
}

-(void)getInvitableFriendsList:(int)pTotalFriendsCount
{
    NSDictionary *params1 = @{
                              @"fields": @"id,name,picture",
                              @"limit": [NSString stringWithFormat:@"%d", pTotalFriendsCount + 5],
                              };
    //Get Freind List
    NSMutableString *facebookRequest = [NSMutableString new];
    [facebookRequest appendString:@"/"];
    [facebookRequest appendString:[FBSDKAccessToken currentAccessToken].userID];
    [facebookRequest appendString:@"/invitable_friends"];
    
    FBSDKGraphRequest *request3 = [[FBSDKGraphRequest alloc]
                                   initWithGraphPath:facebookRequest
                                   parameters:params1
                                   HTTPMethod:@"GET"];
    [request3 startWithCompletionHandler:^(FBSDKGraphRequestConnection *connection,
                                           id result,
                                           NSError *error) {
        if (error) {
            
            WWSocialManagerRef->executeCallback(false);
        }
        else
        {
            
            //Get Root Array
            NSArray* _fbDataArray = [result objectForKey:@"data"];
            
            //Loop Data  Array
            for (NSDictionary* object in _fbDataArray)
            {
                NSString* _tFbId = [object objectForKey:@"id"];
                NSString* _tFbName = [object objectForKey:@"name"];
                
                //Profile Picture
                NSString* _tFbUrl = [[[object objectForKey:@"picture"] objectForKey:@"data"] objectForKey:@"url"];
                
                WWSocialManagerRef->readInvitableFreindList(std::string([_tFbId UTF8String]), std::string([_tFbName UTF8String]), std::string([_tFbUrl UTF8String]));
            }
             
             
             //
             WWSocialManagerRef->executeCallback(true);
        }
        
    }];
}

-(void)getGameFriendsList:(int)pTotalFriendsCount
{
    //Get Freind List
    NSMutableString *facebookRequest = [NSMutableString new];
    [facebookRequest appendString:@"/"];
    [facebookRequest appendString:[FBSDKAccessToken currentAccessToken].userID];
    [facebookRequest appendString:@"/friends"];
    
    NSDictionary *params1 = @{
                              @"fields": @"id,name,picture,score",
                              @"limit": [NSString stringWithFormat:@"%d", pTotalFriendsCount + 5],
                              };
    //Get Freind List
    
    FBSDKGraphRequest *request3 = [[FBSDKGraphRequest alloc]
                                   initWithGraphPath:facebookRequest
                                   parameters:params1
                                   HTTPMethod:@"GET"];
    [request3 startWithCompletionHandler:^(FBSDKGraphRequestConnection *connection,
                                           id result,
                                           NSError *error) {
        
        if (error) {
            
            //Error pop up
            
        }
        else
        {
            
            //Get Root Array
            NSArray* _fbDataArray = [result objectForKey:@"data"];
            
            //Loop Data  Array
            for (NSDictionary* object in _fbDataArray)
            {
                NSString* _tFbId = [object objectForKey:@"id"];
                NSString* _tFbName = [object objectForKey:@"name"];
                
                //Profile Picture
                NSString* _tFbUrl = [[[object objectForKey:@"picture"] objectForKey:@"data"] objectForKey:@"url"];
                
                NSNumber *_tFbScore = [NSNumber numberWithInt:0];
                if ([object objectForKey:@"score"])
                {
                    _tFbScore = [[[[object objectForKey:@"score"] objectForKey:@"data"] objectAtIndex:0] objectForKey:@"score"];
                }
                
                
                WWSocialManagerRef->readGameFreindList(std::string([_tFbId UTF8String]), std::string([_tFbName UTF8String]), std::string([_tFbUrl UTF8String]),[_tFbScore intValue]);
            }
            //
            WWSocialManagerRef->sortgameFriendList();
        }
    }];
}

-(void)inviteFriends
{
    FBSDKGameRequestContent *gameRequestContent = [[FBSDKGameRequestContent alloc] init];
    gameRequestContent.message = @"Dead Count";
    gameRequestContent.recipients = _mCollectUserIdArray;
    gameRequestContent.actionType = FBSDKGameRequestActionTypeNone;
    
    // Assuming self implements <FBSDKGameRequestDialogDelegate>
    [FBSDKGameRequestDialog showWithContent:gameRequestContent delegate:self];

}

-(void)postTextOnTimeline
{
    AppController *controller = (AppController *) [UIApplication sharedApplication].delegate;
    
    FBSDKShareLinkContent *content = [[FBSDKShareLinkContent alloc] init];
    content.contentURL = [NSURL URLWithString:@""];
    FBSDKShareDialog *dialog = [FBSDKShareDialog showFromViewController:(UIViewController*)controller.viewController
                                                            withContent:content
                                                               delegate:self];
    
}

-(void)postImageOnTimeline
{
    NSLog(@"Image %@",_mShareImage);
    UIImage *image = [UIImage imageNamed:_mShareImage];
    
    FBSDKSharePhoto *photo = [[FBSDKSharePhoto alloc] init];
    photo.image = image;
    photo.userGenerated = YES;
    photo.caption = @"";
    
    FBSDKSharePhotoContent *content = [[FBSDKSharePhotoContent alloc] init];
    content.photos = @[photo];
    
    AppController *controller = (AppController *) [UIApplication sharedApplication].delegate;
    FBSDKShareDialog *dialog = [FBSDKShareDialog showFromViewController:(UIViewController*)controller.viewController
                                                            withContent:content
                                                               delegate:self];
     
}

#pragma mark - Share Facebook Message
-(void)shareMessageOnFacebook:(NSString*)shareMessage
{
    _mShareDiscription = shareMessage;
    
    if ([[FBSDKAccessToken currentAccessToken] hasGranted:@"public_profile"])
    {
        // TODO: publish content.
        [self postTextOnTimeline];
        
    }
    else
    {
        [self loginFacebook];
    }
//    [self loginFacebook];
}

#pragma mark - Share Photo
-(void)sharePhotoOnFacebook:(NSString *)imageName
{
    _mShareImage = imageName;
    if ([[FBSDKAccessToken currentAccessToken] hasGranted:@"public_profile"]) {
        
        [self postImageOnTimeline];
    }
    else
    {
        [self loginFacebook];
    }
}

#pragma mark - FBSDKSharingDelegate
- (void)sharer:(id<FBSDKSharing>)sharer didCompleteWithResults:(NSDictionary *)results
{
    NSLog(@"completed share:%@", results);
}

- (void)sharer:(id<FBSDKSharing>)sharer didFailWithError:(NSError *)error
{
    NSLog(@"completed error:%@", error);
}

- (void)sharerDidCancel:(id<FBSDKSharing>)sharer
{
    
}

#pragma mark -  App Invite Dialog
- (void)appInviteDialog:(FBSDKAppInviteDialog *)appInviteDialog didCompleteWithResults:(NSDictionary *)results
{
    NSLog(@"completed share:%@", results);
}

- (void)appInviteDialog:(FBSDKAppInviteDialog *)appInviteDialog didFailWithError:(NSError *)error
{
    NSLog(@"completed error:%@", error);
}

- (void)gameRequestDialog:(FBSDKGameRequestDialog *)gameRequestDialog didCompleteWithResults:(NSDictionary *)results
{
    
}

/*!
 @abstract Sent to the delegate when the game request encounters an error.
 @param gameRequestDialog The FBSDKGameRequestDialog that completed.
 @param error The error.
 */
- (void)gameRequestDialog:(FBSDKGameRequestDialog *)gameRequestDialog didFailWithError:(NSError *)error
{
    
}

/*!
 @abstract Sent to the delegate when the game request dialog is cancelled.
 @param gameRequestDialog The FBSDKGameRequestDialog that completed.
 */
- (void)gameRequestDialogDidCancel:(FBSDKGameRequestDialog *)gameRequestDialog
{
    
}

@end
