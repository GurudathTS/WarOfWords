
#include "WWObjectiveCCalls.h"
#import "WWObjectiveC.h"

#pragma mark - Dictionary
void WWObjectiveCCalls::loadDictionary(std::string pDictionarypath)
{
    NSString* stringref = [NSString stringWithCString:pDictionarypath.c_str()
                                             encoding:[NSString defaultCStringEncoding]];
    [WWObjectiveC loadDictionary:stringref];
}

bool WWObjectiveCCalls::checkifWordContainsDictionary(std::string pStr)
{
    NSString* stringref = [NSString stringWithCString:pStr.c_str()
                                             encoding:[NSString defaultCStringEncoding]];
    bool pIsCorrectWord = [WWObjectiveC checkIfWordpresentOnDictionary:stringref];
    
    return pIsCorrectWord;
}

bool WWObjectiveCCalls::isDictionaryWordCall(std::string pStr)
{
    NSString* stringref = [NSString stringWithCString:pStr.c_str()
                                                                     encoding:[NSString defaultCStringEncoding]];
    bool pIsCorrectWord = [WWObjectiveC isDictionaryWord:stringref];
    
    return pIsCorrectWord;
}
