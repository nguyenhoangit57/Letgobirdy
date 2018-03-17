//
//  MonsterLayer.cpp
//  JumpingSnail
//
//  Created by Hoang Nguyen on 1/17/17.
//
//

#include "MonsterLayer.h"
#include "Barrier.h"
#include "Monster.h"
#include <cstdlib>
#include "GameManager.h"
#include "GameDefineState.h"
#include "TestBody.h"

MonsterLayer::~MonsterLayer()
{
    
}
bool MonsterLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    isFirstRun = true;
    visibleSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();
    pointStart = Vec2(10, 40);
    
    auto spLanding = Sprite::create("landing.png");
    spLanding->setPosition(Vec2(visibleSize.width/2, spLanding->getContentSize().height/2));
    this->addChild(spLanding,1);
    return true;
}
void MonsterLayer::setGameManager(GameManager* gamanager)
{
    this->gameManager = gamanager;
}


void MonsterLayer::initPhysicForMap(b2World* physic)
{
    physicWorld = physic;
    gameManager->initPhysic(physicWorld);
    this->initPhysicLanding();
}
void MonsterLayer::update(float dt, bool isCanUpdatePhysic)
{
    if(gameManager)
    {
        gameManager->update(dt, isCanUpdatePhysic);
    }
}
void swapInt(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}
int MonsterLayer::randomTypeMonster(){
    int type = 0;
    if(arrayType.empty()){
        int numberType0 = rand() %2+3;
        int numberType1 = rand() %4+3;
        for (int i = 0; i < numberType0; i++) {
            arrayType.push_back(0);
        }
        for (int i = 0; i < numberType1; i++) {
            arrayType.push_back(1);
        }
    }else{
        int numberArray = rand()% arrayType.size();
        type = arrayType.at(numberArray);
        
        int temp = arrayType.at(numberArray);
        arrayType.at(numberArray) = arrayType.at(arrayType.size()-1);
        arrayType.at(arrayType.size()-1) = temp;
        arrayType.pop_back();
    }
    return type;
}


void MonsterLayer::createMapWithMonster(int level,int counterMonster, float startPointY,int indexNotMonster)
{
    srand( (unsigned)time(NULL) );
    int intWidth1 = visibleSize.width*3/4;
    int intWidth2 = visibleSize.width/4;
    
    int randomSlice1 = rand() % 3+2;
    int randomSlice2 = rand() % 5+6;
    int hiddenIndex = rand() % 7+3;
    float veclocityMonster = DELTA_MONSTER_A;
    if(level >= 2) {
        hiddenIndex = 1000;
        veclocityMonster = DELTA_MONSTER_A + 0.4f;
    }
   
    
    for (int i = 0; i < counterMonster; i++)
    {
        int randomPostionX1 =  0 + (rand() % int(intWidth1));
        int randomPostionX2  = intWidth2 + (rand() % (int)(visibleSize.width - intWidth2));
        
        Barrier* barrier = Barrier::createspriteFileName("tree.png");
        barrier->setPosition(Vec2(visibleSize.width/2,startPointY + HEIGHT_DISTANCE +i*HEIGHT_DISTANCE));
        this->addChild(barrier,200);
        int randomTypeMonster = this->randomTypeMonster();
        if(i != indexNotMonster && i != hiddenIndex)
        {
            Monster* monster = new Monster();
            if(randomTypeMonster == 0)
            {
                monster->setPosition(Vec2(randomPostionX1, barrier->getPositionY()));
            }
            else
            {
                monster->setPosition(Vec2(randomPostionX2, barrier->getPositionY()));
            }
            if(veclocityMonster + i/40 > DELTA_CHARARTER){
                veclocityMonster = DELTA_CHARARTER - i/40;
            }
            monster->setVeclocity(veclocityMonster + i/40);
            monster->setTypeMonster(randomTypeMonster);
            monster->initMonsterWithSpine();
            if( i == randomSlice1 || i == randomSlice2) {
                monster->setSliceMonster(true);
                if(i == randomSlice1){
                    monster->setScaleX(-1);
                     monster->setPosition(Vec2(intWidth1*0.9, barrier->getPositionY()));
                }else{
                     monster->setPosition(Vec2(intWidth2*1.2, barrier->getPositionY()));
                }
                monster->addPrisoner();
            }else{
                monster->setSliceMonster(false);
            }
            this->addChild(monster,200);
            gameManager->manageBarrierAndMonster(barrier, monster);
        }
        else
        {
            gameManager->manageBarrierAndMonster(barrier, NULL);
        }
    }
}

