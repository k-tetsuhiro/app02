//
//  Animation.h
//  app02
//
//  Created by k_tetsuhiro on 2014/07/15.
//
//

#ifndef __app02__Animation__
#define __app02__Animation__


#include "cocos2d.h"

USING_NS_CC;

class Animation
{
public:
    static CCFiniteTimeAction* titleCharaAction(float originSize);
    static CCFiniteTimeAction* clearCharaAction();
    static CCFiniteTimeAction* tutorialArrowTouchAction(CCObject* target, SEL_CallFunc selector);
};

#endif /* defined(__app02__Animation__) */
