
#include "WWObjectiveCCalls.h"
#import "WWObjectiveC.h"

#pragma mark - Facebook
bool WWObjectiveCCalls::isDictionaryWordCall(std::string pStr)
{
    NSString* stringref = [NSString stringWithCString:pStr.c_str()
                                                                     encoding:[NSString defaultCStringEncoding]];
    bool pIsCorrectWord = [WWObjectiveC isDictionaryWord:stringref];
    
    return pIsCorrectWord;
}
