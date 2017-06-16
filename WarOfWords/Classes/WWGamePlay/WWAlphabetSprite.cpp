//
//  WWAlphabetSprite.cpp
//  WarOfWords
//
//  Created by Gurudath on 2/20/17.
//
//

#include "WWAlphabetSprite.h"
#include "WWGameScene.h"
#include "WWGameConstant.h"

#pragma mark - constructor,destructor
WWAlphabetSprite::WWAlphabetSprite()
{
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(WWAlphabetSprite::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(WWAlphabetSprite::onTouchMoved, this);
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
        sprite->sprName = pszFileName;
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
    
    //Set Color to Sprite
    //this->setColor(getColorValue(FC_GAME_TILES_1_DARK));
    
    //create One more Sprite Above that
//    spriteLayer = Sprite::create(sprName);
//    spriteLayer->setPosition(getContentSize() * 0.5);
//    addChild(spriteLayer,1);
//    spriteLayer->setScale(0.95);
//    
//    spriteLayer->setColor(getColorValue(FC_GAME_TILES_2_DARK));
    
    //Create Label
    currentAlphabet = Label::createWithTTF(pCurrentStr.c_str(), FN_GAME_FONT_NAME, FN_GAME_ALPHABET_FONT_SIZE);
    currentAlphabet->setPosition(getContentSize() * 0.5);
    addChild(currentAlphabet,2);
    currentAlphabet->setColor(getColorValue(FC_GAME_TILES_1_DARK));
    
    std::string alphaVal = toString(currentAlphabetVal);
    currentAlphabetValLabel =  Label::createWithTTF(alphaVal.c_str(), FN_GAME_FONT_NAME, FN_GAME_ALPHABET_SCORE_SIZE);
    currentAlphabetValLabel->setPosition(Vec2(getContentSize().width * 0.75, getContentSize().height * 0.2));
    addChild(currentAlphabetValLabel,2);
    currentAlphabetValLabel->setColor(getColorValue(FC_GAME_TILES_1_DARK));
}

void WWAlphabetSprite::updatedGridReferenceValue(int pGridrefVal)
{
    this->gridRefValue = pGridrefVal;
}

#pragma mark - touches
bool WWAlphabetSprite::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto ptouchLocation = touch->getLocation();
    if (this->getBoundingBox().containsPoint(ptouchLocation))
    {
        this->objref->currentGridRefvalue = gridRefValue;
        if (isAlreadyPressed)
        {
            this->removeSetOfLetterFromArray();

        }
        else
        {
            //Check is It Neighbour to Any of the Cell
            this->checkIfCurrentCellNearToPreviousSeelctedCell();
            
            this->setTexture("GameScene/LetterBox02.png");
            isAlreadyPressed = true;
            this->objref->currentSelectedStr.pushBack(this);
        }
    }
    return true;
}

void WWAlphabetSprite::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(this->objref->currentGridRefvalue == gridRefValue)
        return;
    
    auto ptouchLocation = touch->getLocation();
    if (this->getBoundingBox().containsPoint(ptouchLocation))
    {
        this->objref->currentGridRefvalue = gridRefValue;
        if (isAlreadyPressed)
        {
            this->removeSetOfLetterFromArray();
        }
        else
        {
            this->setTexture("GameScene/LetterBox02.png");
            isAlreadyPressed = true;
            this->objref->currentSelectedStr.pushBack(this);
        }
    }
}

void WWAlphabetSprite::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}

void WWAlphabetSprite::checkIfCurrentCellNearToPreviousSeelctedCell()
{
    //loop array
    bool pIsNeightbour = false;
    for(WWAlphabetSprite* alphabetSpr : this->objref->currentSelectedStr)
    {
        log("Alphabet gridRef Value %d",alphabetSpr->gridRefValue);
        log("currentSelectedStr gridRef Value %d",this->gridRefValue);
        
        if ((alphabetSpr->gridRefValue + 1) == this->gridRefValue) {
    
            pIsNeightbour = true;
            break;
        }
        if ((alphabetSpr->gridRefValue - 1) == this->gridRefValue) {
            
            pIsNeightbour = true;
            break;
        }
        if ((alphabetSpr->gridRefValue + 6) == this->gridRefValue) {
            
            pIsNeightbour = true;
            break;
        }
        if ((alphabetSpr->gridRefValue - 6) == this->gridRefValue) {
            
            pIsNeightbour = true;
            break;
        }
    }
    
    if(!pIsNeightbour)
    {
        for(WWAlphabetSprite* alphabetSpr : this->objref->currentSelectedStr)
        {
            alphabetSpr->resetSpriteAfterLost();
        }
        this->objref->currentSelectedStr.clear();
    }
}

void WWAlphabetSprite::removeSetOfLetterFromArray()
{
    ssize_t currentIndex = this->objref->currentSelectedStr.getIndex(this);
    log("currentIndex %zd",currentIndex);
    
    if (currentIndex < this->objref->currentSelectedStr.size()) {
        Vector<WWAlphabetSprite*> remainingAlphabetArray;
        for (int startIndex = 0; startIndex <= currentIndex; startIndex ++ )
        {
            WWAlphabetSprite* pRefSpr = this->objref->currentSelectedStr.at(startIndex);
            remainingAlphabetArray.pushBack(pRefSpr);
        }
        
        for (int index = currentIndex + 1; index < this->objref->currentSelectedStr.size(); index ++ )
        {
            WWAlphabetSprite* pRefSprChange = this->objref->currentSelectedStr.at(index);
            pRefSprChange->resetSpriteAfterLost();
        }
        
        this->objref->currentSelectedStr.clear();
        this->objref->currentSelectedStr.pushBack(remainingAlphabetArray);
        log("Array Count %zd",this->objref->currentSelectedStr.size());
    }
}

void WWAlphabetSprite::resetSprite()
{
    //this->setTexture("square.png");
    //spriteLayer->setColor(getColorValue(FC_GAME_TILES_2_DARK));
    this->setTexture("GameScene/LetterBox01.png");
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
    //this->setTexture("square.png");
    //spriteLayer->setColor(getColorValue(FC_GAME_TILES_2_DARK));
    this->setTexture("GameScene/LetterBox01.png");
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
