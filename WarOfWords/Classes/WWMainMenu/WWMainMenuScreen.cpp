//
//  WWMainMenuScreen.cpp
//  WarOfWords
//
//  Created by Gurudath on 5/2/17.
//
//

#include "WWMainMenuScreen.h"
#include "WWMainMenuActiveList.h"
#include "WWBattleScreen.h"
#include "WWCommonUtilty.h"
#include "WWGameConstant.h"
#include "WWDatamanager.h"

Scene* WWMainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WWMainMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void WWMainMenu::onEnter()
{
    Layer::onEnter();
    
    //Add Ui
    this->addUI();
    
}
void WWMainMenu::onExit()
{
    Layer::onExit();
}

#pragma mark - Init
// on "init" you need to initialize your instance
bool WWMainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    WWDatamanager::sharedManager()->_isUserInMainScene = true;
    WWDatamanager::sharedManager()->_mainScreenRef = this;
    
    this->visibleSize = Director::getInstance()->getVisibleSize();
    this->origin = Director::getInstance()->getVisibleOrigin();
    this->settingPannelLayer = nullptr;
    this->playConfirmationPopup = nullptr;
    WWDatamanager::sharedManager()->lastUpdatedStr = "";
    
    // Background
    auto backgroundSpr = Sprite::create("LandingScreen/LandngScreenBg.png");
    backgroundSpr->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x, this->visibleSize.height/2 + this->origin.y));
    this->addChild(backgroundSpr);
    
    this->getUserDetailsAPI();
    
    return true;
}

