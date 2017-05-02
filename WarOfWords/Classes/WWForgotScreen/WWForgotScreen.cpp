//
//  WWForgotScreen.cpp
//  WarOfWords
//
//  Created by Gurudath on 5/1/17.
//
//

#include "WWForgotScreen.h"
#include "WWLoginScreen.h"

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
        this->email->setPlaceholderFontSize(sprRef->getContentSize().height/2);
        this->email->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
        this->email->setDelegate(this);
        this->email->setVisible(true);
        this->email->setFontSize(sprRef->getContentSize().height/2);
        this->addChild(email);
        this->email->setScale(0.85);
    }
    else if(passwordType == kChangePassword)
    {
        this->confirmPassword = ui::EditBox::create(Size(sprRef->getContentSize().width, sprRef->getContentSize().height), ui::Scale9Sprite::create(pNormalSprite));
        this->confirmPassword->setPosition(Vec2(startPos.x,startPos.y));
        this->confirmPassword->setFontColor(Color3B::BLACK);
        this->confirmPassword->setPlaceHolder("   Confirm password");
        this->confirmPassword->setPlaceholderFontSize(sprRef->getContentSize().height/2);
        this->confirmPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
        this->confirmPassword->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
        this->confirmPassword->setDelegate(this);
        this->confirmPassword->setVisible(true);
        this->confirmPassword->setFontSize(sprRef->getContentSize().height/2);
        this->addChild(confirmPassword);
        this->confirmPassword->setScale(0.85);
        
        startPos = Vec2(startPos.x, startPos.y + sprRef->getContentSize().height + 15);
        this->newPassword = ui::EditBox::create(Size(sprRef->getContentSize().width, sprRef->getContentSize().height), ui::Scale9Sprite::create(pNormalSprite));
        this->newPassword->setPosition(Vec2(startPos.x,startPos.y));
        this->newPassword->setFontColor(Color3B::BLACK);
        this->newPassword->setPlaceHolder("   New password");
        this->newPassword->setPlaceholderFontSize(sprRef->getContentSize().height/2);
        this->newPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
        this->newPassword->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
        this->newPassword->setDelegate(this);
        this->newPassword->setVisible(true);
        this->newPassword->setFontSize(sprRef->getContentSize().height/2);
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
    
    auto* descriptionLabel = Label::createWithTTF(descriptiontext, "fonts/JosefinSlab-Bold.ttf", 34);
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
    
    if (passwordType == kForgotPassword) {
        
        FORGOTPASSWORDTYPE currentType = kVerificationCode;
        Director::getInstance()->replaceScene(WWForgotPasswordScreen::createScene(currentType));
    }
    else if(passwordType == kVerificationCode)
    {
        FORGOTPASSWORDTYPE currentType = kChangePassword;
        Director::getInstance()->replaceScene(WWForgotPasswordScreen::createScene(currentType));
    }
    
    
}

#pragma mark - Editbox
void WWForgotPasswordScreen::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
    log("editBox %p DidBegin !", editBox);
}

void WWForgotPasswordScreen::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
    log("editBox %p DidEnd !", editBox);
}

void WWForgotPasswordScreen::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
    log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void WWForgotPasswordScreen::editBoxReturn(ui::EditBox* editBox)
{
    log("editBox %p was returned !",editBox);
}
