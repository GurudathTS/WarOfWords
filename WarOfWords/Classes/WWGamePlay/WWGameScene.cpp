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
#include "WWPlayerInfo.h"
#include "WWCommonUtilty.h"
#include "WWGameConstant.h"
#include "WWDatamanager.h"
#include "WWResultScreen.h"
#include "WWMainMenuScreen.h"

USING_NS_CC;

#define TOTALGRID 36
#define ROWGRIDCOUNT 6
#define MinAlphabetsRequired 0

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
    WWDatamanager::sharedManager()->gameSceneRef = this;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    this->currentGridRefvalue = 0;
    this->_mUpdatedString = "";
    this->currentPlayerProfress = nullptr;
    this->opponentPlayerProfress = nullptr;
    
    // Background
    auto backgroundSpr = Sprite::create("UI/Background.png");
    backgroundSpr->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(backgroundSpr);
    
    //load Dictionary
    std::string _tDictionarypath = FileUtils::getInstance()->fullPathForFilename("IOSDictionary");
    WWObjectiveCCalls::loadDictionary(_tDictionarypath);
   
    
    if(WWDatamanager::sharedManager()->_isExistingGameStarting)
    {
        ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
        this->getExistingGameDetail();
    }
    else
    {
        if(WWPlayerInfoRef->getTurnUserID() == WWPlayerInfoRef->getCurrentUserID())
        {
            this->initGameScene();
        }
        else
        {
            ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
        }
    }
    
    this->getAlphabetDetailtoServer();

    
    
    return true;
}

void WWGameScene::initGameScene()
{
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
    
    //Send Alphabet Detail to Server
    this->sendAlphabetDetailtoServer();
}

