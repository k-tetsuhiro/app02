//
//  MainGameScene.cpp
//  Arrows
//
//  Created by k_tetsuhiro on 2014/05/20.
//  git commit
//
//

#include "MainGameScene.h"
#include "ResultScene.h"
#include "Arrow.h"
#include "TitleScene.h"
#include "Util.h"
#include "ConstCommon.h"
#include "GameData.h"
#include "Animation.h"
#include "NKLocalizedString.h"

USING_NS_CC;
using namespace std;

CCScene* MainGameScene::scene()
{
    return MainGameScene::sceneWithLevel(1);
}


CCScene* MainGameScene::sceneWithLevel(int level)
{
    CCScene* scene = CCScene::create();
    MainGameScene* layer = MainGameScene::createWithLevel(level);
    scene->addChild(layer);
    
    return scene;
}

MainGameScene* MainGameScene::createWithLevel(int level)
{
    MainGameScene *pRet = new MainGameScene();
    if (pRet && pRet->initWithLevel(level))
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


bool MainGameScene::initWithLevel(int level)
{
    
    // 初期化色を変更
    if (!CCLayerColor::initWithColor(ccc4(0xF1,0xF1,0xF2,0xFF))) //RGBA
    {
        return false;
    }
    
    //初期化に関するものを書く
    m_level = level;
    
    totalGameCount = 0;
    
    gameTime = 0;
    
    minimamCount = 99;
    
    isHighScore = false;
    
    endFlag = false;
    
    isResume = false;

    
    //タッチ判定可能
    setTouchEnabled(false);
    setTouchMode(kCCTouchesOneByOne);
    
    //矢印を配置
    makeArrows();
    
    //ゲーム手数表示
    showGameCountLabel();
    
    //リトライボタン表示
    makeRetryButton();
    
    //一時中断ダイアログ作成
    makeResumeDaialog();
    
    
    return true;
    
}

void MainGameScene::showBackgroud()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pBG = CCSprite::create("background.png");
    pBG->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    pBG->setScale(1.2f);
    this->addChild(pBG);
    
}

void MainGameScene::makeArrows()
{
    
    //GameDataの読み込み
    CCString* jsonFileName = CCString::createWithFormat("Lv%d.json",m_level);
    GameData* gm = new GameData(jsonFileName->getCString());
    
    //矢印の方向
    int *arrowDirection = gm->getDirectionArray();
    
    //矢印の方向
    int *arrowFront = gm->getFrontArray();

    //最小手数
    minimamCount = gm->getMinScore();
    
    
    // higscorekey:m_level
    highScoreKey = ConstCommon::getHighScoreKey(m_level);
    
    //totalGameCount
    totalAllGameCountKey = ConstCommon::getTotalAllGameCountKey();


    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    for(int row = 1; row <= ROW_NUM; row++){
        for(int col = 1; col <= COL_NUM; col++){
            
            int index = ((row - 1) * COL_NUM) + col;
            
            Arrow* arrowObj = Arrow::create();
            
            CCSprite* pArrowOn = CCSprite::create("button_on.png");
            CCSprite* pArrowOff = CCSprite::create("button_off.png");
            
            arrowObj->setDirection(arrowDirection[index - 1]);
            
            arrowObj->setArrowOnSprite(pArrowOn);
            arrowObj->setArrowOffSprite(pArrowOff);
            
            CCSize arrowOffSize = pArrowOff->getContentSize();
            pArrowOff->setPosition(ccp( ((winSize.width - arrowOffSize.width * COL_NUM) / 2) + (arrowOffSize.width / 2 ) + (col - 1) * arrowOffSize.width  ,
                                       ((winSize.height - arrowOffSize.height * ROW_NUM) / 2) + (arrowOffSize.height / 2 ) + (row - 1) * arrowOffSize.height
                                       ));
            
            CCSize arrowOnSize = pArrowOn->getContentSize();
            pArrowOn->setPosition(ccp( ((winSize.width - arrowOnSize.width * COL_NUM) / 2) + (arrowOnSize.width / 2 ) + (col - 1) * arrowOnSize.width  ,
                                      ((winSize.height - arrowOnSize.height * ROW_NUM) / 2) + (arrowOnSize.height / 2 ) + (row - 1) * arrowOnSize.height
                                      ));
            if(arrowFront[index - 1] == 1){
                arrowObj->onFrontArrowSprite(pArrowOff);
            }else{
                arrowObj->onFrontArrowSprite(pArrowOn);
            }
            
           
            arrowObj->setTag(index);
            this->addChild(arrowObj);
        }
        
        
    }
}

