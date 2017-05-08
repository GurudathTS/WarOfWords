//
//  WWMainMenuScreen.cpp
//  WarOfWords
//
//  Created by Gurudath on 5/2/17.
//
//

#include "WWMainMenuScreen.h"
#include "WWMainMenuActiveList.h"

Scene* WWMainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WWMainMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void WWMainMenu::onEnter()
{
    Layer::onEnter();
    
    //Add Ui
    this->addUI();
    
}
void WWMainMenu::onExit()
{
    Layer::onExit();
}

#pragma mark - Init
// on "init" you need to initialize your instance
bool WWMainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->visibleSize = Director::getInstance()->getVisibleSize();
    this->origin = Director::getInstance()->getVisibleOrigin();
    this->settingPannelLayer = nullptr;
    
    // Background
    auto backgroundSpr = Sprite::create("LandingScreen/LandngScreenBg.png");
    backgroundSpr->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x, this->visibleSize.height/2 + this->origin.y));
    this->addChild(backgroundSpr);
    
    return true;
}

void WWMainMenu::addUI()
{
    //logo Image
    auto logoImage = Sprite::create("ForgotPassword/ShieldIcon.png");
    logoImage->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x , this->visibleSize.height + this->origin.y - logoImage->getContentSize().height * 0.7));
    this->addChild(logoImage);
    
    //Setting Button
    this->settingButton = MenuItemImage::create("MainMenu/SettngBtn.png", "MainMenu/SettngBtn.png", CC_CALLBACK_1(WWMainMenu::onClickOnSettingBtn, this));
    this->settingButton->setPosition(Vec2(this->origin.x + this->settingButton->getContentSize().width * 0.8, (this->visibleSize.height) + this->origin.y - (this->settingButton->getContentSize().height * 0.8)));
    this->settingButton->setScale(0.9);
    
    //In app Button
    this->inappbtn = MenuItemImage::create("MainMenu/StoreBtn.png", "MainMenu/StoreBtn.png", CC_CALLBACK_1(WWMainMenu::onClickOnInAppBtn, this));
    this->inappbtn->setPosition(Vec2(this->visibleSize.width + this->origin.x - this->inappbtn->getContentSize().width * 0.8, this->visibleSize.height + this->origin.y - (this->inappbtn->getContentSize().height * 0.8)));
    this->inappbtn->setScale(0.9);
    
    //Quick Match Button
    this->quickMatchBtn = MenuItemImage::create("MainMenu/YellowBtn.png", "MainMenu/YellowBtn.png", CC_CALLBACK_1(WWMainMenu::onClickOnQuickmatchBtn, this));
    this->quickMatchBtn->setPosition(Vec2(this->visibleSize.width/2 + this->origin.x, this->origin.y + this->quickMatchBtn->getContentSize().height));
    this->quickMatchBtn->setScale(0.85);
    
    auto* quickmatchLabel = Label::createWithTTF("Quick Match", "fonts/JosefinSlab-Bold.ttf", 42);
    quickmatchLabel->setPosition(this->quickMatchBtn->getContentSize() * 0.5);
    this->quickMatchBtn->addChild(quickmatchLabel);
    quickmatchLabel->setColor(Color3B::BLUE);
    
    //How to play & guild
    this->howtoPlaybtn = MenuItemImage::create("MainMenu/BlueCommonBtnSamll.png", "MainMenu/BlueCommonBtnSamll.png", CC_CALLBACK_1(WWMainMenu::onClickOnHowToPlaybtnBtn, this));
    this->howtoPlaybtn->setPosition(Vec2(this->quickMatchBtn->getPositionX() - this->howtoPlaybtn->getContentSize().width/2 , this->quickMatchBtn->getPositionY() + this->howtoPlaybtn->getContentSize().height * 1.2));
    this->howtoPlaybtn->setScale(0.85);

    
    auto* howToPlayLabel = Label::createWithTTF("How to Play", "fonts/JosefinSlab-Bold.ttf", 32);
    howToPlayLabel->setPosition(this->howtoPlaybtn->getContentSize() * 0.5);
    this->howtoPlaybtn->addChild(howToPlayLabel);
    howToPlayLabel->setColor(Color3B::BLACK);

    
    this->createbuildbtn = MenuItemImage::create("MainMenu/CommonBtnSmall_Desable.png", "MainMenu/CommonBtnSmall_Desable.png", CC_CALLBACK_1(WWMainMenu::onClickOnGuildbtnBtn, this));
    this->createbuildbtn->setPosition(Vec2(this->quickMatchBtn->getPositionX() + this->createbuildbtn->getContentSize().width/2 , this->quickMatchBtn->getPositionY() + this->createbuildbtn->getContentSize().height * 1.1));
    this->createbuildbtn->setScale(0.85);
    
    auto* buildLabel = Label::createWithTTF("Guilds", "fonts/JosefinSlab-Bold.ttf", 32);
    buildLabel->setPosition(this->createbuildbtn->getContentSize() * 0.5);
    this->createbuildbtn->addChild(buildLabel);
    buildLabel->setColor(Color3B::BLACK);

    //Menu
    Menu* menuBtn = Menu::create(this->settingButton,this->quickMatchBtn,this->inappbtn,this->howtoPlaybtn,this->createbuildbtn, NULL);
    menuBtn->setPosition(Vec2::ZERO);
    this->addChild(menuBtn);
    
    //Profile Column
    this->profileBackground = Sprite::create("MainMenu/ProfileColom.png");
    this->profileBackground->setPosition(Vec2(logoImage->getPositionX(), logoImage->getPositionY() - this->profileBackground->getContentSize().height * 1.2));
    this->addChild(this->profileBackground);
    
    this->profileCircleSpr = Sprite::create("MainMenu/ProfilePicColom.png");
    this->profileCircleSpr->setPosition(Vec2(this->profileCircleSpr->getContentSize().width * 0.4,this->profileBackground->getContentSize().height * 0.5));
    this->profileBackground->addChild(this->profileCircleSpr);
    
    //User Name Label
    this->userNameLabel = Label::createWithTTF("Gurudtaha T S", "fonts/JosefinSlab-Bold.ttf", 32);
    this->userNameLabel->setPosition(Vec2(this->profileCircleSpr->getPositionX() + this->profileCircleSpr->getContentSize().width * 0.65,this->profileBackground->getContentSize().height * 0.65));
    this->profileBackground->addChild(this->userNameLabel);
    this->userNameLabel->setAnchorPoint(Vec2(0,0.5));
    
    this->userDescriptionLabel = Label::createWithTTF("Guild of the Mad badges", "fonts/JosefinSlab-Bold.ttf", 28);
    this->userDescriptionLabel->setPosition(Vec2(this->profileCircleSpr->getPositionX() + this->profileCircleSpr->getContentSize().width * 0.65,this->profileBackground->getContentSize().height * 0.35));
    this->profileBackground->addChild(this->userDescriptionLabel);
    this->userDescriptionLabel->setAnchorPoint(Vec2(0,0.5));

    this->CommonPoupBg = Sprite::create("MainMenu/CommonPopup.png");
    this->CommonPoupBg->setPosition(Vec2(this->visibleSize.width / 2 + this->origin.x , this->profileBackground->getPositionY() - this->profileBackground->getContentSize().height - (this->CommonPoupBg->getContentSize().height * 0.9)/2));
    this->addChild(this->CommonPoupBg);
    this->CommonPoupBg->setScale(0.9);

    auto* headerLabel = Label::createWithTTF("Your Active Games", "fonts/JosefinSlab-Bold.ttf", 34);
    headerLabel->setPosition(Vec2(this->CommonPoupBg->getContentSize().width * 0.5,this->CommonPoupBg->getContentSize().height * 0.9));
    this->CommonPoupBg->addChild(headerLabel);
    
    this->addActiveGamesList();
}