#pragma mark - UI
void WWGameScene::addUI(float pYpos)
{
   
    resultSelectedStr = Label::createWithTTF("", "fonts/Marker Felt.ttf", 40);
    resultSelectedStr->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height / 1.1 + origin.y));
    addChild(resultSelectedStr);
    resultSelectedStr->setVisible(false);
    
    //Add battel
    auto* pbatterSpr = Sprite::create("UI/Logo-Icon.png");
    pbatterSpr->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height / 1.05 + origin.y));
    addChild(pbatterSpr);
    
    //timer label
    this->pTimerLabel = Label::createWithTTF("", FN_GAME_FONT_NAME, FN_GAME_ALPHABET_FONT_SIZE);
    this->pTimerLabel->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height / 1.05 + origin.y - pbatterSpr->getContentSize().height/2 - 25));
    addChild(this->pTimerLabel);
    
    this->hourVal = 48;
    this->minVal = 0;
    this->secVal = 0;
    
    this->updateTimerLabel();
    this->schedule(CC_SCHEDULE_SELECTOR(WWGameScene::updateFunc), 1.0f);
    
    //profile Icon
    auto* currentPlayerProgressBar = Sprite::create("GameScene/HelthBar.png");
    currentPlayerProgressBar->setPosition(Vec2(pbatterSpr->getPositionX() - currentPlayerProgressBar->getContentSize().width * 0.925, pbatterSpr->getPositionY()));
    addChild(currentPlayerProgressBar);
    
    this->userProgressBar = 100;
    this->opponentProgressBar = 100;
    this->currentPlayerProfress = ProgressTimer::create(Sprite::create("GameScene/HelthBarHvr01.png"));
    this->currentPlayerProfress->setType(ProgressTimer::Type::BAR);
    this->currentPlayerProfress->setMidpoint(Vec2(0,0));
    this->currentPlayerProfress->setBarChangeRate(Vec2(1, 0));
    addChild(this->currentPlayerProfress);
    this->currentPlayerProfress->setPosition(Vec2(pbatterSpr->getPositionX() - currentPlayerProgressBar->getContentSize().width * 0.925, pbatterSpr->getPositionY()));
    
    auto* currentPlayerProfile = Sprite::create("MainMenu/ProfilePicColom.png");
    currentPlayerProfile->setPosition(Vec2(-currentPlayerProfile->getContentSize().width * 0.2, currentPlayerProfile->getContentSize().height * 0.1));
    this->currentPlayerProfress->addChild(currentPlayerProfile);
    currentPlayerProfile->setScale(0.4);
    
    if(WWPlayerInfoRef->getCurrentProfilePictureTexture())
        currentPlayerProfile->setTexture(WWPlayerInfoRef->getCurrentProfilePictureTexture());
    else
        currentPlayerProfile->setTexture("MainMenu/round.png");
    
    //Name
    auto* userNameLabel = Label::createWithTTF(WWPlayerInfoRef->getCurrentUserName(), "fonts/JosefinSlab-Bold.ttf", 24);
    userNameLabel->setPosition(Vec2(currentPlayerProgressBar->getContentSize().width * 0.5 , -currentPlayerProgressBar->getContentSize().height * 0.8));
    currentPlayerProgressBar->addChild(userNameLabel);
    
    //opponent Player Progress bar
    auto* opponentPlayerProgressBar = Sprite::create("GameScene/HelthBar.png");
    opponentPlayerProgressBar->setPosition(Vec2(pbatterSpr->getPositionX() + currentPlayerProgressBar->getContentSize().width * 0.925, pbatterSpr->getPositionY()));
    addChild(opponentPlayerProgressBar);
    
    
    this->opponentPlayerProfress = ProgressTimer::create(Sprite::create("GameScene/HelthBarHvr01.png"));
    this->opponentPlayerProfress->setType(ProgressTimer::Type::BAR);
    this->opponentPlayerProfress->setMidpoint(Vec2(1,0));
    this->opponentPlayerProfress->setBarChangeRate(Vec2(1, 0));
    addChild(this->opponentPlayerProfress);
    this->opponentPlayerProfress->setPosition(Vec2(pbatterSpr->getPositionX() + currentPlayerProgressBar->getContentSize().width * 0.925, pbatterSpr->getPositionY()));
    
    auto* opponentPlayerprofile = Sprite::create("MainMenu/ProfilePicColom.png");
    opponentPlayerprofile->setPosition(Vec2(opponentPlayerprofile->getContentSize().width * 1.2, opponentPlayerprofile->getContentSize().height * 0.1));
    this->opponentPlayerProfress->addChild(opponentPlayerprofile);
    opponentPlayerprofile->setScale(0.4);
    
    if(WWPlayerInfoRef->getOpponentProfilePictureTexture())
        opponentPlayerprofile->setTexture(WWPlayerInfoRef->getOpponentProfilePictureTexture());
    else
        opponentPlayerprofile->setTexture("MainMenu/round.png");

    
    //Name
    auto* opponentNameLabel = Label::createWithTTF(WWPlayerInfoRef->getOpponentUserName(), "fonts/JosefinSlab-Bold.ttf", 24);
    opponentNameLabel->setPosition(Vec2(opponentPlayerProgressBar->getContentSize().width * 0.5 , -opponentPlayerProgressBar->getContentSize().height * 0.8));
    opponentPlayerProgressBar->addChild(opponentNameLabel);
    
    //Star
    auto* pPointsColumn = Sprite::create("GameScene/PointsColom.png");
    pPointsColumn->setPosition(Vec2(visibleSize.width/2 + origin.x, pYpos ));
    addChild(pPointsColumn);
    
    
    currentScore = Label::createWithTTF("11 Points", "fonts/JosefinSlab-SemiBold.ttf", 24);
    currentScore->setPosition(Vec2(pPointsColumn->getContentSize().width * 0.6, pPointsColumn->getContentSize().height * 0.5));
    pPointsColumn->addChild(currentScore);
    
    //Back Button
    MenuItemImage* backBtn = MenuItemImage::create("LoginScreen/BackBtn.png", "LoginScreen/BackBtn.png", CC_CALLBACK_1(WWGameScene::onClickOnBackBtn, this));
    backBtn->setPosition(Vec2(this->origin.x + backBtn->getContentSize().width * 0.5, (this->visibleSize.height) + this->origin.y - (backBtn->getContentSize().height * 1.4)));
    backBtn->setScale(0.7);
    
    //Submit Button
    submitButton = MenuItemImage::create("GameScene/SubmitBtn.png", "GameScene/SubmitBtn.png", CC_CALLBACK_1(WWGameScene::onSubmitClicked, this));
    submitButton->setPosition(Vec2(visibleSize.width/2 + origin.x, pPointsColumn->getPositionY() - submitButton->getContentSize().height * 1.05));
    submitButton->setOpacity(100);
    submitButton->setEnabled(false);
    
    Menu* menubtn = Menu::create(submitButton,backBtn, NULL);
    menubtn->setPosition(Vec2::ZERO);
    addChild(menubtn);
    
    this->updateUserProgressBar(0.1);
    this->updateOpponentProgressBar(0.1);
}

