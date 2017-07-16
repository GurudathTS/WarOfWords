//
//  WWCommonUtilty.cpp
//  WarOfWords
//
//  Created by Manjunatha Reddy on 5/10/17.
//
//

#include "WWCommonUtilty.h"
#include "WWGameConstant.h"
#pragma mark - BlockingLayer Functions
BlockingLayer* BlockingLayer::create()
{
    BlockingLayer *layer=new BlockingLayer;
    layer->init();
    layer->setTag(111);
    return layer;
}
bool BlockingLayer::init()
{
    
    if(!cocos2d::LayerColor::initWithColor(cocos2d::Color4B(0,0,0,210))) //
    {
        return false;
    }
    addTouchListner();
    return true;
}
void BlockingLayer::addTouchListner()
{
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = CC_CALLBACK_2(BlockingLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
void BlockingLayer:: onExit()
{
    LayerColor::onExit();
    
}

#pragma mark - ActivtyIndicator Functions
bool ActivtyIndicator::init(const char *status)
{
    if(!BlockingLayer::init())
        return false;
    
    bg= LayerColor::create();//ccc4(0, 0, 0, 0)
    this->addChild(bg);
    bg->setOpacity(0);
    this->setColor(Color3B::BLACK);
    this->setOpacity(50);
    bg->setPosition(Vec2(0, 0));
    bg->runAction(FadeTo::create(0.05,195));
    
    statusLabel = Label::createWithTTF("Connecting", "fonts/JosefinSlab-Bold.ttf", 30);
    this->addChild(statusLabel);
    statusLabel->setString(status);
    this->statusLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2+Director::getInstance()->getVisibleOrigin().x, Director::getInstance()->getVisibleSize().height/2+Director::getInstance()->getVisibleOrigin().y-100));
    
    return true;
    
}

void ActivtyIndicator::Pop()
{
    bg->runAction(FadeTo::create(0.1, 0));
    this->removeFromParent();
}
bool ActivtyIndicator::isActivityIndicatorOnScene()
{
    Node *  node= (Director::getInstance()->getRunningScene());
    Node *  indicator = node->getChildByTag(111);
    return indicator !=NULL;
}
ActivtyIndicator * ActivtyIndicator::activityIndicatorOnScene(const char * status,Node * scene)
{
    Node *  node= (Director::getInstance()->getRunningScene());
    
    if(scene)
    {
        node=scene;
        
    }
    
    Node *  indicator = node->getChildByTag(111);
    
    if(status && indicator == NULL)
    {
        indicator = new ActivtyIndicator;
        ((ActivtyIndicator*)indicator)->init(status);
        indicator->setTag(111);
        node->addChild(indicator,1000);
        indicator->release();
    }
    
    ((ActivtyIndicator*)indicator)->statusLabel->setString(status);
    
    return ((ActivtyIndicator*)indicator);
}

#pragma mark - CommonError dialog
CommonErrorPopup *  CommonErrorPopup::create(std::string title,std::string dedcription,Ref *target, cocos2d::SEL_MenuHandler selector1)
{
    CommonErrorPopup * dilog = new CommonErrorPopup;
    dilog->init(title,dedcription,target,selector1);
    dilog->autorelease();
    return dilog;
    
}


bool CommonErrorPopup::init(std::string title,std::string dedcription,Ref *inTarget, cocos2d::SEL_MenuHandler inSelector1)
{
    if(!BlockingLayer::init())
        return false;
    
    this->originalTarget=inTarget;
    this->okButtonSelector=inSelector1;
    
    LayerColor * bg = LayerColor::create(cocos2d::Color4B(0,0,0,100));
    bg->ignoreAnchorPointForPosition(false);
    this->addChild(bg,3000);
    bg->setOpacity(25);
    bg->runAction(FadeTo::create(0.001, 50));
    bg->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    
    
    
    box = Sprite::create("commonErrorPopup.png");
    this->addChild(box,3000);
    box->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    
    
    
    Label *titleLabel=Label::createWithTTF(title,FN_POPUP_TEXT_FONT_NAME, FN_POPIUP_TITLE_FONT_SIZE);
    titleLabel->setAlignment(TextHAlignment::CENTER);
    box->addChild(titleLabel,10);
    titleLabel->setPosition(Vec2(box->getContentSize().width/2, box->getContentSize().height-60));
    titleLabel->setColor(POPUP_TEXT_COLOR);
    
    
    Label *derciptionLabel=Label::createWithTTF(dedcription,FN_POPUP_TEXT_FONT_NAME, FN_POPIUP_DESCRIPTION_FONT_SIZE);
    derciptionLabel->setAlignment(TextHAlignment::CENTER);
    box->addChild(derciptionLabel,10);
    derciptionLabel->setPosition(Vec2(box->getContentSize().width/2, box->getContentSize().height/2));
    derciptionLabel->setColor(POPUP_TEXT_COLOR);

    
    auto okButtton = MenuItemImage::create("MainMenu/BlueCommonBtnSamll.png", "MainMenu/BlueCommonBtnSamll.png", "MainMenu/BlueCommonBtnSamll.png", CC_CALLBACK_0(CommonErrorPopup::okButtonAction, this));
    okButtton->setPosition(Vec2(box->getContentSize().width/2, okButtton->getContentSize().height*.9));
    

    auto* yesLabel = Label::createWithTTF("OK", "fonts/JosefinSlab-Bold.ttf", 32);
    yesLabel->setPosition(okButtton->getContentSize() * 0.5);
    okButtton->addChild(yesLabel);
    yesLabel->setColor(POPUP_BUTTON_TEXT_COLOR);

    Menu *tempMenu=Menu::create(okButtton, NULL);
    box->addChild(tempMenu);
    tempMenu->setPosition(Vec2(0, 0));
    
    
    box->runAction(Sequence::create(ScaleTo::create(0.0f, 0.1f),ScaleTo::create(0.2f, 1.2f),ScaleTo::create(0.1f, 1.0f),NULL));
    
    return true;
    
}

void CommonErrorPopup::okButtonAction()
{
    if(okButtonSelector!=NULL)
    {
        (originalTarget->*okButtonSelector)(this);
    }
    this->removeFromParent();
    
    
}

