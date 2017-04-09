//
//  WWLoginScreen.cpp
//  WarOfWords
//
//  Created by Gurudath on 3/17/17.
//
//

#include "WWLoginScreen.h"
#include "WWSocialManager.h"
#include "WWSocialFriendDetail.h"
#include "WWGameConstant.h"

Scene* WWLoginScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WWLoginScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
#pragma mark - Init
// on "init" you need to initialize your instance
bool WWLoginScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    addChild(WWSocialManagerRef);
    WWSocialManagerRef->initWithEnum(enumSocialSharingType::kFacebook);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Login Screen", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // add a "close" icon to exit the progress. it's an autorelease object
    loginBtn = MenuItemLabel::create(Label::createWithTTF("Login", "fonts/Marker Felt.ttf", 40) , CC_CALLBACK_1(WWLoginScreen::onClickOnLogin, this));
    
    loginBtn->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height/6));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(loginBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //Check for Facebook Login
    if (WWSocialManagerRef->getFacebookLoggedIn())
    {
        loginBtn->setString("Logout");
    }
    
    return true;
}

void WWLoginScreen::onClickOnLogin(Ref* pSender)
{

    if(WWSocialManagerRef->getFacebookLoggedIn())
    {
         WWSocialManagerRef->logOut(enumSocialSharingType::kFacebook);
    }
    else
    {
        WWSocialManagerRef->setCallback(CC_CALLBACK_1(WWLoginScreen::afterLoginCompleted, this));
        WWSocialManagerRef->logIn(enumSocialSharingType::kFacebook);
        log("......Login .. ....");
    }
}

void WWLoginScreen::afterLoginCompleted(bool pIsDone)
{
    //Fetch Current User Detail
    log("Current USer Info %s",WWSocialManagerRef->currentLoginUserDetail->getName().c_str());

}

void WWLoginScreen::afterFetchUserFriendDetail(bool pIsDone)
{
}
#pragma mark - Login API
void WWLoginScreen::loginToServer()
{
    
//http: //52.24.37.30/wow/wowapi/api/signin?user_id=&facebook_id=1424&email=email@email.com&password=123456&name=Ganesh&gender=male&country=US&facebook_thumbnail=profile.ak.fbcdn.net/hprofile-ak-ash3&ios_push_id=3b989a98d7efe


    
    HttpRequest* request = new (std::nothrow) HttpRequest();
    std::string url=BASE_URL;
    
    url=url+"signin?";
    
    url =url+"user_id"+"="+""+"&";
    
    url=url+"facebook_id"+"="+"100001527270712"+"&";
    
    url=url+"email"+"="+"email@email.com"+"&";

    url=url+"password"+"="+"hgjg"+"&";
    
    
    url=url+"name"+"="+"kfkfk"+"&";
    
    url=url+"gender"+"="+"male"+"&";
    
    url=url+"country"+"="+"ud"+"&";
    
    url=url+"facebook_thumbnail"+"="+"jkk"+"&";
    
    url=url+"ios_push_id"+"="+"j89jj";

    
    
    request->setUrl(url.c_str());
    CCLOG("%s",request->getUrl());
    request->setRequestType(HttpRequest::Type::GET);
    
    
    request->setResponseCallback(CC_CALLBACK_2(WWLoginScreen::onLoginRequestCompleted, this));
    request->setTag("SignIN");
    HttpClient::getInstance()->send(request);
    request->release();
    
}
void WWLoginScreen::onLoginRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    rapidjson::Document document;
    WWGameUtility::getResponseBuffer(response, document);
    if(!document.IsNull())
    {
        
    }
    
}