#pragma mark - Initialize
void WWGameScene::initializeAlphabets()
{
    pAllAlphabetsArray.push_back("A");
    pAllAlphabetsArray.push_back("B");
    pAllAlphabetsArray.push_back("C");
    pAllAlphabetsArray.push_back("D");
    pAllAlphabetsArray.push_back("E");
    pAllAlphabetsArray.push_back("F");
    pAllAlphabetsArray.push_back("G");
    pAllAlphabetsArray.push_back("H");
    pAllAlphabetsArray.push_back("I");
    pAllAlphabetsArray.push_back("J");
    pAllAlphabetsArray.push_back("K");
    pAllAlphabetsArray.push_back("L");
    pAllAlphabetsArray.push_back("M");
    pAllAlphabetsArray.push_back("N");
    pAllAlphabetsArray.push_back("O");
    pAllAlphabetsArray.push_back("P");
    pAllAlphabetsArray.push_back("Q");
    pAllAlphabetsArray.push_back("R");
    pAllAlphabetsArray.push_back("S");
    pAllAlphabetsArray.push_back("T");
    pAllAlphabetsArray.push_back("U");
    pAllAlphabetsArray.push_back("V");
    pAllAlphabetsArray.push_back("W");
    pAllAlphabetsArray.push_back("X");
    pAllAlphabetsArray.push_back("Y");
    pAllAlphabetsArray.push_back("Z");
    
}

int WWGameScene::getAlphabetValue(std::string pAlphabet)
{
   if(pAlphabet == "A" || pAlphabet == "E" || pAlphabet == "I" || pAlphabet == "O" || pAlphabet == "U"|| pAlphabet == "L" || pAlphabet == "R" || pAlphabet == "N" || pAlphabet == "S" || pAlphabet == "T")
   {
       return  1;
   }
    else if(pAlphabet == "D" || pAlphabet == "G")
    {
        return  2;
    }
    else if(pAlphabet == "B" || pAlphabet == "C" || pAlphabet == "M" || pAlphabet == "P")
    {
        return  3;
    }
    else if(pAlphabet == "F" || pAlphabet == "H" || pAlphabet == "V" || pAlphabet == "W" || pAlphabet == "Y")
    {
        return  4;
    }
    else if(pAlphabet == "K")
    {
        return  5;
    }
    else if(pAlphabet == "J" || pAlphabet == "X")
    {
        return  8;
    }
    else if(pAlphabet == "Q" || pAlphabet == "Z")
    {
        return  10;
    }
    
    return 0;
}

void WWGameScene::createAlphabetGridArray()
{
    for(auto alphabet : pAllAlphabetsArray)
    {
        int alphabetvalue = this->getAlphabetValue(alphabet);
        this->createCustomAlphabet(alphabetvalue, alphabet);
    }
}

void WWGameScene::createCustomAlphabet(int currentAlphabetVal , std::string pCurrentStr)
{
    if (pTotalGridAlphabet.size() < TOTALGRID)
    {
        WWAlphabetSprite* _tAlphabetStr = WWAlphabetSprite::create("GameScene/LetterBox01.png");
        addChild(_tAlphabetStr);
        _tAlphabetStr->objref = this;
        _tAlphabetStr->initializeFunc(currentAlphabetVal, pCurrentStr);
        pTotalGridAlphabet.pushBack(_tAlphabetStr);
    }

}

float WWGameScene::createGrid()
{
    float startXPos = origin.x + 120;
    float startYPos = origin.y + visibleSize.height / 1.2;
    int gridArrayCount = 0;
    for (int i = 0; i < ROWGRIDCOUNT; i++)
    {
        float sprheight = 0;
        for (int j = 0; j < ROWGRIDCOUNT; j++)
        {
            WWAlphabetSprite* alphaBetSpr = this->pTotalGridAlphabet.at(gridArrayCount);
            alphaBetSpr->setPosition(Vec2(startXPos, startYPos));
            alphaBetSpr->updatedGridReferenceValue(gridArrayCount);
            startXPos = startXPos + alphaBetSpr->getContentSize().width;
            sprheight = alphaBetSpr->getContentSize().height;
            gridArrayCount++;
        }
        startXPos = origin.x + 120;
        startYPos = startYPos - sprheight;
    }
    
    return startYPos;
}

