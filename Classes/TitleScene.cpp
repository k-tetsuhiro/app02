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


USING_NS_CC;

CCScene* TitleScene::scene(){
    CCScene* scene = CCScene::create();
    TitleScene* layer = TitleScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool TitleScene::init()
{
    /*
    if(!CCLayer::init()){
        return false;
    }
     */
    
    // 初期化色を変更
    //if (!CCLayerColor::initWithColor(ccc4(83, 166, 103, 255))) //RGBA
    if (!CCLayerColor::initWithColor(ccc4(255, 254, 223, 255))) //RGBA
    {
        return false;
    }
    
    srand((unsigned)time(NULL));
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    /*
    //BG start
    if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()){
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("titleBgm.mp3", true);
    }
    
    //background
    CCSprite* pBG = CCSprite::create("title_bg.png");
    pBG->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(pBG);
    
    CCSize bgSize = pBG->getContentSize();
    
    //cat eyes
    CCSprite* pLeftEye = CCSprite::create("cateye.png");
    pLeftEye->setPosition(ccp(bgSize.width * 0.43, bgSize.height * 0.28));
    pLeftEye->runAction(CCRepeatForever::create(CCRotateBy::create(1, 360)));
    pBG->addChild(pLeftEye);
    
    CCSprite* pRightEye = CCSprite::create("cateye.png");
    pRightEye->setPosition(ccp(bgSize.width * 0.54, bgSize.height * 0.28));
    pRightEye->runAction(CCRepeatForever::create(CCRotateBy::create(1, 360)));
    pBG->addChild(pRightEye);
    */
    
    /*
    //title
    CCSprite* pTitle = CCSprite::create("title.png");
    pTitle->setPosition(ccp(size.width * 0.5, size.height * 0.6));
    this->addChild(pTitle);
     */
    
    CCSprite* pA = CCSprite::create("logo_A.png");
    pA->setPosition(ccp(size.width * 0.1, size.height * 0.8));
    pA->setScale(0.6);
    this->addChild(pA);
    
    CCSprite* pR = CCSprite::create("logo_R.png");
    pR->setPosition(ccp(size.width * 0.27, size.height * 0.8));
    pR->setScale(0.6);
    this->addChild(pR);
    
    CCSprite* pR2 = CCSprite::create("logo_R.png");
    pR2->setPosition(ccp(size.width * 0.43, size.height * 0.8));
    pR2->setScale(0.6);
    this->addChild(pR2);
    
    CCSprite* pO = CCSprite::create("logo_O.png");
    pO->setPosition(ccp(size.width * 0.6, size.height * 0.8));
    pO->setScale(0.6);
    this->addChild(pO);
    
    CCSprite* pW = CCSprite::create("logo_W.png");
    pW->setPosition(ccp(size.width * 0.77, size.height * 0.8));
    pW->setScale(0.6);
    this->addChild(pW);
    
    CCSprite* pS = CCSprite::create("logo_S.png");
    pS->setPosition(ccp(size.width * 0.9, size.height * 0.8));
    pS->setScale(0.6);
    this->addChild(pS);


    
    
    
    //start button
    CCMenuItemImage* pStartItem;
    pStartItem = CCMenuItemImage::create("button1.png", "button1.png",this,menu_selector(TitleScene::menuStartCallback));
    pStartItem->setPosition(ccp(size.width * 0.5, size.height * 0.3));
    
    CCLabelTTF* startLabel;
    startLabel = CCLabelTTF::create("PLAY", "Arial", 30.0);
    
    CCSize pStartItemSize = pStartItem->getContentSize();
    startLabel->setPosition(ccp(pStartItemSize.width / 2 ,pStartItemSize.height / 2));
    pStartItem->addChild(startLabel);


    
    CCMenu* pMenu = CCMenu::create(pStartItem,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
    
    //showHighScore
    //showHighScoreLabel();
    
    return true;
    
}


void TitleScene::menuStartCallback(CCObject *pSender)
{
    //show game
    CCScene* scene = LevelSelectScene ::scene();
    CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
    CCDirector::sharedDirector()->replaceScene(tran);
}

