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
#include "WWAlphabetSprite.h"
#include "cocos2d.h"
#include <vector>
#include <string>
#include "WWPowerUpSprite.h"
#include "WWPlayerInfo.h"
#include "extensions/cocos-ext.h"
#include "json/rapidjson.h"
#include "json/filestream.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

#include "extensions/cocos-ext.h"
using namespace cocos2d::extension;
using namespace cocos2d::network;
using namespace cocos2d::ui;

#include "json/rapidjson.h"
#include "json/filestream.h"
#include "json/document.h"

#include "WWGameUtility.h"

using namespace std;
using namespace cocos2d;

class WWGameScene : public Layer
{
public:
    static cocos2d::Scene* createScene();
    WWGameScene* gameSceneRef;
    
    virtual bool init();
    void initGameScene();
    
    //Variable
    cocos2d::Size visibleSize;
    Vec2 origin;
    
    //Different kind of Alphabets Array
    vector<std::string> pOnePointArray;
    vector<std::string> pTwoPointArray;
    vector<std::string> pThreePointArray;
    vector<std::string> pFourPointArray;
    vector<std::string> pFivePointArray;
    vector<std::string> pEightPointArray;
    vector<std::string> pTenPointArray;
    
    vector<std::string> pAllAlphabetsArray;
    
    Vector<WWAlphabetSprite*> pTotalGridAlphabet;
    Vector<WWAlphabetSprite*> currentSelectedStr;
    
    //Init
    void initializeAlphabets();
    void createAlphabetGridArray();
    int  getAlphabetValue(std::string pAlphabet);
    void createCustomAlphabet(int currentAlphabetVal , std::string pCurrentStr);
    float createGrid();
    int currentGridRefvalue;
    std::string _mUpdatedString;
    
    //Score
    Label* currentScore;
    Label* resultSelectedStr;
    void addUI(float pYpos);
    
    //timer
    Label* pTimerLabel;
    Label* pUserPercentageLabel;
    Label* pOpponentPercentageLabel;
    int hourVal;
    int minVal;
    int secVal;
    void updateFunc(float dt);
    void updateTimerLabel();
    
    //Submit
    MenuItemImage* submitButton;
    void onSubmitClicked(Ref* sender);
    void onPowerUpClicked(Ref* sender);
    
    //reset
    void resetGrid();
    void resetgameAfterSomeTime();
    void resetAfterLost();
    
    //Shuffle
    Vector<WWAlphabetSprite*> shuffleArray(Vector<WWAlphabetSprite*> pArray);
    
    //Power Up
    void createPowerUpIcon();
    
    //Progress
    ProgressTimer* currentPlayerProfress;
    ProgressTimer* opponentPlayerProfress;
    
    void updateUserProgressBar(float pTime);
    void updateOpponentProgressBar(float pTime);
    int userProgressBar;
    int opponentProgressBar;

    //Http request
    void sendAlphabetDetailtoServer();
    void onSentAlphabetRequestCompleted(HttpClient *sender, HttpResponse *response);
    void getAlphabetDetailtoServer();
    void onGetAlphabetRequestCompleted(HttpClient *sender, HttpResponse *response);
    void createAlphabetFromServer(std::string pAlphabetStr);
    void updateAlphabetDetailtoServer();
    void onUpdateAlphabetRequestCompleted(HttpClient *sender, HttpResponse *response);
    void updateAlphabetFromServer(std::string pAlphabetStr);
    void onGameCompleteDetailtoServer();
    
    //Utility
    bool has_only_digits(const std::string s);
    vector<string> split(const string &s, char delim);
    
    void onClickOnBackBtn(Ref* sender);
    
    std::string createGameConfig(std::string pFullAlphabetStr, std::string updatedStr);
    
    void getExistingGameDetail();
    void onGetExistingGameDetail(HttpClient *sender, HttpResponse *response);

    
    // implement the "static create()" method manually
    CREATE_FUNC(WWGameScene);
};

#endif /* WWGameScene_hpp */
