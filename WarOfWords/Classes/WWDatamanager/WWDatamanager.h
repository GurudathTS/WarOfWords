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
    
    
    
};

#endif /* WWDatamanager_hpp */
