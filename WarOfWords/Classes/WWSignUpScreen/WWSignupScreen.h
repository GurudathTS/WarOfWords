//
//  WWSignupScreen.h
//  WarOfWords
//
//  Created by Gurudath on 5/1/17.
//
//

#ifndef WWSignupScreen_h
#define WWSignupScreen_h

#include <stdio.h>
#include "ui/UIEditBox/UIEditBox.h"

#include "cocos2d.h"
using namespace cocos2d;
using namespace cocos2d::ui;

class WWSignUpScreen : public cocos2d::Layer,public EditBoxDelegate
{
private:
    MenuItemToggle* musinBtn, *soundbtn;
    MenuItemImage* backBtn, *signUpBtn;
    
    EditBox* userName, *email, *confirmpassword, *passWord;
    
    //Variable
    Size visibleSize;
    Vec2 origin;
    
    //Button
    void onClickOnSignUp(Ref* pSender);
    void onClickOnMusicbtn(Ref* pSender);
    void onClickOnSoundbtn(Ref* pSender);
    void onClickOnBackBtn(Ref* pSender);
    
    //Editbox
    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)override;
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)override;
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)override;
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox)override;
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    //UI
    void addUI();
    
    // implement the "static create()" method manually
    CREATE_FUNC(WWSignUpScreen);
};


#endif /* WWSignupScreen_h */
