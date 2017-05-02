//
//  WWLoginScreen.cpp
//  WarOfWords
//
//  Created by Gurudath on 3/17/17.
//
//

#include "WWLoginScreen.h"
#include "WWSocialManager.h"
#include "WWSocialFriendDetail.h"
#include "WWGameConstant.h"
#include "WWGameScene.h"
#include "WWLandingScreen.h"
#include "WWForgotScreen.h"

Scene* WWLoginScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WWLoginScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
#pragma mark - Init
// on "init" you need to initialize your instance
bool WWLoginScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    WWSocialManagerRef->initWithEnum(enumSocialSharingType::kFacebook);
    
    this->visibleSize = Director::getInstance()->getVisibleSize();
    this->origin = Director::getInstance()->getVisibleOrigin();
    
    // Background
    auto backgroundSpr = Sprite::create("LandingScreen/LandngScreenBg.png");
    backgroundSpr->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x, this->visibleSize.height/2 + this->origin.y));
    this->addChild(backgroundSpr);
    
    //Add Ui
    this->addUI();
    
    return true;
}

void WWLoginScreen::addUI()
{
    //logo Image
    auto logoImage = Sprite::create("LoadingScreen/Logo.png");
    logoImage->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x , this->visibleSize.height/2 + this->origin.y + logoImage->getContentSize().height/1.6));
    this->addChild(logoImage);
    
    //Back Button
    this->backBtn = MenuItemImage::create("LoginScreen/BackBtn.png", "LoginScreen/BackBtn.png", CC_CALLBACK_1(WWLoginScreen::onClickOnBackBtn, this));
    this->backBtn->setPosition(Vec2(this->origin.x + this->backBtn->getContentSize().width * 0.8, (this->visibleSize.height) + this->origin.y - (this->backBtn->getContentSize().height * 0.8)));
    this->backBtn->setScale(0.9);
    
    //Login Button
    this->logInBtn = MenuItemImage::create("LoginScreen/LoginBtn.png", "LoginScreen/LoginBtn.png", CC_CALLBACK_1(WWLoginScreen::onClickOnLogin, this));
    this->logInBtn->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x, this->visibleSize.height /8 + this->origin.y + this->logInBtn->getContentSize().height));
    this->logInBtn->setScale(0.9);
    
    //Forgot password
    this->forgotpasswordBtn = MenuItemImage::create("LoginScreen/ForgotPasswordBtn.png", "LoginScreen/ForgotPasswordBtn.png", CC_CALLBACK_1(WWLoginScreen::onClickOnForgot, this));
    this->forgotpasswordBtn->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x, this->visibleSize.height /8 + this->origin.y - 20));
    

    //Music Btn
    MenuItemImage* musicOn = MenuItemImage::create("LandingScreen/MusicBtn.png", "LandingScreen/MusicBtn.png");
    MenuItemImage* musicOff = MenuItemImage::create("LandingScreen/MusicBtnMute.png", "LandingScreen/MusicBtnMute.png");
    this->musinBtn = MenuItemToggle::createWithCallback(CC_CALLBACK_1(WWLoginScreen::onClickOnMusicbtn, this), musicOn,musicOff,NULL);
    this->musinBtn->setPosition(Vec2(this->visibleSize.width + this->origin.x - musicOn->getContentSize().width, this->visibleSize.height + this->origin.y - musicOn->getContentSize().height));
    
    //Sound Btn
    MenuItemImage* soundOn = MenuItemImage::create("LandingScreen/SoundBtn.png", "LandingScreen/SoundBtn.png");
    MenuItemImage* soundOff = MenuItemImage::create("LandingScreen/SoundMuteBtn.png", "LandingScreen/SoundMuteBtn.png");
    this->soundbtn = MenuItemToggle::createWithCallback(CC_CALLBACK_1(WWLoginScreen::onClickOnSoundbtn, this), soundOn,soundOff,NULL);
    this->soundbtn->setPosition(Vec2(this->visibleSize.width + this->origin.x - musicOn->getContentSize().width - soundOn->getContentSize().width - 20, this->visibleSize.height + this->origin.y - musicOn->getContentSize().height));
    
    //Menu
    Menu* menuBtn = Menu::create(this->backBtn,this->logInBtn,this->forgotpasswordBtn,this->musinBtn,this->soundbtn, NULL);
    menuBtn->setPosition(Vec2::ZERO);
    this->addChild(menuBtn);
    
    //Editbox
    std::string pNormalSprite = "LoginScreen/NameColm.png";
    auto* sprRef = Sprite::create("LoginScreen/NameColm.png");
    this->userName = EditBox::create(Size(sprRef->getContentSize().width, sprRef->getContentSize().height), ui::Scale9Sprite::create(pNormalSprite));
    this->userName->setPosition(Vec2(this->logInBtn->getPositionX(), this->logInBtn->getPositionY() + (sprRef->getContentSize().height * 2) + 50));
    this->userName->setFontColor(Color3B::BLACK);
    this->userName->setPlaceHolder("   UserName");
    this->userName->setPlaceholderFontSize(sprRef->getContentSize().height/2);
    this->userName->setPlaceholderFontColor(Color3B::WHITE);
    this->userName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    this->userName->setDelegate(this);
    this->userName->setVisible(true);
    this->userName->setFontSize(sprRef->getContentSize().height/2);
    this->addChild(this->userName);
    this->userName->setScale(0.9);
    
    //Password
    this->passWord = ui::EditBox::create(Size(sprRef->getContentSize().width, sprRef->getContentSize().height), ui::Scale9Sprite::create(pNormalSprite));
    this->passWord->setPosition(Vec2(this->logInBtn->getPositionX(), this->logInBtn->getPositionY() + sprRef->getContentSize().height + 35));
    this->passWord->setFontColor(Color3B::BLACK);
    this->passWord->setPlaceHolder("   Password");
    this->passWord->setPlaceholderFontSize(sprRef->getContentSize().height/2);
    this->passWord->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    this->passWord->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
    this->passWord->setDelegate(this);
    this->passWord->setVisible(true);
    this->passWord->setFontSize(sprRef->getContentSize().height/2);
    this->addChild(this->passWord);
    this->passWord->setScale(0.9);

}

