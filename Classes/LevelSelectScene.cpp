//
//  LevelSelectScene.cpp
//  Arrows
//
//  Created by k_tetsuhiro on 2014/06/19.
//
//

#include "LevelSelectScene.h"
#include "MainGameScene.h"
#include "Util.h"
#include "ConstCommon.h"
#include "GameData.h"

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
    
    GameData* gm = new GameData("Lv1.json");
    int test = gm->getMinScore();
    CCLOG("min:%d",test);
    
    
    return true;
    
}



void LevelSelectScene::menuStartCallback(CCObject *pSender)
{
    CCMenuItemImage* targetLevelImage = (CCMenuItemImage*)pSender;
    m_level = targetLevelImage->getTag();
    
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    
    CCMenuItemImage* startMenuBG = CCMenuItemImage::create("logo_Info.png","logo_Info.png");
    startMenuBG->setScale(0.6);
    startMenuBG->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    startMenuBG->setEnabled(false);
    
    
    CCString* levelStr = CCString::createWithFormat("Lv:%d",m_level);
    CCSize pStartBGSize = startMenuBG->getContentSize();
    CCLabelTTF* levelLabel;
    levelLabel = CCLabelTTF::create(levelStr->getCString(), "Copperplate", 60.0);
    levelLabel->setColor(ccc3(0, 0, 0));
    levelLabel->setPosition(ccp(pStartBGSize.width * 0.5 ,pStartBGSize.height * 0.75));
    startMenuBG->addChild(levelLabel);
    
    //最小手数
    CCString* jsonFileName = CCString::createWithFormat("Lv%d.json",m_level);
    GameData* gm = new GameData(jsonFileName->getCString());
    int minScore = gm->getMinScore();
    
    //ハイスコアを表示
    // higscorekey:m_level
    stringstream ss2;
    ss2 << ":" << m_level;
    highScoreKey = ConstCommon::HIGH_SCORE_KEY+ss2.str();
    
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
   
    
    int bestScore = userDefault->getFloatForKey(highScoreKey.c_str(),99);
    CCString* bestStr = CCString::createWithFormat("Min:%d  Best:%d",minScore,bestScore);
    CCLabelTTF* bestLabel;
    bestLabel = CCLabelTTF::create(bestStr->getCString(), "Copperplate", 60.0);
    bestLabel->setColor(ccc3(0, 0, 0));
    bestLabel->setPosition(ccp(pStartBGSize.width * 0.5 ,pStartBGSize.height * 0.5));
    startMenuBG->addChild(bestLabel);
    
    
    CCMenuItemImage* titleItem = CCMenuItemImage::create("button1.png","button1.png" ,this, menu_selector(LevelSelectScene::startGame));
    titleItem->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.45));
    
    
    CCLabelTTF* titleLabel;
    titleLabel = CCLabelTTF::create("START", "Arial", 30.0);
    
    CCSize pTitleItemSize = titleItem->getContentSize();
    titleLabel->setPosition(ccp(pTitleItemSize.width / 2 ,pTitleItemSize.height / 2));
    titleItem->addChild(titleLabel);
    titleItem->setScale(0.8);
    
    
    
    CCMenuItemImage* returnGameItem = CCMenuItemImage::create("button2.png","button2.png" ,this, menu_selector(LevelSelectScene::hiddenStartMenu));
    returnGameItem->setPosition(ccp(winSize.width * 0.7, winSize.height * 0.45));
    
    CCLabelTTF* returnGameLabel;
    returnGameLabel = CCLabelTTF::create("CANCLE", "Arial", 30.0);
    
    CCSize pReturnGameSize = returnGameItem->getContentSize();
    returnGameLabel->setPosition(ccp(pReturnGameSize.width / 2 ,pReturnGameSize.height / 2));
    returnGameItem->addChild(returnGameLabel);
    returnGameItem->setScale(0.8);
    
    
    
    CCMenu* resumeDialog = CCMenu::create(startMenuBG, titleItem, returnGameItem, NULL);
    resumeDialog->setPosition(CCPointZero);
    resumeDialog->setTag(tagStartMenuDialog);
    this->addChild(resumeDialog);
    
   }

void LevelSelectScene::startGame()
{
    //show game
    CCScene* scene = MainGameScene ::sceneWithLevel(m_level);
    CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
    CCDirector::sharedDirector()->replaceScene(tran);

    
}

void LevelSelectScene::hiddenStartMenu()
{
    CCMenu* startMenu = (CCMenu*)this->getChildByTag(tagStartMenuDialog);
    if(startMenu){
        this->removeChild(startMenu);
    }
    
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

