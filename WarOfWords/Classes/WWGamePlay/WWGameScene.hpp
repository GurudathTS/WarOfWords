//
//  WWGameScene.hpp
//  WarOfWords
//
//  Created by Gurudath on 2/20/17.
//
//

#ifndef WWGameScene_hpp
#define WWGameScene_hpp

#include <stdio.h>
#include "WWAlphabetSprite.hpp"
#include "cocos2d.h"
#include <vector>
#include <string>

using namespace std;
using namespace cocos2d;

class WWGameScene : public Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    //Variable
    Size visibleSize;
    Vec2 origin;
    
    //Different kind of Alphabets Array
    vector<std::string> pOnePointArray;
    vector<std::string> pTwoPointArray;
    vector<std::string> pThreePointArray;
    vector<std::string> pFourPointArray;
    vector<std::string> pFivePointArray;
    vector<std::string> pEightPointArray;
    vector<std::string> pTenPointArray;
    
    Vector<WWAlphabetSprite*> pTotalGridAlphabet;
    Vector<WWAlphabetSprite*> currentSelectedStr;
    
    //Init
    void initializeAlphabets();
    void createAlphabetGridArray();
    void createCustomAlphabet(int currentAlphabetVal , std::string pCurrentStr);
    void createGrid();
    
    //Score
    Label* currentScore;
    Label* resultSelectedStr;
    void addUI();
    
    //Submit
    void onSubmitClicked(Ref* sender);
    
    //reset
    void resetGrid();
    void resetgameAfterSomeTime();
    void resetAfterLost();
    
    //Shuffle
    Vector<WWAlphabetSprite*> shuffleArray(Vector<WWAlphabetSprite*> pArray);
    
    // implement the "static create()" method manually
    CREATE_FUNC(WWGameScene);
};

#endif /* WWGameScene_hpp */
