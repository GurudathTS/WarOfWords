//
//  WWSocialFriendDetail.h
//  War of Words
//
//  Created by Gurudath
//
//

#ifndef WWSocialFriendDetail_h
#define WWSocialFriendDetail_h

#include "cocos2d.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
using namespace cocos2d::network;
using namespace cocos2d;

#include <fstream>
#include <string>
using namespace std;

class WWSocialFriendDetail : public Ref
{
private:
     CC_SYNTHESIZE_READONLY(std::string, _mName, Name);
     CC_SYNTHESIZE_READONLY(std::string, _mImageURL, ImageURL);
     CC_SYNTHESIZE_READONLY(std::string, _mID, ID);
     CC_SYNTHESIZE_READONLY(int, _mScore, Score);
     CC_SYNTHESIZE_READONLY(Texture2D*, _mTexture, Texture);
     
private:
     std::function<void(Texture2D*)> _mDelegate;
     
     void loadURL();
     void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
     std::string fileNameFromUrl(std::string url);
    
public:
     WWSocialFriendDetail(std::string pName
                                 ,std::string pImageURL
                                 ,std::string pID
                                 ,int pScore);
     virtual ~WWSocialFriendDetail();
     WWSocialFriendDetail* getClone();
     bool operator<(WWSocialFriendDetail* rhs) { return _mScore < rhs->getScore();}
     void setDelegate(const std::function<void(Texture2D*)> pCallback);
     void removeDelegate();
};

#endif /* WWSocialFriendDetail_h */