#pragma mark - button Action
void WWGameScene::onClickOnBackBtn(Ref* sender)
{
    HttpClient::getInstance()->destroyInstance();
    Director::getInstance()->replaceScene(WWMainMenu::createScene());
}

void WWGameScene::onSubmitClicked(Ref* sender)
{
    log("Submit Action");
    if(WWPlayerInfoRef->getTurnUserID() != WWPlayerInfoRef->getCurrentUserID())
        return;
    
    if(currentSelectedStr.size() < MinAlphabetsRequired)
    {
        MessageBox("Please Select 4 Letter", "Error");
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
    bool _tTest = true;
    if(WWObjectiveCCalls::checkifWordContainsDictionary(_tSelectedStr))
    {
        log("..................... Dictionary present......................");
        std::string alphaVal = toString(totalScore);
        alphaVal = "Score: " + alphaVal;
        currentScore->setString(alphaVal);
        resultSelectedStr->setString(_tSelectedStr);
        //this->resetGrid();
        this->opponentProgressBar = this->opponentProgressBar - totalScore;
        if(this->opponentProgressBar <= 0)
        {
            //Game Lose // Win
            this->onGameCompleteDetailtoServer();
            return;
        }
        else
        {
            //Reset Grid
            this->resetGrid();
        }
    }
    else
    {
        log("..................... Dictionary Not present......................");
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
    this->_mUpdatedString = "";
    
    //loop array
    for(WWAlphabetSprite* alphabetSpr : currentSelectedStr)
        alphabetSpr->resetSprite();
    
    auto* sequenceAct = Sequence::create(DelayTime::create(2),CallFunc::create( CC_CALLBACK_0(WWGameScene::updateAlphabetDetailtoServer,this)),CallFunc::create( CC_CALLBACK_0(WWGameScene::resetgameAfterSomeTime,this)), NULL);
    this->runAction(sequenceAct);
    
}



void WWGameScene::resetgameAfterSomeTime()
{
    currentScore->setString("Score: 0");
    resultSelectedStr->setString("");
    
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
    Sprite* pbgSpr = Sprite::create("GameScene/BottomDropdown.png");
    pbgSpr->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + pbgSpr->getContentSize().height/2));
    addChild(pbgSpr);
    
    //Down Icon
    Sprite* downIconSpr = Sprite::create("GameScene/ArrwBtn.png");
    downIconSpr->setPosition(Vec2(pbgSpr->getContentSize().width * 0.5, pbgSpr->getContentSize().height * 0.95));
    pbgSpr->addChild(downIconSpr);
    
    float startXPos = origin.x + 100;
    float startYPos = pbgSpr->getPositionY() + 40;
    
    //Power Up Icon
    WWPowerUpSprite* icon1 = WWPowerUpSprite::create("GameScene/PowerUp01.png");
    icon1->setPosition(Vec2(startXPos, startYPos));
    addChild(icon1);
    icon1->initUI("GameScene/PowerUp01_CountColm.png");
    
    startXPos = startXPos + icon1->getContentSize().width + 40;
    WWPowerUpSprite* icon2 = WWPowerUpSprite::create("GameScene/PowerUp02.png");
    icon2->setPosition(Vec2(startXPos, startYPos));
    addChild(icon2);
    icon2->initUI("GameScene/PowerUp02_CountColm.png");
    
    startXPos = startXPos + icon2->getContentSize().width + 40;
    WWPowerUpSprite* icon3 = WWPowerUpSprite::create("GameScene/PowerUp03.png");
    icon3->setPosition(Vec2(startXPos, startYPos));
    addChild(icon3);
    icon3->initUI("GameScene/PowerUp03_CountColm.png");
    
    startXPos = startXPos + icon3->getContentSize().width + 40;
    WWPowerUpSprite* icon4 = WWPowerUpSprite::create("GameScene/PowerUp04.png");
    icon4->setPosition(Vec2(startXPos, startYPos));
    addChild(icon4);
    icon4->initUI("GameScene/PowerUp04_colm.png");
    
    startXPos = startXPos + icon4->getContentSize().width + 40;
    WWPowerUpSprite* icon5 = WWPowerUpSprite::create("GameScene/PowerUp05.png");
    icon5->setPosition(Vec2(startXPos, startYPos));
    addChild(icon5);
    icon5->initUI("GameScene/PowerUp05_CountColm.png");
    
    startYPos = startYPos - icon5->getContentSize().height - 30;
    startXPos = origin.x + 100;
    
    WWPowerUpSprite* icon6 = WWPowerUpSprite::create("GameScene/PowerUp06.png");
    icon6->setPosition(Vec2(startXPos, startYPos));
    addChild(icon6);
    icon6->initUI("");
    
    startXPos = startXPos + icon6->getContentSize().width + 40;
    WWPowerUpSprite* icon7 = WWPowerUpSprite::create("GameScene/PowerUp07.png");
    icon7->setPosition(Vec2(startXPos, startYPos));
    addChild(icon7);
    icon7->initUI("");
    
    startXPos = startXPos + icon7->getContentSize().width + 40;
    WWPowerUpSprite* icon8 = WWPowerUpSprite::create("GameScene/PowerUp08.png");
    icon8->setPosition(Vec2(startXPos, startYPos));
    addChild(icon8);
    icon8->initUI("");

    startXPos = startXPos + icon8->getContentSize().width + 40;
    WWPowerUpSprite* icon9 = WWPowerUpSprite::create("GameScene/PowerUp09.png");
    icon9->setPosition(Vec2(startXPos, startYPos));
    addChild(icon9);
    icon9->initUI("");

    startXPos = startXPos + icon9->getContentSize().width + 40;
    WWPowerUpSprite* icon10 = WWPowerUpSprite::create("GameScene/PowerUp10.png");
    icon10->setPosition(Vec2(startXPos, startYPos));
    addChild(icon10);
    icon10->initUI("");

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


#pragma mark - Send Game Data to Server
void WWGameScene::sendAlphabetDetailtoServer()
{
    ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
    
    std::string _tFullAlphabetStr = "";
    for (int i = 0; i < this->pTotalGridAlphabet.size(); i++)
    {
        WWAlphabetSprite* alphaBetSpr = this->pTotalGridAlphabet.at(i);
        _tFullAlphabetStr = _tFullAlphabetStr + alphaBetSpr->currentAlphabet->getString();
    }
    
    log("......... _tFullAlphabetStr ........ %s",_tFullAlphabetStr.c_str());
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    std::string opponentHealth = NumToString(this->opponentProgressBar);
    std::string UserHealth = NumToString(this->userProgressBar);
    std::string pConfigSTr = this->createGameConfig(_tFullAlphabetStr, "");
    url=url+"savegame?";
    url=url+"apiKey"+"="+WWDatamanager::sharedManager()->getAPIKey();
    url=url+"&challengeId"+"="+WWPlayerInfoRef->getChallengeID();
    url=url+"&opponentUserId"+"="+WWPlayerInfoRef->getOpponentUserID();
    url=url+"&turnUserId"+"="+WWPlayerInfoRef->getOpponentUserID();
    url=url+"&userHealth"+"="+UserHealth;
    url=url+"&userScore"+"="+"";
    url=url+"&opponentHealth"+"="+opponentHealth;
    url=url+"&opponentScore"+"="+"";
    url=url+"&gameConfig"+"="+pConfigSTr; //
    url=url+"&wonBy"+"="+"";
    url=url+"&status"+"="+"2";
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::POST);
    
    request->setResponseCallback(CC_CALLBACK_2(WWGameScene::onSentAlphabetRequestCompleted, this));
    request->setTag("saveGameData");
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
    
}
void WWGameScene::onSentAlphabetRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    
    ActivtyIndicator::PopIfActiveFromScene(this);
    log("..........On Save Completed.......");
}

