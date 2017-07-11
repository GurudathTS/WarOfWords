//
//  WWForgotScreen.cpp
//  WarOfWords
//
//  Created by Gurudath on 5/1/17.
//
//

#include "WWForgotScreen.h"
#include "WWLoginScreen.h"
#include "WWCommonUtilty.h"
#include "WWDatamanager.h"

Scene* WWForgotPasswordScreen::createScene(FORGOTPASSWORDTYPE type)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WWForgotPasswordScreen::create();
    layer->passwordType = type;
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void WWForgotPasswordScreen::onEnter()
{
    Layer::onEnter();
    
    log("Password Type %d",passwordType);

    //Add Ui
    this->addUI();
   
}
void WWForgotPasswordScreen::onExit()
{
    Layer::onExit();
}

#pragma mark - Init
// on "init" you need to initialize your instance
bool WWForgotPasswordScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->email = NULL;
    this->newPassword = NULL;
    this->confirmPassword = NULL;
    
    this->visibleSize = Director::getInstance()->getVisibleSize();
    this->origin = Director::getInstance()->getVisibleOrigin();
    
    // Background
    auto backgroundSpr = Sprite::create("LandingScreen/LandngScreenBg.png");
    backgroundSpr->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x, this->visibleSize.height/2 + this->origin.y));
    this->addChild(backgroundSpr);
    
    
    //Error Info label
    _errorInfoLabel = Label::createWithTTF("", "fonts/JosefinSlab-Bold.ttf", 42);
    _errorInfoLabel->setPosition(this->visibleSize.width/2+this->origin.x,this->visibleSize.height*.05+this->origin.y);
    this->addChild(_errorInfoLabel,100);
    _errorInfoLabel->setColor(Color3B::RED);
    _errorInfoLabel->setOpacity(0);
    

    return true;
}

