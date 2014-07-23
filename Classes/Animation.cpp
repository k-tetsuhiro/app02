//
//  Animation.cpp
//  app02
//
//  Created by k_tetsuhiro on 2014/07/15.
//
//

#include "Animation.h"

CCFiniteTimeAction* Animation::titleCharaAction(float originSize)
{
    CCDelayTime* delay1 = CCDelayTime::create(1.3);
    CCScaleTo* scaleUp = CCScaleTo::create(0.2, originSize * 2);
    CCDelayTime* delay2 = CCDelayTime::create(0.1);
    CCScaleTo* scaleDown = CCScaleTo::create(0.2, originSize);
    
    return CCSequence::create(delay1, scaleUp, delay2, scaleDown, NULL);
}

CCFiniteTimeAction* Animation::clearCharaAction()
{
    CCDelayTime* delay1 = CCDelayTime::create(0.1);
    CCScaleTo* scaleUp = CCScaleTo::create(0.2, 1.1);
    CCDelayTime* delay2 = CCDelayTime::create(0.3);
    CCScaleTo* scaleDown = CCScaleTo::create(0.2, 0.7);
    
    return CCSequence::create(delay1, scaleUp, delay2, scaleDown, NULL);
}

CCFiniteTimeAction* Animation::tutorialArrowTouchAction(CCObject* target, SEL_CallFunc selector)
{
    CCRotateBy* rotate = CCRotateBy::create(0.3, 90);
    CCScaleTo* scaleUp = CCScaleTo::create( 0.15,1.8);
    CCScaleTo* scaleDown = CCScaleTo::create(0.15,1.0);
    CCSequence* seqScale = CCSequence::createWithTwoActions(CCEaseInOut::create(scaleUp, 2), CCEaseInOut::create(scaleDown, 2));
    CCSpawn* spaRotateAndScale = CCSpawn::createWithTwoActions(rotate, seqScale);
    CCCallFunc* func = CCCallFunc::create(target, selector);
    return CCSequence::create(spaRotateAndScale,func, NULL);
}