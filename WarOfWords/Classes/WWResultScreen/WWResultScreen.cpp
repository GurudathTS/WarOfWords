//
//  WWResultScreen.cpp
//  WarOfWords
//
//  Created by Gurudath on 7/15/17.
//
//

#include "WWResultScreen.h"
#include "WWMainMenuScreen.h"

Scene* WWResultScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WWResultScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

#pragma mark - Init
// on "init" you need to initialize your instance
bool WWResultScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->visibleSize = Director::getInstance()->getVisibleSize();
    this->origin = Director::getInstance()->getVisibleOrigin();
    
    //WWPlayerInfoRef->_mIsUserWinGame = false;
    if(WWPlayerInfoRef->_mIsUserWinGame)
    {
        this->addWinScreen();
    }
    else
    {
        this->addLoseScreen();
    }
    return true;
}

void WWResultScreen::addWinScreen()
{
    // Background
    auto backgroundSpr = Sprite::create("ResultScreen/V_Bg.png");
    backgroundSpr->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(backgroundSpr);
    
    //Win Icon
    auto winIcon = Sprite::create("ResultScreen/V_icon.png");
    winIcon->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(winIcon);
    
    //Header
    auto* winHeader = Label::createWithTTF("Victory!", "fonts/Kingthings Sans.ttf", 85);
    winHeader->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height/2 + origin.y + winIcon->getContentSize().height / 2 + 100));
    addChild(winHeader);
    winHeader->setColor(Color3B(161,69,28));

    
    //Submit Btn
    MenuItemImage* submitButton = MenuItemImage::create("MainMenu/YellowBtn.png", "MainMenu/YellowBtn.png", CC_CALLBACK_1(WWResultScreen::gobackToMainScreen, this));
    submitButton->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height/2 + origin.y - winIcon->getContentSize().height / 2 - submitButton->getContentSize().height));
    
    auto* backLabel = Label::createWithTTF("Go Back Home", "fonts/Kingthings Sans.ttf", 44);
    backLabel->setPosition(submitButton->getContentSize() * 0.5);
    submitButton->addChild(backLabel);
    backLabel->setColor(Color3B(164,74,76));
    
    Menu* menubtn = Menu::create(submitButton, NULL);
    menubtn->setPosition(Vec2::ZERO);
    addChild(menubtn);
    
}

void WWResultScreen::addLoseScreen()
{
    // Background
    auto backgroundSpr = Sprite::create("ResultScreen/Defeat_Bg.png");
    backgroundSpr->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(backgroundSpr);
    
    //Lose Icon
    auto loseIcon = Sprite::create("ResultScreen/Defeat_Icon.png");
    loseIcon->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(loseIcon);
    
    //Header
    auto* loseHeader = Label::createWithTTF("Defeat!", "fonts/Kingthings Sans.ttf", 85);
    loseHeader->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height/2 + origin.y + loseIcon->getContentSize().height / 2 + 100));
    addChild(loseHeader);
    loseHeader->setColor(Color3B(161,69,28));    
    
    //Submit Btn
    MenuItemImage* submitButton = MenuItemImage::create("LoginScreen/BlueCommonBtbn.png", "LoginScreen/BlueCommonBtbn.png", CC_CALLBACK_1(WWResultScreen::gobackToMainScreen, this));
    submitButton->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height/2 + origin.y - loseIcon->getContentSize().height / 2 - submitButton->getContentSize().height));
    
    auto* backLabel = Label::createWithTTF("Go Back Home", "fonts/Kingthings Sans.ttf", 44);
    backLabel->setPosition(submitButton->getContentSize() * 0.5);
    submitButton->addChild(backLabel);
    backLabel->setColor(Color3B(21,69,187));
    
    Menu* menubtn = Menu::create(submitButton, NULL);
    menubtn->setPosition(Vec2::ZERO);
    addChild(menubtn);

}

void WWResultScreen::gobackToMainScreen(Ref* sender)
{
    Director::getInstance()->replaceScene(WWMainMenu::createScene());
}
