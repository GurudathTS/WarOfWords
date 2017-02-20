
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface WWObjectiveC :  NSObject
{
    
}

+(void)loadDictionary:(NSString*)txtPath;
+(BOOL)isDictionaryWord:(NSString*)pStr;
+(BOOL)checkIfWordpresentOnDictionary:(NSString*)pStr;
@end
