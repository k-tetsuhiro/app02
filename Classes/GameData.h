//
//  GameData.h
//  app02
//
//  Created by k_tetsuhiro on 2014/07/09.
//
//

#ifndef __app02__GameData__
#define __app02__GameData__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class GameData{
    
private:
    string filePath;
    int minScore;
    int front[25];
    int direction[25];
    
public:
    void makeData();
    int getMinScore();
    int* getFrontArray();
    int* getDirectionArray();
    
    //__construct
    GameData(string filePath){
        this->filePath = filePath;
        makeData();
    }
    
};



#endif /* defined(__app02__GameData__) */
