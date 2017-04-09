//
//  WWGameUtility.cpp
//  WarOfWords
//
//  Created by Manjunatha Reddy on 4/8/17.
//
//

#include "WWGameUtility.h"
using namespace cocos2d::network;



WWGameUtility::WWGameUtility(void)
{ }

WWGameUtility::~WWGameUtility(void)
{ }


#pragma mark - Response
void  WWGameUtility::getResponseBuffer(void *data , rapidjson::Document &  document)
{
    cocos2d::network::HttpResponse *response = (cocos2d::network::HttpResponse*)data;
    
    
    if (!response)
    {
        return ;
    }
    
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        
    }
    
    int statusCode = response->getResponseCode();
    char statusString[256] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    //m_labelStatusCode->setString(statusString);
    CCLOG("response code: %d", statusCode);
    
    
    
    if (!response->isSucceed())
    {
        CCLOG("response failed");
        CCLOG("error buffer: %s", response->getErrorBuffer());
        
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    
    char * charbuffer =new char[buffer->size()+1];
    
    
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        charbuffer[i]=(*buffer)[i];
    }
    
    charbuffer[buffer->size()]=0;
    
    
    //CCLog("{url in buffer is %s",response->getHttpRequest()->getUrl());
    //CCLog("%s completed", response->getHttpRequest()->getTag());
    CCLOG("Http Test, dump data:%s ",charbuffer);
    
    
    document.Parse<0>(charbuffer);
    delete[] charbuffer;
    
    
}
