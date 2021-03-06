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
using namespace std;

class LevelSelectScene : public cocos2d::CCLayerColor
{
private:
    string highScoreKey;
    int m_level;
    int page_num;
    int best_score[25];
    int min_score[25];
    void replayGame();
    void nextLevelGame();
    void startGame();
    void showNextPage();
    void showPrevPage();
    void hiddenStartMenu();
    CCMenuItemImage* createLevelImage(int level);
    
protected:
    
public:
    const static int tagStartMenuDialog = 100;
    const static int tagLevelSelectMenuDialog = 200;
    virtual bool initWithPage(int pageNum);
    static cocos2d::CCScene* scene();
    static cocos2d::CCScene* sceneWithPage(int pageNum);
    static LevelSelectScene* createWithPage(int pageNum);
    //CREATE_FUNC(LevelSelectScene);
    virtual void menuStartCallback(CCObject* pSender);
};

#endif /* defined(__Arrows__LevelSelectScene__) */