bool MainGameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void MainGameScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

    
    //タップポイント取得
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCPoint touchPoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    if(endFlag){
        
    }else{
        
       
        
        for(int i = 1; i <= COL_NUM * ROW_NUM; i++){
            Arrow* arrowObj = (Arrow *)this->getChildByTag(i);
            
            if(!arrowObj){
                return;
            }
            
            //タッチ判定
            CCRect arrowRect = arrowObj->getArrowSprite()->boundingBox();
            if(arrowRect.containsPoint(touchPoint)){
                
                //タッチ数を更新して表示
                if(totalGameCount < 99){
                    totalGameCount++;
                }
                
                showGameCountLabel();
                
                //z-indexあげる
                arrowObj->setZOrder(Z_ORDER_ARROW);
                
                setTouchEnabled(false);
                
                //タッチした時の内部処理
                arrowObj->onTouchArrow();
                
                
                bool reverseFlag;
                //左端かつ左向き
                if(i % COL_NUM == 1 && arrowObj->getDirection() == 3){
                    reverseFlag = false;
                    
                    //右端かつ右向き
                }else if (i % COL_NUM == 0 && arrowObj->getDirection() == 1){
                    reverseFlag = false;
                    
                    //下端かつ下向き
                }else if (i <= COL_NUM && arrowObj->getDirection() == 2){
                    reverseFlag = false;
                    
                    //上端かつ上向き
                }else if (i <= COL_NUM * ROW_NUM && i > COL_NUM * (ROW_NUM - 1) && arrowObj->getDirection() == 0 ){
                    reverseFlag = false;
                    
                    //反転する場合
                }else{
                    reverseFlag = true;
                    
                }
                
                int addIndex;
                switch (arrowObj->getDirection()) {
                    case 0: //上
                        addIndex = ROW_NUM;break;
                    case 1: //右
                        addIndex = 1;break;
                    case 2: //下
                        addIndex = -ROW_NUM;break;
                    case 3: //左
                        addIndex = -1;break;
                }
                
                int nextIndex = i + addIndex;
                Arrow* nextArrowObj;
                if(nextIndex > 0) {
                   nextArrowObj = (Arrow *)this->getChildByTag(nextIndex);
                }
                
                if(!nextArrowObj){
                    reverseFlag = false;
                }
                
                
                CCCallFunc* funcReverseArrow = CCCallFunc::create(arrowObj, callfunc_selector(Arrow::reverseArrow));
                
                CCRotateBy* rotate = CCRotateBy::create(0.3, 90);
                
                CCScaleTo* scaleUp = CCScaleTo::create( 0.15,1.8);
                CCScaleTo* scaleDown = CCScaleTo::create(0.15,1.0);
                CCSequence* seqScale = CCSequence::createWithTwoActions(CCEaseInOut::create(scaleUp, 2), CCEaseInOut::create(scaleDown, 2));
                
                CCSpawn* spaRotateAndScale = CCSpawn::createWithTwoActions(rotate, seqScale);
                
                CCDelayTime* delay = CCDelayTime::create(0.1);
                CCCallFunc* funcEndJudge = CCCallFunc::create(this, callfunc_selector(MainGameScene::endJudgemnet));
                
                if(reverseFlag){
                    
                    CCCallFunc* funcReverseNextArrow = CCCallFunc::create(nextArrowObj, callfunc_selector(Arrow::reverseArrow));
                    arrowObj->getArrowSprite()->runAction(CCSequence::create(spaRotateAndScale, delay, funcReverseArrow, funcReverseNextArrow, funcEndJudge, NULL));
                }else{
                    arrowObj->getArrowSprite()->runAction(CCSequence::create(spaRotateAndScale, delay, funcReverseArrow, funcEndJudge, NULL));
                }
                
                if(arrowObj->getArrowSprite() == arrowObj->getArrowOnSprite()){
                    //Onの場合
                    arrowObj->getArrowOffSprite()->setRotation(arrowObj->getDirection() * 90);
                }else if(arrowObj->getArrowSprite() == arrowObj->getArrowOffSprite()){
                    //Offの場合
                    arrowObj->getArrowOnSprite()->setRotation(arrowObj->getDirection() * 90);
                }
                
            }
            
        }
        
    }
}