#pragma mark - Button
void WWLoginScreen::onClickOnBackBtn(Ref* pSender)
{
    //replace Scene
    Director::getInstance()->replaceScene(WWLandingScreen::createScene());
}

void WWLoginScreen::onClickOnMusicbtn(Ref* pSender)
{
    
}

void WWLoginScreen::onClickOnSoundbtn(Ref* pSender)
{
    
}

void WWLoginScreen::onClickOnForgot(Ref* pSender)
{
    //replace Scene
    FORGOTPASSWORDTYPE currentType = kForgotPassword;
    Director::getInstance()->replaceScene(WWForgotPasswordScreen::createScene(currentType));
}

void WWLoginScreen::onClickOnLogin(Ref* pSender)
{

    //if(WWSocialManagerRef->getFacebookLoggedIn())
    //{
         //WWSocialManagerRef->logOut(enumSocialSharingType::kFacebook);
    //}
    //else
    //{
        //WWSocialManagerRef->setCallback(CC_CALLBACK_1(WWLoginScreen::afterLoginCompleted, this));
        //WWSocialManagerRef->logIn(enumSocialSharingType::kFacebook);
        log("......Login .. ....");
    //}
}

void WWLoginScreen::afterLoginCompleted(bool pIsDone)
{
    //Fetch Current User Detail
    log("Current USer Info %s",WWSocialManagerRef->currentLoginUserDetail->getName().c_str());
    
    //replace to Game Scene
    Director::getInstance()->replaceScene(WWGameScene::createScene());

}

#pragma mark - Login API
void WWLoginScreen::loginToServer()
{
    
//http: //52.24.37.30/wow/wowapi/api/signin?user_id=&facebook_id=1424&email=email@email.com&password=123456&name=Ganesh&gender=male&country=US&facebook_thumbnail=profile.ak.fbcdn.net/hprofile-ak-ash3&ios_push_id=3b989a98d7efe
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"signin?";
    
    url =url+"user_id"+"="+""+"&";
    
    url=url+"facebook_id"+"="+"100001527270712"+"&";
    
    url=url+"email"+"="+"email@email.com"+"&";

    url=url+"password"+"="+"hgjg"+"&";
    
    
    url=url+"name"+"="+"kfkfk"+"&";
    
    url=url+"gender"+"="+"male"+"&";
    
    url=url+"country"+"="+"ud"+"&";
    
    url=url+"facebook_thumbnail"+"="+"jkk"+"&";
    
    url=url+"ios_push_id"+"="+"j89jj";

    
    request->setUrl("");
    CCLOG("%s",request->getUrl());
    request->setRequestType(HttpRequest::Type::GET);
    
    
    request->setResponseCallback(CC_CALLBACK_2(WWLoginScreen::onLoginRequestCompleted, this));
    request->setTag("SignIN");
    HttpClient::getInstance()->send(request);
    request->release();
    
}
void WWLoginScreen::onLoginRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    if(!document.IsNull())
    {
        
    }
}

#pragma mark - Editbox
void WWLoginScreen::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
    log("editBox %p DidBegin !", editBox);
}

void WWLoginScreen::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
    log("editBox %p DidEnd !", editBox);
}

void WWLoginScreen::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
    log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void WWLoginScreen::editBoxReturn(ui::EditBox* editBox)
{
    log("editBox %p was returned !",editBox);
}
