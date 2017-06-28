//
//  WWPlayerInfo.cpp
//  WarOfWords
//
//  Created by Gurudath on 6/17/17.
//
//

#include "WWPlayerInfo.h"

using namespace cocos2d;

static WWPlayerInfo *_mInstance = nullptr;
WWPlayerInfo* WWPlayerInfo::getInstance()
{
    if (!_mInstance)
    {
        _mInstance = new (std::nothrow) WWPlayerInfo();
        _mInstance->retain();
    }
    
    return _mInstance;
}
WWPlayerInfo::WWPlayerInfo()
:_mDelegate(nullptr)
{
    initializeUserInfo("","", "", "");
    initializeOpponentinfo("","", "", "");
}

WWPlayerInfo::~WWPlayerInfo()
{
    
}

#pragma mark - Initialize User Info
void WWPlayerInfo::initializeUserInfo(std::string pUserName,std::string pUserId, std::string pUserProfilePicture, std::string pUserHealthBar)
{
    _mCurrentUserName = pUserName;
    _mCurrentUserProfilePtcture = pUserProfilePicture;
    _mCurrentUserHealthBar = pUserHealthBar;
    _mCurrentId = pUserId;
    
    loadUserProfileURL();
    
}

void WWPlayerInfo::updateUserName(std::string pUserName)
{
    _mCurrentUserName = pUserName;
}

void WWPlayerInfo::updateProfilePicture(std::string pProfilePictureUrl)
{
    _mCurrentUserProfilePtcture = pProfilePictureUrl;
    loadUserProfileURL();
}

void WWPlayerInfo::updateHealthBar(std::string pHealthBar)
{
    _mCurrentUserHealthBar = pHealthBar;
}


std::string WWPlayerInfo::fileNameFromUrl(std::string url)
{
    std::string name = url;
    name.erase( remove( name.begin(), name.end(), '/' ), name.end() );
    name.erase( remove( name.begin(), name.end(), ':' ), name.end() );
    return name;
}

void WWPlayerInfo::loadUserProfileURL()
{
    if(_mCurrentUserProfilePtcture == "")
    {
        _mCurrentProfilePictureTexture = nullptr;
        return;
    }
    
    // Save image file to device.
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    writablePath.append(fileNameFromUrl(_mCurrentUserProfilePtcture));
    _mCurrentProfilePictureTexture = Director::getInstance()->getTextureCache()->addImage(writablePath.c_str());
    if (!_mCurrentProfilePictureTexture)
    {
        HttpRequest* request = new (std::nothrow) HttpRequest();
        request->setUrl(_mCurrentUserProfilePtcture.c_str());
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback(CC_CALLBACK_2(WWPlayerInfo::onHttpRequestCompletedUser, this));
        HttpClient::getInstance()->send(request);
        request->release();
    }
}

void WWPlayerInfo::onHttpRequestCompletedUser(HttpClient *sender, HttpResponse *response)
{
    //Response data
    if (!response)
    {
        log("No Response");
        return;
    }
    
    if (!response->isSucceed())
    {
        log("response failed");
        log("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    std::vector< char> *buffer = response->getResponseData();
    // Save image file to device.
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    writablePath.append(fileNameFromUrl(_mCurrentUserProfilePtcture));
    
    std::ofstream outfile(writablePath.c_str());
    for (unsigned int i = 0; i < buffer->size(); i++)
        outfile<<(*buffer)[i];
    outfile.close();
    
    _mCurrentProfilePictureTexture =Director::getInstance()->getTextureCache()->addImage(writablePath.c_str());
    
}

#pragma mark - Initialize Opponent User info
void WWPlayerInfo::initializeOpponentinfo(std::string pOpponentName,std::string pUserId, std::string pOpponentProfilePicture, std::string pOpponentHealthBar)
{
    _mOpponentUserName = pOpponentName;
    _mOpponentUserHealthBar = pOpponentHealthBar;
    _mOpponentUserProfilePtcture = pOpponentProfilePicture;
    _mOpponentUserId = pUserId;
    
    loadOpponentProfileURL();
}

void WWPlayerInfo::updateOpponentUserName(std::string pUserName)
{
    _mOpponentUserName = pUserName;
}

void WWPlayerInfo::updateOpponentProfilePicture(std::string pProfilePictureUrl)
{
    _mOpponentUserProfilePtcture = pProfilePictureUrl;
    loadOpponentProfileURL();
}

void WWPlayerInfo::updateOpponentHealthBar(std::string pHealthBar)
{
    _mOpponentUserHealthBar = pHealthBar;
}

void WWPlayerInfo::updateOpponentUserID(std::string pUserId)
{
    _mOpponentUserId = pUserId;
}

void WWPlayerInfo::updateChallengeID(std::string pChallengeId)
{
    _mChallengeId = pChallengeId;
}

void WWPlayerInfo::updateTurnUserID(std::string pTurnUserID)
{
    _mturnUserId = pTurnUserID;
}


void WWPlayerInfo::loadOpponentProfileURL()
{
    
    if(_mOpponentUserProfilePtcture == "")
    {
        _mOpponentProfilePictureTexture = nullptr;
        return;
    }
    
    // Save image file to device.
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    writablePath.append(fileNameFromUrl(_mOpponentUserProfilePtcture));
    _mOpponentProfilePictureTexture = Director::getInstance()->getTextureCache()->addImage(writablePath.c_str());
    if (!_mOpponentProfilePictureTexture)
    {
        HttpRequest* request = new (std::nothrow) HttpRequest();
        request->setUrl(_mOpponentUserProfilePtcture.c_str());
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback(CC_CALLBACK_2(WWPlayerInfo::onHttpRequestCompletedOpponent, this));
        HttpClient::getInstance()->send(request);
        request->release();
    }
}

void WWPlayerInfo::onHttpRequestCompletedOpponent(HttpClient *sender, HttpResponse *response)
{
    //Response data
    if (!response)
    {
        log("No Response");
        return;
    }
    
    if (!response->isSucceed())
    {
        log("response failed");
        log("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    std::vector< char> *buffer = response->getResponseData();
    // Save image file to device.
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    writablePath.append(fileNameFromUrl(_mOpponentUserProfilePtcture));
    
    std::ofstream outfile(writablePath.c_str());
    for (unsigned int i = 0; i < buffer->size(); i++)
        outfile<<(*buffer)[i];
    outfile.close();
    
    _mOpponentProfilePictureTexture =Director::getInstance()->getTextureCache()->addImage(writablePath.c_str());
    
}

#pragma mark - Call Backs
void WWPlayerInfo::setCallback(const std::function<void(bool)> pCallback)
{
    _mDelegate = pCallback;
}

void WWPlayerInfo::executeCallback(bool pResult)
{
    if (_mDelegate)
        _mDelegate(pResult);
    
    _mDelegate = nullptr;
}
