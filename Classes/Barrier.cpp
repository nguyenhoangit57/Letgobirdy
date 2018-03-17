//
//  Barrier.cpp
//  JumpingSnail
//
//  Created by Hoang Nguyen on 12/13/16.
//
//

#include "Barrier.h"
#include "GameDefineState.h"
Barrier::Barrier()
{
    isPhysic =  false;
    isUpdatePosition = false;
}
Barrier::~Barrier()
{
    
}
Barrier* Barrier::createspriteFileName(const char* file)
{
    Barrier* barrier = new Barrier();
    barrier->createWithFileName(file);
    barrier->setNewState(RUNNING);
    return barrier;
}
Barrier* Barrier::createspriteFrameName(const char* file)
{
    Barrier* barrier = new Barrier();
    barrier->createWithFrameName(file);
    barrier->setNewState(RUNNING);
    return barrier;
}
void Barrier::initBodyWithPhysicManager(b2World* physicWorld, const Vec2& postion)

{
    if(!isPhysic)
    {
        postionUpdateBarrier = b2Vec2((postion.x)/PTM_RATIO ,(postion.y - this->getContentSize().height*0.1f)/PTM_RATIO);
        isPhysic = true;
        b2BodyDef barrierBodyDef;
        barrierBodyDef.type = b2_staticBody;
        barrierBodyDef.userData = this;
        barrierBodyDef.bullet = true;
        barrierBodyDef.position.Set((postion.x)/PTM_RATIO ,(postion.y - this->getContentSize().height*2)/PTM_RATIO);
        worldPhyicManger = physicWorld;
        bodyBarrier = worldPhyicManger->CreateBody(&barrierBodyDef);
        bodyBarrier->SetFixedRotation(false);
        
        b2PolygonShape barrier_shape;
        barrier_shape.SetAsBox(this->getContentSize().width/2/PTM_RATIO, 0.4/PTM_RATIO);
        b2FixtureDef barrier_FixDef;
        barrier_FixDef.density = 0;
        barrier_FixDef.friction = 0;
        barrier_FixDef.restitution  = 0.0;
        barrier_FixDef.filter.categoryBits = kBarrierCatBit;
        barrier_FixDef.filter.maskBits = kBarrierMaskBit;
        barrier_FixDef.shape = &barrier_shape;
        bodyBarrier->CreateFixture(&barrier_FixDef);
    }
}
void Barrier::activeUpdatePhysic()
{
    if(isPhysic) {
        auto action1 = DelayTime::create(0.2f);
        auto action2 = CallFunc::create([=](){
            bodyBarrier->SetTransform(postionUpdateBarrier,0.0f);
        });
        this->runAction(Sequence::create(action1,action2, NULL));
    }
}
void Barrier::runActionWhenContactWithCharacter()
{
    isUpdatePosition = true;
    float position_BeforeRun = this->getPositionY() - 15.0f;
    float position_AfterRun =  position_BeforeRun + 15.0f;
    
    auto action1 = MoveTo::create(0.1, Vec2(this->getPositionX(), position_BeforeRun));
    auto action2 = MoveTo::create(0.1, Vec2(this->getPositionX(), position_AfterRun));
    auto action3 = CallFunc::create([=](){
        isUpdatePosition = false;
    });
    this->runAction(Sequence::create(action1,action2,action3, NULL));
}


void Barrier::onEnter()
{
    BaseObject::onEnter();

    
}
void Barrier::onExit()
{
    BaseObject::onExit();
}

void Barrier::update(float dt)
{
}
