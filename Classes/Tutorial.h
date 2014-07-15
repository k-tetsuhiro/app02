//
//  Tutorial.h
//  app02
//
//  Created by k_tetsuhiro on 2014/07/15.
//
//

#ifndef __app02__Tutorial__
#define __app02__Tutorial__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Tutorial : public cocos2d::CCLayerColor
{
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Tutorial);
};

#endif /* defined(__app02__Tutorial__) */
