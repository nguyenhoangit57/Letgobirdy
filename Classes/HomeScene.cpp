//
//  HomeScene.cpp
//  JumpingSnail
//
//  Created by Nguyen Chi Hoang on 4/5/17.
//
//

#include "HomeScene.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "Admob.h"
#include "AdmodAndroid.h"
#include "SimpleAudioEngine.h"
#define TAG_BTN_PLAY 101
Scene* HomeScene::createHomeScene()
{
    auto scene = Scene::create();
    auto layer = HomeScene::create();
    scene->addChild(layer);
    return scene;
}
bool HomeScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    UserDefault::getInstance()->setIntegerForKey("HomeFullVideo", UserDefault::getInstance()->getIntegerForKey("HomeFullVideo", 0) + 1);
    if(UserDefault::getInstance()->getIntegerForKey("HomeFullVideo", 0) > 8) {
        UserDefault::getInstance()->setIntegerForKey("HomeFullVideo",0);
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        Admob::getInstance()->loadInterstitial();
        Admob::getInstance()->showInterstitial();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        AdmodAndroid::showFullAdvertiment();
#endif
    }else{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        Admob::getInstance()->showBanner(AdmobPosition::TopCenter);
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        AdmodAndroid::showBanner();
#endif
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("musicgame.mp3",true);
    winSize = Director::getInstance()->getWinSize();
    auto bg = Sprite::create("bg_start.png");
    bg->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->addChild(bg,1);
    
    auto spLogo = Sprite::create("logoGame.png");
    spLogo->setPosition(Vec2(winSize.width/2, winSize.height*0.56));
    spLogo->setScale(0.8);
    this->addChild(spLogo,2);
    
    ui::Button* btnPlay = ui::Button::create("button_play_normal.png","","",ui::Widget::TextureResType::LOCAL);
    btnPlay->setZoomScale(0.1f);
    btnPlay->setPosition(Vec2(winSize.width/2, spLogo->getPositionY() - btnPlay->getContentSize().height*2.0));
    btnPlay->setTag(TAG_BTN_PLAY);
    
    btnPlay->addClickEventListener(CC_CALLBACK_1(HomeScene::eventClickPlay,this));
    btnPlay->setSwallowTouches(true);
    this->addChild(btnPlay,3);
    
    Admob::getInstance()->showBanner(AdmobPosition::TopCenter);
    return true;
}
void HomeScene::update(float dt)
{
    
}

void HomeScene::eventClickPlay(Ref* pSender)
{
    int  tag =  ((ui::Button*)pSender)->getTag();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundClick.mp3");
    if(tag == TAG_BTN_PLAY)
    {
        Director::getInstance()->replaceScene(GameScene::createGameScene());
    }
}


void HomeScene::onEnter()
{
    Layer::onEnter();
    EventListenerKeyboard *keyboardEvent = EventListenerKeyboard::create();
    keyboardEvent->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event*){
        if(keyCode == EventKeyboard::KeyCode::KEY_BACK){
            Director::getInstance()->end();
        }
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardEvent, this);
}
void HomeScene::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}
