//
//  DebugBoot.cpp
//  app02
//
//  Created by k_tetsuhiro on 9/5/14.
//
//

#include "DebugBoot.h"
#include "GameData.h"
#include "Arrow.h"

CCScene* DebugBoot::scene()
{
    CCScene* scene = CCScene::create();
    DebugBoot* layer = DebugBoot::create();
    scene->addChild(layer);
    
    return scene;
}

bool DebugBoot::init()
{
    // 初期化色を変更
    if (!CCLayerColor::initWithColor(ccc4(0xFF,0xEF,0xFF,0xFF))) //RGBA
    {
        return false;
    }
    
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    this->makeArrows();
    
    return true;
}

void DebugBoot::makeArrows()
{
    
    //GameDataの読み込み
    CCString* jsonFileName = CCString::createWithFormat("debugGame.json");
    GameData* gm = new GameData(jsonFileName->getCString());
    
    //矢印の方向
    int *arrowDirection = gm->getDirectionArray();
    
    //矢印の方向
    int *arrowFront = gm->getFrontArray();
    
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


bool DebugBoot::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void DebugBoot::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    
    //タップポイント取得
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCPoint touchPoint = pDirector->convertToGL(pTouch->getLocationInView());
    for(int i = 1; i <= COL_NUM * ROW_NUM; i++){
        Arrow* arrowObj = (Arrow *)this->getChildByTag(i);
        
        if(!arrowObj){
            return;
        }
        
        //タッチ判定
        CCRect arrowRect = arrowObj->getArrowSprite()->boundingBox();
        if(arrowRect.containsPoint(touchPoint)){
            
            //z-indexあげる
            arrowObj->setZOrder(100);
            
            //タッチした時の内部処理(逆向き)
            arrowObj->reRotateArrow();
            
            
            bool reverseFlag;
            //左端かつ下向き
            if(i % COL_NUM == 1 && arrowObj->getDirection() == 2){
                reverseFlag = false;
                
                //右端かつ上向き
            }else if (i % COL_NUM == 0 && arrowObj->getDirection() == 0){
                reverseFlag = false;
                
                //下端かつ右向き
            }else if (i <= COL_NUM && arrowObj->getDirection() == 1){
                reverseFlag = false;
                
                //上端かつ左向き
            }else if (i <= COL_NUM * ROW_NUM && i > COL_NUM * (ROW_NUM - 1) && arrowObj->getDirection() == 3 ){
                reverseFlag = false;
                
                //反転する場合
            }else{
                reverseFlag = true;
                
            }
            
            int addIndex;
            switch (arrowObj->getDirection()) {
                case 0: //上
                    addIndex = 1;break;
                case 1: //右
                    addIndex = -ROW_NUM;break;
                case 2: //下
                    addIndex = -1;break;
                case 3: //左
                    addIndex = ROW_NUM;break;
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
            
            CCRotateBy* rotate = CCRotateBy::create(0.3, -90);
            
            CCScaleTo* scaleUp = CCScaleTo::create( 0.15,1.8);
            CCScaleTo* scaleDown = CCScaleTo::create(0.15,1.0);
            CCSequence* seqScale = CCSequence::createWithTwoActions(CCEaseInOut::create(scaleUp, 2), CCEaseInOut::create(scaleDown, 2));
            
            CCSpawn* spaRotateAndScale = CCSpawn::createWithTwoActions(rotate, seqScale);
            
            CCDelayTime* delay = CCDelayTime::create(0.1);
            
            if(reverseFlag){
                
                CCCallFunc* funcReverseNextArrow = CCCallFunc::create(nextArrowObj, callfunc_selector(Arrow::reverseArrow));
                arrowObj->getArrowSprite()->runAction(CCSequence::create(spaRotateAndScale, delay, funcReverseArrow, funcReverseNextArrow, NULL));
            }else{
                arrowObj->getArrowSprite()->runAction(CCSequence::create(spaRotateAndScale, delay, funcReverseArrow, NULL));
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

