//
//  TitleScene.cpp
//  Arrows
//
//  Created by k_tetsuhiro on 2014/05/27.
//
//

#include "TitleScene.h"
#include "cocos2d.h"
#include "LevelSelectScene.h"
#include "ConstCommon.h"
#include "Animation.h"
#include "Tutorial.h"
#include "NativeCodeLauncher.h"
#include "DebugBoot.h"


USING_NS_CC;

CCScene* TitleScene::scene(){
    CCScene* scene = CCScene::create();
    TitleScene* layer = TitleScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool TitleScene::init()
{
    
    //debug
    this->debugBoot = true;
    
    // 初期化色を変更
    if (!CCLayerColor::initWithColor(ccc4(0xFF,0xEF,0xFF,0xFF))) //RGBA
    {
        return false;
    }
    
    //GameCenterにログイン
    Cocos2dExt::NativeCodeLauncher::loginGameCenter();
    
    //一回もクリアしたことなければチュートリアル表示
     CCUserDefault*  userDefault = CCUserDefault::sharedUserDefault();
    string tutorialKey = ConstCommon::getTutorialKey();
    this->firstTimeGame = ! userDefault->getBoolForKey(tutorialKey.c_str());

    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pA = CCSprite::create("logo_A.png");
    float originSize = ((size.width * 0.937) / 6) / pA->getContentSize().width;
    
    pA->setPosition(ccp(size.width * 0.1, size.height * 0.8));
    //pA->setScale(0.6);
    pA->setScale(originSize);
    pA->runAction(Animation::titleCharaAction(originSize));
    this->addChild(pA);
    
    CCSprite* pR = CCSprite::create("logo_R.png");
    pR->setPosition(ccp(size.width * 0.26, size.height * 0.8));
    //pR->setScale(0.6);
    pR->setScale(originSize);
    pR->runAction(CCSequence::create(CCDelayTime::create(0.05),Animation::titleCharaAction(originSize),NULL));
    this->addChild(pR);
    
    CCSprite* pR2 = CCSprite::create("logo_R.png");
    pR2->setPosition(ccp(size.width * 0.42, size.height * 0.8));
    //pR2->setScale(0.6);
    pR2->setScale(originSize);
    pR2->runAction(CCSequence::create(CCDelayTime::create(0.1),Animation::titleCharaAction(originSize),NULL));
    this->addChild(pR2);
    
    CCSprite* pO = CCSprite::create("logo_O.png");
    pO->setPosition(ccp(size.width * 0.58, size.height * 0.8));
    //pO->setScale(0.6);
    pO->setScale(originSize);
    pO->runAction(CCSequence::create(CCDelayTime::create(0.15),Animation::titleCharaAction(originSize),NULL));
    this->addChild(pO);
    
    CCSprite* pW = CCSprite::create("logo_W.png");
    pW->setPosition(ccp(size.width * 0.74, size.height * 0.8));
    //pW->setScale(0.6);
    pW->setScale(originSize);
    pW->runAction(CCSequence::create(CCDelayTime::create(0.2),Animation::titleCharaAction(originSize),NULL));
    this->addChild(pW);
    
    CCSprite* pS = CCSprite::create("logo_S.png");
    pS->setPosition(ccp(size.width * 0.9, size.height * 0.8));
    //pS->setScale(0.6);
    pS->setScale(originSize);
    pS->runAction(CCSequence::create(CCDelayTime::create(0.25),Animation::titleCharaAction(originSize),NULL));
    this->addChild(pS);


    
    
    
    //start button
    CCMenuItemImage* pStartItem;
    pStartItem = CCMenuItemImage::create("button1.png", "button1.png",this,menu_selector(TitleScene::menuStartCallback));
    pStartItem->setPosition(ccp(size.width * 0.5, size.height * 0.3));
    pStartItem->setScale((size.width * 0.4) / pStartItem->getContentSize().width);
    
    CCLabelTTF* startLabel;
    startLabel = CCLabelTTF::create("PLAY", "Arial", 30.0);
    
    CCSize pStartItemSize = pStartItem->getContentSize();
    startLabel->setPosition(ccp(pStartItemSize.width / 2 ,pStartItemSize.height / 2));
    pStartItem->addChild(startLabel);


    
    CCMenu* pMenu = CCMenu::create(pStartItem,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
    
    
    if(! this->firstTimeGame){
        //チュートリアルを再度受けられるようにボタン生成
        //start button
        CCMenuItemImage* pTutorItem;
        pTutorItem = CCMenuItemImage::create("button2.png", "button2.png",this,menu_selector(TitleScene::menuTutorCallback));
        pTutorItem->setPosition(ccp(size.width * 0.5, size.height * 0.4));
        pTutorItem->setScale((size.width * 0.4) / pTutorItem->getContentSize().width);
        
        CCLabelTTF* tutorLabel;
        tutorLabel = CCLabelTTF::create("TUTORIAL", "Arial", 30.0);
        
        CCSize pTutorItemSize = pTutorItem->getContentSize();
        tutorLabel->setPosition(ccp(pTutorItemSize.width / 2 ,pTutorItemSize.height / 2));
        pTutorItem->addChild(tutorLabel);
        pMenu->addChild(pTutorItem);
        
        //ランキングのボタン生成
        if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS){
            CCMenuItemImage* pRankingItem;
            pRankingItem = CCMenuItemImage::create("button3.png", "button3.png",this,menu_selector(TitleScene::menuRankingCallback));
            pRankingItem->setPosition(ccp(size.width * 0.5, size.height * 0.5));
            pRankingItem->setScale((size.width * 0.4) / pRankingItem->getContentSize().width);
            
            CCLabelTTF* rankingLabel;
            rankingLabel = CCLabelTTF::create("ACHIVEMENT", "Arial", 30.0);
            
            CCSize pRankingItemSize = pRankingItem->getContentSize();
            rankingLabel->setPosition(ccp(pRankingItemSize.width / 2 ,pRankingItemSize.height / 2));
            pRankingItem->addChild(rankingLabel);
            pMenu->addChild(pRankingItem);

        }

    }
    
    //debug
    if(this->debugBoot){
        CCMenuItemImage* pDebugBootItem;
        pDebugBootItem = CCMenuItemImage::create("button3.png", "button3.png",this,menu_selector(TitleScene::menuDebugBootCallback));
        pDebugBootItem->setPosition(ccp(size.width * 0.5, size.height * 0.2));
        pDebugBootItem->setScale((size.width * 0.4) / pDebugBootItem->getContentSize().width);
        
        CCLabelTTF* debugBootLabel;
        debugBootLabel = CCLabelTTF::create("DEBUG BOOT", "Arial", 30.0);
        
        debugBootLabel->setPosition(ccp(pDebugBootItem->getContentSize().width / 2 ,pDebugBootItem->getContentSize().height / 2));
        pDebugBootItem->addChild(debugBootLabel);
        pMenu->addChild(pDebugBootItem);

    }
    
    return true;
    
}


void TitleScene::menuStartCallback(CCObject *pSender)
{
    
    CCScene* scene;
    //一回もクリアしたことなければチュートリアル表示
    if(this->firstTimeGame){
        scene = Tutorial::scene();
    }else{
        scene = LevelSelectScene ::scene();
    }
    
    CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
    CCDirector::sharedDirector()->replaceScene(tran);
}

void TitleScene::menuTutorCallback(CCObject *pSender)
{
    
    CCScene* scene;
    scene = Tutorial::scene();
    CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
    CCDirector::sharedDirector()->replaceScene(tran);
}

void TitleScene::menuRankingCallback(CCObject *pSender)
{
    Cocos2dExt::NativeCodeLauncher::openAchievement();
}

void TitleScene::menuDebugBootCallback(cocos2d::CCObject *pSender)
{
    
    CCScene* scene;
    scene = DebugBoot::scene();
    CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
    CCDirector::sharedDirector()->replaceScene(tran);
}

