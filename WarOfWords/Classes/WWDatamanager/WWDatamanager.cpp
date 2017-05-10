//
//  WWDatamanager.cpp
//  WarOfWords
//
//  Created by Manjunatha Reddy on 5/10/17.
//
//

#include "WWDatamanager.h"


static WWDatamanager *gSharedManager = NULL;

WWDatamanager::WWDatamanager(void)
{
    
}
WWDatamanager* WWDatamanager::sharedManager(void) {
    
    WWDatamanager *pRet = gSharedManager;
    
    if (! gSharedManager)
    {
        pRet = gSharedManager = new WWDatamanager();
        
        if (! gSharedManager->init())
        {
            delete gSharedManager;
            gSharedManager = NULL;
            pRet = NULL;
        }
    }
    return pRet;
}

#pragma mark - Init
bool WWDatamanager::init(void)
{
    
    return true;
}

#pragma mark - API key
std::string WWDatamanager::getAPIKey()
{
    return UserDefault::getInstance()->getStringForKey("APIKey", "NotExist");
}
void WWDatamanager::setAPIKey(std::string apiKey)
{
    UserDefault::getInstance()->setStringForKey("APIKey", apiKey);
}

#pragma mark - API key

void WWDatamanager::setUserId(std::string userId)
{
    UserDefault::getInstance()->setStringForKey("UserId", userId);

}
std::string WWDatamanager::getUserId()
{
    return UserDefault::getInstance()->getStringForKey("UserId", "NotExist");

}


