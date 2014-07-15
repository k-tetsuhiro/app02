//
//  ConstCommon.h
//  Arrows
//
//  Created by k_tetsuhiro on 2014/06/03.
//
//

#ifndef __Arrows__ConstCommon__
#define __Arrows__ConstCommon__

#include <iostream>
#include "cocos2d.h"
using namespace std;


class ConstCommon{
public:
    static const int TOTAL_ARROW_NUM = 25;
    static const int DEFAULT_HIGH_SCORE_NUM = 99;
    static string getHighScoreKey(int level);
    static string getTotalAllGameCountKey();

};

#endif /* defined(__Arrows__ConstCommon__) */