void MonsterLayer::initPhysicLanding()
{
    /*setup bottom land*/
    b2PolygonShape shapeLand;
    shapeLand.SetAsBox((visibleSize.width)/PTM_RATIO, (HALF_PASS_HEIGHT_LANGDING*3/4) /PTM_RATIO);
    b2FixtureDef WallFixDef;
    WallFixDef.density = 0;
    WallFixDef.friction = 0;
    WallFixDef.restitution  = 0.0;
    WallFixDef.shape = &shapeLand;
    WallFixDef.filter.categoryBits = kLandCatBit;
    WallFixDef.filter.maskBits = kLandMaskBit;
    b2BodyDef landBodyDef;
    landBodyDef.type = b2_staticBody;
    landBodyDef.position.Set(pointStart.x/PTM_RATIO, pointStart.y/2/PTM_RATIO);
    b2Body* body = physicWorld->CreateBody(&landBodyDef);
    body->CreateFixture(&WallFixDef);
    
    /*setup left land*/
    b2PolygonShape shapeLeftLand;
    shapeLeftLand.SetAsBox((10)/PTM_RATIO, (Director::getInstance()->getWinSize().height*1000) /PTM_RATIO);
    b2FixtureDef WallLeftFixDef;
    WallLeftFixDef.density = 0.0f;
    WallLeftFixDef.friction = 0;
    WallLeftFixDef.restitution  = -10.0;
    WallLeftFixDef.shape = &shapeLeftLand;
    WallLeftFixDef.filter.categoryBits = kWallFiniteCatBit;
    WallLeftFixDef.filter.maskBits = kWallFiniteMasBit;
    b2BodyDef landLeftBodyDef;
    landLeftBodyDef.type = b2_staticBody;
    landLeftBodyDef.position.Set((visibleSize.width)/PTM_RATIO, (visibleSize.height/2)/PTM_RATIO);
    b2Body* bodyLeft = physicWorld->CreateBody(&landLeftBodyDef);
    bodyLeft->CreateFixture(&WallLeftFixDef);
    
    
    /*setup right land*/
    b2PolygonShape shapeRighttLand;
    shapeRighttLand.SetAsBox((10)/PTM_RATIO, (Director::getInstance()->getWinSize().height*1000) /PTM_RATIO);
    b2FixtureDef WallRightFixDef;
    WallRightFixDef.density = 0.0f;
    WallRightFixDef.friction = 0;
    WallRightFixDef.restitution  = -10.0;
    WallRightFixDef.shape = &shapeRighttLand;
    WallRightFixDef.filter.categoryBits = kWallFiniteCatBit;
    WallRightFixDef.filter.maskBits = kWallFiniteMasBit;
    b2BodyDef landRightBodyDef;
    landRightBodyDef.type = b2_staticBody;
    landRightBodyDef.position.Set(0/PTM_RATIO, (visibleSize.height/2) /PTM_RATIO);
    b2Body* bodyRightLand = physicWorld->CreateBody(&landRightBodyDef);
    bodyRightLand->CreateFixture(&WallRightFixDef);
    physicWorld->SetDebugDraw(new TestBody());
    physicWorld->SetAllowSleeping(false);
}


void MonsterLayer::onEnter()
{
    Layer::onEnter();
    
}
void MonsterLayer::onExit()
{
    Layer::onExit();
    
}







