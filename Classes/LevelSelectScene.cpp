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

CCScene* LevelSelectScene::scene()
{
    return LevelSelectScene::sceneWithPage(1);
}

CCScene* LevelSelectScene::sceneWithPage(int pageNum)
{
    CCScene* scene = CCScene::create();
    LevelSelectScene* layer = LevelSelectScene::createWithPage(pageNum);
    scene->addChild(layer);
    
    return scene;
}

LevelSelectScene* LevelSelectScene::createWithPage(int pageNum)
{
    LevelSelectScene *pRet = new LevelSelectScene();
    if (pRet && pRet->initWithPage(pageNum))
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


bool LevelSelectScene::initWithPage(int pageNum)
{
     CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // 初期化色を変更
    if (!CCLayerColor::initWithColor(ccc4(0xF8,0xEC,0xDE,0xFF))) //RGBA
    {
        return false;
    }
    
    this->page_num = pageNum;
    
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    // is_tutorial
    string tutorialKey = ConstCommon::getTutorialKey();
    bool tutorClear = userDefault->getBoolForKey(tutorialKey.c_str());
    if( ! tutorClear){
        userDefault->setBoolForKey(tutorialKey.c_str(), true);
        userDefault->flush();
    }

    
    //start button
    CCArray* pLevelArr = new CCArray;
    
    //page1->1〜15 ... page2->16〜30
    for (int i=1 + ((page_num - 1)* 15); i <= 15 + ((page_num - 1)* 15); i++) {
        //create Level Button
        pLevelArr->addObject(createLevelImage(i));
    }

    CCMenu* pMenu = CCMenu::createWithArray(pLevelArr);
    pMenu->setPosition(CCPointZero);
    pMenu->setTag(tagLevelSelectMenuDialog);
    
    if(this->page_num != 2){
        CCMenuItemImage* nextItem = CCMenuItemImage::create("next.png","next.png.png" ,this, menu_selector(LevelSelectScene::showNextPage));
        nextItem->setPosition(ccp(winSize.width * 0.8, winSize.height * 0.2));
        nextItem->setScale(0.2);
        pMenu->addChild(nextItem);
    }
    
    if(this->page_num != 1){
        CCMenuItemImage* prevItem = CCMenuItemImage::create("prev.png","prev.png" ,this, menu_selector(LevelSelectScene::showPrevPage));
        prevItem->setPosition(ccp(winSize.width * 0.2, winSize.height * 0.2));
        prevItem->setScale(0.2);
        pMenu->addChild(prevItem);
    }
    
   
    
    this->addChild(pMenu);
    
   

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

    //ハイスコアを表示
    CCString* bestStr = CCString::createWithFormat("MIN:%d  BEST:%d",min_score[m_level-1],best_score[m_level-1]);
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
    
    
    //bestScoreも初期化
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    highScoreKey = ConstCommon::getHighScoreKey(level);
    best_score[level-1] = userDefault->getFloatForKey(highScoreKey.c_str(),99);
    
    //minScoreも初期化
    CCString* jsonFileName = CCString::createWithFormat("Lv%d.json",level);
    GameData* gm = new GameData(jsonFileName->getCString());
    min_score[level-1] = gm->getMinScore();
    
    int rank;
    
    if(min_score[level-1] >= best_score[level-1]){
        rank = 3;
    }else if( min_score[level-1] <= best_score[level-1] + 8){
        rank = 2;
    }else{
        rank = 1;
    }
    
    
    int fileNum = ((level - 1) / 3) + 1;
    if(fileNum > 5){
        fileNum = fileNum - (( fileNum / 5) * 5) + 1;
    }
    CCString* filePathName = CCString::createWithFormat("level_circle_%d.png",fileNum);

    CCMenuItemImage* pLevel;
    pLevel = CCMenuItemImage::create(filePathName->getCString(), filePathName->getCString(),this,menu_selector(LevelSelectScene::menuStartCallback));
    pLevel->setScale(0.25);
    pLevel->setScale( ((size.width * 0.585) / 3) / pLevel->getContentSize().width );
    
    int posLevel = level - (15 * ((level - 1) / 15));
    pLevel->setPosition(ccp(
                            size.width * (((((posLevel - 1) % 3) + 1) * 0.3) - 0.1),
                            size.height * (0.9 - (((posLevel - 1) / 3 ) * 0.128)) - 70
                            ));
    
    CCSize pLevelSize = pLevel->getContentSize();
    
    if(best_score[level-1] != 99){
        for (int i=0; i < rank; i++) {
            CCSprite* pStar = CCSprite::create("level_star.png");
            
            if(i == 0){
                pStar->setPosition(ccp(pLevelSize.width * 0.5 - pStar->getContentSize().width, pLevelSize.height * 0.75));
            }else if(i == 1){
                pStar->setPosition(ccp(pLevelSize.width * 0.5, pLevelSize.height * 0.75));
            }else{
                pStar->setPosition(ccp(pLevelSize.width * 0.5 + pStar->getContentSize().width, pLevelSize.height * 0.75));
            }
           
            pLevel->addChild(pStar);
        }

    }

    
    
    CCLabelTTF* levelLabel;
    levelLabel = CCLabelTTF::create(levelString->getCString(), "Arial", 150.0);
    levelLabel->setColor(ccc3(0x00,0x00,0x00));
    
    levelLabel->setPosition(ccp(pLevelSize.width / 2 ,pLevelSize.height / 2));
    pLevel->addChild(levelLabel);
    
    pLevel->setTag(level);

    return pLevel;
}


void LevelSelectScene::showNextPage()
{
    CCScene* scene = LevelSelectScene ::sceneWithPage(this->page_num + 1);
    CCTransitionFlipX* tran = CCTransitionFlipX::create(1, scene, kCCTransitionOrientationLeftOver);
    CCDirector::sharedDirector()->replaceScene(tran);
    
    
}

void LevelSelectScene::showPrevPage()
{
    CCScene* scene = LevelSelectScene ::sceneWithPage(this->page_num - 1);
    CCTransitionFlipX* tran = CCTransitionFlipX::create(1, scene, kCCTransitionOrientationRightOver);
    CCDirector::sharedDirector()->replaceScene(tran);
    
    
}