void WWMainMenu::addUI()
{
    //logo Image
    auto logoImage = Sprite::create("ForgotPassword/ShieldIcon.png");
    logoImage->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x , this->visibleSize.height + this->origin.y - logoImage->getContentSize().height * 0.7));
    this->addChild(logoImage);
    
    //Setting Button
    this->settingButton = MenuItemImage::create("MainMenu/SettngBtn.png", "MainMenu/SettngBtn.png", CC_CALLBACK_1(WWMainMenu::onClickOnSettingBtn, this));
    this->settingButton->setPosition(Vec2(this->origin.x + this->settingButton->getContentSize().width * 0.8, (this->visibleSize.height) + this->origin.y - (this->settingButton->getContentSize().height * 0.8)));
    this->settingButton->setScale(0.9);
    
    //In app Button
    this->inappbtn = MenuItemImage::create("MainMenu/StoreBtn.png", "MainMenu/StoreBtn.png", CC_CALLBACK_1(WWMainMenu::onClickOnInAppBtn, this));
    this->inappbtn->setPosition(Vec2(this->visibleSize.width + this->origin.x - this->inappbtn->getContentSize().width * 0.8, this->visibleSize.height + this->origin.y - (this->inappbtn->getContentSize().height * 0.8)));
    this->inappbtn->setScale(0.9);
    
    //Quick Match Button
    this->quickMatchBtn = MenuItemImage::create("MainMenu/YellowBtn.png", "MainMenu/YellowBtn.png", CC_CALLBACK_1(WWMainMenu::onClickOnQuickmatchBtn, this));
    this->quickMatchBtn->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x, this->origin.y + this->quickMatchBtn->getContentSize().height));
    this->quickMatchBtn->setScale(0.85);
    
    auto* quickmatchLabel = Label::createWithTTF("Quick Match", "fonts/Kingthings Sans.ttf", 44);
    quickmatchLabel->setPosition(this->quickMatchBtn->getContentSize() * 0.5);
    this->quickMatchBtn->addChild(quickmatchLabel);
    quickmatchLabel->setColor(Color3B(164,74,76));
    
    //How to play & guild
    this->howtoPlaybtn = MenuItemImage::create("MainMenu/BlueCommonBtnSamll.png", "MainMenu/BlueCommonBtnSamll.png", CC_CALLBACK_1(WWMainMenu::onClickOnHowToPlaybtnBtn, this));
    this->howtoPlaybtn->setPosition(Vec2(this->quickMatchBtn->getPositionX() - this->howtoPlaybtn->getContentSize().width/2 , this->quickMatchBtn->getPositionY() + this->howtoPlaybtn->getContentSize().height * 1.2));
    this->howtoPlaybtn->setScale(0.85);

    
    auto* howToPlayLabel = Label::createWithTTF("How to Play", "fonts/Kingthings Sans.ttf", 46);
    howToPlayLabel->setPosition(this->howtoPlaybtn->getContentSize() * 0.5);
    this->howtoPlaybtn->addChild(howToPlayLabel);
    howToPlayLabel->setColor(Color3B(29, 61, 187));

    
    this->createbuildbtn = MenuItemImage::create("MainMenu/CommonBtnSmall_Desable.png", "MainMenu/CommonBtnSmall_Desable.png", CC_CALLBACK_1(WWMainMenu::onClickOnGuildbtnBtn, this));
    this->createbuildbtn->setPosition(Vec2(this->quickMatchBtn->getPositionX() + this->createbuildbtn->getContentSize().width/2 , this->quickMatchBtn->getPositionY() + this->createbuildbtn->getContentSize().height * 1.1));
    this->createbuildbtn->setScale(0.85);
    
    auto* buildLabel = Label::createWithTTF("Guilds", "fonts/Kingthings Sans.ttf", 46);
    buildLabel->setPosition(this->createbuildbtn->getContentSize() * 0.5);
    this->createbuildbtn->addChild(buildLabel);
    buildLabel->setColor(Color3B(126, 126, 126));

    //Menu
    Menu* menuBtn = Menu::create(this->settingButton,this->quickMatchBtn,this->inappbtn,this->howtoPlaybtn,this->createbuildbtn, NULL);
    menuBtn->setPosition(Vec2::ZERO);
    this->addChild(menuBtn);
    
    //Profile Column
    this->profileBackground = Sprite::create("MainMenu/ProfileColom.png");
    this->profileBackground->setPosition(Vec2(logoImage->getPositionX(), logoImage->getPositionY() - this->profileBackground->getContentSize().height * 1.2));
    this->addChild(this->profileBackground);
    
    this->profileCircleSpr = Sprite::create("MainMenu/ProfilePicColom.png");
    this->profileCircleSpr->setPosition(Vec2(this->profileCircleSpr->getContentSize().width * 0.4,this->profileBackground->getContentSize().height * 0.5));
    this->profileBackground->addChild(this->profileCircleSpr);
    
    if(WWPlayerInfoRef->getCurrentProfilePictureTexture())
        this->profileCircleSpr->setTexture(WWPlayerInfoRef->getCurrentProfilePictureTexture());
    else
        this->profileCircleSpr->setTexture("MainMenu/round.png");


    //User Name Label
    this->userNameLabel = Label::createWithTTF(WWPlayerInfoRef->getCurrentUserName(), "fonts/JosefinSlab-Bold.ttf", 34);
    this->userNameLabel->setPosition(Vec2(this->profileCircleSpr->getPositionX() + this->profileCircleSpr->getContentSize().width * 0.65,this->profileBackground->getContentSize().height * 0.65));
    this->profileBackground->addChild(this->userNameLabel);
    this->userNameLabel->setAnchorPoint(Vec2(0,0.5));
    
    this->userDescriptionLabel = Label::createWithTTF("Guild of the Mad badges", "fonts/JosefinSlab-SemiBold.ttf", 28);
    this->userDescriptionLabel->setPosition(Vec2(this->profileCircleSpr->getPositionX() + this->profileCircleSpr->getContentSize().width * 0.65,this->profileBackground->getContentSize().height * 0.35));
    this->profileBackground->addChild(this->userDescriptionLabel);
    this->userDescriptionLabel->setAnchorPoint(Vec2(0,0.5));

    this->CommonPoupBg = Sprite::create("MainMenu/CommonPopup.png");
    this->CommonPoupBg->setPosition(Vec2(this->visibleSize.width / 2 + this->origin.x , this->profileBackground->getPositionY() - this->profileBackground->getContentSize().height - (this->CommonPoupBg->getContentSize().height * 0.9)/2));
    this->addChild(this->CommonPoupBg);
    this->CommonPoupBg->setScale(0.9);

    auto* headerLabel = Label::createWithTTF("Your Active Games", "fonts/JosefinSlab-Bold.ttf", 36);
    headerLabel->setPosition(Vec2(this->CommonPoupBg->getContentSize().width * 0.5,this->CommonPoupBg->getContentSize().height * 0.9));
    this->CommonPoupBg->addChild(headerLabel);
    
    this->getAllActiveGamesDetail();
    this->addActiveGamesList();
}

