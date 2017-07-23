//
//  WWDatamanager.hpp
//  WarOfWords
//
//  Created by Manjunatha Reddy on 5/10/17.
//
//

#ifndef WWDatamanager_hpp
#define WWDatamanager_hpp

#include "cocos2d.h"
#include "WWMainMenuScreen.h"
USING_NS_CC;

class WWDatamanager: public Ref
{
    
private:
    WWDatamanager(void);
    
public:
    bool init(void);
    static WWDatamanager* sharedManager(void);
    
    //APIkey
    std::string getAPIKey();
    void setAPIKey(std::string apiKey);
    
    //UserId
    void setUserId(std::string userId);
    std::string getUserId();
    
    
    //UserName
    void setUserName(std::string userId);
    std::string getUserName();    
    
    std::string _forgotPasswordEmailId;
    
    std::string dmdeviceToken ="fhfjfjjfjfj";
    
    bool _isUserInMainScene = false;
    int userHealth;
    std::string lastUpdatedStr;
    WWMainMenu *_mainScreenRef;
    bool _isExistingGameStarting = false;
    
};

#endif /* WWDatamanager_hpp */
