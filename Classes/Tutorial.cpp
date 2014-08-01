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
#include "NKLocalizedString.h"

CCScene* Tutorial::scene(){
    CCScene* scene = CCScene::create();
    Tutorial* layer = Tutorial::create();
    scene->addChild(layer);
    
    return scene;
}

bool Tutorial::init()
{
    // 初期化色を変更
    if (!CCLayerColor::initWithColor(ccc4(0xD6,0xFF,0xFF,0xFF))) //RGBA
    {
        return false;
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    //TUTORIAL
    CCSprite* pTutor = CCSprite::create("logo_tutorial.png");
    pTutor->setPosition(ccp(-pTutor->getContentSize().width, winSize.height * 0.5));
    pTutor->setRotation(330);
    CCDelayTime* delay1 = CCDelayTime::create(0.4);
    CCMoveTo* move1 = CCMoveTo::create(1.0f, ccp(winSize.width * 0.3, winSize.height * 0.95));
    pTutor->runAction(CCSequence::create(delay1,move1,NULL));
   
    
    
    CCString* totorialStr = CCString::createWithFormat("TUTORIAL");
    CCLabelTTF* tutorialLabel = CCLabelTTF::create(totorialStr->getCString(), "Copperplate", 55.0);
    tutorialLabel->setColor(ccc3(255, 255, 255));
    tutorialLabel->setPosition(ccp(pTutor->getContentSize().width * 0.40, pTutor->getContentSize().height * 0.5));
    
    pTutor->addChild(tutorialLabel);
    this->addChild(pTutor);
    
    //purposeを表示
    showScene1();
    
    return true;
    
}

void Tutorial::showPurpose(){
    this->removeChild(pMenuScene2);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    //titleLabel
    CCString* titleStr = CCString::create(NKLocalizedString::LocalizedString("purpose", "PURPOSE"));
    CCLabelTTF* titleLabel = CCLabelTTF::create(titleStr->getCString(), "Copperplate", 80.0);
    titleLabel->setColor(ccc3(0, 0, 0));
    CCMenuItem* pTitleItem = CCMenuItem::create();
    pTitleItem->addChild(titleLabel);
    pTitleItem->setPosition(ccp(winSize.width * 0.5 ,winSize.height * 0.8));
    
    //preImage
    CCSprite* pPreArrow = CCSprite::create("tutor_pre.png");
    pPreArrow->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    CCMenuItem* pPreArrowItem = CCMenuItem::create();
    pPreArrowItem->addChild(pPreArrow);
    CCSpawn* moveLeft = CCSpawn::create( CCScaleTo::create(0.5, 0.5) , CCMoveTo::create(0.5, ccp(winSize.width * 0.2, winSize.height * 0.5)),NULL);
    CCSequence* action = CCSequence::create(CCDelayTime::create(2.0),moveLeft,NULL);
    pPreArrow->runAction(action);
    
    //afterImage
    CCSprite* pAfterArrow = CCSprite::create("tutor_after.png");
    pAfterArrow->setPosition(ccp(winSize.width * 0.8, winSize.height * 0.5));
    pAfterArrow->setScale(0.5);
    pAfterArrow->setOpacity(0);
    pAfterArrow->runAction(CCSequence::create(CCDelayTime::create(6.5),CCFadeIn::create(0.3),NULL));
    CCMenuItem* pAfterArrowItem = CCMenuItem::create();
    pAfterArrowItem->addChild(pAfterArrow);
    
    //loadingImage1
    CCSprite* pLoadImage1 = CCSprite::create("tutor_next.png");
    pLoadImage1->setScale(0.35);
    pLoadImage1->setPosition(ccp(winSize.width * 0.5 - pLoadImage1->getContentSize().width * 0.2, winSize.height * 0.5));
    pLoadImage1->setOpacity(0);
    pLoadImage1->runAction(CCSequence::create(CCDelayTime::create(4.0),CCFadeIn::create(0.3),NULL));
    CCMenuItem* pLoadItem1 = CCMenuItem::create();
    pLoadItem1->addChild(pLoadImage1);
    
    //loadingImage2
    CCSprite* pLoadImage2 = CCSprite::create("tutor_next.png");
    pLoadImage2->setScale(0.35);
    pLoadImage2->setPosition(ccp(winSize.width * 0.5 , winSize.height * 0.5));
    pLoadImage2->setOpacity(0);
    pLoadImage2->runAction(CCSequence::create(CCDelayTime::create(4.7),CCFadeIn::create(0.3),NULL));
    CCMenuItem* pLoadItem2 = CCMenuItem::create();
    pLoadItem2->addChild(pLoadImage2);
    
    //loadingImage3
    CCSprite* pLoadImage3 = CCSprite::create("tutor_next.png");
    pLoadImage3->setScale(0.35);
    pLoadImage3->setPosition(ccp(winSize.width * 0.5 + pLoadImage1->getContentSize().width * 0.2, winSize.height * 0.5));
    pLoadImage3->setOpacity(0);
    pLoadImage3->runAction(CCSequence::create(CCDelayTime::create(5.4),CCFadeIn::create(0.3),NULL));
    CCMenuItem* pLoadItem3 = CCMenuItem::create();
    pLoadItem3->addChild(pLoadImage3);
    
    //explainLabel
    CCString* explainStr = CCString::create(NKLocalizedString::LocalizedString("tutor_purpose_explain1", "This game is very simply"));
    CCLabelTTF* explainLabel = CCLabelTTF::create(explainStr->getCString(), "Arial", 40.0);
    explainLabel->setColor(ccc3(0, 0, 0));
    explainLabel->setOpacity(0);
    explainLabel->runAction(CCSequence::create(CCDelayTime::create(3.2),CCFadeIn::create(0.3),NULL));
    CCMenuItem* pExlplainItem = CCMenuItem::create();
    pExlplainItem->addChild(explainLabel);
    pExlplainItem->setPosition(ccp(winSize.width * 0.5 ,winSize.height * 0.7));
    
    //explainLabel2
    CCCallFunc* funcEnd = CCCallFunc::create(this, callfunc_selector(Tutorial::visibleNextButton));
    
    CCString* explainStr2 = CCString::create(NKLocalizedString::LocalizedString("tutor_purpose_explain2", "Goal is to make all YELLOW"));
    CCLabelTTF* explainLabel2 = CCLabelTTF::create(explainStr2->getCString(), "Arial", 40.0);
    explainLabel2->setColor(ccc3(0, 0, 0));
    explainLabel2->setOpacity(0);
    explainLabel2->runAction(CCSequence::create(CCDelayTime::create(7.5),CCFadeIn::create(0.3),CCDelayTime::create(1.5),funcEnd,NULL));
    CCMenuItem* pExlplainItem2 = CCMenuItem::create();
    pExlplainItem2->addChild(explainLabel2);
    pExlplainItem2->setPosition(ccp(winSize.width * 0.5 ,winSize.height * 0.65));
    
    pMenuPurpose = CCMenu::create(pTitleItem,pExlplainItem,pExlplainItem2,pPreArrowItem,pAfterArrowItem,pLoadItem1,pLoadItem2,pLoadItem3,NULL);
    pMenuPurpose->setPosition(CCPointZero);
    this->addChild(pMenuPurpose);
    
}

void Tutorial::showScene1()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    //start button
    CCMenuItemImage* pScene1Item;
    pScene1Item = CCMenuItemImage::create("button_off.png", "button_off.png",this,menu_selector(Tutorial::doScene1));
    pScene1Item->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    pScene1Item->setTag(TAG_SCENE_1_ITEM_1);
    
    
    CCString* ruleStr = CCString::createWithFormat("RULE 1");
    CCLabelTTF* ruleLabel = CCLabelTTF::create(ruleStr->getCString(), "Copperplate", 80.0);
    ruleLabel->setColor(ccc3(0, 0, 0));
    ruleLabel->setPosition(ccp(winSize.width * 0.5 ,winSize.height * 0.8));
    CCMenuItem* pScene1Item2 = CCMenuItem::create();
    pScene1Item2->addChild(ruleLabel);
    pScene1Item2->setPosition(CCPointZero);
    
    CCLabelTTF* touchLabel;
    
    touchLabel = CCLabelTTF::create(NKLocalizedString::LocalizedString("touch", "TOUCH"), "Arial", 40.0);
    touchLabel->setColor(ccc3(0, 0, 0));
    touchLabel->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5 - pScene1Item->getContentSize().height + 20));
    CCMenuItem* pScene1Item3 = CCMenuItem::create();
    pScene1Item3->addChild(touchLabel);
    pScene1Item3->setPosition(CCPointZero);
    pScene1Item3->setTag(TAG_SCENE_1_ITEM_3);

    pMenuScene1 = CCMenu::create(pScene1Item,pScene1Item2,pScene1Item3,NULL);
    pMenuScene1->setPosition(CCPointZero);
    pMenuScene1->setScale(winSize.width/640);
    this->addChild(pMenuScene1);
    
    
}


