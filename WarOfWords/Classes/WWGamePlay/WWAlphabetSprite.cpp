//
//  WWAlphabetSprite.cpp
//  WarOfWords
//
//  Created by Gurudath on 2/20/17.
//
//

#include "WWAlphabetSprite.hpp"
#include "WWGameScene.hpp"

#pragma mark - constructor,destructor
WWAlphabetSprite::WWAlphabetSprite()
{
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(WWAlphabetSprite::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(WWAlphabetSprite::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

WWAlphabetSprite::~WWAlphabetSprite()
{
    //Destructor
}

#pragma mark - create sprite
WWAlphabetSprite* WWAlphabetSprite::create(const char *pszFileName)
{
    WWAlphabetSprite *sprite = new (std::nothrow) WWAlphabetSprite();
    if (sprite && sprite->initWithFile(pszFileName))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

#pragma mark - Initialize
void WWAlphabetSprite::initializeFunc(int currentAlphabetVal , std::string pCurrentStr)
{
    isAlreadyPressed = false;
    alphabetValue = currentAlphabetVal;
    
    //Create Label
    currentAlphabet = Label::createWithTTF(pCurrentStr.c_str(), "fonts/Marker Felt.ttf", 30);
    currentAlphabet->setPosition(getContentSize() * 0.5);
    addChild(currentAlphabet);
    
    std::string alphaVal = toString(currentAlphabetVal);
    currentAlphabetValLabel =  Label::createWithTTF(alphaVal.c_str(), "fonts/Marker Felt.ttf", 25);
    currentAlphabetValLabel->setPosition(getContentSize() * 0.8);
    addChild(currentAlphabetValLabel);
    currentAlphabetValLabel->setColor(Color3B::GREEN);
}

#pragma mark - touches
bool WWAlphabetSprite::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto ptouchLocation = touch->getLocation();
    if (this->getBoundingBox().containsPoint(ptouchLocation))
    {
        if (isAlreadyPressed)
        {
            this->setTexture("square.png");
            isAlreadyPressed = false;
            if (this->objref->currentSelectedStr.contains(this))
                this->objref->currentSelectedStr.eraseObject(this);
        }
        else
        {
            this->setTexture("square_pressed.png");
            isAlreadyPressed = true;
            this->objref->currentSelectedStr.pushBack(this);
        }
    }
    return true;
}

void WWAlphabetSprite::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}

void WWAlphabetSprite::resetSprite()
{
    this->setTexture("square.png");
    isAlreadyPressed = false;
    
    //fade off Action
    auto* fadeoffAction = FadeTo::create(0.5, 0);
    this->currentAlphabet->runAction(fadeoffAction);
    this->currentAlphabetValLabel->runAction(fadeoffAction->clone());
    
    auto* sequenceAct = Sequence::create(DelayTime::create(0.5),CallFunc::create( CC_CALLBACK_0(WWAlphabetSprite::createRandomAlphabet,this)), NULL);
    this->runAction(sequenceAct);
    
}

void WWAlphabetSprite::resetSpriteAfterLost()
{
    this->setTexture("square.png");
    isAlreadyPressed = false;
}


void WWAlphabetSprite::createRandomAlphabet()
{
    //get random  Num
    int randval = arc4random() % 7;
    int randomAlphabetval;
    std::string randomAlphabetStr = "";
    if (randval == 0)
    {
        randomAlphabetStr = this->objref->pOnePointArray.at(arc4random() % this->objref->pOnePointArray.size());
        randomAlphabetval = 1;
    }
    else if(randval == 1)
    {
        randomAlphabetStr = this->objref->pTwoPointArray.at(arc4random() % this->objref->pTwoPointArray.size());
        randomAlphabetval = 2;
    }
    else if(randval == 2)
    {
        randomAlphabetStr = this->objref->pThreePointArray.at(arc4random() % this->objref->pThreePointArray.size());
        randomAlphabetval = 3;
    }
    else if(randval == 3)
    {
        randomAlphabetStr = this->objref->pFourPointArray.at(arc4random() % this->objref->pFourPointArray.size());
        randomAlphabetval = 4;
    }
    else if(randval == 4)
    {
        randomAlphabetStr = this->objref->pFivePointArray.at(arc4random() % this->objref->pFivePointArray.size());
        randomAlphabetval = 5;
    }
    else if(randval == 5)
    {
        randomAlphabetStr = this->objref->pEightPointArray.at(arc4random() % this->objref->pEightPointArray.size());
        randomAlphabetval = 8;
    }
    else
    {
        randomAlphabetStr = this->objref->pTenPointArray.at(arc4random() % this->objref->pTenPointArray.size());
        randomAlphabetval = 10;
    }
    this->updateNewAlphabet(randomAlphabetval, randomAlphabetStr);
    
}

void WWAlphabetSprite::updateNewAlphabet(int currentAlphabetVal , std::string pCurrentStr)
{
    //get Random Alphabet
    alphabetValue = currentAlphabetVal;
    currentAlphabet->setString(pCurrentStr);
    
    std::string alphaVal = toString(currentAlphabetVal);
    currentAlphabetValLabel->setString(alphaVal);
    
    //fade off Action
    auto* fadeoffAction = FadeTo::create(0.5, 255);
    this->currentAlphabet->runAction(fadeoffAction);
    this->currentAlphabetValLabel->runAction(fadeoffAction->clone());

}
