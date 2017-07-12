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

class WWGameScene;

template<typename T> std::string NumToString(T t) {
    // to_string() prints different numbers of digits for floats depending on
    // platform and isn't available on Android, so we use stringstream
    std::stringstream ss;
    ss << t;
    return ss.str();
}

class WWAlphabetSprite:public Sprite
{
public:
    
    WWAlphabetSprite();
    ~WWAlphabetSprite();
    
    static WWAlphabetSprite* create(const char *pSpriteFrame);
    std::string sprName;
    
    //property
    Sprite* spriteLayer;
    bool isAlreadyPressed;
    Label* currentAlphabet;
    Label* currentAlphabetValLabel;
    int alphabetValue;
    int gridRefValue;
    
    WWGameScene* objref;
    
    //Func
    void initializeFunc(int currentAlphabetVal, std::string pCurrentStr);
    void updatedGridReferenceValue(int pGridrefVal);
    
    void resetSprite();
    void resetSpriteAfterLost();
    void createRandomAlphabet();
    void updateNewAlphabet(int currentAlphabetVal , std::string pCurrentStr);
    
    void checkIfCurrentCellNearToPreviousSeelctedCell();
    void removeSetOfLetterFromArray();
    
    //Update
    void updateRandomAlphabet(std::string pAlphabet);
    void updateSprite(std::string pStr);
    
    //touches
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

};

#endif /* WWAlphabetSprite_hpp */