void MainGameScene::endJudgemnet()
{
    
    setTouchEnabled(true);
    for(int i = 1; i <= COL_NUM * ROW_NUM; i++){
        Arrow* arrowObj = (Arrow *)this->getChildByTag(i);
        if( ! arrowObj->getOnFlag()){
            //まだ全てONになっていない
            return;
        }
    }
    //終了
    endFlag = true;
    
    //ハイスコアであれば保持
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    
    int highScore = userDefault->getFloatForKey(highScoreKey.c_str(),ConstCommon::DEFAULT_HIGH_SCORE_NUM);
    if( highScore > totalGameCount){
        isHighScore = true;
        userDefault->setFloatForKey(highScoreKey.c_str(), totalGameCount);
    }
    
    //ゲーム回数を記録
    int totalAllGameCount = userDefault->getFloatForKey(totalAllGameCountKey.c_str(),0);
    userDefault->setFloatForKey(totalAllGameCountKey.c_str(), totalAllGameCount+1);
    userDefault->flush();
    
    
    
    //終了アニメーション
    this->endAnimation();
    
}

void MainGameScene::endAnimation()
{
    
    CCMenu* retryButton = (CCMenu*)this->getChildByTag(tagRetryButton);
    if(retryButton){
        //retryButton->setOpacity(0);
        retryButton->setEnabled(false);
    }
    
    int moveIndex[25] = {1,2,3,4,5,10,15,20,25,24,23,22,21,16,11,6,7,8,9,14,19,18,17,12,13};
    for(int i = 1; i <= COL_NUM * ROW_NUM; i++){
        CCRotateBy* rotate = CCRotateBy::create(1.5, 360);
        Arrow* arrowObj = (Arrow *)this->getChildByTag(moveIndex[i-1]);
        CCDelayTime* delay = CCDelayTime::create(0.04 * i);
        CCSequence* seq;
        if(i == COL_NUM * ROW_NUM){
             CCCallFunc* funcShowClearDialog = CCCallFunc::create(this, callfunc_selector(MainGameScene::showClearDialog));
            seq = CCSequence::create(delay,rotate, funcShowClearDialog, NULL);
        }else{
            seq = CCSequence::create(delay,rotate,NULL);
        }
        arrowObj->getArrowSprite()->runAction(seq);
    }

    
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pC = CCSprite::create("clear_C.png");
    pC->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.6));
    pC->setScale(0.0);
    pC->setZOrder(Z_ORDER_CLEAR_DIALOG);
    pC->runAction(CCSequence::create(CCDelayTime::create(0.1),Animation::clearCharaAction(),NULL));
    this->addChild(pC);
    
    CCSprite* pL = CCSprite::create("clear_L.png");
    pL->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.6));
    pL->setScale(0.0);
    pL->setZOrder(Z_ORDER_CLEAR_DIALOG);
    pL->runAction(CCSequence::create(CCDelayTime::create(0.3),Animation::clearCharaAction(),NULL));
    this->addChild(pL);
    
    CCSprite* pE = CCSprite::create("clear_E.png");
    pE->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.6));
    pE->setScale(0.0);
    pE->setZOrder(Z_ORDER_CLEAR_DIALOG);
    pE->runAction(CCSequence::create(CCDelayTime::create(0.5),Animation::clearCharaAction(),NULL));
    this->addChild(pE);
    
    CCSprite* pA = CCSprite::create("clear_A.png");
    pA->setPosition(ccp(winSize.width * 0.7, winSize.height * 0.6));
    pA->setScale(0.0);
    pA->setZOrder(Z_ORDER_CLEAR_DIALOG);
    pA->runAction(CCSequence::create(CCDelayTime::create(0.7),Animation::clearCharaAction(),NULL));
    this->addChild(pA);
    
    CCSprite* pR = CCSprite::create("clear_R.png");
    pR->setPosition(ccp(winSize.width * 0.9, winSize.height * 0.6));
    pR->setScale(0.0);
    pR->setZOrder(Z_ORDER_CLEAR_DIALOG);
    pR->runAction(CCSequence::create(CCDelayTime::create(0.9),Animation::clearCharaAction(),NULL));
    this->addChild(pR);

    
    
}


