//
//  WWGameScene.cpp
//  WarOfWords
//
//  Created by Gurudath on 2/20/17.
//
//

#include "WWGameScene.hpp"
#include "WWObjectiveCCalls.h"

USING_NS_CC;

#define TOTALGRID 64
#define ROWGRIDCOUNT 8

Scene* WWGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WWGameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WWGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    // Background
    auto backgroundSpr = Sprite::create("Background.png");
    backgroundSpr->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(backgroundSpr);
    
    //load Dictionary
    std::string _tDictionarypath = FileUtils::getInstance()->fullPathForFilename("IOSDictionary");
    WWObjectiveCCalls::loadDictionary(_tDictionarypath);
   
    
    //Initialize Alphabets
    this->initializeAlphabets();
    
    //UI
    this->addUI();
    
    //Create Alphabets Grid
    this->createAlphabetGridArray();
    this->createAlphabetGridArray();
    this->createAlphabetGridArray();
    
    //Shuffle Array
    pTotalGridAlphabet = this->shuffleArray(pTotalGridAlphabet);
    log("........ Array Count............ %zd",pTotalGridAlphabet.size());
    
    this->createGrid();
    
    return true;
}

#pragma mark - UI
void WWGameScene::addUI()
{
    currentScore = Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf", 40);
    currentScore->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height / 1.2 + origin.y));
    addChild(currentScore);
    
    resultSelectedStr = Label::createWithTTF("", "fonts/Marker Felt.ttf", 40);
    resultSelectedStr->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height / 1.1 + origin.y));
    addChild(resultSelectedStr);
    
    //Submit Button
    auto* submitButton = MenuItemFont::create("SUBMIT", CC_CALLBACK_1(WWGameScene::onSubmitClicked, this));
    submitButton->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height / 8 + origin.y));
    
    Menu* menuBtn = Menu::create(submitButton, NULL);
    menuBtn->setPosition(Vec2::ZERO);
    addChild(menuBtn);
}

#pragma mark - Initialize
void WWGameScene::initializeAlphabets()
{
    //Create 1st point Array
    pOnePointArray.push_back("A");
    pOnePointArray.push_back("E");
    pOnePointArray.push_back("I");
    pOnePointArray.push_back("O");
    pOnePointArray.push_back("U");
    pOnePointArray.push_back("L");
    pOnePointArray.push_back("R");
    pOnePointArray.push_back("N");
    pOnePointArray.push_back("S");
    pOnePointArray.push_back("T");
    
    //2Nd
    pTwoPointArray.push_back("D");
    pTwoPointArray.push_back("G");
    
    //3Rd
    pThreePointArray.push_back("B");
    pThreePointArray.push_back("C");
    pThreePointArray.push_back("M");
    pThreePointArray.push_back("P");
    
    //4rth
    pFourPointArray.push_back("F");
    pFourPointArray.push_back("H");
    pFourPointArray.push_back("V");
    pFourPointArray.push_back("W");
    pFourPointArray.push_back("Y");
    
    //5th
    pFivePointArray.push_back("K");

    //6th
    pEightPointArray.push_back("J");
    pEightPointArray.push_back("X");
    
    //7th
    pTenPointArray.push_back("Q");
    pTenPointArray.push_back("Z");
    
}

void WWGameScene::createAlphabetGridArray()
{
    for(auto alphabet : pOnePointArray)
    {
        this->createCustomAlphabet(1, alphabet);
    }
    
    for(auto alphabet1 : pTwoPointArray)
    {
        this->createCustomAlphabet(2, alphabet1);
    }
    
    for(auto alphabet2 : pThreePointArray)
    {
        this->createCustomAlphabet(3, alphabet2);
    }
    
    for(auto alphabet3 : pFourPointArray)
    {
        this->createCustomAlphabet(4, alphabet3);
    }
    
    for(auto alphabet4 : pFivePointArray)
    {
        this->createCustomAlphabet(5, alphabet4);
    }
    
    for(auto alphabet5 : pEightPointArray)
    {
        this->createCustomAlphabet(8, alphabet5);
    }
    
    for(auto alphabet6 : pTenPointArray)
    {
        this->createCustomAlphabet(10, alphabet6);
    }
}

