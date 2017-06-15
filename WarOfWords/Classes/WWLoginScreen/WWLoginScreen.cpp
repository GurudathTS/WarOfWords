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

#include "WWDatamanager.h"
#include "WWCommonUtilty.h"
#include "WWMainMenuScreen.h"


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
    
    //Error Info label
    _errorInfoLabel = Label::createWithTTF("", "fonts/JosefinSlab-Bold.ttf", 42);
    _errorInfoLabel->setPosition(this->visibleSize.width/2+this->origin.x,this->visibleSize.height*.05+this->origin.y);
    this->addChild(_errorInfoLabel,100);
    _errorInfoLabel->setColor(Color3B::RED);
    _errorInfoLabel->setOpacity(0);
    
    
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
    this->userName->setPlaceholderFontSize(40);
    this->userName->setPlaceholderFontName("fonts/JosefinSlab-SemiBold.ttf");
    this->userName->setPlaceholderFontColor(Color3B(124, 37, 61));
    this->userName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    this->userName->setDelegate(this);
    this->userName->setVisible(true);
    this->userName->setFontSize(40);
    this->addChild(this->userName);
    this->userName->setScale(0.9);
    
    //Password
    this->passWord = ui::EditBox::create(Size(sprRef->getContentSize().width, sprRef->getContentSize().height), ui::Scale9Sprite::create(pNormalSprite));
    this->passWord->setPosition(Vec2(this->logInBtn->getPositionX(), this->logInBtn->getPositionY() + sprRef->getContentSize().height + 35));
    this->passWord->setFontColor(Color3B::BLACK);
    this->passWord->setPlaceHolder("   Password");
    this->passWord->setPlaceholderFontSize(40);
    this->passWord->setPlaceholderFontName("fonts/JosefinSlab-SemiBold.ttf");
    this->passWord->setPlaceholderFontColor(Color3B(124, 37, 61));
    this->passWord->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    this->passWord->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
    this->passWord->setDelegate(this);
    this->passWord->setVisible(true);
    this->passWord->setFontSize(40);
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
    

if(this->checkEnteredDataIsValid())
{
    this->loginToServer();

}
    
   
}

#pragma mark - Data validation
bool WWLoginScreen::checkEnteredDataIsValid()
{

    bool isEmpty = false;
    std::string errorText = "";
    if(strcmp(this->userName->getText(), "")==0)
    {
        isEmpty = true;
        errorText = "email is empty";
    }
    else if(strcmp(this->passWord->getText(), "")==0)
    {
        isEmpty = true;
        errorText = "password is empty";
        
        
    }
    if(isEmpty)
    {
        _errorInfoLabel->setString(errorText);
        _errorInfoLabel->runAction(Sequence::create(FadeIn::create(.1),DelayTime::create(1.0),FadeOut::create(.1), NULL));
        return false;
    }
    bool isEmailValid = std::spc_email_isvalid(this->userName->getText());
    if(!isEmailValid)
    {
        _errorInfoLabel->setString("Email is not vaild");
        _errorInfoLabel->runAction(Sequence::create(FadeIn::create(.1),DelayTime::create(1.0),FadeOut::create(.1), NULL));
        return false;
    }
    
    return true;

    
}

#pragma mark - Login API
void WWLoginScreen::loginToServer()
{
    
    ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);

    http://52.24.37.30:3000/api/signin?user_id=&authId=100001527270712&name=kfkfk&email=manjunathareddyn@gmail.com&password=hgjg&thumbnail=jkk&deviceId=j89jj&deviceType=IOS
    
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"signin?";
    
    
    url=url+"authId"+"="+""+"&";
    url=url+"name"+"="+this->userName->getText()+"&";

    
    url=url+"email"+"="+this->userName->getText()+"&";

    url=url+"password"+"="+this->passWord->getText()+"&";
    
    
    
    
    url=url+"thumbnail"+"="+""+"&";
    
    url=url+"deviceId"+"="+WWDatamanager::sharedManager()->dmdeviceToken+"&";
    
    url=url+"deviceType"+"="+"IOS";


    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
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
        int errorCode = document["errorCode"].GetInt();
        std::string msg = document["msg"].GetString();
        if(errorCode == 0 && (strcmp(msg.c_str(), "Success")==0))
        {
            std::string userId = document["user"]["id"].GetString();
            std::string apiKey = document["user"]["apiKey"].GetString();
            
            WWDatamanager::sharedManager()->setAPIKey(apiKey);
            WWDatamanager::sharedManager()->setUserId(userId);
            
            
            ActivtyIndicator::PopIfActiveFromScene(this);
            Director::getInstance()->replaceScene(WWMainMenu::createScene());
            
            
        }
        else  if(errorCode == 1 && (strcmp(msg.c_str(), "Wrong Email or Password")==0))

        {
            ActivtyIndicator::PopIfActiveFromScene(this);
            _errorInfoLabel->setString("Wrong Email or Password");
            _errorInfoLabel->runAction(Sequence::create(FadeIn::create(.1),DelayTime::create(1.0),FadeOut::create(.1), NULL));

            log("server error");
        }
        
        
        
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
