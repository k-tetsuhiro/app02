//
//  Arrow.cpp
//  Arrows
//
//  Created by k_tetsuhiro on 2014/05/22.
//
//

#include "Arrow.h"
#include "cocos2d.h"
#include "MainGameScene.h"

USING_NS_CC;

Arrow* Arrow::create()
{
    Arrow* arrowObj = new Arrow();
    if(arrowObj){
        arrowObj->autorelease();
        return arrowObj;
    }
    return NULL;
    
    /*
    CCSprite *pobSprite = new CCSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
     */
}



void Arrow::setArrowOnSprite(cocos2d::CCSprite *pArrow){
    this->pArrowOn = pArrow;
    this->addChild(this->pArrowOn);
}

void Arrow::setArrowOffSprite(cocos2d::CCSprite *pArrow){
    this->pArrowOff = pArrow;
    this->addChild(this->pArrowOff);
}

void Arrow::onFrontArrowSprite(cocos2d::CCSprite *pArrow){
    if(pArrow == this->pArrowOff){
        this->pArrowOn->setOpacity(0);
        this->pArrowOff->setOpacity(255);
         this->onFlag = false;
    }
    if(pArrow == this->pArrowOn){
        this->pArrowOn->setOpacity(255);
        this->pArrowOff->setOpacity(0);
        this->onFlag = true;
    }
    
    this->pArrowOn->setRotation(this->direction * 90);
    this->pArrowOff->setRotation(this->direction * 90);
    
    this->pArrow = pArrow;
}

void Arrow::reverseArrow(){
    if(this->pArrow == this->pArrowOff){
        this->pArrowOn->setOpacity(255);
        this->pArrowOff->setOpacity(0);
        this->pArrow = this->pArrowOn;
        this->onFlag = true;
        return;
    }
    if(this->pArrow == this->pArrowOn){
        this->pArrowOn->setOpacity(0);
        this->pArrowOff->setOpacity(255);
        this->pArrow = this->pArrowOff;
        this->onFlag = false;
        return;
    }

}

void Arrow::rotateArrow()
{
    
    if(this->direction == 3){
        this->direction = 0;
    }else{
        this->direction++;
    }
    
}

void Arrow::onTouchArrow()
{
    rotateArrow();
    
}



CCSprite* Arrow::getArrowSprite(){
    return this->pArrow;
}

CCSprite* Arrow::getArrowOnSprite()
{
    return this->pArrowOn;
}

CCSprite* Arrow::getArrowOffSprite()
{
    return this->pArrowOff;
}

bool Arrow::getOnFlag()
{
    return this->onFlag;
}

int Arrow::getDirection()
{
    return this->direction;
}

void Arrow::setDirection(int direction)
{
    this->direction = direction;
}



