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
    if (!CCLayerColor::initWithColor(ccc4(0xF8,0xEC,0xDE,0xFF))) //RGBA
    {
        return false;
    }
    
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    // is_tutorial
    string tutorialKey = ConstCommon::getTutorialKey();
    bool tutorClear = userDefault->getBoolForKey(tutorialKey.c_str());
    if( ! tutorClear){
        userDefault->setBoolForKey(tutorialKey.c_str(), true);
    }

    
    //start button
    CCArray* pLevelArr = new CCArray;
    
    for (int i=1; i <= 15; i++) {
        pLevelArr->addObject(createLevelImage(i));
    }

    CCMenu* pMenu = CCMenu::createWithArray(pLevelArr);
    pMenu->setPosition(CCPointZero);
    pMenu->setTag(tagLevelSelectMenuDialog);
    this->addChild(pMenu);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    CCString* stageSelectStr = CCString::createWithFormat("STAGE SELECT");
    CCLabelTTF* stageSelectLabel = CCLabelTTF::create(stageSelectStr->getCString(), "Copperplate", 70.0);
    stageSelectLabel->setColor(ccc3(0, 0, 0));
    stageSelectLabel->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.95));
    this->addChild(stageSelectLabel);
    
    return true;
    
}



void LevelSelectScene::menuStartCallback(CCObject *pSender)
{
    
    CCMenu* levelSelectMenu = (CCMenu*)this->getChildByTag(tagLevelSelectMenuDialog);
    if(levelSelectMenu){
        levelSelectMenu->setOpacity(128);
        levelSelectMenu->setEnabled(false);
    }
    
    CCMenuItemImage* targetLevelImage = (CCMenuItemImage*)pSender;
    m_level = targetLevelImage->getTag();
    
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemImage* startMenuBG = CCMenuItemImage::create("logo_Info2.png","logo_Info2.png");
    startMenuBG->setScale(0.7);
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
    highScoreKey = ConstCommon::getHighScoreKey(m_level);
    
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
   
    
    int bestScore = userDefault->getFloatForKey(highScoreKey.c_str(),99);
    CCString* bestStr = CCString::createWithFormat("MIN:%d  BEST:%d",minScore,bestScore);
    CCLabelTTF* bestLabel;
    bestLabel = CCLabelTTF::create(bestStr->getCString(), "Copperplate", 60.0);
    bestLabel->setColor(ccc3(0, 0, 0));
    bestLabel->setPosition(ccp(pStartBGSize.width * 0.5 ,pStartBGSize.height * 0.5));
    startMenuBG->addChild(bestLabel);
    
    
    CCMenuItemImage* titleItem = CCMenuItemImage::create("button1.png","button1.png" ,this, menu_selector(LevelSelectScene::startGame));
    titleItem->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.42));
    
    
    CCLabelTTF* titleLabel;
    titleLabel = CCLabelTTF::create("START", "Arial", 30.0);
    
    CCSize pTitleItemSize = titleItem->getContentSize();
    titleLabel->setPosition(ccp(pTitleItemSize.width / 2 ,pTitleItemSize.height / 2));
    titleItem->addChild(titleLabel);
    titleItem->setScale(0.8);
    
    
    
    CCMenuItemImage* returnGameItem = CCMenuItemImage::create("button2.png","button2.png" ,this, menu_selector(LevelSelectScene::hiddenStartMenu));
    returnGameItem->setPosition(ccp(winSize.width * 0.7, winSize.height * 0.42));
    
    CCLabelTTF* returnGameLabel;
    returnGameLabel = CCLabelTTF::create("CANCEL", "Arial", 30.0);
    
    CCSize pReturnGameSize = returnGameItem->getContentSize();
    returnGameLabel->setPosition(ccp(pReturnGameSize.width / 2 ,pReturnGameSize.height / 2));
    returnGameItem->addChild(returnGameLabel);
    returnGameItem->setScale(0.8);
    
    
    
    CCMenu* resumeDialog = CCMenu::create(startMenuBG, titleItem, returnGameItem, NULL);
    resumeDialog->setPosition(CCPointZero);
    resumeDialog->setTag(tagStartMenuDialog);
    resumeDialog->setScale(winSize.width/640);
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
    
    CCMenu* levelSelectMenu = (CCMenu*)this->getChildByTag(tagLevelSelectMenuDialog);
    if(levelSelectMenu){
        levelSelectMenu->setOpacity(255);
        levelSelectMenu->setEnabled(true);
    }
    
}

CCMenuItemImage* LevelSelectScene::createLevelImage(int level)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCString* levelString = CCString::createWithFormat("%d",level);
    
    int fileNum = ((level - 1) / 3) + 1;
    CCString* filePathName = CCString::createWithFormat("level_circle_%d.png",fileNum);

    CCMenuItemImage* pLevel;
    pLevel = CCMenuItemImage::create(filePathName->getCString(), filePathName->getCString(),this,menu_selector(LevelSelectScene::menuStartCallback));
    pLevel->setScale(0.25);
    pLevel->setScale( ((size.width * 0.585) / 3) / pLevel->getContentSize().width );
    pLevel->setPosition(ccp(
                            size.width * (((((level - 1) % 3) + 1) * 0.3) - 0.1),
                            size.height * (0.9 - (((level - 1) / 3 ) * 0.15)) - 70
                            ));
    
    
    CCLabelTTF* levelLabel;
    levelLabel = CCLabelTTF::create(levelString->getCString(), "Arial", 150.0);
    levelLabel->setColor(ccc3(0x00,0x00,0x00));
    
    CCSize pLevelSize = pLevel->getContentSize();
    levelLabel->setPosition(ccp(pLevelSize.width / 2 ,pLevelSize.height / 2));
    pLevel->addChild(levelLabel);
    
    pLevel->setTag(level);

    return pLevel;
}