void WWForgotPasswordScreen::addUI()
{
    //logo Image
    auto logoImage = Sprite::create("ForgotPassword/ShieldIcon.png");
    logoImage->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x , this->visibleSize.height + this->origin.y - logoImage->getContentSize().height * 0.7));
    this->addChild(logoImage);
    
    //Back Button
    this->backBtn = MenuItemImage::create("LoginScreen/BackBtn.png", "LoginScreen/BackBtn.png", CC_CALLBACK_1(WWForgotPasswordScreen::onClickOnBackBtn, this));
    this->backBtn->setPosition(Vec2(this->origin.x + this->backBtn->getContentSize().width * 0.8, (this->visibleSize.height) + this->origin.y - (this->backBtn->getContentSize().height * 0.8)));
    this->backBtn->setScale(0.9);
    
    
    //Sign Up Button
    this->submitBtn = MenuItemImage::create("ForgotPassword/sUBMITbTN.png", "ForgotPassword/sUBMITbTN.png", CC_CALLBACK_1(WWForgotPasswordScreen::onClickOnSubmitBtn, this));
    this->submitBtn->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x, this->visibleSize.height /3.5 + this->origin.y));
    this->submitBtn->setScale(0.85);
    
    //Menu
    Menu* menuBtn = Menu::create(this->backBtn,this->submitBtn, NULL);
    menuBtn->setPosition(Vec2::ZERO);
    this->addChild(menuBtn);
    
    //Editbox
    std::string pNormalSprite = "LoginScreen/NameColm.png";
    auto* sprRef = Sprite::create("LoginScreen/NameColm.png");
    
    Vec2 startPos = Vec2(this->submitBtn->getPositionX(), this->submitBtn->getPositionY() + sprRef->getContentSize().height + 35);
    
    //Email
    if (passwordType == kVerificationCode || passwordType == kForgotPassword)
    {
        std::string placeHolderText = "   Email";
        if (passwordType == kVerificationCode)
        {
            placeHolderText = "   Verification Code";
        }
        
        this->email = ui::EditBox::create(Size(sprRef->getContentSize().width, sprRef->getContentSize().height), ui::Scale9Sprite::create(pNormalSprite));
        this->email->setPosition(Vec2(startPos.x,startPos.y));
        this->email->setFontColor(Color3B::BLACK);
        this->email->setPlaceHolder(placeHolderText.c_str());
        this->email->setPlaceholderFontSize(40);
        this->email->setPlaceholderFontName("fonts/JosefinSlab-SemiBold.ttf");
        this->email->setPlaceholderFontColor(Color3B(124, 37, 61));
        this->email->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
        this->email->setDelegate(this);
        this->email->setVisible(true);
        this->email->setFontSize(40);
        this->addChild(email);
        this->email->setScale(0.85);
    }
    else if(passwordType == kChangePassword)
    {
        this->confirmPassword = ui::EditBox::create(Size(sprRef->getContentSize().width, sprRef->getContentSize().height), ui::Scale9Sprite::create(pNormalSprite));
        this->confirmPassword->setPosition(Vec2(startPos.x,startPos.y));
        this->confirmPassword->setFontColor(Color3B::BLACK);
        this->confirmPassword->setPlaceHolder("   Confirm password");
        this->confirmPassword->setPlaceholderFontSize(20);
        this->confirmPassword->setPlaceholderFontName("fonts/JosefinSlab-SemiBold.ttf");
        this->confirmPassword->setPlaceholderFontColor(Color3B(124, 37, 61));
        this->confirmPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
        this->confirmPassword->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
        this->confirmPassword->setDelegate(this);
        this->confirmPassword->setVisible(true);
        this->confirmPassword->setFontSize(40);
        this->addChild(confirmPassword);
        this->confirmPassword->setScale(0.85);
        
        startPos = Vec2(startPos.x, startPos.y + sprRef->getContentSize().height + 15);
        this->newPassword = ui::EditBox::create(Size(sprRef->getContentSize().width, sprRef->getContentSize().height), ui::Scale9Sprite::create(pNormalSprite));
        this->newPassword->setPosition(Vec2(startPos.x,startPos.y));
        this->newPassword->setFontColor(Color3B::BLACK);
        this->newPassword->setPlaceHolder("   New password");
        this->newPassword->setPlaceholderFontSize(20);
        this->newPassword->setPlaceholderFontName("fonts/JosefinSlab-SemiBold.ttf");
        this->newPassword->setPlaceholderFontColor(Color3B(124, 37, 61));
        this->newPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
        this->newPassword->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
        this->newPassword->setDelegate(this);
        this->newPassword->setVisible(true);
        this->newPassword->setFontSize(40);
        this->addChild(newPassword);
        this->newPassword->setScale(0.85);

        startPos = Vec2(startPos.x, startPos.y - 15);

    }
    
    //Forgot Password
    std::string headerText = "Forgot your Password?";
    std::string descriptiontext = "We will send a Verification \ncode to your email. \n Please enter it below.";
    
    float scaleVal = 1.2;
    if (passwordType == kVerificationCode)
    {
        headerText = "Please verify your Email";
        descriptiontext = "We have sent a Verification \n code to your email. \n Please enter it below.";
    }
    if (passwordType == kChangePassword)
    {
        headerText = "Change your Password";
        descriptiontext = "Please Type in your new Password";
        scaleVal = 1.0;
    }
    
    auto* descriptionbg = Sprite::create("ForgotPassword/ForgotPasswdColom.png");
    startPos = Vec2(startPos.x, startPos.y + descriptionbg->getContentSize().height);
    descriptionbg->setPosition(Vec2(startPos.x,startPos.y));
    addChild(descriptionbg);
    descriptionbg->setScale(0.85, scaleVal);
    
    auto* headerLabel = Label::createWithTTF(headerText, "fonts/JosefinSlab-Bold.ttf", 40);
    headerLabel->setPosition(Vec2(descriptionbg->getContentSize().width/2, descriptionbg->getContentSize().height / 1.4));
    descriptionbg->addChild(headerLabel);
    headerLabel->setScale(1.15, 1.0 - (scaleVal - 1.0));
    
    auto* descriptionLabel = Label::createWithTTF(descriptiontext, "fonts/JosefinSlab-SemiBold.ttf", 34);
    descriptionLabel->setPosition(Vec2(descriptionbg->getContentSize().width/2, descriptionbg->getContentSize().height / 2.8));
    descriptionbg->addChild(descriptionLabel);
    descriptionLabel->setAlignment(cocos2d::TextHAlignment::CENTER);
    descriptionLabel->setScale(1.15, 1.0 - (scaleVal - 1.0));

    
}

#pragma mark - Button
void WWForgotPasswordScreen::onClickOnBackBtn(Ref* pSender)
{
    Director::getInstance()->replaceScene(WWLoginScreen::createScene());
}

void WWForgotPasswordScreen::onClickOnSubmitBtn(Ref* pSender)
{
    
    if (passwordType == kForgotPassword)
    {
        if(this->checkEnteredDataIsValid())
        {
            this->sumbitEmailApi();
        }
    }
    else if(passwordType == kVerificationCode)
    {
        
        if(this->checkEnteredDataIsValid())
        {
            this->sumbitVerificationCodeApi();
        }
       
        
    }
    else if(passwordType == kChangePassword)
    {
        
        if(this->checkEnteredDataIsValid())
        {
            this->newPasswordSubmitApi();
        }
        
        
    }
    
    
    
}

#pragma mark - Editbox
void WWForgotPasswordScreen::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
  //  log("editBox %p DidBegin !", editBox);
}

void WWForgotPasswordScreen::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
   // log("editBox %p DidEnd !", editBox);
}

