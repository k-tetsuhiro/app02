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
private:
    CCMenu* pMenuScene1;
    CCMenu* pMenuScene2;
    
    void showScene1();
    void doScene1();
    void endScene1();
    void showScene2();
    void doScene2();
    void endScene2();
    void endTutorial();
    
    const static int TAG_SCENE_1_ITEM_1 = 101;
    const static int TAG_SCENE_2_ITEM_1 = 201;
    
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Tutorial);
};

#endif /* defined(__app02__Tutorial__) */
