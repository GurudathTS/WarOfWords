//
//  WWLandingScreen.cpp
//  WarOfWords
//
//  Created by Gurudath on 5/1/17.
//
//

#include "WWLandingScreen.h"
#include "WWLoginScreen.h"
#include "WWSignupScreen.h"
#include "WWSocialManager.h"
#include "WWSocialFriendDetail.h"
#include "WWGameConstant.h"
#include "WWDatamanager.h"
#include "WWCommonUtilty.h"
#include "WWMainMenuScreen.h"

Scene* WWLandingScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WWLandingScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
#pragma mark - Init
// on "init" you need to initialize your instance
bool WWLandingScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->visibleSize = Director::getInstance()->getVisibleSize();
    this->origin = Director::getInstance()->getVisibleOrigin();
    
    //Facebook
    WWSocialManagerRef->initWithEnum(enumSocialSharingType::kFacebook);
    
    // Background
    auto backgroundSpr = Sprite::create("LandingScreen/LandngScreenBg.png");
    backgroundSpr->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(backgroundSpr);
    
    //Add Ui
    this->addUI();
    
    return true;
}

void WWLandingScreen::addUI()
{
    //logo Image
    auto logoImage = Sprite::create("LoadingScreen/Logo.png");
    logoImage->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x , this->visibleSize.height/2 + this->origin.y + logoImage->getContentSize().height/1.6));
    this->addChild(logoImage);
    
    //Sign Login Facebook Button
    this->loginFacebookBtn = MenuItemImage::create("LandingScreen/FbLoginBtn.png", "LandingScreen/FbLoginBtn.png", CC_CALLBACK_1(WWLandingScreen::onClickOnLoginFacebook, this));
    this->loginFacebookBtn->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x, this->visibleSize.height/8 + this->origin.y + this->loginFacebookBtn->getContentSize().height + 20));
    this->loginFacebookBtn->setScale(0.9);
    
    //Login Button
    this->loginBtn = MenuItemImage::create("LandingScreen/LoginBtn.png", "LandingScreen/LoginBtn.png", CC_CALLBACK_1(WWLandingScreen::onClickOnLoginbtn, this));
    this->loginBtn->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x - this->loginBtn->getContentSize().width/2, this->visibleSize.height/8 + this->origin.y - 10));
    this->loginBtn->setScale(0.85);
    
    
    //Sign Up
    this->signUpBtn = MenuItemImage::create("LandingScreen/SignUpBtn.png", "LandingScreen/SignUpBtn.png", CC_CALLBACK_1(WWLandingScreen::onClickOnSinUpbtn, this));
    this->signUpBtn->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x + this->loginBtn->getContentSize().width/2, this->visibleSize.height/8 + this->origin.y - 10));
    this->signUpBtn->setScale(0.85);
    
    
    //Music Btn
    MenuItemImage* musicOn = MenuItemImage::create("LandingScreen/MusicBtn.png", "LandingScreen/MusicBtn.png");
    MenuItemImage* musicOff = MenuItemImage::create("LandingScreen/MusicBtnMute.png", "LandingScreen/MusicBtnMute.png");
    this->musinBtn = MenuItemToggle::createWithCallback(CC_CALLBACK_1(WWLandingScreen::onClickOnMusicbtn, this), musicOn,musicOff,NULL);
    this->musinBtn->setPosition(Vec2(this->visibleSize.width + this->origin.x - musicOn->getContentSize().width, this->visibleSize.height + this->origin.y - musicOn->getContentSize().height));
    
    //Sound Btn
    MenuItemImage* soundOn = MenuItemImage::create("LandingScreen/SoundBtn.png", "LandingScreen/SoundBtn.png");
    MenuItemImage* soundOff = MenuItemImage::create("LandingScreen/SoundMuteBtn.png", "LandingScreen/SoundMuteBtn.png");
    this->soundbtn = MenuItemToggle::createWithCallback(CC_CALLBACK_1(WWLandingScreen::onClickOnSoundbtn, this), soundOn,soundOff,NULL);
    this->soundbtn->setPosition(Vec2(this->visibleSize.width + this->origin.x - musicOn->getContentSize().width - soundOn->getContentSize().width - 20, this->visibleSize.height + this->origin.y - musicOn->getContentSize().height));
    
    //Menu
    Menu* menuBtn = Menu::create(this->loginFacebookBtn,this->loginBtn,this->signUpBtn,this->musinBtn,this->soundbtn, NULL);
    menuBtn->setPosition(Vec2::ZERO);
    this->addChild(menuBtn);
    
}