void WWMainMenu::addActiveGamesList()
{
    int totalNoFriends = 0;
    int offsetval = 5;
    int totalContentSize = (this->profileBackground->getContentSize().height + offsetval) * totalNoFriends;
    
    //Scroll View
    this->activeGameListScrollView = ScrollView::create(Size(this->CommonPoupBg->getContentSize().width, this->CommonPoupBg->getContentSize().height * 0.8));
    this->CommonPoupBg->addChild(this->activeGameListScrollView);
    this->activeGameListScrollView->setDirection(ScrollView::Direction::VERTICAL);
    this->activeGameListScrollView->setPosition(0, this->CommonPoupBg->getContentSize().height * 0.025);
    this->activeGameListScrollView->setBounceable(true);
    this->activeGameListScrollView->setAnchorPoint(Vec2(0.5, 0.5));
    this->activeGameListScrollView->setContentOffset(Vec2(0, this->CommonPoupBg->getContentSize().height * 0.1));
    
    this->activeGameListScrollView->setContentSize(Size(this->profileBackground->getContentSize().width, totalContentSize));
    this->activeGameListScrollView->setContentOffset(Vec2(0,this->activeGameListScrollView->minContainerOffset().y));
    
    
    Vec2 startPos = Vec2(this->CommonPoupBg->getContentSize().width * 0.05, totalContentSize - this->profileBackground->getContentSize().height);
    
    for (int i=0; i<totalNoFriends; i++)
    {
        //Create Game List
        MainMenuActiveList* activeList1 = MainMenuActiveList::create();
        activeList1->setContentSize(Size(this->profileBackground->getContentSize().width, this->profileBackground->getContentSize().height));
        activeList1->setPosition(Vec2(startPos.x,startPos.y));
        this->activeGameListScrollView->addChild(activeList1);
        activeList1->addUI("Gurudtaha T S", "", "Guild of the Mad badges",12);
        startPos.y = startPos.y - this->profileBackground->getContentSize().height - offsetval;
    }
   
}

#pragma mark - Button
void WWMainMenu::onClickOnSettingBtn(Ref* pSender)
{

    if (this->settingPannelLayer == nullptr) {
        
        this->settingPannelLayer = WWSettingsPannel::getSettingsBtn();
        this->settingPannelLayer->setPosition(Vec2::ZERO);
        this->addChild(this->settingPannelLayer,100);
        this->settingPannelLayer->mainMenuRef = this;
    }
}

void WWMainMenu::onClickOnInAppBtn(Ref* pSender)
{
    
}

void WWMainMenu::onClickOnQuickmatchBtn(Ref* pSender)
{
    this->getRamdomUserAPI();
    
}

void WWMainMenu::onClickOnHowToPlaybtnBtn(Ref* pSender)
{
    
}

void WWMainMenu::onClickOnGuildbtnBtn(Ref* pSender)
{
    MessageBox("", "COMING SOON!!");
}

