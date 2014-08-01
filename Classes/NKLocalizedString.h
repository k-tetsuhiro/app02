//
//  NKLocalizedString.h
//  app02
//
//  Created by k_tetsuhiro on 2014/08/01.
//
//

#ifndef __app02__NKLocalizedString__
#define __app02__NKLocalizedString__

#include "cocos2d.h"

USING_NS_CC;

class  NKLocalizedString:
public cocos2d::CCObject
{
public:
    static void init();
    static const char* LocalizedString(const char* searchKey, const char* comment);
    
};

#endif /* defined(__app02__NKLocalizedString__) */
