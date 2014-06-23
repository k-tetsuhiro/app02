//
//  Arrow.h
//  Arrows
//
//  Created by k_tetsuhiro on 2014/05/22.
//
//

#ifndef __Arrows__Arrow__
#define __Arrows__Arrow__

#include "cocos2d.h"

USING_NS_CC;

class Arrow : public cocos2d::CCNode
{
private:
    CCSprite* pArrow;
    CCSprite* pArrowOn;
    CCSprite* pArrowOff;
    bool onFlag;
    int direction;
    
protected:
    
public:
    static Arrow* create();
    void onFrontArrowSprite(CCSprite *pArrow);
    void setArrowOnSprite(CCSprite *pArrow);
    void setArrowOffSprite(CCSprite *pArrow);
    void setDirection(int direction);
    
    void onTouchArrow();
    void reverseArrow();
    void rotateArrow();
    bool getOnFlag();
    CCSprite* getArrowSprite();
    CCSprite* getArrowOnSprite();
    CCSprite* getArrowOffSprite();
    int getDirection();
    
    
};

#endif /* defined(__Arrows__Arrow__) */
