//
//  WWLoginScreen.hpp
//  WarOfWords
//
//  Created by Gurudath on 3/17/17.
//
//

#ifndef WWLoginScreen_h
#define WWLoginScreen_h

#include "WWSocialManager.h"
#include <stdio.h>
#include "WWGameUtility.h"
#include "ui/UIEditBox/UIEditBox.h"

#include "cocos2d.h"
using namespace cocos2d;
using namespace cocos2d::network;
using namespace cocos2d::ui;

class WWLoginScreen : public cocos2d::Layer,public EditBoxDelegate
{
private:
    MenuItemToggle* musinBtn, *soundbtn;
    MenuItemImage* backBtn, *forgotpasswordBtn, *logInBtn;
    
    EditBox* userName, *passWord;
    
    //Variable
    Size visibleSize;
    Vec2 origin;
    
    //Button
    void onClickOnMusicbtn(Ref* pSender);
    void onClickOnSoundbtn(Ref* pSender);
    void onClickOnBackBtn(Ref* pSender);
    void onClickOnForgot(Ref* pSender);
    
    //Editbox
    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)override;
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)override;
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)override;
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox)override;
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init()override;
    
    //UI
    void addUI();
    
    void onClickOnLogin(Ref* pSender);
    
    //connecting server functions
    void loginToServer();
    void onLoginRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    Label *_errorInfoLabel;
    bool checkEnteredDataIsValid();
    

    // implement the "static create()" method manually
    CREATE_FUNC(WWLoginScreen);
};


#endif /* WWLoginScreen_hpp */
