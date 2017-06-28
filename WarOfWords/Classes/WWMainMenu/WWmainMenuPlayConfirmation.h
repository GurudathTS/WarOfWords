//
//  WWmainMenuPlayConfirmation.h
//  WarOfWords
//
//  Created by Gurudath on 6/28/17.
//
//

#ifndef WWmainMenuPlayConfirmation_h
#define WWmainMenuPlayConfirmation_h
#include <stdio.h>

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class WWMainMenu;

class WWmainMenuPlayConfirmation : public Node
{
private:
    LayerColor*    _mBGLayer;
    MenuItemImage* yesBtn, *noBtn;
    
    WWmainMenuPlayConfirmation();
    void addUI();
    
    void onClickOnYesbtn(Ref* pSender);
    void onClickOnNobtn(Ref* pSender);
    
public:
    WWMainMenu* objref;
    static WWmainMenuPlayConfirmation* getConfirmationPopup();
    ~WWmainMenuPlayConfirmation();
    
};


#endif /* WWmainMenuPlayConfirmation_h */
