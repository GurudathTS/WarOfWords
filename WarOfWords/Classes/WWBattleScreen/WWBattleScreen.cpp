//
//  WWBattleScreen.cpp
//  WarOfWords
//
//  Created by Gurudath on 5/20/17.
//
//

#include "WWBattleScreen.h"
#include "WWGameScene.h"

Scene* WWBattleScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WWBattleScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
#pragma mark - Init
// on "init" you need to initialize your instance
bool WWBattleScreen::init()
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
    backgroundSpr->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(backgroundSpr);
    
    //Add Ui
    this->addUI();
    
    return true;
}

void WWBattleScreen::addUI()
{
    //logo Image
    auto logoImage = Sprite::create("ForgotPassword/ShieldIcon.png");
    logoImage->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x , this->visibleSize.height + this->origin.y - logoImage->getContentSize().height * 0.7));
    this->addChild(logoImage);
    
    //BG
    auto battleBg =  Sprite::create("BattleScreen/BattleColom.png");
    battleBg->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x , this->visibleSize.height/1.8 + this->origin.y));
    this->addChild(battleBg);
    
    //Header
    auto* headerLabel = Label::createWithTTF("To Battle!", "fonts/Kingthings Sans.ttf", 46);
    headerLabel->setPosition(Vec2(battleBg->getContentSize().width * 0.5, battleBg->getContentSize().height * 0.85));
    battleBg->addChild(headerLabel);
    headerLabel->setColor(Color3B(29, 61, 187));
    
    //profile Icon
    auto* currentPlayerProfile = Sprite::create("MainMenu/ProfilePicColom.png");
    currentPlayerProfile->setPosition(Vec2(battleBg->getContentSize().width * 0.25, battleBg->getContentSize().height * 0.5));
    battleBg->addChild(currentPlayerProfile);
    
    if(WWPlayerInfoRef->getCurrentProfilePictureTexture())
        currentPlayerProfile->setTexture(WWPlayerInfoRef->getCurrentProfilePictureTexture());
    else
        currentPlayerProfile->setTexture("MainMenu/round.png");
    
    //Name
    auto* userNameLabel = Label::createWithTTF(WWPlayerInfoRef->getCurrentUserName(), "fonts/JosefinSlab-Bold.ttf", 32);
    userNameLabel->setPosition(Vec2(currentPlayerProfile->getContentSize().width * 0.5 , -currentPlayerProfile->getContentSize().height * 0.2));
    currentPlayerProfile->addChild(userNameLabel);
    
    auto* opponentPlayerprofile = Sprite::create("MainMenu/ProfilePicColom.png");
    opponentPlayerprofile->setPosition(Vec2(battleBg->getContentSize().width * 0.75, battleBg->getContentSize().height * 0.5));
    battleBg->addChild(opponentPlayerprofile);
    if(WWPlayerInfoRef->getOpponentProfilePictureTexture())
        opponentPlayerprofile->setTexture(WWPlayerInfoRef->getOpponentProfilePictureTexture());
    else
        opponentPlayerprofile->setTexture("MainMenu/round.png");
    
    //Name
    auto* opponentNameLabel = Label::createWithTTF(WWPlayerInfoRef->getOpponentUserName(), "fonts/JosefinSlab-Bold.ttf", 32);
    opponentNameLabel->setPosition(Vec2(opponentPlayerprofile->getContentSize().width * 0.5 , -opponentPlayerprofile->getContentSize().height * 0.2));
    opponentPlayerprofile->addChild(opponentNameLabel);
    
    //Header
    auto* vsLbel = Label::createWithTTF("Vs", "fonts/Kingthings Sans.ttf", 46);
    vsLbel->setPosition(Vec2(battleBg->getContentSize().width * 0.5, battleBg->getContentSize().height * 0.5));
    battleBg->addChild(vsLbel);
    vsLbel->setColor(Color3B::WHITE);
    
    auto* sequenceAction = Sequence::create(DelayTime::create(6),
                                            CallFunc::create( CC_CALLBACK_0(WWBattleScreen::replaceScene,this)),NULL);
    this->runAction(sequenceAction);
    
}

void WWBattleScreen::replaceScene()
{
    Director::getInstance()->replaceScene(WWGameScene::createScene());
}
