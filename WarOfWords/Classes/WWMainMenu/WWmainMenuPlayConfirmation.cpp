//
//  WWmainMenuPlayConfirmation.cpp
//  WarOfWords
//
//  Created by Gurudath on 6/28/17.
//
//

#include "WWmainMenuPlayConfirmation.h"
#include "WWMainMenuScreen.h"


#pragma mark - Init Functions -
WWmainMenuPlayConfirmation* WWmainMenuPlayConfirmation::getConfirmationPopup()
{
    auto _tObject = new (std::nothrow) WWmainMenuPlayConfirmation();
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

WWmainMenuPlayConfirmation::WWmainMenuPlayConfirmation()
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

WWmainMenuPlayConfirmation::~WWmainMenuPlayConfirmation()
{
    
}
/*************************************************************************************/
#pragma mark - Property Functions -




/*************************************************************************************/
#pragma mark - Private Functions -
void WWmainMenuPlayConfirmation::addUI()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Sprite* _tBG   = Sprite::create("SettingPage/SettngPopup.png");
    _mBGLayer->addChild(_tBG);
    _tBG->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    _tBG->setScale(0.9);
    
    //Setting Label
    auto* settingHeaderLabel = Label::createWithTTF("Do you Want \n Accept payer", "fonts/JosefinSlab-Bold.ttf", 64);
    settingHeaderLabel->setPosition(Vec2(_tBG->getContentSize().width * 0.5, _tBG->getContentSize().height * 0.7));
    _tBG->addChild(settingHeaderLabel);
    settingHeaderLabel->setColor(Color3B::RED);
    

    //Yes btn
    this->yesBtn = MenuItemImage::create("MainMenu/BlueCommonBtnSamll.png", "MainMenu/BlueCommonBtnSamll.png", CC_CALLBACK_1(WWmainMenuPlayConfirmation::onClickOnYesbtn, this));
    this->yesBtn->setPosition(Vec2(_tBG->getContentSize().width * 0.25, _tBG->getContentSize().height * 0.2));
    this->yesBtn->setScale(0.85);
    
    auto* yesLabel = Label::createWithTTF("YES", "fonts/JosefinSlab-Bold.ttf", 32);
    yesLabel->setPosition(this->yesBtn->getContentSize() * 0.5);
    this->yesBtn->addChild(yesLabel);
    yesLabel->setColor(Color3B::BLACK);
    
    //No Btn
    this->noBtn = MenuItemImage::create("MainMenu/BlueCommonBtnSamll.png", "MainMenu/BlueCommonBtnSamll.png", CC_CALLBACK_1(WWmainMenuPlayConfirmation::onClickOnNobtn, this));
    this->noBtn->setPosition(Vec2(_tBG->getContentSize().width * 0.75, _tBG->getContentSize().height * 0.2));
    this->noBtn->setScale(0.85);
    
    auto* noLabel = Label::createWithTTF("NO", "fonts/JosefinSlab-Bold.ttf", 32);
    noLabel->setPosition(this->noBtn->getContentSize() * 0.5);
    this->noBtn->addChild(noLabel);
    noLabel->setColor(Color3B::BLACK);
    
    //Menu
    Menu* menuBtn = Menu::create(this->yesBtn,this->noBtn, NULL);
    menuBtn->setPosition(Vec2::ZERO);
    _tBG->addChild(menuBtn);
}

void WWmainMenuPlayConfirmation::onClickOnYesbtn(Ref* pSender)
{
    this->objref->callbackFromConfirmationPopup(true);
}

void WWmainMenuPlayConfirmation::onClickOnNobtn(Ref* pSender)
{
    this->objref->callbackFromConfirmationPopup(false);

}
