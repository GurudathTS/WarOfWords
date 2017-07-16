//
//  WWMainMenuActiveList.h
//  WarOfWords
//
//  Created by Gurudath on 5/2/17.
//
//

#ifndef WWMainMenuActiveList_h
#define WWMainMenuActiveList_h

#include <stdio.h>
#include "cocos2d.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
using namespace cocos2d::network;
using namespace cocos2d;

#include <fstream>
#include <string>
using namespace std;

class MainMenuActiveList :public Layer
{
private:
    CC_SYNTHESIZE_READONLY(std::string, _mNameRef, NameRef);
    CC_SYNTHESIZE_READONLY(std::string, _mImageURL, ImageURL);
    CC_SYNTHESIZE_READONLY(std::string, _mDescription, Description);
    CC_SYNTHESIZE_READONLY(Texture2D*, _mTexture, Texture);
    
private:
    Sprite* profilePictureImg, *battleIconImg;
    std::string challengID;
    bool isYourTurn;
    std::string opponentUserId;
    std::string thumbUrl;
    int opponentHealth;
    Label* userNameLabel, *userDescriptionlabel;
    
public:
    MainMenuActiveList();
    static MainMenuActiveList* create();
    virtual ~MainMenuActiveList();
    
    void addUI(std::string pName
               ,std::string pImageURL
               ,std::string pDescription,int pHealth);


};

#endif /* WWMainMenuActiveList_h */
