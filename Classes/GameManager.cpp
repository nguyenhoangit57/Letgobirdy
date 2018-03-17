//
//  GameManager.cpp
//  JumpingSnail
//
//  Created by Hoang Nguyen on 1/16/17.
//
//

#include "GameManager.h"
#include "GameDefineState.h"

GameManager::GameManager()
{
    isGameOver = false;
    if(!arrayBarrier.empty())
    {
        arrayBarrier.clear();
    }
    if(!arrayMonster.empty())
    {
        arrayMonster.clear();
    }
}
GameManager::~GameManager()
{
    this->clearDataForGame();
}
void GameManager::manageBarrierAndMonster(Barrier* barrier , Monster* monster)
{
    if(barrier != NULL)
    {
        arrayBarrier.push_back(barrier);
    }
    if(monster != NULL)
    {
        arrayMonster.push_back(monster);
    }
}

void GameManager::addMonster(Barrier* barrier)
{
    
}
void GameManager::addBarrier(Barrier* barrier)
{
    
}
void GameManager::managerCharacter(Character* character)
{
    this->character = character;
}
void GameManager::restartGameManager()
{
    isGameOver = false;
    if(!arrayBarrier.empty())
    {
        arrayBarrier.clear();
    }
    if(!arrayMonster.empty())
    {
        arrayMonster.clear();
    }
}

void GameManager::update(float dt, bool isUpdatePhyic)
{
    if(isGameOver == false)
    {
        if(!arrayBarrier.empty())
        {
            for(std::vector<Barrier*>::iterator it = arrayBarrier.begin(); it != arrayBarrier.end(); ++it) {
                
                if(!(*it)->getIsPhysic()&& character->getNewStateNewCharacter())
                {
                    if(character->getPositionY() > ((*it)->getPositionY() - (*it)->getContentSize().height*0.2))
                    {
                        character->setCurrentHeight((*it)->getPositionY());
                        (*it)->initBodyWithPhysicManager(worldPhyicManger, (*it)->getPosition());
                        (*it)->activeUpdatePhysic();
                        
                    }
                }
            }
        }
        if(!arrayMonster.empty())
        {
            for(std::vector<Monster*>::iterator it = arrayMonster.begin(); it != arrayMonster.end(); ++it)
            {
                (*it)->update(dt);
                if(character->checkDieCharacter( (*it)->getPosition()) && character->getCheckGameOver())
                {
                    isGameOver = true;
                    character->changeStateToDie();
                }
            }
        }
    }
}

void GameManager::setVisiableWhenTouch()
{
    for(std::vector<Barrier*>::iterator it = arrayBarrier.begin(); it != arrayBarrier.end(); ++it) {
        if((*it)->getPositionY() > character->getPositionY() + HEIGHT_DISTANCE * 5)
        {
            (*it)->setVisible(false);
        }
        else if((*it)->getPositionY() < character->getPositionY() - HEIGHT_DISTANCE *1.5)
        {
            arrayBarrier.erase(it);
        }
        else{
            (*it)->setVisible(true);
        }
    }
    for(std::vector<Monster*>::iterator it = arrayMonster.begin(); it != arrayMonster.end(); ++it) {
        if((*it)->getPositionY() > character->getPositionY() + HEIGHT_DISTANCE * 5)
        {
            (*it)->setVisible(false);
        }
        else if((*it)->getPositionY() < character->getPositionY() - HEIGHT_DISTANCE*1.5 )
        {
            arrayMonster.erase(it);
        }
        else{
            (*it)->setVisible(true);
        }
    }
}

int GameManager::getCountBarrier()
{
    return (int)arrayBarrier.size();
}

void GameManager::clearDataForGame()
{
    if(!arrayBarrier.empty())
    {
        arrayBarrier.clear();
    }
    if(!arrayMonster.empty())
    {
        arrayMonster.clear();
    }
}
void GameManager::initPhysic(b2World* world)
{
    worldPhyicManger = world;
}

