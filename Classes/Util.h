//
//  Util.h
//  Arrows
//
//  Created by k_tetsuhiro on 2014/06/04.
//
//

#ifndef __Arrows__Util__
#define __Arrows__Util__

#include <iostream>
#include <fstream>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Util{
    
public:
    static int* makeArrayDataByCsv(string csvPath);
};

#endif /* defined(__Arrows__Util__) */
