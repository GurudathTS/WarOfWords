//
//  WWBattleScreen.h
//  WarOfWords
//
//  Created by Gurudath on 5/20/17.
//
//

#ifndef WWBattleScreen_h
#define WWBattleScreen_h

#include <stdio.h>
#include "cocos2d.h"
#include "WWPlayerInfo.h"
using namespace cocos2d;

class WWBattleScreen : public cocos2d::Layer
{
private:
    
    //Variable
    Size visibleSize;
    Vec2 origin;
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    //UI
    void addUI();
    
    void replaceScene();
    
    // implement the "static create()" method manually
    CREATE_FUNC(WWBattleScreen);
};


#endif /* WWBattleScreen_h */
