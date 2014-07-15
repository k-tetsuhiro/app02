//
//  GameData.cpp
//  app02
//
//  Created by k_tetsuhiro on 2014/07/09.
//
//

#include "GameData.h"
#include "cocos2d.h"
#include "picojson.h"

USING_NS_CC;
using namespace std;

void GameData::makeData()
{
    string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(this->filePath.c_str());
    unsigned long* pFileSize =  (unsigned long*) malloc(sizeof(unsigned long));
    unsigned char* pData = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", pFileSize);
    picojson::value v;
    
    string err;
    picojson::parse(v, pData, pData + strlen((const char*) pData), &err);
    if(err.empty()){
        picojson::object& all = v.get<picojson::object>();
        this->minScore = all["min_score"].get<double>();
        
        picojson::array frontArray = all["front"].get<picojson::array>();
        int i, l = frontArray.size();
        for(i = 0; i < l; i++){
            this->front[i] = frontArray[i].get<double>();
        }
        
        picojson::array dirctionArray = all["direction"].get<picojson::array>();
        int j, k = dirctionArray.size();
        for(j = 0; j < k; j++){
            this->direction[j] = dirctionArray[j].get<double>();
        }

    }else{
        CCAssert(false, "json perse err");
    }
   
    
}

int GameData::getMinScore()
{
    return this->minScore;
}

int* GameData::getFrontArray()
{
    return this->front;
}

int* GameData::getDirectionArray()
{
    return this->direction;
}