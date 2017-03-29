//
//  WWLoginScreen.cpp
//  WarOfWords
//
//  Created by Gurudath on 3/17/17.
//
//

#include "WWLoginScreen.h"
#include "WWSocialManager.h"

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

// on "init" you need to initialize your instance
bool WWLoginScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    addChild(WWSocialManagerRef);
    WWSocialManagerRef->initWithEnum(enumSocialSharingType::kFacebook);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Login Screen", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // add a "close" icon to exit the progress. it's an autorelease object
    loginBtn = MenuItemLabel::create(Label::createWithTTF("Login", "fonts/Marker Felt.ttf", 40) , CC_CALLBACK_1(WWLoginScreen::onClickOnLogin, this));
    
    loginBtn->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height/6));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(loginBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //Check for Facebook Login
    if (WWSocialManagerRef->getFacebookLoggedIn())
    {
        loginBtn->setString("Logout");
    }
    
    return true;
}

void WWLoginScreen::onClickOnLogin(Ref* pSender)
{

    if(WWSocialManagerRef->getFacebookLoggedIn())
    {
         WWSocialManagerRef->logOut(enumSocialSharingType::kFacebook);
    }
    else
    {
        WWSocialManagerRef->setCallback(CC_CALLBACK_1(WWLoginScreen::afterLoginCompleted, this));
        WWSocialManagerRef->logIn(enumSocialSharingType::kFacebook);
        log("......Login .. ....");
    }
}

void WWLoginScreen::afterLoginCompleted(bool pIsDone)
{
    WWSocialManagerRef->getGameFriendsList(enumSocialSharingType::kFacebook);
}