#pragma mark - Get Random userAPI
void WWMainMenu::getRamdomUserAPI()
{
    ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
    
http://52.24.37.30:3000/api/signin?user_id=&authId=100001527270712&name=kfkfk&email=manjunathareddyn@gmail.com&password=hgjg&thumbnail=jkk&deviceId=j89jj&deviceType=IOS
    
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"getrandomuser?";
    
    
    url=url+"apiKey"+"="+WWDatamanager::sharedManager()->getAPIKey();
    
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::GET);
    
    
    request->setResponseCallback(CC_CALLBACK_2(WWMainMenu::onGetRamdomUserAPIRequestCompleted, this));
    request->setTag("getRandomuser");
    HttpClient::getInstance()->sendImmediate(request);
    request->release();

}


void WWMainMenu::onGetRamdomUserAPIRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    ActivtyIndicator::PopIfActiveFromScene(this);
    

    
    if (!response)
    {
        return;
    }
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    
    std::string id = document["user"]["id"].GetString();
    std::string name = document["user"]["name"].GetString();

    std::string email = document["user"]["email"].GetString();
    
    std::string thumbnail =  document["user"]["thumbnail"].GetString();

//    if(document["user"]["thumbnail"] != NULL)
//    {
//       thumbnail = document["user"]["thumbnail"].GetString();
//
//    }
    

    std::string loginType = document["user"]["loginType"].GetString();

    
    WWPlayerInfo::getInstance()->initializeOpponentinfo(name, id,thumbnail, "10");

    
    this->requestForPlayAPI();
    
    
    
    

    
}

#pragma mark - Get user detail API
void WWMainMenu::getUserDetailsAPI()
{
    ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
    
    
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"getuserdetails?";
    
    url=url+"id"+"="+WWDatamanager::sharedManager()->getUserId()+"&";

    url=url+"apiKey"+"="+WWDatamanager::sharedManager()->getAPIKey();
    
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::GET);
    
    
    request->setResponseCallback(CC_CALLBACK_2(WWMainMenu::onGetUserDetailsAPIRequestCompleted, this));
    request->setTag("getuserdetails");
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
 
}
void WWMainMenu::onGetUserDetailsAPIRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    
    
    if (!response)
    {
        return;
    }
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    
    std::string id = document["user"]["id"].GetString();
    std::string name = document["user"]["name"].GetString();
    
    std::string email = document["user"]["email"].GetString();
    
    std::string thumbnail = document["user"]["thumbnail"].GetString();
    
    std::string loginType = document["user"]["loginType"].GetString();
    
    
    
    WWPlayerInfo::getInstance()->initializeUserInfo(name,id, thumbnail, "10");
    this->userNameLabel->setString(WWPlayerInfoRef->getCurrentUserName());
    
    ActivtyIndicator::PopIfActiveFromScene(this);
    this->getGamesAPI();

    

}
#pragma mark - Request For Play API
void WWMainMenu::requestForPlayAPI()
{
    ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
    
  //  2017-06-18 12:11:12.562 WarOfWords-mobile[1255:23397] Starting to load http://52.24.37.30:3000/api/play?apiKey=99946db7d676c03c7dd5cd2e49fb81152a3e3a18fcff1d7af2a1120bbe188ae6&userId	=59462084e90023131ab8988c&opponentUserId=5942b9d9512f3c5985f67660

    
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"play?";
    url=url+"apiKey"+"="+WWDatamanager::sharedManager()->getAPIKey();
    url=url+"&userId"+"="+WWPlayerInfo::getInstance()->getCurrentUserID();
    url=url+"&opponentUserId"+"="+WWPlayerInfo::getInstance()->getOpponentUserID();
    
//   std:string postData = "";
//    postData = postData+"apiKey"+"="+WWDatamanager::sharedManager()->getAPIKey();
//    
//    postData=postData+"&userId"+"="+WWPlayerInfo::getInstance()->getCurrentUserID();
//    
//    postData=postData+"&opponentUserId"+"="+WWPlayerInfo::getInstance()->getOpponentUserID();
//    
//    log("postData is %s",postData.c_str());
//    
//    // write the post data
////    const char* postData = "apiKey=/"+WWDatamanager::sharedManager()->getAPIKey()+"/"+"&"+"userId"=Extensions Test/NetworkTest&opponentUserId=gfhh";
//    request->setRequestData(postData.c_str(), strlen(postData.c_str()));
    
    
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::POST);
    
    
    request->setResponseCallback(CC_CALLBACK_2(WWMainMenu::onRequestForPlayAPIRequestCompleted, this));
    request->setTag("play");
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
    

}
void WWMainMenu::onRequestForPlayAPIRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    
}