void WWForgotPasswordScreen::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
   // log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void WWForgotPasswordScreen::editBoxReturn(ui::EditBox* editBox)
{
   // log("editBox %p was returned !",editBox);
}
#pragma mark - Submit emailAPI
void WWForgotPasswordScreen::sumbitEmailApi()
{
    ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
    
http://52.24.37.30:3000/api/signin?user_id=&authId=100001527270712&name=kfkfk&email=manjunathareddyn@gmail.com&password=hgjg&thumbnail=jkk&deviceId=j89jj&deviceType=IOS
    
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"sendverification?";

    
    
    
    url=url+"email"+"="+this->email->getText()+"&";
    
    
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::GET);
    
    
    request->setResponseCallback(CC_CALLBACK_2(WWForgotPasswordScreen::onSubmitApiRequestCompleted, this));
    request->setTag("SendVerification");
    HttpClient::getInstance()->send(request);
    request->release();
    
}
void WWForgotPasswordScreen::onSubmitApiRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    
    if (!response)
    {
        return;
    }
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    if(!document.IsNull())
    {
        WWDatamanager::sharedManager()->_forgotPasswordEmailId = this->email->getText();
        FORGOTPASSWORDTYPE currentType = kVerificationCode;
        Director::getInstance()->replaceScene(WWForgotPasswordScreen::createScene(currentType));

    }
    
}
#pragma mark - Verification code API
void WWForgotPasswordScreen::sumbitVerificationCodeApi()
{
    ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
    
http://52.24.37.30:3000/api/signin?user_id=&authId=100001527270712&name=kfkfk&email=manjunathareddyn@gmail.com&password=hgjg&thumbnail=jkk&deviceId=j89jj&deviceType=IOS
    
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"verifyemail?";
    
    
    
    
    url=url+"email"+"="+WWDatamanager::sharedManager()->_forgotPasswordEmailId+"&";
    url=url+"code"+"="+this->email->getText()+"&";

    
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::GET);
    
    
    request->setResponseCallback(CC_CALLBACK_2(WWForgotPasswordScreen::onVerificationCodeApiRequestCompleted, this));
    request->setTag("SendVerification");
    HttpClient::getInstance()->send(request);
    request->release();
    
}
void WWForgotPasswordScreen::onVerificationCodeApiRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    if(!document.IsNull())
    {
        int code = document["errorCode"].GetInt();
        if(code == 0)
        {
            FORGOTPASSWORDTYPE currentType = kChangePassword;
            Director::getInstance()->replaceScene(WWForgotPasswordScreen::createScene(currentType));
            
        }
        else
        {
            ActivtyIndicator::PopIfActiveFromScene(this);
            _errorInfoLabel->setString("Enter valid code");
            _errorInfoLabel->runAction(Sequence::create(FadeIn::create(.1),DelayTime::create(1.0),FadeOut::create(.1), NULL));
            
        }
        
    }
    
}
#pragma mark - New password API
void WWForgotPasswordScreen::newPasswordSubmitApi()
{
    ActivtyIndicator::activityIndicatorOnScene("Please wait..",this);
    
http://52.24.37.30:3000/api/signin?user_id=&authId=100001527270712&name=kfkfk&email=manjunathareddyn@gmail.com&password=hgjg&thumbnail=jkk&deviceId=j89jj&deviceType=IOS
    
    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"changepassword?";
    
    
    
    
    url=url+"email"+"="+WWDatamanager::sharedManager()->_forgotPasswordEmailId+"&";
    url=url+"password"+"="+this->newPassword->getText()+"&";
    
    
    
    request->setUrl(url);
    CCLOG(" url is %s",request->getUrl());
    request->setRequestType(HttpRequest::Type::GET);
    
    
    request->setResponseCallback(CC_CALLBACK_2(WWForgotPasswordScreen::onNewPasswordSubmitApiRequestCompleted, this));
    request->setTag("Changepassword");
    HttpClient::getInstance()->send(request);
    request->release();

}
void WWForgotPasswordScreen::onNewPasswordSubmitApiRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    if(!document.IsNull())
    {
        if(document["errorCode"].GetInt() == 0 && (strcmp(document["msg"].GetString(), "Password changed successfully")==0))

        Director::getInstance()->replaceScene(WWLoginScreen::createScene());
        
    }
    else
    {
        ActivtyIndicator::PopIfActiveFromScene(this);
        
    }
    
}

#pragma mark - Data validation
bool WWForgotPasswordScreen::checkEnteredDataIsValid()
{
    
    bool isEmpty = false;
    std::string errorText = "";
    
    
    if(passwordType == kForgotPassword)
    {
        if(strcmp(this->email->getText(), "")==0)
        {
            isEmpty = true;
            errorText = "email is empty";
            
            
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
        
    }
    else  if(passwordType == kVerificationCode)

    {
        if(strcmp(this->email->getText(), "")==0)
        {
            isEmpty = true;
            errorText = "code is empty";
            
            
        }
        if(isEmpty)
        {
            _errorInfoLabel->setString(errorText);
            _errorInfoLabel->runAction(Sequence::create(FadeIn::create(.1),DelayTime::create(1.0),FadeOut::create(.1), NULL));
            return false;
        }
        
    }
    else  if(passwordType == kChangePassword)
    {
        if(strcmp(this->newPassword->getText(), "")==0)
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
        
        
        if(strcmp(this->newPassword->getText(), this->confirmPassword->getText())!=0)
        {
            _errorInfoLabel->setString("Password is not maching");
            _errorInfoLabel->runAction(Sequence::create(FadeIn::create(.1),DelayTime::create(1.0),FadeOut::create(.1), NULL));
            return false;
        }

    }

    
    return true;
    
    
}

