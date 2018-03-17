
//
//  Character.cpp
//  JumpingSnail
//
//  Created by Hoang Nguyen on 12/13/16.
//
//

#include "Character.h"
#include "GameDefineState.h"
#include "SimpleAudioEngine.h"


Character::Character()
{
    isCheckGameOver = true;
    isUpdateWhenTouch = false;
    isTouchCharacter  = true;
    isNewCharacter = false;
    isFitstRunGame = true;
    isCanTouch = false;
    state = C_RUNNING;
}
Character::~Character()
{
}

void Character::setState(int state)
{
    this->state = state;
    if(state == C_PAUSING){
       this->stopAllActions();
    }
}
void Character::changeStateToPause()
{
    state = C_PAUSING;
    this->stopAllActions();
}
void Character::changeStateToRun()
{
    if(state  != C_DIE && state != C_RUNNING)
    {
        state = C_RUNNING;
        skeletonCharacter->clearTrack();
        skeletonCharacter->setAnimation(0, "walk", true);
    }
}

void Character::changeStateToDie()
{
    state = C_DIE;
    skeletonCharacter->clearTrack();
    skeletonCharacter->setAnimation(0, "die", false);
    if(delegate)
    {
        delegate->dieCharacterForgame();
    }
}
void Character::changeStateJump()
{
    skeletonCharacter->clearTrack();
    skeletonCharacter->setAnimation(0, "jump", false);
}

void Character::update(float dt)
{
    
    if(state == C_RUNNING)
    {
        if(isFitstRunGame == false)
        {
            if(this->getPositionX() >= Director::getInstance()->getWinSize().width - (WIDTH_RUN_BUFFER) && director!= FLYING)
            {
                isTouchCharacter = false;
                director = LEFT;
                currentState = LEFT;
            }
            else if( this->getPositionX() <= (WIDTH_RUN_BUFFER) && director!= FLYING)
            {
                isTouchCharacter = false;
                director = RIGHT;
                currentState = RIGHT;
            }
            else
            {
                isTouchCharacter = true;
            }
            
            if(director == LEFT)
            {
                this->setPositionX(this->getPositionX() -  this->getVeclocity());
                this->setScaleX(-1);
            }
            if(director == RIGHT)
            {
                this->setPositionX(this->getPositionX() +  this->getVeclocity());
                this->setScaleX(1);
            }
            
            if(bodyCharacter && director!= FLYING)
            {
                bodyCharacter->SetTransform(b2Vec2(this->getPositionX()/PTM_RATIO, (this->getPositionY() + BUFFER_SIZE_HEIGHT/2)/PTM_RATIO), 0.0f);
            }
            if(director == FLYING )
            {
                this->setPosition(Vec2(bodyCharacter->GetPosition().x*PTM_RATIO, (bodyCharacter->GetPosition().y)*PTM_RATIO - BUFFER_SIZE_HEIGHT/2));
            }
            
            if (isUpdateWhenTouch == true)
            {
                isUpdateWhenTouch = false;
                if(this->getPositionY() > limitHeightPosition)
                {
                    isNewCharacter = true;
                    if(delegate)
                    {
                        delegate->jumpCharacterComplete(true);
                    }
                }
            }
        }
        else
        {
            this->setPositionX(this->getPositionX() +  this->getVeclocity()*3);
            this->setScaleX(1);
            bodyCharacter->SetTransform(b2Vec2(this->getPositionX()/PTM_RATIO,(this->getPositionY() + BUFFER_SIZE_HEIGHT/2)/PTM_RATIO), 0.0f);
            if(this->getPositionX() > 0)
            {
                isFitstRunGame = false;
                isCanTouch = true;
            }
        }
    }
}

bool Character::getFirsRun()
{
    return isFitstRunGame;
}

bool Character::getCheckGameOver() {
    return isCheckGameOver;
}


void Character::contactWithLanding()
{
    isCanTouch = true;
    isCheckGameOver = true;
    isNewCharacter = false;
    if(director == CONTACT_LANDING && currentState == LEFT)
    {
        director = LEFT;
        currentState = LEFT;
    }
    if(director == CONTACT_LANDING && currentState == RIGHT)
    {
        director = RIGHT;
        currentState = RIGHT;
    }
    this->setPositionY(currentHeight);
}


