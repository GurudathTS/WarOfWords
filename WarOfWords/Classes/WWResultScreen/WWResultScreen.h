//
//  WWResultScreen.h
//  WarOfWords
//
//  Created by Gurudath on 7/15/17.
//
//

#ifndef WWResultScreen_h
#define WWResultScreen_h

#include <stdio.h>

#include <stdio.h>
#include "cocos2d.h"
#include "WWPlayerInfo.h"
using namespace cocos2d;

class WWResultScreen : public cocos2d::Layer
{
private:
    
    //Variable
    Size visibleSize;
    Vec2 origin;
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    //UI
    void addWinScreen();
    void addLoseScreen();
    
    void gobackToMainScreen(Ref* sender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(WWResultScreen);
};


#endif /* WWResultScreen_h */