void WWGameScene::getAlphabetDetailtoServer()
{
    //ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"getupdates?";
    url=url+"apiKey"+"="+WWDatamanager::sharedManager()->getAPIKey();
    url=url+"&lastUpdatedDate"+"="+WWDatamanager::sharedManager()->lastUpdatedStr;
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::GET);
    
    request->setResponseCallback(CC_CALLBACK_2(WWGameScene::onGetAlphabetRequestCompleted, this));
    request->setTag("getGameData");
    HttpClient::getInstance()->send(request);
    request->release();
    
}
void WWGameScene::onGetAlphabetRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    
    if(WWDatamanager::sharedManager()->gameSceneRef != this)
        return;
    
    if (!response)
    {
        return;
    }
    int statusCode = (int)response->getResponseCode();
    if(statusCode == -1)
    {
        this->getAlphabetDetailtoServer();
        return;
        
    }
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);

    log("..........On Save Completed.......");
    
    //Check error code
    int errorCodeNo = document["errorCode"].GetInt();
    
    if(errorCodeNo == 0)
    {
        //Check Status
        std::string _tStatus = document["games"][0]["status"].GetString();
        std::string _tAlphabetStr = document["games"][0]["gameConfig"].GetString();
        std::string _tTurnUserId = document["games"][0]["turnUserId"].GetString();
        WWPlayerInfoRef->updateTurnUserID(_tTurnUserId);
        
        //Opponent user ID
        std::string _tOpponentHealth = document["games"][0]["opponentHealth"].GetString();
        std::string _tUserHealth = document["games"][0]["userHealth"].GetString();

        this->userProgressBar = std::atoi(_tUserHealth.c_str());
        this->opponentProgressBar = std::atoi(_tOpponentHealth.c_str());
        this->updateUserProgressBar(0.5);
        this->updateOpponentProgressBar(0.5);

        long int updatedStr = document["lastUpdatedDate"].GetInt();
        WWDatamanager::sharedManager()->lastUpdatedStr = NumToString(updatedStr);
        
        rapidjson::Document document1;
        document1.Parse<0>(_tAlphabetStr.c_str());
        
        std::string fullStr  = document1["FullAlphabetString"].GetString();
        std::string updaStr  = document1["LastTurnAlbhabet"].GetString();
        
        if(_tStatus == "1")
        {
            //Finished
            std::string _tWinUserId = document["games"][0]["wonBy"].GetString();
            if (_tWinUserId == WWPlayerInfoRef->getCurrentUserID())
                WWPlayerInfoRef->_mIsUserWinGame = true;
            else
                WWPlayerInfoRef->_mIsUserWinGame = false;
            
            Director::getInstance()->replaceScene(WWResultScreen::createScene());
            
            return;
            
        }
        
        if(_tStatus == "5")
        {
            if(_tTurnUserId == WWPlayerInfoRef->getCurrentUserID())
            {
                //Update Alphabet
                this->updateAlphabetFromServer(updaStr);
            }
        }
        else
        {
            if(_tTurnUserId == WWPlayerInfoRef->getCurrentUserID())
            {
                this->createAlphabetFromServer(fullStr);
            }
        }

    }
    //else
    {

        this->getAlphabetDetailtoServer();
    }
}

