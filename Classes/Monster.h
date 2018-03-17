//
//  Monster.h
//  JumpingSnail
//
//  Created by Hoang Nguyen on 12/13/16.
//
//

#ifndef Monster_h
#define Monster_h

#include <stdio.h>
#include "Barrier.h"
#include <Box2D/Box2D.h>
#include <spine/spine-cocos2dx.h>
#include "spine/spine-cocos2dx.h"
using namespace spine;
class Monster: public Node
{
    
private:
    bool sliceMonster;
    int type;
    int director;
    bool isFirtRun;
    spine::SkeletonAnimation* skeletonNode ;
    float veclocity;
    Sprite* priSoner;
public:
    void initMonsterWithSpine();
    Monster();
    virtual ~Monster();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    void setVeclocity(float vecloCity);
    void setSliceMonster(bool slice);
    
    void setTypeMonster(int type);
    int getTypeMonster();
    void changeRunActionWitAnimation();
    void changePauseActionWithAnimation();
    
    void addPrisoner();
};

#endif /* Monster_h */
