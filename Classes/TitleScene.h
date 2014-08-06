//
//  TitleScene.h
//  Arrows
//
//  Created by k_tetsuhiro on 2014/05/27.
//
//

#ifndef __Arrows__TitleScene__
#define __Arrows__TitleScene__

#include "cocos2d.h"

USING_NS_CC;

class TitleScene : public cocos2d::CCLayerColor
{
private:
    bool firstTimeGame;
    
protected:
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(TitleScene);
    virtual void menuStartCallback(CCObject* pSender);
    virtual void menuTutorCallback(CCObject* pSender);
    virtual void menuRankingCallback(CCObject* pSender);
};

#endif /* defined(__Arrows__TitleScene__) */