void Tutorial::doScene1()
{
    CCMenuItemImage* pScene1MenuItem = (CCMenuItemImage*) pMenuScene1->getChildByTag(TAG_SCENE_1_ITEM_1);
    if(pScene1MenuItem) {
        SEL_CallFunc selector = callfunc_selector(Tutorial::endScene1);
        pScene1MenuItem->runAction(Animation::tutorialArrowTouchAction(this, selector));
        pScene1MenuItem->setEnabled(false);
    }
    
    CCMenuItem* pScene1Item3= (CCMenuItem*) pMenuScene1->getChildByTag(TAG_SCENE_1_ITEM_3);
    if(pScene1Item3) {
        pMenuScene1->removeChild(pScene1Item3, true);
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
    pNextItem = CCMenuItemImage::create("button2.png", "button2.png",this,menu_selector(Tutorial::showScene2));
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
    CCString* explainStr = CCString::create(NKLocalizedString::LocalizedString("tutor_scene1_explain", "You got it!\nIf you touch an arrow\nIt is rotate and change color"));
    CCLOG("%s",explainStr->getCString());
    CCLabelTTF* explainLabel = CCLabelTTF::create(explainStr->getCString(), "Arial", 40.0);
    explainLabel->setColor(ccc3(0, 0, 0));
    
    CCMenuItem* pScene1Item3 = CCMenuItem::create();
    pScene1Item3->addChild(explainLabel);
    pScene1Item3->setPosition(ccp(winSize.width * 0.5 ,winSize.height * 0.65));

    pMenuScene1->addChild(pScene1Item3);
    
}

void Tutorial::showScene2()
{
    this->removeChild(pMenuScene1);
    
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    //start button
    CCMenuItemImage* pScene2Item1;
    pScene2Item1 = CCMenuItemImage::create("button_off.png", "button_off.png",this,menu_selector(Tutorial::doScene2));
    pScene2Item1->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5 - 30));
    pScene2Item1->setTag(TAG_SCENE_2_ITEM_1);
    
    
    CCMenuItem* pScene2Item2 = CCMenuItem::create();
    
    CCSprite* pArrow1 = CCSprite::create("button_off.png");
    pArrow1->setPosition(ccp(winSize.width * 0.5 + pArrow1->getContentSize().width , winSize.height * 0.5 - pArrow1->getContentSize().height - 30));
    pScene2Item2->addChild(pArrow1);
   
    
    CCSprite* pArrow2 = CCSprite::create("button_off.png");
    pArrow2->setPosition(ccp(winSize.width * 0.5 , winSize.height * 0.5 - pArrow2->getContentSize().height - 30));
    pScene2Item2->addChild(pArrow2);
    
    CCSprite* pArrow3 = CCSprite::create("button_off.png");
    pArrow3->setPosition(ccp(winSize.width * 0.5 - pArrow3->getContentSize().width , winSize.height * 0.5 - pArrow1->getContentSize().height - 30));
    pScene2Item2->addChild(pArrow3);
    
    CCSprite* pArrow4 = CCSprite::create("button_off.png");
    pArrow4->setPosition(ccp(winSize.width * 0.5 + pArrow4->getContentSize().width , winSize.height * 0.5 - 30));
    pScene2Item2->addChild(pArrow4);
    
    CCSprite* pArrow6 = CCSprite::create("button_off.png");
    pArrow6->setPosition(ccp(winSize.width * 0.5 - pArrow6->getContentSize().width , winSize.height * 0.5 - 30));
    pScene2Item2->addChild(pArrow6);
    
    CCSprite* pArrow7 = CCSprite::create("button_off.png");
    pArrow7->setPosition(ccp(winSize.width * 0.5 + pArrow7->getContentSize().width , winSize.height * 0.5 + pArrow7->getContentSize().height - 30));
    pScene2Item2->addChild(pArrow7);
    
    
    CCSprite* pArrow8 = CCSprite::create("button_off.png");
    pArrow8->setPosition(ccp(winSize.width * 0.5 , winSize.height * 0.5 + pArrow8->getContentSize().height - 30));
    pScene2Item2->addChild(pArrow8);
    
    CCSprite* pArrow9 = CCSprite::create("button_off.png");
    pArrow9->setPosition(ccp(winSize.width * 0.5 - pArrow9->getContentSize().width , winSize.height * 0.5 + pArrow9->getContentSize().height - 30));
    pScene2Item2->addChild(pArrow9);


    
    
    CCString* ruleStr = CCString::createWithFormat("RULE 2");
    CCLabelTTF* ruleLabel = CCLabelTTF::create(ruleStr->getCString(), "Copperplate", 80.0);
    ruleLabel->setColor(ccc3(0, 0, 0));
    CCMenuItem* pScene1Item4 = CCMenuItem::create();
    pScene1Item4->addChild(ruleLabel);
    pScene1Item4->setPosition(ccp(winSize.width * 0.5 ,winSize.height * 0.8));
    
    CCLabelTTF* touchLabel;
    touchLabel = CCLabelTTF::create(NKLocalizedString::LocalizedString("center_touch", "CENTER\nTOUCH"), "Arial", 40.0);
    touchLabel->setColor(ccc3(0, 0, 0));
    touchLabel->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.25 ));
    CCMenuItem* pScene2Item5 = CCMenuItem::create();
    pScene2Item5->addChild(touchLabel);
    pScene2Item5->setPosition(CCPointZero);
    pScene2Item5->setTag(TAG_SCENE_2_ITEM_5);

    
    
    
    pMenuScene2 = CCMenu::create(pScene2Item1,pScene2Item2,pScene1Item4,pScene2Item5,NULL);
    pMenuScene2->setPosition(CCPointZero);
    this->addChild(pMenuScene2);
    
    
}

