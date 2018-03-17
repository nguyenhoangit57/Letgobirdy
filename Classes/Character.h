//
//  Character.h
//  JumpingSnail
//
//  Created by Hoang Nguyen on 12/13/16.
//
//

#ifndef Character_h
#define Character_h

#include <stdio.h>
#include <Box2D/Box2D.h>
#include <spine/spine-cocos2dx.h>
#include "cocos2d.h"
USING_NS_CC;


class DelegateCharacter
{
public:
    virtual void resetTouch() = 0;
    virtual void jumpCharacterComplete(bool complete) = 0;
    virtual void jumpCharacterReadyTouch() = 0;
    virtual void dieCharacterForgame() = 0;
};

class Character : public Node
{
private:
    int currentState;
    int typeCharacter;
    int director;
    int state;
    
    b2World* worldPhyicManger;
    b2Body * bodyCharacter;
    float limitHeightPosition;
    float currentHeight;
    
    bool isFitstRunGame;
    bool isNewCharacter;
    bool isUpdateStatus ;
    bool isTouchCharacter;
    bool isUpdateWhenTouch;
    DelegateCharacter* delegate;
    spine::SkeletonAnimation* skeletonCharacter;
    float vecloCity;
    float positionXBeforJump;
    bool isCheckGameOver;
    float positionJumping;
    

public:
    bool isCanTouch;
    
public:
    
    Character();
    virtual ~Character();
    void update(float dt);
    void onEnter();
    void onExit();
    
    //Define body character
    void defineBodyCharacter(b2World* worldPhysic);
    
    // Action character
    void changeStateToRun();
    void changeStateToJumpOneTouch();
    void changeStateToDie();
    void changeStateJump();
    void changeStateToPause();
    void changeStateJumpTwoTouch();
    
    // Contact 
    void contactWithLanding();
    void contactWithWall();
    void contactBarrier(bool isFlying);
    
    // Veclocity character
    void setVeclocity(float vecity);
    float getVeclocity();
    
    //Current height
    float getCurrentHeight();
    void setCurrentHeight(float height);

    //Get current state
    int getCurrentStateCharacter();
    
    //JumpSuccecc == New Character
    bool getNewStateNewCharacter();
    
    //Director character
    void setDirectorCharacter(int director);
    int getDirectorForCharacter();
    
    //Limit heght character need pass when jump
     float getLimitPostionCharacter();
    
    //Action when doubleJump success
    void changeFilterDataWithJumpDoubleTouchSuccess();
    
    void cacularVecLinearVelocityContactWithWallSuccess(float heightContact, b2Vec2 lineartV2);
  
    //Status character PAUSING - RUNNING - DIE
    int getStateChacter();
    
    //First run when start Game
    bool getFirsRun();
    
    //Register delegate character
    void setDelegate(DelegateCharacter* delegate);
    
    // can Jump character continue
    void readyTouchJumpCharacter();
    
    //Create Character by Spine
    void createCharacterBySpine();
    
    //Die character
    bool checkDieCharacter(const Vec2& position);
    
    void setState(int state);
    
    bool getCheckGameOver();
    

};

#endif /* Character_h */