void MainGameScene::showGameCountLabel()
{
    
    CCString* countString = CCString::createWithFormat("%d",totalGameCount);
    
    CCSprite* pTouchWaku = (CCSprite*)this->getChildByTag(tagTouchWaku);
    if(pTouchWaku){
         CCLabelTTF* countLabel = (CCLabelTTF*)pTouchWaku->getChildByTag(tagGameCountLavel);
        if(countLabel){
             countLabel->setString(countString->getCString());
            return;
        }
    }else{
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite* pTouchWaku= CCSprite::create("touch_waku.png");
        pTouchWaku->setScale(0.5);
        CCSize pTouchSize = pTouchWaku->getContentSize();
        pTouchWaku->setPosition(ccp(winSize.width - pTouchSize.width * 0.4, winSize.height - pTouchSize.height * 0.4));
        pTouchWaku->setTag(tagTouchWaku);
        
       
        CCLabelTTF* countLabel;
        countLabel = CCLabelTTF::create(countString->getCString(), "Arial", 80.0);
        countLabel->setPosition(ccp(pTouchSize.width * 0.5, pTouchSize.height * 0.6));
        countLabel->setColor(ccc3(0, 0, 0));
        countLabel->setTag(tagGameCountLavel);
        
        CCLabelTTF* countLabel2;
        countLabel2 = CCLabelTTF::create("touch", "Arial", 50.0);
        countLabel2->setPosition(ccp(pTouchSize.width * 0.5, pTouchSize.height * 0.3));
        countLabel2->setColor(ccc3(0, 0, 0));
        
        
        pTouchWaku->addChild(countLabel);
        pTouchWaku->addChild(countLabel2);
        this->addChild(pTouchWaku);
    }
}


void MainGameScene::showGametimeLabel()
{
    CCString* timeString = CCString::createWithFormat("%8.3f",gameTime);
    CCLabelTTF* timerLabel = (CCLabelTTF*)this->getChildByTag(tagGametimeLabel);
    if(timerLabel){
        timerLabel->setString(timeString->getCString());
    }else{
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        timerLabel = CCLabelTTF::create(timeString->getCString(), "Arial", 40.0);
        timerLabel->setPosition(ccp(winSize.width * 0.8, winSize.height * 0.9));
        timerLabel->setColor(ccc3(0, 0, 0));
        timerLabel->setTag(tagGametimeLabel);
        this->addChild(timerLabel);
    }
    
}

