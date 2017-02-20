//
//  WWAlphabetSprite.hpp
//  WarOfWords
//
//  Created by Gurudath on 2/20/17.
//
//

#ifndef WWAlphabetSprite_hpp
#define WWAlphabetSprite_hpp

#include <stdio.h>
#include <sstream>
#include "cocos2d.h"
using namespace cocos2d;

template<typename T>
std::string toString(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

class WWGameScene;

class WWAlphabetSprite:public Sprite
{
public:
    
    WWAlphabetSprite();
    ~WWAlphabetSprite();
    
    static WWAlphabetSprite* create(const char *pSpriteFrame);
    
    //property
    bool isAlreadyPressed;
    Label* currentAlphabet;
    Label* currentAlphabetValLabel;
    int alphabetValue;
    
    WWGameScene* objref;
    
    //Func
    void initializeFunc(int currentAlphabetVal, std::string pCurrentStr);
    void resetSprite();
    void resetSpriteAfterLost();
    void createRandomAlphabet();
    void updateNewAlphabet(int currentAlphabetVal , std::string pCurrentStr);
    
    //touches
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

};

#endif /* WWAlphabetSprite_hpp */
