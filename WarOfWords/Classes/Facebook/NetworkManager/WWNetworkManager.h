
/*
 
 WWNetworkManager.h
 
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



#ifndef WWNetworkManager_h
#define WWNetworkManager_h

#include "cocos2d.h"
using namespace cocos2d;

#include "network/HttpRequest.h"
#include "network/HttpClient.h"
using namespace cocos2d::network;
class WWNetworkManager : public cocos2d::Ref
{
public:
    
    ~WWNetworkManager();
    
    static  WWNetworkManager* sharedManager(void);
    
    //Initialize methods
     void setDelegate(const std::function<void(bool)>& pCallback);
    
    //Network status
    bool checkCurrentNetworkStatus();
    void onNetworkChange(bool pIsInternetConnected);
    
private:
    WWNetworkManager();
    void initializeInternetCheckConnection();
     
    //Http Request
    void checkInternetWithPing(bool pIsInternetConnected);
    void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    std::function<void(bool)> _mDelegate;
};

#endif /* NTDataManagerClass_h */