void WWGameScene::createAlphabetFromServer(std::string pAlphabetStr)
{
    for (int i = 0; i < pAlphabetStr.length(); i++)
    {
        std::string pStringStr = pAlphabetStr.substr(i,1);
        pAllAlphabetsArray.push_back(pStringStr);
    }
    
    this->createAlphabetGridArray();
    
    //Shuffle Array
    //pTotalGridAlphabet = this->shuffleArray(pTotalGridAlphabet);
    log("........ Array Count............ %zd",pTotalGridAlphabet.size());
    
    float yPos = this->createGrid();
    
    //Power Up
    this->createPowerUpIcon();
    
    //UI
    this->addUI(yPos);
    
    //Remove Active Indicator
    ActivtyIndicator::PopIfActiveFromScene(this);

}

#pragma mark - Update Game Detail
void WWGameScene::updateAlphabetDetailtoServer()
{
    ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
    
    log("......... _tFullAlphabetStr ........ %s",this->_mUpdatedString.c_str());
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    std::string _tFullAlphabetStr = "";
    for (int i = 0; i < this->pTotalGridAlphabet.size(); i++)
    {
        WWAlphabetSprite* alphaBetSpr = this->pTotalGridAlphabet.at(i);
        _tFullAlphabetStr = _tFullAlphabetStr + alphaBetSpr->currentAlphabet->getString();
    }
    
    std::string pConfigSTr = this->createGameConfig(_tFullAlphabetStr, this->_mUpdatedString);

    std::string opponentHealth = NumToString(this->opponentProgressBar);
    std::string UserHealth = NumToString(this->userProgressBar);
    url=url+"savegame?";
    url=url+"apiKey"+"="+WWDatamanager::sharedManager()->getAPIKey();
    url=url+"&challengeId"+"="+WWPlayerInfoRef->getChallengeID();
    url=url+"&opponentUserId"+"="+WWPlayerInfoRef->getOpponentUserID();
    url=url+"&turnUserId"+"="+WWPlayerInfoRef->getOpponentUserID();
    url=url+"&userHealth"+"="+UserHealth;
    url=url+"&userScore"+"="+"";
    url=url+"&opponentHealth"+"="+opponentHealth;
    url=url+"&opponentScore"+"="+"";
    url=url+"&gameConfig"+"="+pConfigSTr.c_str();
    url=url+"&wonBy"+"="+"";
    url=url+"&status"+"="+"5";   //    //Status 5 means Update
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::POST);
    
    request->setResponseCallback(CC_CALLBACK_2(WWGameScene::onUpdateAlphabetRequestCompleted, this));
    request->setTag("saveGameData");
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
    
}

