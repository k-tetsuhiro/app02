//
//  ResultScene.cpp
//  Arrows
//
//  Created by k_tetsuhiro on 2014/06/18.
//
//

#include "ResultScene.h"
#include "ConstCommon.h"
#include "MainGameScene.h"
#include "TitleScene.h"
#include "NativeCodeLauncher.h"

USING_NS_CC;
using namespace std;

//const
int ResultScene::max_level = 15;


CCScene* ResultScene::sceneWithParam(int level, int minScore, int resultScore)
{
    CCScene* scene = CCScene::create();
    ResultScene* layer = ResultScene::createWithParam(level,minScore,resultScore);
    scene->addChild(layer);
    
    return scene;
}

ResultScene* ResultScene::createWithParam(int level, int minScore, int resultScore)
{
    ResultScene *pRet = new ResultScene();
    if (pRet && pRet->initWithParam(level,minScore,resultScore))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool ResultScene::initWithParam(int level, int minScore, int resultScore)
{
    
    // 初期化色を変更
    if (!CCLayerColor::initWithColor(ccc4(0xF8,0xEC,0xDE,0xFF))) //RGBA
    {
        return false;
    }
    
    //初期化に関するものを書く
    m_level = level;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    //RESULTの文字
    CCLabelTTF* resultLabel;
    resultLabel = CCLabelTTF::create("RESULT", "Arial", 100.0);
    resultLabel->setColor(ccc3(0, 0, 0));
    resultLabel->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.9));
    this->addChild(resultLabel);
    
    
    
    //今回のスコア
    CCString* resultScoreStr = CCString::createWithFormat("TOUCH : %d",resultScore);
    CCLabelTTF* resultScoreLabel;
    resultScoreLabel = CCLabelTTF::create(resultScoreStr->getCString(), "Arial", 60.0);
    resultScoreLabel->setColor(ccc3(0, 0, 0));
    resultScoreLabel->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.6));
    this->addChild(resultScoreLabel);
    
    //今回のLv
    CCString* levelStr = CCString::createWithFormat("Lv : %d",level);
    CCLabelTTF* levelLabel;
    levelLabel = CCLabelTTF::create(levelStr->getCString(), "Arial", 60.0);
    levelLabel->setColor(ccc3(0, 0, 0));
    levelLabel->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.7));
    this->addChild(levelLabel);
    
    int rank;
    
    if(minScore >= resultScore){
        rank = 3;
        
        //Game　Center
        Cocos2dExt::NativeCodeLauncher::postAchievement(level, 100);
    }else if( minScore <= resultScore + 8){
        rank = 2;
    }else{
        rank = 1;
    }
    
    for (int i=0; i < rank; i++) {
        CCSprite* pStar = CCSprite::create("star.png");
        pStar->setScale(0.2);
        
        float posX;
        if(i == 0){
            posX = 0.3;
        }else if(i == 1){
            posX = 0.5;
        }else{
            posX = 0.7;
        }
        pStar->setPosition(ccp(winSize.width * posX, winSize.height * 0.8));
        this->addChild(pStar);
    }
    
    
    //リトライボタン
    CCMenuItemImage* pRetryItem;
    pRetryItem = CCMenuItemImage::create("reload.png", "reload.png",this,menu_selector(ResultScene::replayGame));
    pRetryItem->setScale(0.3);
    pRetryItem->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.3));
    
    //次のレベルへ
    CCMenuItemImage* pNextLevelItem;
    if (m_level == max_level){
        pNextLevelItem = CCMenuItemImage::create("next.png", "next.png",this,menu_selector(ResultScene::showTitleMenu));
    }else{
        pNextLevelItem = CCMenuItemImage::create("next.png", "next.png",this,menu_selector(ResultScene::nextLevelGame));
    }
    pNextLevelItem->setScale(0.3);
    pNextLevelItem->setPosition(ccp(winSize.width * 0.7, winSize.height * 0.3));
    
    
    CCMenu* pMenu = CCMenu::create(pRetryItem,pNextLevelItem,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);

    return true;
    
}

void ResultScene::replayGame()
{
    CCScene* scene = MainGameScene ::sceneWithLevel(m_level);
    CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
    CCDirector::sharedDirector()->replaceScene(tran);
    
}

void ResultScene::nextLevelGame()
{
    CCScene* scene = MainGameScene ::sceneWithLevel(m_level+1);
    CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
    CCDirector::sharedDirector()->replaceScene(tran);
    
}

void ResultScene::showTitleMenu()
{
    CCScene* scene = TitleScene::scene();
    CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
    CCDirector::sharedDirector()->replaceScene(tran);
    
}