void MainGameScene::showMinimamCount()
{
    CCString* minCountString = CCString::createWithFormat("MIN:%d",minimamCount);
    CCLabelTTF* minCountLabel = (CCLabelTTF*)this->getChildByTag(tagMinimamCountLabel);
    if(minCountLabel){
        minCountLabel->setString(minCountString->getCString());
    }else{
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        minCountLabel = CCLabelTTF::create(minCountString->getCString(), "Arial", 40.0);
        minCountLabel->setPosition(ccp(winSize.width * 0.8, winSize.height * 0.8));
        minCountLabel->setColor(ccc3(0, 0, 0));
        minCountLabel->setTag(tagGametimeLabel);
        this->addChild(minCountLabel);
    }
    
}


void MainGameScene::makeRetryButton()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCMenuItemImage* retryItem = CCMenuItemImage::create("menu_waku.png","menu_waku.png" ,this, menu_selector(MainGameScene::showResumeDialog));
    
    retryItem->setScale(0.5);
    CCSize pRetryItemSize = retryItem->getContentSize();
    retryItem->setPosition(ccp( pRetryItemSize.width * 0.4, winSize.height - pRetryItemSize.height * 0.4));
    
    CCMenu* retryButton = CCMenu::create(retryItem,NULL);
    retryButton->setPosition(CCPointZero);
    retryButton->setTag(tagRetryButton);
    retryButton->setEnabled(false);
    this->addChild(retryButton);
}

void MainGameScene::makeClearDaialog()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemImage* titleItem = CCMenuItemImage::create("logo_menu.png","logo_menu.png" ,this, menu_selector(MainGameScene::tapTitleButton));
    titleItem->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.3));
    
    CCMenuItemImage* retryItem = CCMenuItemImage::create("logo_restart.png","logo_restart.png" ,this, menu_selector(MainGameScene::tapRetryButton));
    retryItem->setPosition(ccp(winSize.width * 0.8, winSize.height * 0.3));
    
    CCMenu* clearDialog = CCMenu::create(titleItem,retryItem,NULL);
    clearDialog->setPosition(CCPointZero);
    clearDialog->setTag(tagClearDialog);
    clearDialog->setOpacity(0);
    clearDialog->setEnabled(false);
    this->addChild(clearDialog);
}

void MainGameScene::makeResumeDaialog()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    
    //CCSpriteで作ると、タッチ判定無効とかめんどくさいからBGもMenuItemで作る
    CCMenuItemImage* resumeBG = CCMenuItemImage::create("logo_Info2.png","logo_Info2.png");
    resumeBG->setScale(0.7);
    resumeBG->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    resumeBG->setEnabled(false);
    
    CCSize pResumeBGSize = resumeBG->getContentSize();
    CCLabelTTF* resumeLabel;
    
    resumeLabel = CCLabelTTF::create(NKLocalizedString::LocalizedString("resume", "RESUME"), "Copperplate", 60.0);
    resumeLabel->setColor(ccc3(0, 0, 0));
    resumeLabel->setPosition(ccp(pResumeBGSize.width * 0.5 ,pResumeBGSize.height * 0.7));
    resumeBG->addChild(resumeLabel);
   
    
    CCMenuItemImage* titleItem = CCMenuItemImage::create("button1.png","button1.png" ,this, menu_selector(MainGameScene::tapTitleButton));
    titleItem->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.47));
    
    
    CCLabelTTF* titleLabel;
    titleLabel = CCLabelTTF::create("TITLE", "Arial", 30.0);
    
    CCSize pTitleItemSize = titleItem->getContentSize();
    titleLabel->setPosition(ccp(pTitleItemSize.width / 2 ,pTitleItemSize.height / 2));
    titleItem->addChild(titleLabel);
    titleItem->setScale(0.8);

    
    
    CCMenuItemImage* returnGameItem = CCMenuItemImage::create("button2.png","button2.png" ,this, menu_selector(MainGameScene::returnMainGame));
    returnGameItem->setPosition(ccp(winSize.width * 0.7, winSize.height * 0.47));
    
    CCLabelTTF* returnGameLabel;
    returnGameLabel = CCLabelTTF::create("CANCEL", "Arial", 30.0);
    
    CCSize pReturnGameSize = returnGameItem->getContentSize();
    returnGameLabel->setPosition(ccp(pReturnGameSize.width / 2 ,pReturnGameSize.height / 2));
    returnGameItem->addChild(returnGameLabel);
    returnGameItem->setScale(0.8);
    
    CCMenuItemImage* retryGameItem = CCMenuItemImage::create("button3.png","button3.png" ,this, menu_selector(MainGameScene::doRetry));
    retryGameItem->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.39));
    
    CCLabelTTF* retryGameLabel;
    retryGameLabel = CCLabelTTF::create("RETRY", "Arial", 30.0);
    
    CCSize pRetryGameSize = retryGameItem->getContentSize();
    retryGameLabel->setPosition(ccp(pRetryGameSize.width / 2 ,pRetryGameSize.height / 2));
    retryGameItem->addChild(retryGameLabel);
    retryGameItem->setScale(0.8);

    
    
    CCMenu* resumeDialog = CCMenu::create(resumeBG, titleItem, returnGameItem,retryGameItem,NULL);
    resumeDialog->setPosition(CCPointZero);
    resumeDialog->setTag(tagResumeDialog);
    resumeDialog->setOpacity(0);
    resumeDialog->setZOrder(Z_ORDER_RESUME_DIALOG);
    resumeDialog->setEnabled(false);
    this->addChild(resumeDialog);
}

