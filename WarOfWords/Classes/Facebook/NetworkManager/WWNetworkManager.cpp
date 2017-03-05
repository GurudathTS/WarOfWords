/*
 
 WWNetworkManager.hpp
 
 WWNetworkManager is singleton class.
 Which has callback (OnNetworkChangeCallback) method to pass information on network change.
 This is common manager class for IOS & Android.
 IOS uses Reachability class to detrmine the internet current status and change.
 Android uses Connectivity manager to detrmine current internet status.
 BroadcastReceiver used for determine change in network connection.
 Check for Http request with url for security connection available
 In order to communicate between IOS & Android uses bridge class namely ZinfinityIosInterface & ZinfinityAndroidInterface
 
 Note:
 For Android Network changes callback will occur more than once in some devices.
 Using boolean method we can avoid multiple callbacks.
 
 */

#include "WWNetworkManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #include "WWiOSInterface.h"
#endif

using namespace cocos2d;

static WWNetworkManager *_mSharedManager = nullptr;

WWNetworkManager* WWNetworkManager::sharedManager()
{
    if (!_mSharedManager)
    {
         _mSharedManager = new (std::nothrow) WWNetworkManager();
         _mSharedManager->retain();
    }
     
    return _mSharedManager;
}

WWNetworkManager::WWNetworkManager()
:_mDelegate(nullptr)
{
    
}

WWNetworkManager::~WWNetworkManager()
{
    _mDelegate = nullptr;
    _mSharedManager = nullptr;
}

#pragma mark - Init
void WWNetworkManager::initializeInternetCheckConnection()
{
    //Initialize the Notifier for Internet Connectivity
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        WWiOSInterfaceRef->initializeNetworkNotifier();
    #endif
    
    //Check Status of Internet
    bool isInterConnected = this->checkCurrentNetworkStatus();
    if (_mDelegate)
        _mDelegate(isInterConnected);
}

void WWNetworkManager::setDelegate(const std::function<void(bool)>& pCallback)
{
    _mDelegate = pCallback;
     initializeInternetCheckConnection();
}

#pragma mark - Network Status
bool WWNetworkManager::checkCurrentNetworkStatus()
{
    bool isConnected=false;
     
    return isConnected;
}

void WWNetworkManager::onNetworkChange(bool isInternetConnected)
{
    if (_mDelegate)
        checkInternetWithPing(isInternetConnected);
}

#pragma mark - Ping Request for Connection check
void WWNetworkManager::checkInternetWithPing(bool isInterConnected)
{
    if (isInterConnected)
    {
        //Make Http Request for Ping
        HttpRequest* request = new (std::nothrow) HttpRequest();
        request->setUrl("https://www.google.co.in");
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback(CC_CALLBACK_2(WWNetworkManager::onHttpRequestCompleted, this));
        HttpClient::getInstance()->send(request);
        request->release();
 
    }
    else
    {
        if (_mDelegate)
            _mDelegate(isInterConnected);
    }
}

void WWNetworkManager::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    bool isInterConnected=false;
    if (!response || !response->isSucceed())
    {
        isInterConnected = false;
    }
    else
    {
        isInterConnected = true;
    }
     
    if (_mDelegate)
        _mDelegate(isInterConnected);
}


