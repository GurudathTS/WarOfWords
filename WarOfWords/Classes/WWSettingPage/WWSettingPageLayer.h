//
//  WWSettingPageLayer.h
//  WarOfWords
//
//  Created by Gurudath on 5/8/17.
//
//

#ifndef WWSettingPageLayer_h
#define WWSettingPageLayer_h

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class WWMainMenu;
class WWSettingsPannel : public Node
{
private:
    LayerColor*    _mBGLayer;
    MenuItemToggle* musinBtn, *soundbtn,*notificationBtn;
    MenuItemImage* doneBtn;

    WWSettingsPannel();
    void addUI();
    
    void onClickOnMusicbtn(Ref* pSender);
    void onClickOnSoundbtn(Ref* pSender);
    void onClickOnNotificationbtn(Ref* pSender);
    void onClickOnDonebtnBtn(Ref* pSender);
   
public:
    static WWSettingsPannel* getSettingsBtn();
    ~WWSettingsPannel();
    WWMainMenu* mainMenuRef;

    
};


#endif /* WWSettingPageLayer_h */
