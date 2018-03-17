//
//  GameScene.cpp
//  JumpingSnail
//
//  Created by Hoang Nguyen on 2/14/17.
//
//

#include "GameScene.h"
#include "MainLayer.h"
#define COLOR_BG_POP_UP_START Color4B(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f,0.0f)
Scene* GameScene::createGameScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    auto mainLayer = MainLayer::create();
    scene->addChild(layer,1);
    scene->addChild(mainLayer,2);
    
    auto leftLanding = Sprite::create("tree_decor.png");
    leftLanding->setPosition(Vec2(leftLanding->getContentSize().width/8, Director::getInstance()->getWinSize().height/2));
    scene->addChild(leftLanding,4);
    
    auto rightLanding = Sprite::create("tree_decor.png");
    rightLanding->setPosition(Vec2( Director::getInstance()->getWinSize().width - leftLanding->getContentSize().width/8, Director::getInstance()->getWinSize().height/2));
    rightLanding->setScaleX(-1);
    scene->addChild(rightLanding,4);
    
    return scene;
}
bool GameScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    visibleSize = Director::getInstance()->getWinSize();
    this->createBackGroundForGame();
    
    return true;
}
void GameScene::update(float dt)
{
    
}

/*
 create back ground for game scenen
 */
void GameScene::createBackGroundForGame()
{
    Sprite* bg = Sprite::create("bg.png");
    bg->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(bg,1);
    
    
}



