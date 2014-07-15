//
//  Tutorial.cpp
//  app02
//
//  Created by k_tetsuhiro on 2014/07/15.
//
//

#include "Tutorial.h"
#include "Arrow.h"
#include "Animation.h"
#include "LevelSelectScene.h"

CCScene* Tutorial::scene(){
    CCScene* scene = CCScene::create();
    Tutorial* layer = Tutorial::create();
    scene->addChild(layer);
    
    return scene;
}

bool Tutorial::init()
{
    // 初期化色を変更
    if (!CCLayerColor::initWithColor(ccc4(0xF8,0xEC,0xDE,0xFF))) //RGBA
    {
        return false;
    }
    //1を表示
    showScene1();
    
    return true;
    
}

void Tutorial::showScene1()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    //start button
    CCMenuItemImage* pScene1Item;
    pScene1Item = CCMenuItemImage::create("button_off.png", "button_off.png",this,menu_selector(Tutorial::doScene1));
    pScene1Item->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    pScene1Item->setTag(TAG_SCENE_1_ITEM_1);
    
    
    CCString* touchStr = CCString::createWithFormat("TOUCH!");
    CCLabelTTF* touchLabel = CCLabelTTF::create(touchStr->getCString(), "Copperplate", 80.0);
    touchLabel->setColor(ccc3(0, 0, 0));
   
    
    CCMenuItem* pScene1Item2 = CCMenuItem::create();
    pScene1Item2->addChild(touchLabel);
    pScene1Item2->setPosition(ccp(winSize.width * 0.5 ,winSize.height * 0.8));
    
    
    
    pMenuScene1 = CCMenu::create(pScene1Item,pScene1Item2,NULL);
    pMenuScene1->setPosition(CCPointZero);
    this->addChild(pMenuScene1);
    
    
}


void Tutorial::doScene1()
{
    CCMenuItemImage* pScene1Item = (CCMenuItemImage*) pMenuScene1->getChildByTag(TAG_SCENE_1_ITEM_1);
    if(pScene1Item) {
        SEL_CallFunc selector = callfunc_selector(Tutorial::endScene1);
        pScene1Item->runAction(Animation::tutorialArrowTouchAction(this, selector));
    }
}

void Tutorial::endScene1()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pArrow = CCSprite::create("button_on.png");
    pArrow->setRotation(90);
    CCMenuItem* pArrowItem = CCMenuItem::create();
    pArrowItem->addChild(pArrow);
    pArrowItem->setPosition(ccp(winSize.width/2,winSize.height/2));
    pMenuScene1->addChild(pArrowItem);
    
    //start button
    CCMenuItemImage* pNextItem;
    pNextItem = CCMenuItemImage::create("button2.png", "button2.png",this,menu_selector(Tutorial::endTutorial));
    pNextItem->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.3));
    
    CCLabelTTF* nextLabel;
    nextLabel = CCLabelTTF::create("NEXT", "Arial", 30.0);
    
    CCSize pStartItemSize = pNextItem->getContentSize();
    nextLabel->setPosition(ccp(pStartItemSize.width / 2 ,pStartItemSize.height / 2));
    pNextItem->addChild(nextLabel);
    
    pMenuScene1->addChild(pNextItem);
    
    CCMenuItemImage* pScene1Item = (CCMenuItemImage*) pMenuScene1->getChildByTag(TAG_SCENE_1_ITEM_1);
    if(pScene1Item) {
        pScene1Item->setOpacity(0);
    }

   
}

void Tutorial::endTutorial()
{
   CCScene* scene = LevelSelectScene ::scene();
   CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
   CCDirector::sharedDirector()->replaceScene(tran);
}