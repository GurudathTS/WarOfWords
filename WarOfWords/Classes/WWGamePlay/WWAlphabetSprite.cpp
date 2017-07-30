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
#include "WWObjectiveCCalls.h"
#include "WWPlayerInfo.h"

#pragma mark - constructor,destructor
WWAlphabetSprite::WWAlphabetSprite()
{
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(WWAlphabetSprite::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(WWAlphabetSprite::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(WWAlphabetSprite::onTouchEnded, this);
    //listener->setSwallowTouches(true);
    
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
    
    if(WWPlayerInfoRef->getCurrentUserID() != WWPlayerInfoRef->getTurnUserID())
        return false;
    
    auto ptouchLocation = touch->getLocation();
    auto rectUpdatedVal = this->getBoundingBox();
    float widthVal = rectUpdatedVal.size.width * 0.3;
    float heoghtVal = rectUpdatedVal.size.height * 0.3;
    rectUpdatedVal = Rect(rectUpdatedVal.origin.x + (widthVal / 2), rectUpdatedVal.origin.y + (heoghtVal / 2), rectUpdatedVal.size.width * 0.7, rectUpdatedVal.size.height * 0.7);
    if (rectUpdatedVal.containsPoint(ptouchLocation))
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
        return true;
    }
    return true;
}

void WWAlphabetSprite::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(this->objref->currentGridRefvalue == gridRefValue)
        return;
    
    auto ptouchLocation = touch->getLocation();
    auto rectUpdatedVal = this->getBoundingBox();
    float widthVal = rectUpdatedVal.size.width * 0.3;
    float heoghtVal = rectUpdatedVal.size.height * 0.3;
    rectUpdatedVal = Rect(rectUpdatedVal.origin.x + (widthVal / 2), rectUpdatedVal.origin.y + (heoghtVal / 2), rectUpdatedVal.size.width * 0.7, rectUpdatedVal.size.height * 0.7);
    if (rectUpdatedVal.containsPoint(ptouchLocation))
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
    //if(this->objref->currentSelectedStr.size() > 3)
    {
        //loop array & Check Selected String
        std::string _tSelectedStr = "";
        for(WWAlphabetSprite* alphabetSpr : this->objref->currentSelectedStr)
        {
            if (alphabetSpr->isAlreadyPressed)
            {
                std::string _tCurStr = alphabetSpr->currentAlphabet->getString();
                _tSelectedStr = _tSelectedStr + _tCurStr;
            }
        }
        //Check if Word is present on Dictionary
         bool _tTest = true;
        if(WWObjectiveCCalls::checkifWordContainsDictionary(_tSelectedStr))
        {
            this->objref->submitButton->setOpacity(255);
            this->objref->submitButton->setEnabled(true);
            this->objref->updateScoreValue();
        }
        else
        {
            this->objref->submitButton->setOpacity(100);
            this->objref->submitButton->setEnabled(false);
            this->objref->resetScoreValue();
        }
    }
    
}

