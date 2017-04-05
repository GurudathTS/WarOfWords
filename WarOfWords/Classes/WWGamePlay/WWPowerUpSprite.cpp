//
//  WWPowerUpSprite.cpp
//  WarOfWords
//
//  Created by Gurudath on 4/1/17.
//
//

#include "WWPowerUpSprite.h"
#include "WWGameScene.h"
#include "WWGameConstant.h"


#pragma mark - constructor,destructor
WWPowerUpSprite::WWPowerUpSprite()
{
    this->scoreval = 0;
}

WWPowerUpSprite::~WWPowerUpSprite()
{
    //Destructor
}

#pragma mark - create sprite
WWPowerUpSprite* WWPowerUpSprite::create(const char *pszFileName)
{
    WWPowerUpSprite *sprite = new (std::nothrow) WWPowerUpSprite();
    if (sprite && sprite->initWithFile(pszFileName))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void WWPowerUpSprite::initUI()
{
    this->scoreLabel = Label::createWithTTF("0", FN_GAME_FONT_NAME, FN_GAME_FONT_SIZE);
    this->scoreLabel->setPosition(Vec2(getContentSize().width * 0.5, getContentSize().height * 0.15));
    addChild(this->scoreLabel);
}

#pragma mark - update Score Label
void WWPowerUpSprite::updateScoreLabel(int pScore)
{
    this->scoreval = pScore;
    this->scoreLabel->setString(toString(pScore));
}
