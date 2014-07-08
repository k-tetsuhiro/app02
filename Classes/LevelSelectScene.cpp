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
    
    //start button
    CCArray* pLevelArr = new CCArray;
    
    
    for (int i=1; i <= 15; i++) {
        pLevelArr->addObject(createLevelImage(i));
    }
    
    CCMenu* pMenu = CCMenu::createWithArray(pLevelArr);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
    
    
    return true;
    
}



void LevelSelectScene::menuStartCallback(CCObject *pSender)
{
    CCMenuItemImage* targetLevelImage = (CCMenuItemImage*)pSender;
    m_level = targetLevelImage->getTag();
    
    //show game
    CCScene* scene = MainGameScene ::sceneWithLevel(m_level);
    CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
    CCDirector::sharedDirector()->replaceScene(tran);
}

CCMenuItemImage* LevelSelectScene::createLevelImage(int level)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCString* levelString = CCString::createWithFormat("%d",level);

    CCMenuItemImage* pLevel;
    pLevel = CCMenuItemImage::create("level_circle.png", "level_circle.png",this,menu_selector(LevelSelectScene::menuStartCallback));
    pLevel->setScale(0.25);
    pLevel->setPosition(ccp(
                            size.width * (((((level - 1) % 3) + 1) * 0.3) - 0.1),
                            size.height * (0.9 - (((level - 1) / 3 ) * 0.15))
                            ));
    
    
    CCLabelTTF* levelLabel;
    levelLabel = CCLabelTTF::create(levelString->getCString(), "Arial", 150.0);
    levelLabel->setColor(ccc3(83, 166, 103));
    
    CCSize pLevelSize = pLevel->getContentSize();
    levelLabel->setPosition(ccp(pLevelSize.width / 2 ,pLevelSize.height / 2));
    pLevel->addChild(levelLabel);
    
    pLevel->setTag(level);

    return pLevel;
}