void MainGameScene::tapRetryButton()
{
    doRetry();
}

void MainGameScene::doRetry()
{
    CCScene* scene = (CCScene*)MainGameScene::createWithLevel(m_level);
    CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
    CCDirector::sharedDirector()->replaceScene(tran);
}

//クリアしたら、何手かかったかと、ランク表示、もう一回やる,次のレベルに進む　を表示する ...　ResultSceneで
void MainGameScene::showClearDialog()
{
    CCScene* newGameScene = (CCScene*)ResultScene::createWithParam(m_level, minimamCount, totalGameCount);
    CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, newGameScene);
    CCDirector::sharedDirector()->replaceScene(tran);
}

void MainGameScene::showResumeDialog()
{
    setTouchEnabled(false);
    CCMenu* resumeDialog = (CCMenu*)this->getChildByTag(tagResumeDialog);
    if(resumeDialog){
        resumeDialog->setOpacity(255);
        resumeDialog->setEnabled(true);
    }
    
}

void MainGameScene::returnMainGame()
{
    setTouchEnabled(true);
    CCMenu* resumeDialog = (CCMenu*)this->getChildByTag(tagResumeDialog);
    if(resumeDialog){
        resumeDialog->setOpacity(0);
        resumeDialog->setEnabled(false);
    }
}



void MainGameScene::tapTitleButton()
{
    CCScene* scene = TitleScene ::scene();
    CCTransitionFadeTR* tran = CCTransitionFadeTR::create(1, scene);
    CCDirector::sharedDirector()->replaceScene(tran);
    
}

