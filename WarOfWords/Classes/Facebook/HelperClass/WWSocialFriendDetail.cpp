//
//  WWSocialFriendDetail.cpp
//
//  Created by Gurudath on
//
//

#include "WWSocialFriendDetail.h"
WWSocialFriendDetail::WWSocialFriendDetail(std::string pName
                                                         ,std::string pImageURL
                                                         ,std::string pID
                                           ,int pScore,std::string eMail)
:_mTexture(nullptr)
,_mDelegate(nullptr)

{
     _mName = pName;
     _mID = pID;
     _mImageURL = pImageURL;
     _mScore = pScore;
    _mEmail = eMail;
     loadURL();
}

WWSocialFriendDetail::~WWSocialFriendDetail()
{
    
}

WWSocialFriendDetail* WWSocialFriendDetail::getClone()
{
    WWSocialFriendDetail* _tReurnObject = new WWSocialFriendDetail(_mName
                                                                                 ,_mImageURL
                                                                                 ,_mID
                                                                                 ,_mScore,_mEmail);
    return _tReurnObject;
}

std::string WWSocialFriendDetail::fileNameFromUrl(std::string url)
{
     std::string name = url;
     name.erase( remove( name.begin(), name.end(), '/' ), name.end() );
     name.erase( remove( name.begin(), name.end(), ':' ), name.end() );
     return name;
}

void WWSocialFriendDetail::loadURL()
{
     // Save image file to device.
     std::string writablePath = FileUtils::getInstance()->getWritablePath();
     writablePath.append(fileNameFromUrl(_mImageURL));
     _mTexture = Director::getInstance()->getTextureCache()->addImage(writablePath.c_str());
     if (!_mTexture)
     {
          HttpRequest* request = new (std::nothrow) HttpRequest();
          request->setUrl(_mImageURL.c_str());
          request->setRequestType(HttpRequest::Type::GET);
          request->setResponseCallback(CC_CALLBACK_2(WWSocialFriendDetail::onHttpRequestCompleted, this));
          HttpClient::getInstance()->send(request);
          request->release();
     }
}

void WWSocialFriendDetail::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
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
     writablePath.append(fileNameFromUrl(_mImageURL));
     
     std::ofstream outfile(writablePath.c_str());
     for (unsigned int i = 0; i < buffer->size(); i++)
          outfile<<(*buffer)[i];
     outfile.close();
     
     _mTexture =Director::getInstance()->getTextureCache()->addImage(writablePath.c_str());
     if (_mTexture && _mDelegate)
          _mDelegate(_mTexture);
     _mDelegate = nullptr;
}

void WWSocialFriendDetail::setDelegate(const std::function<void(Texture2D*)> pCallback)
{
     _mDelegate = pCallback;
}
void WWSocialFriendDetail::removeDelegate()
{
     _mDelegate = nullptr;
}