void Tutorial::doScene2()
{
    CCMenuItemImage* pScene2Item = (CCMenuItemImage*) pMenuScene2->getChildByTag(TAG_SCENE_2_ITEM_1);
    if(pScene2Item) {
        SEL_CallFunc selector = callfunc_selector(Tutorial::endScene2);
        pScene2Item->runAction(Animation::tutorialArrowTouchAction(this, selector));
        pScene2Item->setEnabled(false);
    }
    
    CCMenuItem* pScene2Item5= (CCMenuItem*) pMenuScene2->getChildByTag(TAG_SCENE_2_ITEM_5);
    if(pScene2Item5) {
        pMenuScene2->removeChild(pScene2Item5, true);
    }
}


void Tutorial::endScene2()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pArrow = CCSprite::create("button_on.png");
    pArrow->setRotation(90);
    CCMenuItem* pArrowItem = CCMenuItem::create();
    pArrowItem->addChild(pArrow);
    pArrowItem->setPosition(ccp(winSize.width/2,winSize.height/2 - 30));
    pMenuScene2->addChild(pArrowItem);
    
    CCSprite* pArrow2 = CCSprite::create("button_on.png");
    pArrow2->runAction(CCRepeatForever::create(CCSequence::create(CCDelayTime::create(1.0),CCFadeOut::create(0.01),CCDelayTime::create(0.3),CCFadeIn::create(0.01),NULL)));
    CCMenuItem* pArrowItem2 = CCMenuItem::create();
    pArrowItem2->addChild(pArrow2);
    pArrowItem2->setPosition(ccp(winSize.width/2 + pArrow2->getContentSize().width,winSize.height/2 - 30));
    pArrowItem2->setZOrder(10);
    
    pMenuScene2->addChild(pArrowItem2);

    
    
    //start button
    CCMenuItemImage* pNextItem;
    pNextItem = CCMenuItemImage::create("button2.png", "button2.png",this,menu_selector(Tutorial::showPurpose));
    pNextItem->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.2));
    
    CCLabelTTF* nextLabel;
    nextLabel = CCLabelTTF::create("NEXT", "Arial", 30.0);
    
    CCSize pStartItemSize = pNextItem->getContentSize();
    nextLabel->setPosition(ccp(pStartItemSize.width * 0.5 ,pStartItemSize.height * 0.5));
    pNextItem->addChild(nextLabel);
    
    pMenuScene2->addChild(pNextItem);
    
    CCMenuItemImage* pScene2Item = (CCMenuItemImage*) pMenuScene2->getChildByTag(TAG_SCENE_2_ITEM_1);
    if(pScene2Item) {
        pScene2Item->setOpacity(0);
    }
    CCString* explainStr = CCString::create(NKLocalizedString::LocalizedString("tutor_scene2_explain", "Great!\nChange the color\nin an arrow direction"));
    CCLabelTTF* explainLabel = CCLabelTTF::create(explainStr->getCString(), "Arial", 40.0);
    explainLabel->setColor(ccc3(0, 0, 0));
    
    CCMenuItem* pScene2Item3 = CCMenuItem::create();
    pScene2Item3->addChild(explainLabel);
    pScene2Item3->setPosition(ccp(winSize.width * 0.5 ,winSize.height * 0.7));
    
    pMenuScene2->addChild(pScene2Item3);
}



void Tutorial::endTutorial()
{
   CCScene* scene = LevelSelectScene ::scene();
   CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
   CCDirector::sharedDirector()->replaceScene(tran);
}



void Tutorial::visibleNextButton(CCObject *pObject)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    //nextButton
    CCMenuItemImage* pNextItem;
    pNextItem = CCMenuItemImage::create("button2.png", "button2.png",this,menu_selector(Tutorial::endTutorial));
    pNextItem->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.25));
    CCLabelTTF* nextLabel;
    nextLabel = CCLabelTTF::create("FINISH", "Arial", 30.0);
    CCSize pStartItemSize = pNextItem->getContentSize();
    nextLabel->setPosition(ccp(pStartItemSize.width / 2 ,pStartItemSize.height / 2));
    pNextItem->addChild(nextLabel);
    
    pMenuPurpose->addChild(pNextItem);
}
