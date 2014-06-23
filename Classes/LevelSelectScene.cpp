//
//  LevelSelectScene.cpp
//  Arrows
//
//  Created by k_tetsuhiro on 2014/06/19.
//
//

#include "LevelSelectScene.h"
#include "MainGameScene.h"

USING_NS_CC;

CCScene* LevelSelectScene::scene(){
    CCScene* scene = CCScene::create();
    LevelSelectScene* layer = LevelSelectScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool LevelSelectScene::init()
{
    // 初期化色を変更
    //if (!CCLayerColor::initWithColor(ccc4(83, 166, 103, 255))) //RGBA
    if (!CCLayerColor::initWithColor(ccc4(255, 254, 223, 255))) //RGBA
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    
    //start button
    CCMenuItemImage* pStartItem;
    pStartItem = CCMenuItemImage::create("button1.png", "button1.png",this,menu_selector(LevelSelectScene::menuStartCallback));
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


void LevelSelectScene::menuStartCallback(CCObject *pSender)
{
    //show game
    CCScene* scene = MainGameScene ::sceneWithLevel(1);
    CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
    CCDirector::sharedDirector()->replaceScene(tran);
}

