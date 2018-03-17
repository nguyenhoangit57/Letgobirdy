//
//  MyListender.cpp
//  KidsKid
//
//  Created by Nguyễn Chí Hoàng on 5/22/15.
//
//

#include "MyListenner.h"
#include "Character.h"
#include "GameDefineState.h"
#include "Barrier.h"
#include "Monster.h"
void processCollisionPlayerVsObject(b2Body* playerBody , b2Body* objectBody)
{
    Character* player = (Character*)playerBody->GetUserData();
    if(objectBody->GetFixtureList()[0].GetFilterData().categoryBits == kBarrierCatBit)
    {
        if(player->getDirectorForCharacter() == FLYING)
        {
            player->setDirectorCharacter(CONTACT_BARRIER);
            player->contactBarrier(true);
            player->setState(C_IDLE);
            Barrier* barrier = (Barrier*)objectBody->GetUserData();
            barrier->runActionWhenContactWithCharacter();
        }
        if(player->getStateChacter() != C_DIE)
        {
            player->changeStateToRun();
        }
        player->readyTouchJumpCharacter();
    }
}

MyListender::MyListender(){
    
}

void MyListender::BeginContact(b2Contact* contact){
    if (contact && contact->IsTouching())
    {
        b2Body* bodyUserDataA = contact->GetFixtureA()->GetBody();
        b2Body* bodyUserDataB = contact->GetFixtureB()->GetBody();
        if ( bodyUserDataB->GetUserData() !=NULL  && bodyUserDataA->GetUserData() !=NULL)
        {
            Character* player = dynamic_cast<Character*>((Ref*)bodyUserDataA->GetUserData());
            if(player)
            {
                processCollisionPlayerVsObject(bodyUserDataA, bodyUserDataB);
            }
            else
            {
                processCollisionPlayerVsObject(bodyUserDataB, bodyUserDataA);
            }
            if(delegate)
            {
                delegate->restoreIndexListener(0);
            }
        }
        else if(bodyUserDataA->GetUserData() != NULL && bodyUserDataB->GetUserData() == NULL)
        {
            if(bodyUserDataB->GetFixtureList()[0].GetFilterData().categoryBits == kWallFiniteCatBit)
            {
                Character* player = (Character*)bodyUserDataA->GetUserData();
                if(player->getDirectorForCharacter() == FLYING)
                {
                    player->setDirectorCharacter(CONTACT_WALL);
                    if(delegate)
                    {
                        delegate->contactWithWall();
                    }
                }
            }
            if(bodyUserDataB->GetFixtureList()[0].GetFilterData().categoryBits == kLandCatBit)
            {
                Character* player = (Character*)bodyUserDataA->GetUserData();
                player->setDirectorCharacter(CONTACT_LANDING);
                if(delegate)
                {
                    delegate->restoreIndexListener(0);
                    delegate->contactWithLanding();
                    
                }
                 player->setState(C_IDLE);
                if(player->getStateChacter() != C_DIE)
                {
                    player->changeStateToRun();
                }
                player->readyTouchJumpCharacter();
            }
        }
        else if(bodyUserDataA->GetUserData() == NULL && bodyUserDataB->GetUserData() != NULL)
        {
            
            if(bodyUserDataA->GetFixtureList()[0].GetFilterData().categoryBits == kWallFiniteCatBit)
            {
                Character* player = (Character*)bodyUserDataB->GetUserData();
                if(player->getDirectorForCharacter() == FLYING)
                {
                    player->setDirectorCharacter(CONTACT_WALL);
                    if(delegate)
                    {
                        delegate->contactWithWall();
                    }
                }
            }
            if(bodyUserDataA->GetFixtureList()[0].GetFilterData().categoryBits == kLandCatBit)
            {
                Character* player = (Character*)bodyUserDataB->GetUserData();
                player->setDirectorCharacter(CONTACT_LANDING);
                if(delegate)
                {
                    delegate->restoreIndexListener(0);
                    delegate->contactWithLanding();
                }
                 player->setState(C_IDLE);
                if(player->getStateChacter() != C_DIE)
                {
                    player->changeStateToRun();
                }
                player->readyTouchJumpCharacter();
            }
        }
    }
}
void MyListender::EndContact(b2Contact* contact){
    
}
void MyListender::PreSolve(b2Contact *contact, const b2Manifold *oldManifold){
    
    
}
void MyListender::setDelegate(DelegateListener* mDelegate)
{
    this->delegate = mDelegate;
}
