//
//  WWSignupScreen.cpp
//  WarOfWords
//
//  Created by Gurudath on 5/1/17.
//
//

#include "WWSignupScreen.h"
#include "WWLandingScreen.h"
#include "WWGameConstant.h"
#include "WWDatamanager.h"
#include "WWCommonUtilty.h"
#include "WWMainMenuScreen.h"

Scene* WWSignUpScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WWSignUpScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
#pragma mark - Init
// on "init" you need to initialize your instance
bool WWSignUpScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
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


void WWSignUpScreen::addUI()
{
    //logo Image
    auto logoImage = Sprite::create("LoadingScreen/Logo.png");
    logoImage->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x , this->visibleSize.height/2 + this->origin.y + logoImage->getContentSize().height/1.5));
    this->addChild(logoImage);
    
    //Back Button
    this->backBtn = MenuItemImage::create("LoginScreen/BackBtn.png", "LoginScreen/BackBtn.png", CC_CALLBACK_1(WWSignUpScreen::onClickOnBackBtn, this));
    this->backBtn->setPosition(Vec2(this->origin.x + this->backBtn->getContentSize().width * 0.8, (this->visibleSize.height) + this->origin.y - (this->backBtn->getContentSize().height * 0.8)));
    this->backBtn->setScale(0.9);
    
    //Sign Up Button
    this->signUpBtn = MenuItemImage::create("LoginScreen/SignUpBtn.png", "LoginScreen/SignUpBtn.png", CC_CALLBACK_1(WWSignUpScreen::onClickOnSignUp, this));
    this->signUpBtn->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x, this->visibleSize.height /8 + this->origin.y));
    this->signUpBtn->setScale(0.9);
    

    //Music Btn
    MenuItemImage* musicOn = MenuItemImage::create("LandingScreen/MusicBtn.png", "LandingScreen/MusicBtn.png");
    MenuItemImage* musicOff = MenuItemImage::create("LandingScreen/MusicBtnMute.png", "LandingScreen/MusicBtnMute.png");
    this->musinBtn = MenuItemToggle::createWithCallback(CC_CALLBACK_1(WWSignUpScreen::onClickOnMusicbtn, this), musicOn,musicOff,NULL);
    this->musinBtn->setPosition(Vec2(this->visibleSize.width + this->origin.x - musicOn->getContentSize().width, this->visibleSize.height + this->origin.y - musicOn->getContentSize().height));
    
    //Sound Btn
    MenuItemImage* soundOn = MenuItemImage::create("LandingScreen/SoundBtn.png", "LandingScreen/SoundBtn.png");
    MenuItemImage* soundOff = MenuItemImage::create("LandingScreen/SoundMuteBtn.png", "LandingScreen/SoundMuteBtn.png");
    this->soundbtn = MenuItemToggle::createWithCallback(CC_CALLBACK_1(WWSignUpScreen::onClickOnSoundbtn, this), soundOn,soundOff,NULL);
    this->soundbtn->setPosition(Vec2(this->visibleSize.width + this->origin.x - musicOn->getContentSize().width - soundOn->getContentSize().width - 20, this->visibleSize.height + this->origin.y - musicOn->getContentSize().height));
    
    //Menu
    Menu* menuBtn = Menu::create(this->backBtn,this->signUpBtn,this->musinBtn,this->soundbtn, NULL);
    menuBtn->setPosition(Vec2::ZERO);
    this->addChild(menuBtn);
    
    //Editbox
    std::string pNormalSprite = "LoginScreen/NameColm.png";
    auto* sprRef = Sprite::create("LoginScreen/NameColm.png");

    Vec2 startPos = Vec2(this->signUpBtn->getPositionX(), this->signUpBtn->getPositionY() + sprRef->getContentSize().height + 35);
    
    //Password
    this->confirmpassword = ui::EditBox::create(Size(sprRef->getContentSize().width, sprRef->getContentSize().height), ui::Scale9Sprite::create(pNormalSprite));
    this->confirmpassword->setPosition(Vec2(startPos.x,startPos.y));
    this->confirmpassword->setFontColor(Color3B::BLACK);
    this->confirmpassword->setPlaceHolder("   Confirm Password");
    this->confirmpassword->setPlaceholderFontSize(40);
    this->confirmpassword->setPlaceholderFontName("fonts/JosefinSlab-SemiBold.ttf");
    this->confirmpassword->setPlaceholderFontColor(Color3B(124, 37, 61));
    this->confirmpassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    this->confirmpassword->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
    this->confirmpassword->setDelegate(this);
    this->confirmpassword->setVisible(true);
    this->confirmpassword->setFontSize(40);
    this->addChild(this->confirmpassword);
    this->confirmpassword->setScale(0.9);
    
    startPos = Vec2(startPos.x, startPos.y + sprRef->getContentSize().height + 10);
    this->passWord = ui::EditBox::create(Size(sprRef->getContentSize().width, sprRef->getContentSize().height), ui::Scale9Sprite::create(pNormalSprite));
    this->passWord->setPosition(Vec2(startPos.x,startPos.y));
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
    
    //Email
    startPos = Vec2(startPos.x, startPos.y + sprRef->getContentSize().height + 10);
    this->email = ui::EditBox::create(Size(sprRef->getContentSize().width, sprRef->getContentSize().height), ui::Scale9Sprite::create(pNormalSprite));
    this->email->setPosition(Vec2(startPos.x,startPos.y));
    this->email->setFontColor(Color3B::BLACK);
    this->email->setPlaceHolder("   Email");
    this->email->setPlaceholderFontSize(40);
    this->email->setPlaceholderFontName("fonts/JosefinSlab-SemiBold.ttf");
    this->email->setPlaceholderFontColor(Color3B(124, 37, 61));
    this->email->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
    this->email->setDelegate(this);
    this->email->setVisible(true);
    this->email->setFontSize(40);
    this->addChild(email);
    this->email->setScale(0.9);
    
    //UserName
    startPos = Vec2(startPos.x, startPos.y + sprRef->getContentSize().height + 10);

    this->userName = EditBox::create(Size(sprRef->getContentSize().width, sprRef->getContentSize().height), ui::Scale9Sprite::create(pNormalSprite));
    this->userName->setPosition(Vec2(startPos.x,startPos.y));
    this->userName->setFontColor(Color3B::BLACK);
    this->userName->setPlaceHolder("   User Name");
    this->userName->setPlaceholderFontSize(40);
    this->userName->setPlaceholderFontName("fonts/JosefinSlab-SemiBold.ttf");
    this->userName->setPlaceholderFontColor(Color3B(124, 37, 61));
    this->userName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    this->userName->setDelegate(this);
    this->userName->setVisible(true);
    this->userName->setFontSize(40);
    this->addChild(this->userName);
    this->userName->setScale(0.9);
    
}