void MainGameScene::showStartInfo()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemImage* pStartItem;
    pStartItem = CCMenuItemImage::create("logo_Info2.png", "logo_Info2.png",this,menu_selector(MainGameScene::startGame));
    pStartItem->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    pStartItem->setScale(0.7);
     CCSize pStartItemSize = pStartItem->getContentSize();
    
    CCLabelTTF* startLabel1;
    startLabel1 = CCLabelTTF::create("Let's Arrows", "Copperplate", 60.0);
    startLabel1->setColor(ccc3(0, 0, 0));
    startLabel1->setPosition(ccp(pStartItemSize.width * 0.5 ,pStartItemSize.height * 0.7));
    pStartItem->addChild(startLabel1);
    
    CCString* levelStr = CCString::createWithFormat("Lv:%d",m_level);
    CCLabelTTF* levelLabel;
    levelLabel = CCLabelTTF::create(levelStr->getCString(), "Copperplate", 60.0);
    levelLabel->setColor(ccc3(0, 0, 0));
    levelLabel->setPosition(ccp(pStartItemSize.width * 0.5 ,pStartItemSize.height * 0.5));
    pStartItem->addChild(levelLabel);


    
    CCString* minCountString = CCString::createWithFormat("MIN  %d  TOUCH",minimamCount);
    CCLabelTTF* startLabel2;
    startLabel2 = CCLabelTTF::create(minCountString->getCString(), "Copperplate", 50.0);
    startLabel2->setColor(ccc3(0, 0, 0));
    startLabel2->setPosition(ccp(pStartItemSize.width * 0.5 ,pStartItemSize.height * 0.2));
    pStartItem->addChild(startLabel2);
    
    
    CCMenu* pMenu = CCMenu::create(pStartItem,NULL);
    pMenu->setPosition(CCPointZero);
    pMenu->setTag(tagStartInfo);
    
    this->addChild(pMenu);

    
}

void MainGameScene::showCountDown()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    //3
    CCDelayTime* delay1 = CCDelayTime::create(0.5);
    CCScaleTo* scaleUp = CCScaleTo::create(0.1, 1);
    CCDelayTime* delay2 = CCDelayTime::create(0.3);
    CCScaleTo* scaleDown = CCScaleTo::create(0.1, 0);
    
    CCSprite* pNum3 = CCSprite::create("3.png");
    pNum3->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.6));
    pNum3->setScale(0);
    pNum3->runAction(CCSequence::create(delay1,scaleUp,delay2,scaleDown,NULL));
    
    this->addChild(pNum3, 1);
    
    
    //2
    CCDelayTime* p2Delay = CCDelayTime::create(1);
    
    CCSprite* pNum2 = CCSprite::create("2.png");
    pNum2->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.6));
    pNum2->setScale(0);
    pNum2->runAction(CCSequence::create(p2Delay,delay1,scaleUp,delay2,scaleDown,NULL));
    
    this->addChild(pNum2, 1);
    
    //1
    CCDelayTime* p1Delay = CCDelayTime::create(2);
    
    CCSprite* pNum1 = CCSprite::create("1.png");
    pNum1->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.6));
    pNum1->setScale(0);
    pNum1->runAction(CCSequence::create(p1Delay,delay1,scaleUp,delay2,scaleDown,NULL));
    
    this->addChild(pNum1, 1);
    
    //GO
    CCDelayTime* pGoDelay = CCDelayTime::create(3);
    CCCallFunc* funcGameStart = CCCallFunc::create(this, callfunc_selector(MainGameScene::startGame));
    
    CCSprite* pGO = CCSprite::create("go.png");
    pGO->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.6));
    pGO->setScale(0);
    pGO->runAction(CCSequence::create(pGoDelay,delay1,scaleUp,delay2,scaleDown,funcGameStart,NULL));
    
    this->addChild(pGO, 1);
    
    
}

void MainGameScene::startGame()
{
    //タッチを有効に
    setTouchEnabled(true);
    
    //リトライボタンを有効に
    CCMenu* retryButton = (CCMenu*)this->getChildByTag(tagRetryButton);
    if(retryButton){
        retryButton->setEnabled(true);
    }
    
    //startInfoを消す
    CCMenu* startInfo = (CCMenu*)this->getChildByTag(tagStartInfo);
    if(startInfo){
        this->removeChild(startInfo);
    }
    
}



void MainGameScene::onEnterTransitionDidFinish()
{
    //メニュー表示
    showStartInfo();

}

void MainGameScene::measureGameTime(float fDelta)
{
    gameTime += fDelta;
    showGametimeLabel();
}