void WWGameScene::onGameCompleteDetailtoServer()
{
    ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
    
    log("......... _tFullAlphabetStr ........ %s",this->_mUpdatedString.c_str());
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    std::string _tFullAlphabetStr = "";
    for (int i = 0; i < this->pTotalGridAlphabet.size(); i++)
    {
        WWAlphabetSprite* alphaBetSpr = this->pTotalGridAlphabet.at(i);
        _tFullAlphabetStr = _tFullAlphabetStr + alphaBetSpr->currentAlphabet->getString();
    }
    
    std::string pConfigSTr = this->createGameConfig(_tFullAlphabetStr, this->_mUpdatedString);
    
    std::string opponentHealth = NumToString(this->opponentProgressBar);
    std::string UserHealth = NumToString(this->userProgressBar);
    url=url+"savegame?";
    url=url+"apiKey"+"="+WWDatamanager::sharedManager()->getAPIKey();
    url=url+"&challengeId"+"="+WWPlayerInfoRef->getChallengeID();
    url=url+"&opponentUserId"+"="+WWPlayerInfoRef->getOpponentUserID();
    url=url+"&turnUserId"+"="+WWPlayerInfoRef->getOpponentUserID();
    url=url+"&userHealth"+"="+UserHealth;
    url=url+"&userScore"+"="+"";
    url=url+"&opponentHealth"+"="+opponentHealth;
    url=url+"&opponentScore"+"="+"";
    url=url+"&gameConfig"+"="+pConfigSTr.c_str();
    url=url+"&wonBy"+"="+WWPlayerInfoRef->getCurrentUserID();
    url=url+"&status"+"="+"1";   //    //Status 4 means Update
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::POST);
    
    request->setResponseCallback(CC_CALLBACK_2(WWGameScene::onUpdateAlphabetRequestCompleted, this));
    request->setTag("saveGameData");
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
    
}

void WWGameScene::onUpdateAlphabetRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    
    ActivtyIndicator::PopIfActiveFromScene(this);
    log("..........On Update Completed.......");
}

void WWGameScene::updateAlphabetFromServer(std::string pAlphabetStr)
{
    
    //Seperate String From Delimter
    vector<std::string> spliStr = this->split(pAlphabetStr, '/');
    
    for (int i = 0; i < spliStr.size(); i++)
    {
        std::string pStringStr = spliStr.at(i);
        int gridRefVal = std::atoi(pStringStr.c_str());
        if (this->has_only_digits(pStringStr))
        {
            if((i + 1) < spliStr.size())
            {
                std::string pNextStr = spliStr.at(i+1);
                
                //loop array
                for(WWAlphabetSprite* alphabetSpr : pTotalGridAlphabet)
                {
                    if (alphabetSpr->gridRefValue == gridRefVal) {
                        
                        alphabetSpr->updateSprite(pNextStr);
                        break;
                    }
                }
            }
        }
    }
    
    auto* sequenceAct = Sequence::create(DelayTime::create(2),CallFunc::create( CC_CALLBACK_0(WWGameScene::resetgameAfterSomeTime,this)), NULL);
    this->runAction(sequenceAct);

    //Remove Active Indicator
    ActivtyIndicator::PopIfActiveFromScene(this);
    
}

