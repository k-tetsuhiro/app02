//
//  Tutorial.cpp
//  app02
//
//  Created by k_tetsuhiro on 2014/07/15.
//
//

#include "Tutorial.h"

CCScene* Tutorial::scene(){
    CCScene* scene = CCScene::create();
    Tutorial* layer = Tutorial::create();
    scene->addChild(layer);
    
    return scene;
}

bool Tutorial::init()
{
    // 初期化色を変更
    if (!CCLayerColor::initWithColor(ccc4(0xF8,0xEC,0xDE,0xFF))) //RGBA
    {
        return false;
    }
    
    return true;
    
}
