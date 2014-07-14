//
//  ResultScene.h
//  Arrows
//
//  Created by k_tetsuhiro on 2014/06/18.
//
//

#ifndef __Arrows__ResultScene__
#define __Arrows__ResultScene__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class ResultScene : public cocos2d::CCLayerColor
{
private:
    static int max_level;//Lv増えたら更新する
    int m_level;
    void replayGame();
    void nextLevelGame();
    void showTitleMenu();
    
protected:
    
public:
    virtual bool initWithParam(int level,int minScore ,int resultScore);
    static cocos2d::CCScene* sceneWithParam(int level,int minScore ,int resultScore);
    static ResultScene* createWithParam(int level,int minScore ,int resultScore);
};


#endif /* defined(__Arrows__ResultScene__) */