#pragma mark - get All Active Games
void WWMainMenu::getAllActiveGamesDetail()
{
   // HttpClient::getInstance()->setTimeoutForRead(120);
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"getupdates?";
    url=url+"apiKey"+"="+WWDatamanager::sharedManager()->getAPIKey();
    url=url+"&lastUpdatedDate"+"="+WWDatamanager::sharedManager()->lastUpdatedStr;

    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::GET);
    
    request->setResponseCallback(CC_CALLBACK_2(WWMainMenu::onGetAllActiveGamesDetail, this));
    request->setTag("getAllActiveGames");
    HttpClient::getInstance()->send(request);
    request->release();
}

void WWMainMenu::onGetAllActiveGamesDetail(HttpClient *sender, HttpResponse *response)
{
    if(!WWDatamanager::sharedManager()->_isUserInMainScene)
    {
        return;
    }

    if (!response)
    {
         this->getAllActiveGamesDetail();
        return;
    }
    
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);

    int statusCode = (int)response->getResponseCode();
    if(statusCode == -1)
    {
        this->getAllActiveGamesDetail();
        return;

    }
    
    
    //Check error code
    int errorCodeNo = document["errorCode"].GetInt();
    
    if(errorCodeNo == 0)
    {
        int arraySize = document["games"].Size();
        log("Array Size...... %d",arraySize);
        if (arraySize > 0)
        {
            log("Opponent Player Requested...");
            std::string _tChallengeId = document["games"][0]["challengeId"].GetString();
            std::string _tTurnUserId = document["games"][0]["turnUserId"].GetString();
            std::string userId = document["games"][0]["userId"].GetString();
            std::string _tStatus = document["games"][0]["status"].GetString();
            
            long int updatedStr = document["lastUpdatedDate"].GetInt();
            WWDatamanager::sharedManager()->lastUpdatedStr = NumToString(updatedStr);
    
            std::string _tOpponentUserId = document["games"][0]["opponentUserId"].GetString();
            
            WWPlayerInfoRef->updateChallengeID(_tChallengeId);
            WWPlayerInfoRef->updateTurnUserID(_tTurnUserId);
            WWPlayerInfoRef->updateOpponentUserID(_tOpponentUserId);
            
            
            if(_tStatus == "4")
            {
                //if(userId == WWPlayerInfoRef->getCurrentUserID())
                //{
                    std::string _tOpponentUserName  = document["games"][0]["opponentName"].GetString();
                    std::string _tOppoentProfileImg  = document["games"][0]["opponentThumbnail"].GetString();
                    
                    WWPlayerInfoRef->updateOpponentUserName(_tOpponentUserName);
                    WWPlayerInfoRef->updateOpponentProfilePicture(_tOppoentProfileImg);
                    
                    //Add Activity Indicator
                    this->addConfirmationPlayPopUp();
                //}
            }
            else if(_tStatus == "2")
            {
                //HttpClient::getInstance()->destroyInstance();
                WWDatamanager::sharedManager()->_isUserInMainScene = false;
                WWDatamanager::sharedManager()->_isExistingGameStarting = false;

                Director::getInstance()->replaceScene(WWBattleScreen::createScene());
            }

        }
        else
        {
          

        }
        
    }
      this->getAllActiveGamesDetail();
    
}

