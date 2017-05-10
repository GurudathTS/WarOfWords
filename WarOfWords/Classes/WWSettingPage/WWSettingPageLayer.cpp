//
//  WWSettingPageLayer.cpp
//  WarOfWords
//
//  Created by Gurudath on 5/8/17.
//
//

#include "WWSettingPageLayer.h"

#pragma mark - Init Functions -
WWSettingsPannel* WWSettingsPannel::getSettingsBtn()
{
    auto _tObject = new (std::nothrow) WWSettingsPannel();
    if(_tObject)
    {
        _tObject->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE(_tObject);
        _tObject = nullptr;
    }
    
    return _tObject;
}

WWSettingsPannel::WWSettingsPannel()
{
    Node::init();
    setAnchorPoint(Vec2(0, 0));
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    setContentSize(Size(visibleSize.width,visibleSize.height));
    
    _mBGLayer = LayerColor::create(Color4B::BLACK);
    _mBGLayer->setOpacity(255 * 0.6);
    addChild(_mBGLayer);
    
    
    addUI();
}

WWSettingsPannel::~WWSettingsPannel()
{
    
}
/*************************************************************************************/
#pragma mark - Property Functions -




/*************************************************************************************/
#pragma mark - Private Functions -
void WWSettingsPannel::addUI()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Sprite* _tBG   = Sprite::create("SettingPage/SettngPopup.png");
    _mBGLayer->addChild(_tBG);
    _tBG->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    _tBG->setScale(0.9);
    
    //Setting Label
    auto* settingHeaderLabel = Label::createWithTTF("Settings", "fonts/JosefinSlab-Bold.ttf", 64);
    settingHeaderLabel->setPosition(Vec2(_tBG->getContentSize().width * 0.5, _tBG->getContentSize().height * 0.85));
    _tBG->addChild(settingHeaderLabel);
    settingHeaderLabel->setColor(Color3B::RED);
    
    //Music Btn
    MenuItemImage* musicOn = MenuItemImage::create("LandingScreen/MusicBtn.png", "LandingScreen/MusicBtn.png");
    MenuItemImage* musicOff = MenuItemImage::create("LandingScreen/MusicBtnMute.png", "LandingScreen/MusicBtnMute.png");
    this->musinBtn = MenuItemToggle::createWithCallback(CC_CALLBACK_1(WWSettingsPannel::onClickOnMusicbtn, this), musicOn,musicOff,NULL);
    this->musinBtn->setPosition(Vec2(_tBG->getContentSize().width * 0.25, _tBG->getContentSize().height * 0.5));
    
    //Music Label
    auto* musicLabel = Label::createWithTTF("Music", "fonts/JosefinSlab-Bold.ttf", 42);
    musicLabel->setPosition(Vec2(_tBG->getContentSize().width * 0.4, _tBG->getContentSize().height * 0.5));
    _tBG->addChild(musicLabel);
    musicLabel->setColor(Color3B::RED);
    musicLabel->setAnchorPoint(Vec2(0, 0.5));

    
    //Sound Btn
    MenuItemImage* soundOn = MenuItemImage::create("LandingScreen/SoundBtn.png", "LandingScreen/SoundBtn.png");
    MenuItemImage* soundOff = MenuItemImage::create("LandingScreen/SoundMuteBtn.png", "LandingScreen/SoundMuteBtn.png");
    this->soundbtn = MenuItemToggle::createWithCallback(CC_CALLBACK_1(WWSettingsPannel::onClickOnSoundbtn, this), soundOn,soundOff,NULL);
    this->soundbtn->setPosition(Vec2(_tBG->getContentSize().width * 0.25, _tBG->getContentSize().height*0.65));
    
    //Sound Label
    auto* soundLabel = Label::createWithTTF("Sound", "fonts/JosefinSlab-Bold.ttf", 42);
    soundLabel->setPosition(Vec2(_tBG->getContentSize().width * 0.4, _tBG->getContentSize().height * 0.65));
    _tBG->addChild(soundLabel);
    soundLabel->setColor(Color3B::RED);
    soundLabel->setAnchorPoint(Vec2(0, 0.5));
    
    MenuItemImage* NotificationOn = MenuItemImage::create("SettingPage/NotificationsIcon.png", "SettingPage/NotificationsIcon.png");
    MenuItemImage* NotificationOff = MenuItemImage::create("SettingPage/NotificationsIcon.png", "SettingPage/NotificationsIcon.png");
    this->notificationBtn = MenuItemToggle::createWithCallback(CC_CALLBACK_1(WWSettingsPannel::onClickOnNotificationbtn, this), NotificationOn,NotificationOff,NULL);
    this->notificationBtn->setPosition(Vec2(_tBG->getContentSize().width * 0.25, _tBG->getContentSize().height * 0.35));
    
    //Sound Label
    auto* notificationLabel = Label::createWithTTF("Notifications", "fonts/JosefinSlab-Bold.ttf", 42);
    notificationLabel->setPosition(Vec2(_tBG->getContentSize().width * 0.4, _tBG->getContentSize().height * 0.35));
    _tBG->addChild(notificationLabel);
    notificationLabel->setColor(Color3B::RED);
    notificationLabel->setAnchorPoint(Vec2(0, 0.5));
    
    //Done btn
    //How to play & guild
    this->doneBtn = MenuItemImage::create("MainMenu/BlueCommonBtnSamll.png", "MainMenu/BlueCommonBtnSamll.png", CC_CALLBACK_1(WWSettingsPannel::onClickOnDonebtnBtn, this));
    this->doneBtn->setPosition(Vec2(_tBG->getContentSize().width * 0.5, _tBG->getContentSize().height * 0.15));
    this->doneBtn->setScale(0.85);
    
    auto* doneLabel = Label::createWithTTF("Done", "fonts/JosefinSlab-Bold.ttf", 32);
    doneLabel->setPosition(this->doneBtn->getContentSize() * 0.5);
    this->doneBtn->addChild(doneLabel);
    doneLabel->setColor(Color3B::BLACK);
    
    //Menu
    Menu* menuBtn = Menu::create(this->notificationBtn,this->musinBtn,this->soundbtn,this->doneBtn, NULL);
    menuBtn->setPosition(Vec2::ZERO);
    _tBG->addChild(menuBtn);
}

void WWSettingsPannel::onClickOnMusicbtn(Ref* pSender)
{
    
}

void WWSettingsPannel::onClickOnSoundbtn(Ref* pSender)
{
    
}

void WWSettingsPannel::onClickOnNotificationbtn(Ref* pSender)
{
    
}

void WWSettingsPannel::onClickOnDonebtnBtn(Ref* pSender)
{
    this->removeFromParentAndCleanup(true);
}
