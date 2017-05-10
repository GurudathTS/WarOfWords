//
//  WWCommonUtilty.cpp
//  WarOfWords
//
//  Created by Manjunatha Reddy on 5/10/17.
//
//

#include "WWCommonUtilty.h"
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