void WWMainMenu::addConfirmationPlayPopUp()
{
    if(this->playConfirmationPopup == nullptr)
    {
        this->playConfirmationPopup = WWmainMenuPlayConfirmation::getConfirmationPopup();
        this->playConfirmationPopup->setPosition(Vec2::ZERO);
        this->addChild(this->playConfirmationPopup,100);
        this->playConfirmationPopup->objref = this;
    }
}

void WWMainMenu::callbackFromConfirmationPopup(bool pIsConfirmed)
{
    this->playConfirmationPopup->removeFromParentAndCleanup(true);
    this->playConfirmationPopup = nullptr;
    
    this->updatePlayerAcceptStatus(pIsConfirmed);
    
//    if(pIsConfirmed)
//    {
//       // HttpClient::getInstance()->destroyInstance();
//        WWDatamanager::sharedManager()->_isUserInMainScene = false;
//
//        Director::getInstance()->replaceScene(WWBattleScreen::createScene());
//
//    }

}

#pragma mark - Update Player
void WWMainMenu::updatePlayerAcceptStatus(bool pIsAccepted)
{
    ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
    
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"updateplay?";
    url=url+"apiKey"+"="+WWDatamanager::sharedManager()->getAPIKey();
    url=url+"&challengeId"+"="+WWPlayerInfoRef->getChallengeID();
    
    if(pIsAccepted)
        url=url+"&status"+"="+"2";
    else
        url=url+"&status"+"="+"0";

    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::POST);
    
    
    request->setResponseCallback(CC_CALLBACK_2(WWMainMenu::onGetUpdateAPIRequestCompleted, this));
    request->setTag("updateplay");
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
}

void WWMainMenu::onGetUpdateAPIRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if(!WWDatamanager::sharedManager()->_isUserInMainScene)
    {
        return;
    }
    

    if (!response)
    {
        return;
    }
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    
    log("..........Get Games Detail.......");
    ActivtyIndicator::PopIfActiveFromScene(this);
    
    int errorCodeNo = document["errorCode"].GetInt();
    if(errorCodeNo == 0)
    {
        this->getAllActiveGamesDetail();
    }
}


