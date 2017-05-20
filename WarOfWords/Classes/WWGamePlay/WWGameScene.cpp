//
//  WWGameScene.cpp
//  WarOfWords
//
//  Created by Gurudath on 2/20/17.
//
//

#include "WWGameScene.h"
#include "WWObjectiveCCalls.h"
#include "WWGameConstant.h"
#include "WWSocialManager.h"
#include "WWSocialFriendDetail.h"

USING_NS_CC;

#define TOTALGRID 36
#define ROWGRIDCOUNT 6
#define MinAlphabetsRequired 4

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
    auto backgroundSpr = Sprite::create("UI/Background.png");
    backgroundSpr->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(backgroundSpr);
    
    //load Dictionary
    std::string _tDictionarypath = FileUtils::getInstance()->fullPathForFilename("IOSDictionary");
    WWObjectiveCCalls::loadDictionary(_tDictionarypath);
   
    
    //Initialize Alphabets
    this->initializeAlphabets();

    //Create Alphabets Grid
    this->createAlphabetGridArray();
    this->createAlphabetGridArray();
    this->createAlphabetGridArray();
    
    //Shuffle Array
    pTotalGridAlphabet = this->shuffleArray(pTotalGridAlphabet);
    log("........ Array Count............ %zd",pTotalGridAlphabet.size());
    
    float yPos = this->createGrid();
    
    //Power Up
    this->createPowerUpIcon();
    
    //UI
    this->addUI(yPos);
    
    return true;
}

#pragma mark - UI
void WWGameScene::addUI(float pYpos)
{
    currentScore = Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf", 40);
    currentScore->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height / 1.2 + origin.y));
    addChild(currentScore);
    currentScore->setVisible(false);
    
    resultSelectedStr = Label::createWithTTF("", "fonts/Marker Felt.ttf", 40);
    resultSelectedStr->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height / 1.1 + origin.y));
    addChild(resultSelectedStr);
    
    //Add battel
    auto* pbatterSpr = Sprite::create("UI/Logo-Icon.png");
    pbatterSpr->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height / 1.05 + origin.y));
    addChild(pbatterSpr);
    
    //timer label
    this->pTimerLabel = Label::createWithTTF("", FN_GAME_FONT_NAME, FN_GAME_ALPHABET_FONT_SIZE);
    this->pTimerLabel->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height / 1.05 + origin.y - pbatterSpr->getContentSize().height/2 - 50));
    addChild(this->pTimerLabel);
    
    this->hourVal = 23;
    this->minVal = 0;
    this->secVal = 0;
    
    this->updateTimerLabel();
    this->schedule(CC_SCHEDULE_SELECTOR(WWGameScene::updateFunc), 1.0f);
    
    //User Name & Profle
    auto* profilePict = Sprite::create("square.png");
    profilePict->setPosition(Vec2(visibleSize.width/8 + origin.x, visibleSize.height / 1.05 + origin.y));
    addChild(profilePict);
    
//    if(WWSocialManagerRef->currentLoginUserDetail->getTexture())
//    {
//        profilePict->setTexture(WWSocialManagerRef->currentLoginUserDetail->getTexture());
//    }
    
    std::string userName = "Guest";
    if(WWSocialManagerRef->currentLoginUserDetail)
    {
        log("Current USer Info %s",WWSocialManagerRef->currentLoginUserDetail->getName().c_str());
        userName = WWSocialManagerRef->currentLoginUserDetail->getName();
    }
    
    auto* userNameLabel = Label::createWithTTF(userName, FN_GAME_FONT_NAME, FN_GAME_ALPHABET_SCORE_SIZE);
    userNameLabel->setPosition(Vec2(visibleSize.width/8 + origin.x, visibleSize.height / 1.05 + origin.y - profilePict->getContentSize().height ));
    addChild(userNameLabel);
    userNameLabel->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    
    
    //Submit Button
    auto* submitButton = MenuItemFont::create("SUBMIT", CC_CALLBACK_1(WWGameScene::onSubmitClicked, this));
    submitButton->setPosition(Vec2(visibleSize.width/2 + origin.x, pYpos - 50));
    submitButton->setFontSize(35);
    
    Menu* menubtn = Menu::create(submitButton, NULL);
    menubtn->setPosition(Vec2::ZERO);
    addChild(menubtn);
    
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

float WWGameScene::createGrid()
{
    float startXPos = origin.x + 90;
    float startYPos = origin.y + visibleSize.height / 1.25;
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
        startXPos = origin.x + 90;
        startYPos = startYPos - sprheight;
    }
    
    return startYPos;
}

