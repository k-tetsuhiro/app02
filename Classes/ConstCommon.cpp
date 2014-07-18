//
//  ConstCommon.cpp
//  Arrows
//
//  Created by k_tetsuhiro on 2014/06/03.
//
//


#include "ConstCommon.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

string ConstCommon::getHighScoreKey(int level)
{
    //highScore:Level:m_level;
    CCString* highScoreKey = CCString::createWithFormat("highScore:level:%d",level);
    return highScoreKey->getCString();
}

string ConstCommon::getTotalAllGameCountKey()
{
    CCString* highScoreKey = CCString::createWithFormat("totalGameCount");
    return highScoreKey->getCString();
}