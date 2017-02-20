
#import "WWObjectiveC.h"

@implementation WWObjectiveC

static NSMutableArray *allTheWords;

#pragma mark - Get Word from Dictionary
+(void)loadDictionary:(NSString*)txtPath
{
    //load Dictionary
    allTheWords = [[NSMutableArray alloc]init];
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0),^(void){
        
        NSString *stringFromFile = [[NSString alloc]
                                    initWithContentsOfFile:txtPath
                                    encoding:NSUTF8StringEncoding
                                    error:nil ];
        for (NSString *word in [stringFromFile componentsSeparatedByString:@"\n"]) {
            [allTheWords addObject:word];
        }
    });
    
}

+(BOOL)isDictionaryWord:(NSString*)pStr
{
    UITextChecker *checker = [[UITextChecker alloc] init];
    NSLocale *currentLocale = [NSLocale currentLocale];
    NSString *currentLanguage = [currentLocale objectForKey:NSLocaleLanguageCode];
    NSRange searchRange = NSMakeRange(0, [pStr length]);
    
    NSRange misspelledRange = [checker rangeOfMisspelledWordInString:pStr range:searchRange startingAt:0 wrap:NO language:currentLanguage];
    BOOL isRealWord = misspelledRange.location == NSNotFound;
    
    // Call step two, to confirm that this is a real word
    if (isRealWord) {
        isRealWord = [self isRealWordOK:pStr];
    }
    return isRealWord;
    
}

+(BOOL)checkIfWordpresentOnDictionary:(NSString*)pStr
{
    BOOL isPresent = false;
    
    if ([allTheWords containsObject:[pStr lowercaseString]])
    {
        isPresent = true;
    }
    
    return isPresent;
}

+(BOOL)isRealWordOK:(NSString *)wordToCheck
{
    
    UITextChecker *checker = [[UITextChecker alloc] init];
    // we dont want to use any words that the lexicon has learned.
    if ([UITextChecker hasLearnedWord:wordToCheck]) {
        return NO;
    }
    
    // now we are going to use the word completion function to see if this word really exists, by removing the final letter and then asking auto complete to complete the word, then look through all the results and if its not found then its not a real word. Note the auto complete is very acurate unlike the spell checker.
    NSRange range = NSMakeRange(0, wordToCheck.length - 1);
    NSArray *guesses = [checker completionsForPartialWordRange:range inString:wordToCheck language:@"en_US"];
    
    // confirm that the word is found in the auto-complete list
    for (NSString *guess in guesses) {
        
        if ([guess isEqualToString:wordToCheck]) {
            // we found the word in the auto complete list so it's real :-)
            return YES;
        }
    }
    
    // if we get to here then it's not a real word :-(
    NSLog(@"Word not found in second dictionary check:%@",wordToCheck);
    return NO;
    
}

#pragma mark - Dealloc
- (void)dealloc
{
    [super dealloc];
}

@end