void WWMainMenu::addActiveGamesList()
{
    int totalNoFriends = 5;
    int offsetval = 5;
    int totalContentSize = (this->profileBackground->getContentSize().height + offsetval) * totalNoFriends;
    
    //Scroll View
    this->activeGameListScrollView = ScrollView::create(Size(this->CommonPoupBg->getContentSize().width, this->CommonPoupBg->getContentSize().height * 0.8));
    this->CommonPoupBg->addChild(this->activeGameListScrollView);
    this->activeGameListScrollView->setDirection(ScrollView::Direction::VERTICAL);
    this->activeGameListScrollView->setPosition(0, this->CommonPoupBg->getContentSize().height * 0.025);
    this->activeGameListScrollView->setBounceable(true);
    this->activeGameListScrollView->setAnchorPoint(Vec2(0.5, 0.5));
    //this->activeGameListScrollView->setContentOffset(Vec2(0, -totalContentSize/2));
    
    this->activeGameListScrollView->setContentSize(Size(this->profileBackground->getContentSize().width, totalContentSize));
    
    Vec2 startPos = Vec2(this->CommonPoupBg->getContentSize().width * 0.05, totalContentSize - this->profileBackground->getContentSize().height);
    
    for (int i=0; i<totalNoFriends; i++)
    {
        //Create Game List
        MainMenuActiveList* activeList1 = MainMenuActiveList::create();
        activeList1->setContentSize(Size(this->profileBackground->getContentSize().width, this->profileBackground->getContentSize().height));
        activeList1->setPosition(Vec2(startPos.x,startPos.y));
        this->activeGameListScrollView->addChild(activeList1);
        activeList1->addUI("Gurudtaha T S", "", "Guild of the Mad badges");
        startPos.y = startPos.y - this->profileBackground->getContentSize().height - offsetval;
    }
   
}

#pragma mark - Button
void WWMainMenu::onClickOnSettingBtn(Ref* pSender)
{

    if (this->settingPannelLayer == nullptr) {
        
        this->settingPannelLayer = WWSettingsPannel::getSettingsBtn();
        this->settingPannelLayer->setPosition(Vec2::ZERO);
        this->addChild(this->settingPannelLayer,100);
    }
}

void WWMainMenu::onClickOnInAppBtn(Ref* pSender)
{
    
}

void WWMainMenu::onClickOnQuickmatchBtn(Ref* pSender)
{

}

void WWMainMenu::onClickOnHowToPlaybtnBtn(Ref* pSender)
{
    
}

void WWMainMenu::onClickOnGuildbtnBtn(Ref* pSender)
{
    
}