#pragma mark - Get Games First Time
void WWMainMenu::getGamesAPI()
{
    HttpClient::getInstance()->setTimeoutForRead(120);
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"getgames?";
    url=url+"apiKey"+"="+WWDatamanager::sharedManager()->getAPIKey();
    //url=url+"&challengeId"+"="+WWPlayerInfoRef->getChallengeID();
    
    
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::GET);
    
    request->setResponseCallback(CC_CALLBACK_2(WWMainMenu::onGetGamesAPIRequestCompleted, this));
    request->setTag("getgames");
    HttpClient::getInstance()->sendImmediate(request);
    request->release();

}
void WWMainMenu::onGetGamesAPIRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if(!WWDatamanager::sharedManager()->_isUserInMainScene)
    {
        return;
    }
    
    if (!response)
    {
        this->getGamesAPI();
        return;
    }
    
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    
    int statusCode = (int)response->getResponseCode();
    if(statusCode == -1)
    {
        this->getGamesAPI();
        return;
        
    }
    
    //Check error code
    int errorCodeNo = document["errorCode"].GetInt();
    
    if(errorCodeNo == 0)
    {
        int arraySize = document["games"].Size();
        log("Array Size...... %d",arraySize);
        if (arraySize > 0)
        {
            //Update Scroll View
            int totalNoFriends = arraySize;
            int offsetval = 5;
            int totalContentSize = (this->profileBackground->getContentSize().height + offsetval) * totalNoFriends;
            
             this->activeGameListScrollView->setContentSize(Size(this->profileBackground->getContentSize().width, totalContentSize));
            this->activeGameListScrollView->setContentOffset(Vec2(0,this->activeGameListScrollView->minContainerOffset().y));

            
            Vec2 startPos = Vec2(this->CommonPoupBg->getContentSize().width * 0.05, totalContentSize - this->profileBackground->getContentSize().height);
            
            for (int i=0; i<totalNoFriends; i++)
            {
                std::string _tOpponentUserName  = document["games"][i]["opponentName"].GetString();
                std::string _tOppoentProfileImg  = document["games"][i]["opponentThumbnail"].GetString();
                std::string _tOpponentHealth  = document["games"][i]["opponentHealth"].GetString();
                std::string opponentId  = document["games"][i]["opponentUserId"].GetString();
                std::string turnUserId  = document["games"][i]["turnUserId"].GetString();

                std::string wonBy  = document["games"][i]["wonBy"].GetString();

                std::string challengeId  = document["games"][i]["challengeId"].GetString();

                std::string status  = document["games"][i]["status"].GetString();

                //long int updatedStr = document["updatedDate"].GetInt();
              //  std::string lastUpdatedate = document["updatedDate"].GetString();
                
               // long int updatedStr = document["games"][i]["updatedDate"].GetInt();
                std::string lastUpdatedate =document["games"][i]["updatedDate"].GetString();

                
                //Create Game List
                MainMenuActiveList* activeList1 = MainMenuActiveList::create();
                activeList1->setContentSize(Size(this->profileBackground->getContentSize().width, this->profileBackground->getContentSize().height));
                activeList1->setPosition(Vec2(startPos.x,startPos.y));
                this->activeGameListScrollView->addChild(activeList1);
                activeList1->addUI(_tOpponentUserName, _tOppoentProfileImg, "Guild of the Mad badges",3)
                ;
                activeList1->challengID = challengeId;
                 activeList1->turnUserId = turnUserId;
                activeList1->wonBy = wonBy;
                activeList1->opponentHealth = std::atoi(_tOpponentHealth.c_str());
                activeList1->opponentUserId = opponentId;
                activeList1->status = status;
                activeList1->lastUpdatedStr = lastUpdatedate;


                
                startPos.y = startPos.y - this->profileBackground->getContentSize().height - offsetval;
            }
        }
        else
        {
            
        }
    }
}


void WWMainMenu::sendPushNotificationToUserAPI()
{
    ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
    
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"sendpush?";
    

    url=url+"apiKey"+"="+WWDatamanager::sharedManager()->getAPIKey();
    
    
std:string postData = "";
    postData = postData+"apiKey"+"="+WWDatamanager::sharedManager()->getAPIKey();
    
    postData=postData+"&userId"+"="+WWPlayerInfo::getInstance()->getOpponentUserID();
    
    postData=postData+"&message"+"="+"PlayWithme";
    
    log("postData is %s",postData.c_str());
    
    // write the post data
    //    const char* postData = "apiKey=/"+WWDatamanager::sharedManager()->getAPIKey()+"/"+"&"+"userId"=Extensions Test/NetworkTest&opponentUserId=gfhh";
    request->setRequestData(postData.c_str(), strlen(postData.c_str()));
    
    
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::GET);
    
    
    request->setResponseCallback(CC_CALLBACK_2(WWMainMenu::onSendPushNotificationToUserAPIRequestCompleted, this));
    request->setTag("getuserdetails");
    HttpClient::getInstance()->send(request);
    request->release();
    
}
void WWMainMenu::onSendPushNotificationToUserAPIRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    
}
#pragma mark - Active game list button action
void  WWMainMenu::activeListBattleIconAction(std::string challengeId,std::string oppName,std::string oppId,std::string oppThumb, std::string status,std::string turnId,std::string wonBy)
{
    WWPlayerInfoRef->updateChallengeID(challengeId);
    WWPlayerInfoRef->updateTurnUserID(turnId);
    WWPlayerInfoRef->updateOpponentUserID(oppId);
    WWPlayerInfoRef->updateOpponentUserName(oppName);
    WWDatamanager::sharedManager()->_isExistingGameStarting = true;
    WWDatamanager::sharedManager()->_isUserInMainScene = false;
    Director::getInstance()->replaceScene(WWBattleScreen::createScene());


}
