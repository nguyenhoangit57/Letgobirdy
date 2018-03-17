//
//  BaseObject.cpp
//  JumpingSnail
//
//  Created by Hoang Nguyen on 12/13/16.
//
//

#include "BaseObject.h"
#include "GameDefineState.h"
BaseObject::BaseObject()
{
    isPhysic =  false;
}
BaseObject::~BaseObject()
{
    
}
void BaseObject::createWithFileName(const char* fileName)
{
    Sprite::initWithFile(fileName);
}
void BaseObject::createWithFrameName(const char* fileName)
{
    Sprite::initWithSpriteFrameName(fileName);
}
void BaseObject::onEnter()
{
    Sprite::onEnter();
}
void BaseObject::onExit()
{
    Sprite::onExit();
}
void BaseObject::update(float dt)
{
    
}
void BaseObject::createWithAnimation()
{
    
}
void BaseObject::setVeclocity(float vecity)
{
    this->vecloCity = vecity;
}
float BaseObject::getVeclocity()
{
    return vecloCity;
}

void BaseObject::setNewState(int newstate)
{
    this->state = newstate;
}
int BaseObject::getStateCurrent()
{
    return state;
}
void BaseObject::setFlipSprite(bool isFlip)
{
    this->isFlip = isFlip;
    if(isFlip)
    {
        this->setFlippedX(true);
    }
    else
    {
         this->setFlippedX(false);
    }
}
void BaseObject::setEnableUpdate(bool isStart)
{
    this->isUpdateStatus = isStart;
}
bool BaseObject::getEnableUpdate()
{
    return isUpdateStatus;
}

void BaseObject::setPositionObject(const Vec2& pos)
{
    
}
void BaseObject::setScaleVeclocity(float scale)
{
    this->vecloCity *= scale;
}

bool BaseObject::getIsPhysic()
{
    return isPhysic;
}
void BaseObject::setIsPhyic(bool isPhySic)
{
    this->isPhysic = isPhySic;
}

Vec2 BaseObject::getPositionObject()
{
    return this->getPosition();
}
