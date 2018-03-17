//
//  Monster.cpp
//  JumpingSnail
//
//  Created by Hoang Nguyen on 12/13/16.
//
//

#include "Monster.h"
#include "GameDefineState.h"


Monster::Monster()
{
    isFirtRun = true;
}
Monster::~Monster()
{
    
}

void Monster::onEnter()
{
    Node::onEnter();
}
void Monster::onExit()
{
    Node::onExit();
}
void Monster::setVeclocity(float vecloCity)
{
    this->veclocity = vecloCity;
}
void Monster::setSliceMonster(bool slice){
    this->sliceMonster = slice;
}
void Monster::addPrisoner(){
    if(type == 0) {
         priSoner = Sprite::create("cage_cat.png");
    }else{
         priSoner = Sprite::create("cage_pig.png");
    }
    priSoner->setPosition(Vec2(0, priSoner->getContentSize().height/2));
    this->addChild(priSoner,1);
}
void Monster::update(float dt)
{
    if(sliceMonster == false) {
        if(isFirtRun)
        {
            if(this->getPositionX() > Director::getInstance()->getWinSize().width/2)
            {
                this->setPositionX(this->getPositionX() +  veclocity);
                this->setScaleX(1);
            }
            if(this->getPositionX() <= Director::getInstance()->getWinSize().width/2 )
            {
                this->setPositionX(this->getPositionX() -  veclocity);
                this->setScaleX(-1);
            }
            
            if(this->getPositionX() < - this->getContentSize().width/2 || this->getPositionX() >= Director::getInstance()->getWinSize().width + this->getContentSize().width/2)
            {
                isFirtRun = false;
            }
        }
        else
        {
            if(this->getPositionX() >= Director::getInstance()->getWinSize().width + this->getContentSize().width/2)
            {
                director = LEFT;
            }
            if( this->getPositionX() <= - this->getContentSize().width/2)
            {
                director = RIGHT;
            }
            if(director == LEFT)
            {
                this->setPositionX(this->getPositionX() -  veclocity);
                this->setScaleX(-1);
            }
            if(director == RIGHT)
            {
                this->setPositionX(this->getPositionX() +  veclocity);
                this->setScaleX(1);
            }
        }   
    }
}
void Monster::changePauseActionWithAnimation()
{
    
}
void Monster::setTypeMonster(int type)
{
    this->type = type;
}
int Monster::getTypeMonster()
{
    return type;
}
void Monster::initMonsterWithSpine()
{

    if (type == 0)
    {
        spine::SkeletonAnimation* skeletonNode = spine::SkeletonAnimation::createWithJsonFile("cat.json", "cat.atlas", RATIO_SCALE_MONSTER);
        skeletonNode->clearTrack();
        skeletonNode->setAnimation(0, "walk", true);
        this->addChild(skeletonNode);
    }
    if(type == 1)
    {
        spine::SkeletonAnimation* skeletonNode = spine::SkeletonAnimation::createWithJsonFile("pig.json", "pig.atlas", RATIO_SCALE_MONSTER);
        skeletonNode->clearTrack();
        skeletonNode->setAnimation(0, "walk", true);
        this->addChild(skeletonNode);
        
    }
}
