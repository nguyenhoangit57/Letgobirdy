//
//  HomeScene.h
//  JumpingSnail
//
//  Created by Nguyen Chi Hoang on 4/5/17.
//
//

#ifndef HomeScene_h
#define HomeScene_h

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;


class HomeScene:public Layer
{
public:
    Size winSize;
public:
    static Scene* createHomeScene();
    virtual bool init();
    CREATE_FUNC(HomeScene);
    void update(float dt);
    void eventClickPlay(Ref* pSender);
    
    void onEnter();
    void onExit();
};

#endif /* HomeScene_h */
