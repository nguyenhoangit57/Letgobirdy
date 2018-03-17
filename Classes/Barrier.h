//
//  Barrier.h
//  JumpingSnail
//
//  Created by Hoang Nguyen on 12/13/16.
//
//

#ifndef Barrier_h
#define Barrier_h

#include <stdio.h>
#include <Box2D/Box2D.h>
#include "BaseObject.h"
class Barrier : public BaseObject
{
protected:
    b2World* worldPhyicManger;
    b2Body * bodyBarrier;
    bool isUpdatePosition;
    b2Vec2 postionUpdateBarrier;
public:
    Barrier();
    virtual ~Barrier();
    static Barrier* createspriteFileName(const char* file);
    static Barrier* createspriteFrameName(const char* file);
    void initBodyWithPhysicManager(b2World* physicWorld, const Vec2& postion);
    virtual void onEnter();
    virtual void onExit();
    void update(float dt);
    void runActionWhenContactWithCharacter();
    void activeUpdatePhysic();
};
#endif /* Barrier_h */
