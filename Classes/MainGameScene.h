//
//  MainGameScene.h
//  Arrows
//
//  Created by k_tetsuhiro on 2014/05/20.
//
//

#ifndef __Arrows__MainGameScene__
#define __Arrows__MainGameScene__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class MainGameScene : public cocos2d::CCLayerColor
{
private:
    
    int m_level;
    int totalGameCount;
    float gameTime;
    int minimamCount;
    string highScoreKey;
    bool endFlag;
    bool isHighScore;
    bool isResume;
    
    // ###### method #######
    void showBackgroud();
    void makeArrows();
    void endJudgemnet();
    void endAnimation();
    void showGameCountLabel();
    void makeRetryButton();
    void makeClearDaialog();
    void makeResumeDaialog();
    void tapRetryButton();
    void tapTitleButton();
    void doRetry();
    void showClearDialog();
    void showCountDown();
    void showStartInfo();
    void showGametimeLabel();
    void showMinimamCount();
    void startGame();
    void measureGameTime(float fDelta);
    void showResumeDialog();
    void returnMainGame();
    
    // ##### const #####
    const static int ROW_NUM = 5;
    const static int COL_NUM = 5;
    const static int tagGametimeLabel = 100;
    const static int tagRetryButton = 200;
    const static int tagClearDialog = 300;
    const static int tagMinimamCountLabel = 400;
    const static int tagGameCountLavel = 500;
    const static int tagStartInfo = 600;
    const static int tagTouchWaku = 700;
    const static int tagResumeDialog = 800;
    
    // ##### Z-order ######
    const static int Z_ORDER_ARROW = 100;
    const static int Z_ORDER_RESUME_DIALOG = 200;
    const static int Z_ORDER_CLEAR_DIALOG = 200;
    
    
    
    
    
public:
    static cocos2d::CCScene* scene();
    
    virtual bool initWithLevel(int level);
    //CREATE_FUNC(MainGameScene);
    static cocos2d::CCScene* sceneWithLevel(int level);
    static MainGameScene* createWithLevel(int level);
    //static MainGameScene* create();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void onEnterTransitionDidFinish();
};

#endif /* defined(__Arrows__MainGameScene__) */
