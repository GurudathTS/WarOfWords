//
//  WWForgotScreen.h
//  WarOfWords
//
//  Created by Gurudath on 5/1/17.
//
//

#ifndef WWForgotScreen_h
#define WWForgotScreen_h

#include <stdio.h>
#include "ui/UIEditBox/UIEditBox.h"
#include "WWGameConstant.h"
#include "WWGameUtility.h"

#include "cocos2d.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::network;


class WWForgotPasswordScreen : public cocos2d::Layer,public EditBoxDelegate
{
private:
    MenuItemImage* backBtn, *submitBtn;
    EditBox *email, *newPassword, *confirmPassword;
    
    //Variable
    Size visibleSize;
    Vec2 origin;
    
    FORGOTPASSWORDTYPE passwordType;
    
    //Button
    void onClickOnSubmitBtn(Ref* pSender);
    void onClickOnBackBtn(Ref* pSender);
    
    //Editbox
    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)override;
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)override;
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)override;
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox)override;
    
    //connecting server functions
    void sumbitEmailApi();
    void onSubmitApiRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    void sumbitVerificationCodeApi();
    void onVerificationCodeApiRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    
    void newPasswordSubmitApi();
    void onNewPasswordSubmitApiRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    
    
    Label *_errorInfoLabel;
    bool checkEnteredDataIsValid();
    
    
public:
    static cocos2d::Scene* createScene(FORGOTPASSWORDTYPE type);
    virtual bool init()override;
    void onEnter()override;
    void onExit()override;
    
    //UI
    void addUI();
    
    // implement the "static create()" method manually
    CREATE_FUNC(WWForgotPasswordScreen);
};


#endif /* WWForgotScreen_h */