#pragma mark - button Action
void WWGameScene::onSubmitClicked(Ref* sender)
{
    log("Submit Action");
    
    if(currentSelectedStr.size() < MinAlphabetsRequired)
    {
        MessageBox("Please Select 3 Letter", "Error");
        return;
    }
    
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

void WWGameScene::onPowerUpClicked(Ref* sender)
{
    
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

#pragma mark - Power Up
void WWGameScene::createPowerUpIcon()
{
    //Bg
    Sprite* pbgSpr = Sprite::create("UI/Marble-texture.png");
    pbgSpr->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + pbgSpr->getContentSize().height/2));
    addChild(pbgSpr);
    
    //Down Icon
    Sprite* downIconSpr = Sprite::create("UI/Down-Arrow.png");
    downIconSpr->setPosition(Vec2(pbgSpr->getContentSize().width * 0.5, pbgSpr->getContentSize().height));
    pbgSpr->addChild(downIconSpr);
    
    float startXPos = origin.x + 100;
    float startYPos = pbgSpr->getPositionY() + 40;
    
    //Power Up Icon
    WWPowerUpSprite* icon1 = WWPowerUpSprite::create("GameScene/Fire.png");
    icon1->setPosition(Vec2(startXPos, startYPos));
    addChild(icon1);
    icon1->initUI();
    
    startXPos = startXPos + icon1->getContentSize().width + 50;
    WWPowerUpSprite* icon2 = WWPowerUpSprite::create("GameScene/Earth.png");
    icon2->setPosition(Vec2(startXPos, startYPos));
    addChild(icon2);
    icon2->initUI();
    
    startXPos = startXPos + icon2->getContentSize().width + 50;
    WWPowerUpSprite* icon3 = WWPowerUpSprite::create("GameScene/Poison.png");
    icon3->setPosition(Vec2(startXPos, startYPos));
    addChild(icon3);
    icon3->initUI();
    
    startXPos = startXPos + icon3->getContentSize().width + 50;
    WWPowerUpSprite* icon4 = WWPowerUpSprite::create("GameScene/Shield.png");
    icon4->setPosition(Vec2(startXPos, startYPos));
    addChild(icon4);
    icon4->initUI();
    
    startXPos = startXPos + icon4->getContentSize().width + 50;
    WWPowerUpSprite* icon5 = WWPowerUpSprite::create("GameScene/Cure-All.png");
    icon5->setPosition(Vec2(startXPos, startYPos));
    addChild(icon5);
    icon5->initUI();
    
    startYPos = startYPos - icon5->getContentSize().height - 10;
    startXPos = origin.x + 100;
    
    WWPowerUpSprite* icon6 = WWPowerUpSprite::create("GameScene/Water.png");
    icon6->setPosition(Vec2(startXPos, startYPos));
    addChild(icon6);
    icon6->initUI();
    
    startXPos = startXPos + icon6->getContentSize().width + 50;
    WWPowerUpSprite* icon7 = WWPowerUpSprite::create("GameScene/Air.png");
    icon7->setPosition(Vec2(startXPos, startYPos));
    addChild(icon7);
    icon7->initUI();
    
    startXPos = startXPos + icon7->getContentSize().width + 50;
    WWPowerUpSprite* icon8 = WWPowerUpSprite::create("GameScene/Antidote.png");
    icon8->setPosition(Vec2(startXPos, startYPos));
    addChild(icon8);
    icon8->initUI();

    startXPos = startXPos + icon8->getContentSize().width + 50;
    WWPowerUpSprite* icon9 = WWPowerUpSprite::create("GameScene/Hint.png");
    icon9->setPosition(Vec2(startXPos, startYPos));
    addChild(icon9);
    icon9->initUI();

    
    startXPos = startXPos + icon9->getContentSize().width + 50;
    WWPowerUpSprite* icon10 = WWPowerUpSprite::create("GameScene/Time-Booster.png");
    icon10->setPosition(Vec2(startXPos, startYPos));
    addChild(icon10);
    icon10->initUI();

}

void WWGameScene::updateTimerLabel()
{
    secVal = secVal - 1;
    if (secVal <= 0) {
        secVal = 60;
        minVal = minVal - 1;
    }
    if (minVal <= 0) {
        minVal = 59;
        hourVal = hourVal - 1;
    }
    std::string _tStr = ":";
    std::string _tTimerStr = toString(hourVal) + _tStr + toString(minVal) + _tStr + toString(secVal);
    pTimerLabel->setString(_tTimerStr);
}

void WWGameScene::updateFunc(float dt)
{
    this->updateTimerLabel();
}