void Character::contactBarrier(bool isFlying)
{
    isCanTouch = true;
    isCheckGameOver = true;
    if(director == CONTACT_BARRIER && currentState == LEFT)
    {
        director = LEFT;
        currentState = LEFT;
    }
    else if(director == CONTACT_BARRIER && currentState == RIGHT)
    {
        director = RIGHT;
        currentState = RIGHT;
    }
    if(this->getPositionY() > currentHeight)
    {
        this->setPositionY(currentHeight);
    }
    
}
void Character::cacularVecLinearVelocityContactWithWallSuccess(float heightContact, b2Vec2 lineartV2)
{
    if(director == CONTACT_WALL && currentState == LEFT)
    {
        if(this->getPositionY() > heightContact)
        {
            if(bodyCharacter)
            {
                this->setScaleX(1);
                bodyCharacter->SetLinearVelocity(b2Vec2(lineartV2.x*SCALE_X_BIRD, lineartV2.y*SCALE_Y_BIRD));
            }
            director = FLYING;
            currentState = RIGHT;
        }
        else
        {
            director = LEFT;
            currentState = LEFT;
            
        }
    }
    if(director == CONTACT_WALL && currentState == RIGHT)
    {
        if(this->getPositionY() > heightContact)
        {
            if(bodyCharacter)
            {
                this->setScaleX(-1);
                bodyCharacter->SetLinearVelocity(b2Vec2(-lineartV2.x*SCALE_X_BIRD, lineartV2.y*SCALE_Y_BIRD));
            }
            director = FLYING;
            currentState = LEFT;
        }
        else
        {
            director = RIGHT;
            currentState = RIGHT;
        }
    }
}

void Character::changeStateToJumpOneTouch()
{
    if(this->getPositionX() < (WIDTH_RUN_BUFFER) && currentState == LEFT)
    {
        isTouchCharacter = false;
        if(delegate)
        {
            delegate->resetTouch();
        }
    }
    else if(this->getPositionX() > Director::getInstance()->getWinSize().width - (WIDTH_RUN_BUFFER) && currentState == RIGHT)
    {
        isTouchCharacter = false;
        if(delegate)
        {
            delegate->resetTouch();
        }
    }
    if(state == C_RUNNING && isTouchCharacter)
    {
        positionJumping = this->getPositionX();
        auto delay = DelayTime::create(0.036f);
        auto callFun2 = CallFunc::create([=](){
            isCheckGameOver  = false;
        });
        this->runAction(Sequence::create(delay,callFun2, NULL));
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jump.mp3");
        this->changeStateJump();
        if(bodyCharacter )
        {
            isNewCharacter = false;
            if(director == LEFT && this->getPositionX() >= this->getContentSize().width && this->getPositionX() < Director::getInstance()->getWinSize().width - this->getContentSize().width)
            {
                bodyCharacter->SetLinearVelocity(b2Vec2(- VECLOCITY_JUMP_X*SCALE_X_BIRD, VECLOCITY_ONE_JUMP_Y*SCALE_Y_BIRD));
            }
            if(director == RIGHT &&  this->getPositionX() <= Director::getInstance()->getWinSize().width - this->getContentSize().width &&  this->getPositionX() > this->getContentSize().width)
            {
                bodyCharacter->SetLinearVelocity(b2Vec2(VECLOCITY_JUMP_X*SCALE_X_BIRD, VECLOCITY_ONE_JUMP_Y*SCALE_Y_BIRD) );
            }
            director = FLYING;
        }
    }
}

void Character::contactWithWall()
{
    
    if(isNewCharacter)
    {
        if(positionJumping <= Director::getInstance()->getWinSize().width*0.4 && currentState == LEFT) {
            this->cacularVecLinearVelocityContactWithWallSuccess(HEIGHT_DISTANCE/2,b2Vec2(VECLOCITY_JUMP_X,6.0f));
        }
        else if(positionJumping >= Director::getInstance()->getWinSize().width*0.6f && currentState == RIGHT)
        {
            this->cacularVecLinearVelocityContactWithWallSuccess(HEIGHT_DISTANCE/2,b2Vec2(VECLOCITY_JUMP_X,6.0f));
        }
        else{
            this->cacularVecLinearVelocityContactWithWallSuccess(HEIGHT_DISTANCE/2,b2Vec2(VECLOCITY_JUMP_X,0.0f));
        }
    }
    else
    {
        if(positionJumping < Director::getInstance()->getWinSize().width / 4 && currentState == LEFT) {
            this->cacularVecLinearVelocityContactWithWallSuccess(HEIGHT_DISTANCE/2,b2Vec2(VECLOCITY_JUMP_X, (limitHeightPosition + 28)/this->getPositionY() * 6.0f));
        }
        else if(positionJumping > Director::getInstance()->getWinSize().width*3/4 && currentState == RIGHT)
        {
            this->cacularVecLinearVelocityContactWithWallSuccess(HEIGHT_DISTANCE/2,b2Vec2(VECLOCITY_JUMP_X, (limitHeightPosition + 28)/this->getPositionY() * 6.0f));
        }
        else
        {
            if(currentState == LEFT && this->getPositionY() < currentHeight + HEIGHT_DISTANCE*0.6f) {
                this->cacularVecLinearVelocityContactWithWallSuccess(HEIGHT_DISTANCE/2,b2Vec2(VECLOCITY_JUMP_X,0.0f));
            }
            else if(currentState == RIGHT && this->getPositionY() < currentHeight + HEIGHT_DISTANCE*0.6f)
            {
                this->cacularVecLinearVelocityContactWithWallSuccess(HEIGHT_DISTANCE/2,b2Vec2(VECLOCITY_JUMP_X,0.0f));
            }
            else {
                this->cacularVecLinearVelocityContactWithWallSuccess(HEIGHT_DISTANCE/2,b2Vec2(VECLOCITY_JUMP_X, (limitHeightPosition + 28)/this->getPositionY() * 6.0f));
            }
        }
    }
}




