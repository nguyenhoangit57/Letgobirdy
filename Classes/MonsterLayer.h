//
//  MonsterLayer.h
//  JumpingSnail
//
//  Created by Hoang Nguyen on 1/17/17.
//
//

#ifndef MonsterLayer_h
#define MonsterLayer_h

#include <stdio.h>

#include "cocos2d.h"
#include "GameManager.h"
#include <Box2D/Box2D.h>

USING_NS_CC;
class MonsterLayer: public Layer
{
public:
    std::vector<int> arrayType;
    Size visibleSize ;
    Vec2 origin;
    GameManager* gameManager;
    b2World* physicWorld;
    bool isFirstRun;
    Vec2 pointStart;
public:
    
    void setGameManager(GameManager* gamanager);
    CREATE_FUNC(MonsterLayer);
    virtual ~MonsterLayer();
    virtual bool init();
    void update(float dt, bool isCanUpdatePhysic);
    void createMapWithMonster(int level, int counterMonster, float startPointY, int indexNotMonster);

    virtual void onEnter();
    virtual void onExit();
    void initPhysicForMap(b2World* physic);
    void initPhysicLanding();
    
    int randomTypeMonster();

};

#endif /* MonsterLayer_h */
