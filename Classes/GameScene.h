//
//  GameScene.h
//  JumpingSnail
//
//  Created by Hoang Nguyen on 2/14/17.
//
//

#ifndef GameScene_h
#define GameScene_h

#include <stdio.h>
#include "cocos2d.h"
#include <Box2D/Box2D.h>
using namespace cocos2d;


class GameScene : public Layer
{
private:
    b2World* physicWorld;
    Size visibleSize;
public:
    virtual bool init();
    CREATE_FUNC(GameScene);
    void update(float dt);
    static Scene* createGameScene();
    void createBackGroundForGame();
    
};


#endif /* GameScene_h */
