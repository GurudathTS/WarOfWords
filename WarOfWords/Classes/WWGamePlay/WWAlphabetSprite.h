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
    
    //touches
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

};

#endif /* WWAlphabetSprite_hpp */
