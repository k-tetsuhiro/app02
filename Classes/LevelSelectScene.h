//
//  LevelSelectScene.h
//  Arrows
//
//  Created by k_tetsuhiro on 2014/06/19.
//
//

#ifndef __Arrows__LevelSelectScene__
#define __Arrows__LevelSelectScene__

#include "cocos2d.h"

USING_NS_CC;

class LevelSelectScene : public cocos2d::CCLayerColor
{
private:
    int m_level;
    void replayGame();
    void nextLevelGame();
    
protected:
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(LevelSelectScene);
    virtual void menuStartCallback(CCObject* pSender);
};

#endif /* defined(__Arrows__LevelSelectScene__) */
