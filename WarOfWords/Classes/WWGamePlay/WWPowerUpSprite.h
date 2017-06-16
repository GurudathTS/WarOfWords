//
//  WWPowerUpSprite.hpp
//  WarOfWords
//
//  Created by Gurudath on 4/1/17.
//
//

#ifndef WWPowerUpSprite_hpp
#define WWPowerUpSprite_hpp

#include <stdio.h>
#include <sstream>
#include "cocos2d.h"
using namespace cocos2d;

class WWGameScene;
class WWPowerUpSprite:public Sprite
{
public:
    
    WWPowerUpSprite();
    ~WWPowerUpSprite();
    
    static WWPowerUpSprite* create(const char *pSpriteFrame);
    
    //Score Property
    Label* scoreLabel;
    int scoreval;
    void updateScoreLabel(int pScore);
    
    //Game Obj
    WWGameScene* objref;
    
    //Ui
    void initUI(std::string pImageName);
        
};

#endif /* WWPowerUpSprite_hpp */