void WWGameScene::createCustomAlphabet(int currentAlphabetVal , std::string pCurrentStr)
{
    if (pTotalGridAlphabet.size() < TOTALGRID)
    {
        WWAlphabetSprite* _tAlphabetStr = WWAlphabetSprite::create("square.png");
        addChild(_tAlphabetStr);
        _tAlphabetStr->objref = this;
        _tAlphabetStr->initializeFunc(currentAlphabetVal, pCurrentStr);
        pTotalGridAlphabet.pushBack(_tAlphabetStr);
    }

}

void WWGameScene::createGrid()
{
    float startXPos = origin.x + 100;
    float startYPos = origin.y + visibleSize.height / 1.5;
    int gridArrayCount = 0;
    for (int i = 0; i < ROWGRIDCOUNT; i++)
    {
        float sprheight = 0;
        for (int j = 0; j < ROWGRIDCOUNT; j++)
        {
            WWAlphabetSprite* alphaBetSpr = this->pTotalGridAlphabet.at(gridArrayCount);
            alphaBetSpr->setPosition(Vec2(startXPos, startYPos));
            startXPos = startXPos + alphaBetSpr->getContentSize().width;
            sprheight = alphaBetSpr->getContentSize().height;
            gridArrayCount++;
        }
        startXPos = origin.x + 100;
        startYPos = startYPos - sprheight;
    }
}

#pragma mark - button Action
void WWGameScene::onSubmitClicked(Ref* sender)
{
    log("Submit Action");
    
    //loop array & Check Selected String
    std::string _tSelectedStr = "";
    int totalScore = 0;
    for(WWAlphabetSprite* alphabetSpr : currentSelectedStr)
    {
        if (alphabetSpr->isAlreadyPressed)
        {
            std::string _tCurStr = alphabetSpr->currentAlphabet->getString();
            log("........ Current Alphabet Spr ..... %s",_tCurStr.c_str());
            _tSelectedStr = _tSelectedStr + _tCurStr;
            totalScore = totalScore + alphabetSpr->alphabetValue;
        }
    }

    log("..... Selected Str ..... %s",_tSelectedStr.c_str());
    if(WWObjectiveCCalls::checkifWordContainsDictionary(_tSelectedStr))
    {
        log("..................... Dictionary present......................");
        std::string alphaVal = toString(totalScore);
        alphaVal = "Score: " + alphaVal;
        currentScore->setString(alphaVal);
        resultSelectedStr->setString(_tSelectedStr);
        
        //Reset Grid
        this->resetGrid();
    }
    else
    {
        log("..................... Dictionary Not present......................");
        currentScore->setString("Score: 0");
        resultSelectedStr->setString("Does not present in Dictionary");
        this->resetAfterLost();
    }
}

#pragma mark - reset Animation
void WWGameScene::resetGrid()
{
    //loop array
    for(WWAlphabetSprite* alphabetSpr : currentSelectedStr)
        alphabetSpr->resetSprite();

    auto* sequenceAct = Sequence::create(DelayTime::create(2),CallFunc::create( CC_CALLBACK_0(WWGameScene::resetgameAfterSomeTime,this)), NULL);
    this->runAction(sequenceAct);
    
}

void WWGameScene::resetgameAfterSomeTime()
{
    currentScore->setString("Score: 0");
    resultSelectedStr->setString("Play new game");
    
    currentSelectedStr.clear();

}

void WWGameScene::resetAfterLost()
{
    //loop array
    for(WWAlphabetSprite* alphabetSpr : currentSelectedStr)
        alphabetSpr->resetSpriteAfterLost();
    
    auto* sequenceAct = Sequence::create(DelayTime::create(1),CallFunc::create( CC_CALLBACK_0(WWGameScene::resetgameAfterSomeTime,this)), NULL);
    this->runAction(sequenceAct);
}

#pragma mark - randomize Array
Vector<WWAlphabetSprite*> WWGameScene::shuffleArray(Vector<WWAlphabetSprite*> pArray)
{
    for (int x = 0; x < pArray.size(); x++)
    {
        int randInt = (arc4random() % (pArray.size() - x)) + x;
        pArray.swap(x, randInt);
    }
    return pArray;
}

