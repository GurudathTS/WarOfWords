/*
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE. 
 */

#import "Reachability.h"
#include "WWNetworkManager.h"

static Reachability*   mInstance = NULL;
@implementation Reachability
#pragma  mark - Singleton Class Implementation.
-(id)init
{
     self = [super init];
     if (self)
     {
          
     }
     return self;
}

+(id)alloc
{
     @synchronized([Reachability class])
     {
          NSAssert(mInstance == nil, @"Attempted to allocate a second instance of a Reachability Class.");
          return [super alloc];
     }
     return nil;
}


+(Reachability *)getInstance
{
     if (!mInstance)
          mInstance = [[Reachability alloc] init];
     return mInstance;
}

-(void)checkNetwork
{
     struct sockaddr_in zeroAddress;
     bzero(&zeroAddress, sizeof(zeroAddress));
     zeroAddress.sin_len = sizeof(zeroAddress);
     zeroAddress.sin_family = AF_INET;
     
     SCNetworkReachabilityRef _mReachabilityRef = SCNetworkReachabilityCreateWithAddress(kCFAllocatorDefault, (const struct sockaddr*)&zeroAddress);
     
     if(_mReachabilityRef != NULL)
     {
          //NetworkStatus retVal = NotReachable;
          SCNetworkReachabilityFlags flags;
          if (SCNetworkReachabilityGetFlags(_mReachabilityRef, &flags))
               [self checkNetworkFlag:flags];
          
          //Start Notification when network change...
          if(SCNetworkReachabilitySetCallback(_mReachabilityRef, ReachabilityCallback, NULL))
          {
               if(SCNetworkReachabilityScheduleWithRunLoop(_mReachabilityRef, CFRunLoopGetCurrent(),
                                                           kCFRunLoopDefaultMode))
               {
                    //return bool if need to know corotine is started or not...
               }
          }
          
          CFRelease(_mReachabilityRef);
     }
}

#pragma  mark - Network change callback
static void ReachabilityCallback(SCNetworkReachabilityRef target, SCNetworkReachabilityFlags flags, void* info)
{
     __block SCNetworkReachabilityFlags _tBlockedFlag = flags;
     dispatch_async(dispatch_get_main_queue(), ^{
          [[Reachability getInstance] checkNetworkFlag:_tBlockedFlag];
     });
}

-(void)checkNetworkFlag:(SCNetworkReachabilityFlags)flags
{
     if ((flags & kSCNetworkReachabilityFlagsConnectionRequired) == 0)
     {
          // if target host is reachable and no connection is required then we'll assume (for now) that your on Wi-Fi
          [self setNetworkFlag:TRUE];
     }
     else if ((((flags & kSCNetworkReachabilityFlagsConnectionOnDemand ) != 0) || (flags & kSCNetworkReachabilityFlagsConnectionOnTraffic) != 0))
     {
          // ... and the connection is on-demand (or on-traffic) if the calling application is using the CFSocketStream or higher APIs
          if ((flags & kSCNetworkReachabilityFlagsInterventionRequired) == 0)
          {
               // ... and no [user] intervention is needed
               [self setNetworkFlag:TRUE];
          }
     }
     else if ((flags & kSCNetworkReachabilityFlagsIsWWAN) == kSCNetworkReachabilityFlagsIsWWAN)
     {
          // ... but WWAN connections are OK if the calling application is using the CFNetwork (CFSocketStream?) APIs.
          [self setNetworkFlag:TRUE];
     }
     else
          [self setNetworkFlag:FALSE];
}

-(void)setNetworkFlag:(BOOL)pHasConnection
{
     WWNetworkManager::sharedManager()->onNetworkChange(pHasConnection);
}
@end