void Character::changeFilterDataWithJumpDoubleTouchSuccess()
{
    isCheckGameOver = false;
    b2Filter filter = bodyCharacter->GetFixtureList()[0].GetFilterData();
    filter.categoryBits = kNewChacracterCatBit;
    filter.maskBits = kNewCharacterMaskBit;
    bodyCharacter->GetFixtureList()[0].SetFilterData(filter);
    if(bodyCharacter)
    {
        if(currentState == RIGHT)
        {
            bodyCharacter->SetLinearVelocity(b2Vec2(VECLOCITY_JUMP_X*SCALE_X_BIRD,VECLOCITY_DOUBLE_JUMP_Y*SCALE_Y_BIRD));
        }
        if(currentState == LEFT)
        {
            bodyCharacter->SetLinearVelocity(b2Vec2(- VECLOCITY_JUMP_X*SCALE_X_BIRD,VECLOCITY_DOUBLE_JUMP_Y*SCALE_Y_BIRD));
        }
    }
}


/*
 jump to touch count == 2
 */
void Character::changeStateJumpTwoTouch()
{
    CCLOG("***** Position jump Y  = %f with Limit Height = %f", this->getPositionY(), limitHeightPosition);
    if(bodyCharacter && this->getPositionY() >  limitHeightPosition)
    {
        this->changeFilterDataWithJumpDoubleTouchSuccess();
        isUpdateWhenTouch = true;
        isCanTouch = false;
    }
    else
    {
        isCanTouch = false;
        isUpdateWhenTouch = false;
        this->setPositionY(currentHeight);
        isNewCharacter = false;
        if(delegate)
        {
            delegate->jumpCharacterComplete(false);
        }
    }
}


void Character::setDirectorCharacter(int director)
{
    this->director = director;
}
int Character::getDirectorForCharacter()
{
    return director;
}

void Character::onEnter()
{
    Node::onEnter();
    this->scheduleUpdate();
}
void Character::onExit()
{
    Node::onExit();
    this->unscheduleUpdate();
}
bool Character::getNewStateNewCharacter()
{
    return isNewCharacter;
}
void Character::setCurrentHeight(float height)
{
    this->currentHeight = height;
    limitHeightPosition = this->currentHeight  + HEIGHT_DISTANCE*0.66;
}
float Character::getCurrentHeight(){
    return currentHeight;
}
float Character::getLimitPostionCharacter()
{
    return limitHeightPosition;
}

int Character::getCurrentStateCharacter()
{
    return currentState;
}
void Character::readyTouchJumpCharacter()
{
    if(delegate)
    {
        delegate->jumpCharacterReadyTouch();
    }
}

void Character::setDelegate(DelegateCharacter* delegate)
{
    this->delegate = delegate;
}

int Character::getStateChacter()
{
    return state;
}

void Character::setVeclocity(float vecity)
{
    this->vecloCity = vecity;
}
float Character::getVeclocity()
{
    return vecloCity;
}

bool Character::checkDieCharacter(const Vec2& position)
{
    if(bodyCharacter)
    {
        Vec2 centerCharacter = Vec2(bodyCharacter->GetPosition().x*PTM_RATIO, bodyCharacter->GetPosition().y*PTM_RATIO);
        float distan = centerCharacter.distance(position);
        if(distan < BUFFER_SIZE_HEIGHT + 10)
        {
            return true;
        }
    }
    return false;
}


void Character::defineBodyCharacter(b2World* worldPhysic)
{
    b2BodyDef characterBodyDef;
    characterBodyDef.type = b2_dynamicBody;
    characterBodyDef.userData = this;
    characterBodyDef.bullet = true;
    characterBodyDef.position.Set((this->getPositionX())/PTM_RATIO ,(this->getPositionY() + BUFFER_SIZE_HEIGHT/2)/PTM_RATIO);
    worldPhyicManger = worldPhysic;
    bodyCharacter = worldPhyicManger->CreateBody(&characterBodyDef);
    bodyCharacter->SetFixedRotation(false);
    
    b2CircleShape circleForCharacter;
    circleForCharacter.m_radius = (22)/PTM_RATIO;
    b2FixtureDef c_FixDef;
    c_FixDef.density = 0;
    c_FixDef.friction = 0.0;
    c_FixDef.restitution  = 0.0;
    c_FixDef.filter.categoryBits = kCharactorCatBit;
    c_FixDef.filter.maskBits = kCharactorMaskBit;
    c_FixDef.shape = &circleForCharacter;
    bodyCharacter->CreateFixture(&c_FixDef);
    
}

void Character::createCharacterBySpine()
{
    skeletonCharacter = spine::SkeletonAnimation::createWithJsonFile("bird.json", "bird.atlas", RATIO_SCALE_CHARACTER);
    skeletonCharacter->setPosition(Vec2(0,0));
    skeletonCharacter->setAnimation(0, "walk", true);
    this->addChild(skeletonCharacter);
    
}