void WWAlphabetSprite::checkIfCurrentCellNearToPreviousSeelctedCell()
{
    //loop array
    bool pIsNeightbour = false;
    for(WWAlphabetSprite* alphabetSpr : this->objref->currentSelectedStr)
    {        
        if ((alphabetSpr->gridRefValue + 1) == this->gridRefValue &&  ((this->gridRefValue) % 6 != 0)) {
    
            pIsNeightbour = true;
            break;
        }
        if ((alphabetSpr->gridRefValue - 1) == this->gridRefValue && ((this->gridRefValue + 1) % 6 != 0)) {
            
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
        
        //Check for Daigonal
        int upperGrid = alphabetSpr->gridRefValue + 6;
        int lowerGrid = alphabetSpr->gridRefValue - 6;
        
        if((upperGrid + 1) == this->gridRefValue && ((this->gridRefValue) % 6 != 0))
        {
            pIsNeightbour = true;
            break;
        }
        
        if((upperGrid - 1) == this->gridRefValue && ((this->gridRefValue + 1) % 6 != 0))
        {
            pIsNeightbour = true;
            break;
        }
        
        if((lowerGrid - 1) == this->gridRefValue && ((this->gridRefValue + 1) % 6 != 0))
        {
            pIsNeightbour = true;
            break;
        }
        
        if((lowerGrid + 1) == this->gridRefValue &&  ((this->gridRefValue) % 6 != 0))
        {
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
    
    if (currentIndex < this->objref->currentSelectedStr.size()) {
        Vector<WWAlphabetSprite*> remainingAlphabetArray;
        for (int startIndex = 0; startIndex <= currentIndex; startIndex ++ )
        {
            WWAlphabetSprite* pRefSpr = this->objref->currentSelectedStr.at(startIndex);
            remainingAlphabetArray.pushBack(pRefSpr);
        }
        
        for (int index = ((int)currentIndex); index < this->objref->currentSelectedStr.size(); index ++ )
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
    auto* fadeoffAction = FadeTo::create(0.25, 0);
    this->currentAlphabet->runAction(fadeoffAction);
    this->currentAlphabetValLabel->runAction(fadeoffAction->clone());
    
    auto* sequenceAct = Sequence::create(DelayTime::create(0.25),CallFunc::create( CC_CALLBACK_0(WWAlphabetSprite::createRandomAlphabet,this)), NULL);
    this->runAction(sequenceAct);
    
}

void WWAlphabetSprite::updateSprite(std::string pStr)
{
    //this->setTexture("square.png");
    //spriteLayer->setColor(getColorValue(FC_GAME_TILES_2_DARK));
    this->setTexture("GameScene/LetterBox01.png");
    isAlreadyPressed = false;
    
    //fade off Action
    auto* fadeoffAction = FadeTo::create(0.25, 0);
    this->currentAlphabet->runAction(fadeoffAction);
    this->currentAlphabetValLabel->runAction(fadeoffAction->clone());
    
    auto* sequenceAct = Sequence::create(DelayTime::create(0.25),CallFunc::create( CC_CALLBACK_0(WWAlphabetSprite::updateRandomAlphabet,this,pStr)), NULL);
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
    int randval = arc4random() % 25;
    int randomAlphabetval;
    std::string randomAlphabetStr = "";
    
    if(this->checkIfVowelsArePresent())
    {
        randval = arc4random() % (this->objref->pVowelsArray.size() - 1);
        if(randval >= this->objref->pVowelsArray.size())
            randval = 0;
        randomAlphabetStr = this->objref->pVowelsArray.at(randval);
    }
    else
    {
        randval = arc4random() % (this->objref->pConsonantsArray.size() - 1);
        if(randval >= this->objref->pConsonantsArray.size())
            randval = 0;
        randomAlphabetStr = this->objref->pConsonantsArray.at(randval);
    }
    
    randomAlphabetval = this->objref->getAlphabetValue(randomAlphabetStr);
    this->updateNewAlphabet(randomAlphabetval, randomAlphabetStr);
    
}

bool WWAlphabetSprite::checkIfVowelsArePresent()
{
    log("    Current Alphabet    %s",this->currentAlphabet->getString().c_str());
    std::string currentAlphabetStr = this->currentAlphabet->getString().c_str();
    bool isVowels = false;
    for (int i = 0; i < this->objref->pVowelsArray.size(); i++)
    {
        std::string pAlphabetStr = this->objref->pVowelsArray.at(i);
        if(pAlphabetStr == currentAlphabetStr)
        {
            isVowels = true;
            break;
        }
    }
    return isVowels;
}

void WWAlphabetSprite::updateRandomAlphabet(std::string pAlphabet)
{
    int randomAlphabetval;
    std::string randomAlphabetStr = "";
    
    randomAlphabetStr = pAlphabet;
    randomAlphabetval = this->objref->getAlphabetValue(randomAlphabetStr);
    
    //get Random Alphabet
    alphabetValue = randomAlphabetval;
    currentAlphabet->setString(randomAlphabetStr);
    
    std::string alphaVal = toString(randomAlphabetval);
    currentAlphabetValLabel->setString(alphaVal);
    
    //fade off Action
    auto* fadeoffAction = FadeTo::create(0.5, 255);
    this->currentAlphabet->runAction(fadeoffAction);
    this->currentAlphabetValLabel->runAction(fadeoffAction->clone());
    
}

void WWAlphabetSprite::updateNewAlphabet(int currentAlphabetVal , std::string pCurrentStr)
{
    //First Gridref & Updated Alphabet
    this->objref->_mUpdatedString = this->objref->_mUpdatedString + NumToString(this->gridRefValue);
    this->objref->_mUpdatedString = this->objref->_mUpdatedString + "/";
    this->objref->_mUpdatedString = this->objref->_mUpdatedString + pCurrentStr;
    this->objref->_mUpdatedString = this->objref->_mUpdatedString + "/";

    
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
