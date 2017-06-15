#import <UIKit/UIKit.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    NSString *deviceToken;

}
-(NSString *)getDeviceToken;

@property(nonatomic, readonly) RootViewController* viewController;

@end

