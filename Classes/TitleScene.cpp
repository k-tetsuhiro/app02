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
    
    // 初期化色を変更
    if (!CCLayerColor::initWithColor(ccc4(0xF8,0xEC,0xDE,0xFF))) //RGBA
    {
        return false;
    }
    
    srand((unsigned)time(NULL));
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pA = CCSprite::create("logo_A.png");
    pA->setPosition(ccp(size.width * 0.1, size.height * 0.8));
    pA->setScale(0.6);
    this->addChild(pA);
    
    CCSprite* pR = CCSprite::create("logo_R.png");
    pR->setPosition(ccp(size.width * 0.26, size.height * 0.8));
    pR->setScale(0.6);
    this->addChild(pR);
    
    CCSprite* pR2 = CCSprite::create("logo_R.png");
    pR2->setPosition(ccp(size.width * 0.42, size.height * 0.8));
    pR2->setScale(0.6);
    this->addChild(pR2);
    
    CCSprite* pO = CCSprite::create("logo_O.png");
    pO->setPosition(ccp(size.width * 0.58, size.height * 0.8));
    pO->setScale(0.6);
    this->addChild(pO);
    
    CCSprite* pW = CCSprite::create("logo_W.png");
    pW->setPosition(ccp(size.width * 0.74, size.height * 0.8));
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
    
    return true;
    
}


void TitleScene::menuStartCallback(CCObject *pSender)
{
    //show game
    CCScene* scene = LevelSelectScene ::scene();
    CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
    CCDirector::sharedDirector()->replaceScene(tran);
}

