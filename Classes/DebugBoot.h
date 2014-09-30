//
//  DebugBoot.h
//  app02
//
//  Created by k_tetsuhiro on 9/5/14.
//
//

#ifndef __app02__DebugBoot__
#define __app02__DebugBoot__


#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class DebugBoot : public cocos2d::CCLayerColor
{
private:
    
    // ##### const #####
    const static int ROW_NUM = 5;
    const static int COL_NUM = 5;
    
    // ##### method #####
    void makeArrows();
    
protected:
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(DebugBoot);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    
    
};

#endif /* defined(__app02__DebugBoot__) */
