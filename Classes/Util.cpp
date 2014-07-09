//
//  Util.cpp
//  Arrows
//
//  Created by k_tetsuhiro on 2014/06/04.
//
//

#include "Util.h"
#include "MainGameScene.h"
#include "ConstCommon.h"

int* Util::makeArrayDataByCsv(string csvPath)
{
    int *rData = new int [25];
    
    string filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(csvPath.c_str());
    ifstream ifs(filePath.c_str());
    string csvLine;
    
    if(!ifs){
        //TODO　エラーハンドリング
    	CCAssert(false,"Invalid file");
    }
    
    int i = 0;
    while (getline(ifs, csvLine)) {
        istringstream csvStream(csvLine);
        string csvCol;
        while (getline(csvStream, csvCol, ',')) {
            if(atoi(csvCol.c_str()) != 0){
                rData[i] = atoi(csvCol.c_str());
                i++;
            }
        }
    }
    
    return rData;
}
