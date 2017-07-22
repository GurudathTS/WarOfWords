//
//  WWMainMenuActiveList.cpp
//  WarOfWords
//
//  Created by Gurudath on 5/2/17.
//
//

#include "WWMainMenuActiveList.h"
#include "WWDatamanager.h"
#include "WWMainMenuScreen.h"

MainMenuActiveList::MainMenuActiveList()
{
    
}

MainMenuActiveList::~MainMenuActiveList()
{

}

#pragma mark - create sprite
MainMenuActiveList* MainMenuActiveList::create()
{
    MainMenuActiveList *layer = new (std::nothrow) MainMenuActiveList();
    if (layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void MainMenuActiveList::addUI(std::string pName
                               ,std::string pImageURL
                               ,std::string pDescription,int pHealth)
{
    
    _mNameRef = pName;
    _mDescription = pDescription;
    _mImageURL = pImageURL;
    opponentHealth = pHealth;
    
    //Profile Picture
    this->profilePictureImg = Sprite::create("MainMenu/ProfilePicColom.png");
    this->profilePictureImg->setPosition(Vec2(this->profilePictureImg->getContentSize().width * 0.4,this->getContentSize().height * 0.5));
    this->addChild(this->profilePictureImg);
    this->profilePictureImg->setScale(0.7);
    this->profilePictureImg->setTexture("MainMenu/round.png");
    
    //User Name Label
    this->userNameLabel = Label::createWithTTF(_mNameRef.c_str(), "fonts/JosefinSlab-Bold.ttf", 32);
    this->userNameLabel->setPosition(Vec2(this->profilePictureImg->getPositionX() + (this->profilePictureImg->getContentSize().width * 0.7) * 0.65,this->getContentSize().height * 0.65));
    this->addChild(this->userNameLabel);
    this->userNameLabel->setAnchorPoint(Vec2(0,0.5));
    
    this->userDescriptionlabel = Label::createWithTTF(_mDescription.c_str(), "fonts/JosefinSlab-SemiBold.ttf", 28);
    this->userDescriptionlabel->setPosition(Vec2(this->profilePictureImg->getPositionX() + (this->profilePictureImg->getContentSize().width * 0.7) * 0.65,this->getContentSize().height * 0.35));
    this->addChild(this->userDescriptionlabel);
    this->userDescriptionlabel->setAnchorPoint(Vec2(0,0.5));
    
    this->battleIconImg = Sprite::create("MainMenu/BattleIcon.png");
    this->battleIconImg->setPosition(Vec2(this->getContentSize().width * 0.95, this->getContentSize().height * 0.5));
    this->addChild(this->battleIconImg);
    
    
    MenuItemImage *hiddenMenuItem = MenuItemImage::create("MainMenu/BattleIcon.png", "MainMenu/BattleIcon.png", CC_CALLBACK_0(MainMenuActiveList::battleIconButtonAction, this));
    hiddenMenuItem->setPosition(this->battleIconImg->getContentSize().width/2, this->battleIconImg->getContentSize().height/2);
    hiddenMenuItem->setOpacity(0);
    
    Menu *tempMenu = Menu::createWithItem(hiddenMenuItem);
    this->battleIconImg->addChild(tempMenu);
    tempMenu->setPosition(Vec2::ZERO);
    
}
 void MainMenuActiveList::battleIconButtonAction()
{
    log("com");
    WWDatamanager::sharedManager()->lastUpdatedStr = lastUpdatedStr;
    WWDatamanager::sharedManager()->_mainScreenRef->activeListBattleIconAction(this->challengID, this->opponentName, this->opponentUserId, this->opponenetThumbnail, this->status, this->turnUserId, this->wonBy);
    
}
