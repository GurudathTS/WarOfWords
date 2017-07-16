//
//  WWCommonUtilty.hpp
//  WarOfWords
//
//  Created by Manjunatha Reddy on 5/10/17.
//
//

#ifndef WWCommonUtilty_hpp
#define WWCommonUtilty_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;


#pragma mark - BlockingLayer
class  BlockingLayer: public cocos2d::LayerColor
{
public:
    bool onTouchBegan(cocos2d::Touch * touch , cocos2d::Event *unused_event)
    {
        return true;
    }
    void addTouchListner();
    bool init();
    virtual void onExit();
    static BlockingLayer* create();
};


#pragma mark - ActivtyIndicator
class ActivtyIndicator: public BlockingLayer
{
    bool init(const char *status);
    void Pop();
    
public:
    static void PopIfActive(float time=0)
    {
        using namespace cocos2d;
        Scene *  node= (Director::getInstance()->getRunningScene());
        PopIfActiveFromScene(node,time);
    }
    
    cocos2d::Label * statusLabel;
    
    static void PopIfActiveFromScene(Node * node,float time=0)
    {
        using namespace cocos2d;
        
        ActivtyIndicator * activtyIndicator = (ActivtyIndicator *)node->getChildByTag(111);
        
        if(activtyIndicator == NULL && node->getChildrenCount())
        {
            
            activtyIndicator = (ActivtyIndicator*)node->getChildByTag((111));
        }
        
        if(time==0)
        {
            if(activtyIndicator)
                activtyIndicator->Pop();
        }else
        {
            if(activtyIndicator)
                activtyIndicator->Pop();
        }
        
    }
    
    cocos2d::LayerColor * bg;
    
    static   bool isActivityIndicatorOnScene();
    static  ActivtyIndicator * activityIndicatorOnScene(const char * status,cocos2d::Node * scene=NULL);
    
};



class CommonErrorPopup:public BlockingLayer
{
    Node * box;
    cocos2d::Sprite * bg;
    int coinsToAdd=0;
    Ref *originalTarget;
    cocos2d::SEL_MenuHandler okButtonSelector;
    
    
public:
    CommonErrorPopup(){}
    
    
    virtual std::string dailogBg()
    {
        return "CommonImages/PopupSmall.png";
    }
    
    static CommonErrorPopup * create(std::string title,std::string dedcription,Ref *target=NULL, cocos2d::SEL_MenuHandler selector1=NULL);
    virtual bool init(std::string title,std::string dedcription,Ref *inTarget=NULL, cocos2d::SEL_MenuHandler inSelector1=NULL);
    
    void okButtonAction();
    
    
    
};

#endif /* WWCommonUtilty_hpp */
