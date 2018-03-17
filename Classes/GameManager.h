//
//  GameManager.h
//  JumpingSnail
//
//  Created by Hoang Nguyen on 1/16/17.
//
//

#ifndef GameManager_h
#define GameManager_h

#include <stdio.h>

#include "cocos2d.h"
#include "Monster.h"
#include "Barrier.h"
#include "Character.h"
#include <Box2D/Box2D.h>
USING_NS_CC;


class GameManager
{
public:
    b2World* worldPhyicManger;
    std::vector<Monster*> arrayMonster;
    std::vector<Barrier*> arrayBarrier;
    bool isGameOver;
    Character* character;
public:
    GameManager();
    virtual ~GameManager();
    void manageBarrierAndMonster(Barrier* barrier , Monster* monster);
    void update(float dt, bool isUpdatePhyic);
    void clearDataForGame();
    void addMonster(Barrier* barrier);
    void addBarrier(Barrier* barrier);
    void initPhysic(b2World* world);
    void managerCharacter(Character* character);
    void setVisiableWhenTouch();
    int getCountBarrier();
    void restartGameManager();
};

#endif /* GameManager_h */