#pragma mark - Facebook login
void WWLandingScreen::onClickOnLoginFacebook(Ref* pSender)
{
    ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
    if(WWSocialManagerRef->getFacebookLoggedIn())
    {
        WWSocialManagerRef->setCallback(CC_CALLBACK_1(WWLandingScreen::afterLoginCompleted, this));
        WWSocialManagerRef->getCurrentUserInfo(enumSocialSharingType::kFacebook);

    }
    else
    {
        WWSocialManagerRef->setCallback(CC_CALLBACK_1(WWLandingScreen::afterLoginCompleted, this));
        WWSocialManagerRef->logIn(enumSocialSharingType::kFacebook);
        log("......Login .. ....");
    }
}

void WWLandingScreen::afterLoginCompleted(bool pIsDone)
{
    //Fetch Current User Detail
    log("Current USer Info %s",WWSocialManagerRef->currentLoginUserDetail->getName().c_str());
    

    this->loginToServer();
    //replace to Game Scene
    //Director::getInstance()->replaceScene(WWGameScene::createScene());
    
}
#pragma mark - Login API
void WWLandingScreen::loginToServer()
{
    
    //http: //52.24.37.30/wow/wowapi/api/signin?user_id=&facebook_id=1424&email=email@email.com&password=123456&name=Ganesh&gender=male&country=US&facebook_thumbnail=profile.ak.fbcdn.net/hprofile-ak-ash3&ios_push_id=3b989a98d7efe
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"signin?";
    
    std::string name = std::urlencode(WWSocialManagerRef->currentLoginUserDetail->getName());
    url=url+"authId"+"="+WWSocialManagerRef->currentLoginUserDetail->getID()+"&";
    url=url+"name"+"="+name+"&";
    
    
    url=url+"email"+"="+"manjunathareddyn@gmail.com"+"&";
    
    url=url+"password"+"="+"fgh"+"&";
    
    
    url=url+"thumbnail"+"="+WWSocialManagerRef->currentLoginUserDetail->getImageURL()+"&";
    
    url=url+"deviceId"+"="+"j89jj"+"&";
    
    url=url+"deviceType"+"="+"IOS";
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::GET);
    
    
    request->setResponseCallback(CC_CALLBACK_2(WWLandingScreen::onLoginRequestCompleted, this));
    request->setTag("SignIN");
    HttpClient::getInstance()->send(request);
    request->release();
    
}
void WWLandingScreen::onLoginRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    if(!document.IsNull())
    {
        if(document["errorCode"].GetInt() == 0 && (strcmp(document["msg"].GetString(), "Success")==0))
        {
            std::string userId = document["user"]["id"].GetString();
            std::string apiKey = document["user"]["apiKey"].GetString();
            
            WWDatamanager::sharedManager()->setAPIKey(apiKey);
            WWDatamanager::sharedManager()->setUserId(userId);
            
            ActivtyIndicator::PopIfActiveFromScene(this);
            Director::getInstance()->replaceScene(WWMainMenu::createScene());
        }
        else{
            log("server error");
        }
        
        
        
    }
}

#pragma mark - Guest login
void WWLandingScreen::onClickOnLoginbtn(Ref* pSender)
{
    //replace Scene
    Director::getInstance()->replaceScene(WWLoginScreen::createScene());
}

#pragma mark - SignUp
void WWLandingScreen::onClickOnSinUpbtn(Ref* pSender)
{
    //replace Scene
    Director::getInstance()->replaceScene(WWSignUpScreen::createScene());
}

#pragma mark - Sound
void WWLandingScreen::onClickOnMusicbtn(Ref* pSender)
{
    
}

void WWLandingScreen::onClickOnSoundbtn(Ref* pSender)
{
    
}