#pragma mark - Button
void WWSignUpScreen::onClickOnBackBtn(Ref* pSender)
{
    Director::getInstance()->replaceScene(WWLandingScreen::createScene());
}

void WWSignUpScreen::onClickOnMusicbtn(Ref* pSender)
{
    
}

void WWSignUpScreen::onClickOnSoundbtn(Ref* pSender)
{
    
}

#pragma mark - SignUp button
void WWSignUpScreen::onClickOnSignUp(Ref* pSender)
{

    bool isValid = this->checkEnteredDataIsValid();
    if(isValid)
    {
        ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
        this->signUpAPI();

    }
    
}

#pragma mark - Editbox
void WWSignUpScreen::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
    log("editBox %p DidBegin !", editBox);
}

void WWSignUpScreen::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
    log("editBox %p DidEnd !", editBox);
}

void WWSignUpScreen::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
    log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void WWSignUpScreen::editBoxReturn(ui::EditBox* editBox)
{
    log("editBox %p was returned !",editBox);
}

#pragma mark - Data validation
bool WWSignUpScreen::checkEnteredDataIsValid()
{
    bool isEmpty = false;
    std::string errorText = "";
    if(strcmp(this->userName->getText(), "")==0)
    {
        isEmpty = true;
        errorText = "username is empty";
    }
    else if(strcmp(this->email->getText(), "")==0)
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
    
    
    bool isEmailValid = std::spc_email_isvalid(this->email->getText());
    if(!isEmailValid)
    {
        _errorInfoLabel->setString("Email is not vaild");
        _errorInfoLabel->runAction(Sequence::create(FadeIn::create(.1),DelayTime::create(1.0),FadeOut::create(.1), NULL));
        return false;
    }
    
    if(strcmp(this->passWord->getText(), this->confirmpassword->getText())!=0)
    {
        _errorInfoLabel->setString("Password is not maching");
        _errorInfoLabel->runAction(Sequence::create(FadeIn::create(.1),DelayTime::create(1.0),FadeOut::create(.1), NULL));
        return false;
    }
    
    return true;
    
}

#pragma mark - SignUp API
void WWSignUpScreen::signUpAPI()
{
    
    //http: //52.24.37.30/wow/wowapi/api/signin?user_id=&facebook_id=1424&email=email@email.com&password=123456&name=Ganesh&gender=male&country=US&facebook_thumbnail=profile.ak.fbcdn.net/hprofile-ak-ash3&ios_push_id=3b989a98d7efe
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"signup?";
    
    std::string name = std::urlencode(this->userName->getText());
    url=url+"name"+"="+name+"&";
    
    
    url=url+"email"+"="+std::urlencode(this->email->getText())+"&";
    
    url=url+"password"+"="+this->passWord->getText()+"&";
    
    
    url=url+"thumbnail"+"="+"nothing"+"&";
    
    url=url+"deviceId"+"="+WWDatamanager::sharedManager()->dmdeviceToken+"&";
    
    url=url+"deviceType"+"="+"IOS";
    
    
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::GET);
    
    
    request->setResponseCallback(CC_CALLBACK_2(WWSignUpScreen::onsignUpAPIRequestCompleted, this));
    request->setTag("SignIN");
    HttpClient::getInstance()->send(request);
    request->release();
    
}
void WWSignUpScreen::onsignUpAPIRequestCompleted(HttpClient *sender, HttpResponse *response)
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
        else
        {
            if(strcmp(document["msg"].GetString(), "Email Already Registered") == 0)
            {
                ActivtyIndicator::PopIfActiveFromScene(this);

                _errorInfoLabel->setString("Email Already Registered");
                _errorInfoLabel->runAction(Sequence::create(FadeIn::create(.1),DelayTime::create(1.0),FadeOut::create(.1), NULL));

            }
            log("server error");
        }
        
        
        
    }
}
