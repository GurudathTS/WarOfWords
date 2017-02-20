
#import "WWObjectiveC.h"

@implementation WWObjectiveC

#pragma mark - Get Word from Dictionary
+(BOOL)isDictionaryWord:(NSString*)pStr
{
    UITextChecker *checker = [[UITextChecker alloc] init];
    NSLocale *currentLocale = [NSLocale currentLocale];
    NSString *currentLanguage = [currentLocale objectForKey:NSLocaleLanguageCode];
    NSRange searchRange = NSMakeRange(0, [pStr length]);
    
    NSRange misspelledRange = [checker rangeOfMisspelledWordInString:pStr range:searchRange startingAt:0 wrap:NO language:currentLanguage];
    return misspelledRange.location == NSNotFound;
    
}

#pragma mark - Dealloc
- (void)dealloc
{
    [super dealloc];
}

@end