void WWGameScene::updateUserProgressBar(float pTime)
{
    
    if(this->currentPlayerProfress != nullptr)
    {
        this->currentPlayerProfress->stopAllActions();
        ProgressTo* action = ProgressTo::create(pTime, this->userProgressBar);
        this->currentPlayerProfress->runAction(action);
    }
    
}

void WWGameScene::updateOpponentProgressBar(float pTime)
{
    if(this->opponentPlayerProfress != nullptr)
    {
        this->opponentPlayerProfress->stopAllActions();
        ProgressTo* action = ProgressTo::create(pTime, this->opponentProgressBar);
        this->opponentPlayerProfress->runAction(action);
    }
    
}

bool WWGameScene::has_only_digits(const std::string s){
    
    return s.find_first_not_of( "0123456789" ) == std::string::npos;
}

vector<std::string> WWGameScene::split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

#pragma mark - Game config
std::string WWGameScene::createGameConfig(std::string pFullAlphabetStr, std::string updatedStr)
{

    rapidjson::StringBuffer sstream;
    
    rapidjson::Writer<rapidjson::StringBuffer> writer(sstream);
    
    writer.StartObject();
    writer.String("FullAlphabetString");
    writer.String(pFullAlphabetStr.c_str());

    writer.String("LastTurnAlbhabet");
    writer.String(updatedStr.c_str());
    
    writer.EndObject();
    
    std::string str1 = sstream.GetString();
    std::string pConfigSTr = std::urlencode(str1.c_str()) ;

    return pConfigSTr;

}
#pragma mark - Get Existing game
void WWGameScene::getExistingGameDetail()
{
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"getgame?";
    url=url+"apiKey"+"="+WWDatamanager::sharedManager()->getAPIKey();
    url=url+"&challengeId"+"="+WWPlayerInfoRef->getChallengeID();
    
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::GET);
    
    request->setResponseCallback(CC_CALLBACK_2(WWGameScene::onGetExistingGameDetail, this));
    request->setTag("getgame");
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
    
}
void WWGameScene::onGetExistingGameDetail(HttpClient *sender, HttpResponse *response)
{
    
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    
    int statusCode = (int)response->getResponseCode();
    if(statusCode == -1)
    {
        
        return;
        
    }
    
    //Check error code
    int errorCodeNo = document["errorCode"].GetInt();
    
    if(errorCodeNo == 0)
    {
        
            
            {
                std::string _tOpponentUserName  = document["game"]["opponentName"].GetString();
                std::string _tOppoentProfileImg  = document["game"]["opponentThumbnail"].GetString();
                std::string opponentId  = document["game"]["opponentUserId"].GetString();
                std::string turnUserId  = document["game"]["turnUserId"].GetString();
                std::string wonBy  = document["game"]["wonBy"].GetString();
                std::string challengeId  = document["game"]["challengeId"].GetString();
                std::string status  = document["game"]["status"].GetString();
                std::string lastUpdatedate =document["game"]["updatedDate"].GetString();
                std::string _tAlphabetStr =document["game"]["gameConfig"].GetString();

                
                rapidjson::Document document1;
                document1.Parse<0>(_tAlphabetStr.c_str());
                
                std::string fullStr  = document1["FullAlphabetString"].GetString();
                std::string updaStr  = document1["LastTurnAlbhabet"].GetString();
                log("........... Full String........ %s",fullStr.c_str());
                this->createAlphabetFromServer(fullStr);
                
                //Health bar
                //Opponent user ID
                std::string _tOpponentHealth  = document["game"]["opponentHealth"].GetString();
                std::string _tUserHealth = document["game"]["userHealth"].GetString();
                
                this->userProgressBar = std::atoi(_tUserHealth.c_str());
                this->opponentProgressBar = std::atoi(_tOpponentHealth.c_str());
                this->updateUserProgressBar(0.5);
                this->updateOpponentProgressBar(0.5);
                
            }
        
        //this->getAlphabetDetailtoServer();

        }
}
