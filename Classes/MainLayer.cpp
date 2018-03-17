#include "MainLayer.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "GameDefineState.h"
#include "HomeScene.h"
#include "Admob.h"
#include "AdmodAndroid.h"
#define TAG_CHARACTER 21
#define TAG_LEVEL_LAYER 20
#define COLOR_BG_POP_UP_START Color4B(50.0f/255.0f, 50.0f/255.0f, 50.0f/255.0f,100.0f)
#define COLOR_BG_POP_UP_END Color4B(115.0f/255.0f, 115.0f/255.0f, 115.0f/255.0f,200.0f)
#define TAG_START_LAYER 1234
#define TAG_BTN_SOUND_ON 145
#define TAG_BTN_SOUND_OFF 146
#define TAG_BTN_REPLAY  205
#define TAG_BTN_HOME  206
#define TAG_BTN_SHARE  207
#define TAG_BTN_CLOSE  208
#define TAG_BTN_PLAY  209

static char bufferScore[512] = {0};

bool MainLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    Admob::getInstance()->showBanner(AdmobPosition::TopCenter);
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AdmodAndroid::showBanner();
#endif
    isUpdate = true;
    isUpdatePhyic = false;
    isGameOver = false;
    isReadyTouch = true;
    isTouchContinue = false;
    indexTouch = 0;
    score = 0;
    visibleSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();
    heightCenterScreen = visibleSize.height/2;
    
    physicWorld = new b2World(GRAVITY);
    MyListender* listenrContact = new MyListender();
    listenrContact->setDelegate(this);
    physicWorld->SetContactListener(listenrContact);
    physicWorld->SetAllowSleeping(false);
    
    /*
     LevelGameScene
     */
    this->creacreateCharacter();
    gameManager = new  GameManager();
    gameManager->managerCharacter(character);
    
    
    UserDefault::getInstance()->setIntegerForKey("ShowVideo",  UserDefault::getInstance()->getIntegerForKey("ShowVideo", 0) + 1);
    
    monsterLayer = MonsterLayer::create();
    monsterLayer->setAnchorPoint(Vec2(0, 0));
    monsterLayer->setPosition(Vec2(0,0));
    monsterLayer->setGameManager(gameManager);
    monsterLayer->initPhysicForMap(physicWorld);
    level = 0;
    indexRandomNotMonster = 0;
    monsterLayer->createMapWithMonster(level,MAX_BARRIER_LEVEL, HALF_PASS_HEIGHT_LANGDING,indexRandomNotMonster);
    this->addChild(monsterLayer,TAG_LEVEL_LAYER);
    this->scheduleUpdate();
    
    
    /*
     Label Score
     */
    lbScore = Label::createWithTTF("Score 0", "HGEOSLAB.TTF", 40);
    lbScore->setVisible(false);
    lbScore->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.86f));
    this->addChild(lbScore,100);
    
    /*Start Layer*/
    this->createStartGame();
    
    return true;
}
void MainLayer::creacreateCharacter()
{
    character =  new Character();
    character->setPosition(Vec2(0, HALF_PASS_HEIGHT_LANGDING));
    character->createCharacterBySpine();
    character->setVeclocity(DELTA_CHARARTER);
    character->setCurrentHeight(HALF_PASS_HEIGHT_LANGDING);
    character->defineBodyCharacter(physicWorld);
    character->setDelegate(this);
    this->addChild(character,TAG_CHARACTER);
    
}

void MainLayer::createStartGame()
{
    
    LayerColor* colorBgStart = LayerColor::create(COLOR_BG_POP_UP_START, visibleSize.width, visibleSize.height);
    colorBgStart->setPosition(Vec2::ZERO);
    colorBgStart->setTag(TAG_START_LAYER);
    this->addChild(colorBgStart,500);
    
    
    auto spriteHelp = Sprite::create("help_dialog.png");
    spriteHelp->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.56f));
    colorBgStart->addChild(spriteHelp,1);
    
    
    /**/
    auto btnPlay = ui::Button::create("button_click.png","","",ui::Widget::TextureResType::LOCAL);
    btnPlay->setPosition(Vec2(spriteHelp->getPositionX(),spriteHelp->getPositionY() - spriteHelp->getContentSize().height/2 - btnPlay->getContentSize().height));
    btnPlay->addClickEventListener(CC_CALLBACK_1(MainLayer::btnClickSound,this));
    btnPlay->setSwallowTouches(true);
    btnPlay->setZoomScale(0.1f);
    btnPlay->setTag(TAG_BTN_PLAY);
    colorBgStart->addChild(btnPlay,3);
    
    auto touchListerStart = EventListenerTouchOneByOne::create();
    touchListerStart->setSwallowTouches(true);
    touchListerStart->onTouchBegan = [=](Touch* pTouch, Event* mEvent){
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListerStart, colorBgStart);
    
}

void MainLayer::update(float dt)
{
    if(isUpdate)
    {
        if(!isGameOver)
        {
            if(physicWorld)
            {
                physicWorld->Step(dt, 100, 1);
            }
            if(monsterLayer)
            {
                monsterLayer->update(dt, isUpdatePhyic);
            }
            if(gameManager->getCountBarrier() < 6)
            {
                level ++;
                srand( (unsigned)time(NULL) );
                indexRandomNotMonster = rand() % MAX_BARRIER_LEVEL - 1;
                monsterLayer->createMapWithMonster(level,MAX_BARRIER_LEVEL, HALF_PASS_HEIGHT_LANGDING + MAX_BARRIER_LEVEL*HEIGHT_DISTANCE*level,indexRandomNotMonster);
            }
        }
    }
}



/*
 Delegate My Listenner implement
 */
void MainLayer::restoreIndexListener(int stdLister)
{
    indexTouch = stdLister;
}
void MainLayer::contactWithLanding()
{
    if(character)
    {
        character->contactWithLanding();
    }
}
void MainLayer::contactWithWall()
{
    if(character)
    {
        character->contactWithWall();
    }
}

void MainLayer::resetTouch()
{
    indexTouch = 0;
    isReadyTouch = true;
    isTouchContinue = true;
}

bool MainLayer::onTouchOneByOneBegan(Touch* mTouch, Event* pEvent)
{
    /**
     Logic here
     */
    if(character->isCanTouch == true) {
        if(isGameOver == false && character->getFirsRun() == false)
        {
            if(character->getStateChacter() != C_PAUSING) {
                indexTouch ++;
            }
            if(indexTouch == 1 && isReadyTouch)
            {
                isUpdatePhyic = false;
                isTouchContinue = true;
                isReadyTouch = false;
                character->changeStateToJumpOneTouch();
            }
            if(indexTouch == 2 && isReadyTouch == false && isTouchContinue == true)
            {
                isTouchContinue = false;
                character->changeStateJumpTwoTouch();
                indexTouch = 0;
            }
            if(indexTouch >= 2)
            {
                isReadyTouch = true;
                indexTouch = 0;
            }
        }
    }
    if(this->getChildByTag(999))
    {
        isReadyTouch = true;
        isUpdate = true;
        this->removeChildByTag(999);
    }
    if(character->getStateChacter() == C_PAUSING){
        character->setState(C_RUNNING);
    }
    if(this->getChildByTag(1236)){
        this->getChildByTag(1236)->setVisible(false);
    }
    
    return true;
}
void MainLayer::onTouchOneByOneEnd(Touch* mTouch, Event* pEvent)
{
    
}


void MainLayer::jumpCharacterReadyTouch()
{
    isReadyTouch = true;
    isTouchContinue = true;
}


/*
 Delegate Character implement
 */

void MainLayer::dieCharacterForgame()
{
    UserDefault::getInstance()->setIntegerForKey("FirstOpen", false);
    if ( UserDefault::getInstance()->getIntegerForKey("ShowVideo", 0) > 8){
        UserDefault::getInstance()->setIntegerForKey("ShowVideo", 0);
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
    isGameOver = true;
    this->unschedule("Show-GameOver");
    this->scheduleOnce([=](float dt){
        this->createGameOverLayer();
    }, 1.8f, "Show-GameOver");
}

void MainLayer::jumpCharacterComplete(bool complete)
{
    
    if(complete)
    {
        isUpdatePhyic = true;
        score ++;
        sprintf(bufferScore, "Score %d", score);
        lbScore->setString(bufferScore);
        
        heightCenterScreen += HEIGHT_DISTANCE;
        auto action1 = MoveTo::create(TIME_RUN_ACTION_SCREEN, Vec2(this->getPositionX(), this->getPositionY() - HEIGHT_DISTANCE));
        auto action2 = DelayTime::create(0.0f);
        auto action3 = CallFunc::create([=](){
            gameManager->setVisiableWhenTouch();
        });
        this->runAction(Sequence::create(action1,action2,action3, NULL));
        
        lbScore->runAction(MoveTo::create(TIME_RUN_ACTION_SCREEN, Vec2(lbScore->getPositionX(), lbScore->getPositionY() + HEIGHT_DISTANCE)));
        
         buttonHome->runAction(MoveTo::create(TIME_RUN_ACTION_SCREEN, Vec2(buttonHome->getPositionX(), buttonHome->getPositionY() + HEIGHT_DISTANCE)));
        
        
         buttonSoundOn->runAction(MoveTo::create(TIME_RUN_ACTION_SCREEN, Vec2(buttonSoundOn->getPositionX(), buttonSoundOn->getPositionY() + HEIGHT_DISTANCE)));
        
         buttonSoundOff->runAction(MoveTo::create(TIME_RUN_ACTION_SCREEN, Vec2(buttonSoundOff->getPositionX(), buttonSoundOff->getPositionY() + HEIGHT_DISTANCE)));
    }
}
/*
 Event click sound on - sound off
 */

void MainLayer::btnClickSound(Ref* psender)
{
    int  tag =  ((ui::Button*)psender)->getTag();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundClick.mp3");
    if(tag == TAG_BTN_SOUND_ON)
    {
        
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
        UserDefault::getInstance()->setBoolForKey("Sound-OnGame", false);
    }
    if(tag == TAG_BTN_SOUND_OFF)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
        UserDefault::getInstance()->setBoolForKey("Sound-OnGame", true);
    }
    if(tag == TAG_BTN_REPLAY)
    {
        gameManager->restartGameManager();
        Director::getInstance()->replaceScene(GameScene::createGameScene());
    }
    if(tag == TAG_BTN_HOME)
    {
        gameManager->restartGameManager();
        Director::getInstance()->replaceScene(HomeScene::createHomeScene());
    }
    
    if(tag == TAG_BTN_SHARE)
    {
#if  CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        Application::getInstance()->openURL("https://itunes.apple.com/us/developer/nguyen-chi-hoang/id1208114740");
#endif
#if  CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        Application::getInstance()->openURL("https://play.google.com/store/apps/developer?id=MacroGame&hl=en");
#endif
    }
    if(tag == TAG_BTN_CLOSE)
    {
        character->setState(C_RUNNING);
        isUpdate = true;
        isReadyTouch = true;
        if(this->getChildByTag(999))
        {
            this->removeChildByTag(999);
        }
    }
    if(tag == TAG_BTN_PLAY){
        
        lbScore->setVisible(true);
        if(this->getChildByTag(TAG_START_LAYER))
        {
            this->removeChildByTag(TAG_START_LAYER);
        }
        auto touchLister = EventListenerTouchOneByOne::create();
        touchLister->setSwallowTouches(true);
        touchLister->onTouchBegan = CC_CALLBACK_2(MainLayer::onTouchOneByOneBegan, this);
        touchLister->onTouchEnded = CC_CALLBACK_2(MainLayer::onTouchOneByOneEnd, this);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchLister, this);
        
        this->createShowButtonRightLayout();
    }
}



void MainLayer::createGameOverLayer()
{
    buttonSoundOff->setVisible(false);
    buttonSoundOn->setVisible(false);
    buttonHome->setVisible(false);
    int showAdd =  UserDefault::getInstance()->getIntegerForKey("ShowAdd", 0);
    if(showAdd < 7)
    {
        showAdd++;
        UserDefault::getInstance()->setIntegerForKey("ShowAdd", showAdd);
    }else
    {
        Admob::getInstance()->loadInterstitial();
        Admob::getInstance()->showInterstitial();
        UserDefault::getInstance()->setIntegerForKey("ShowAdd", 0);
    }
    
    int hightScore = UserDefault::getInstance()->getIntegerForKey("Hight-Score", 0);
    if(score >= hightScore)
    {
        hightScore = score;
        UserDefault::getInstance()->setIntegerForKey("Hight-Score", score);
    }
    
    
    LayerColor* layerGameOver = LayerColor::create(COLOR_BG_POP_UP_END, visibleSize.width, visibleSize.height);
    layerGameOver->setPosition(Vec2(0, heightCenterScreen - visibleSize.height/2));
    this->addChild(layerGameOver,600);
    
    
    
    /*Icon game here*/
    auto spLogo = Sprite::create("logoGame.png");
    spLogo->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.76));
    layerGameOver->addChild(spLogo,1);
    
    /*Icon game here*/
    auto spEndGame = Sprite::create("end_dialog.png");
    spEndGame->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.4));
    layerGameOver->addChild(spEndGame,1);
    
    
    
    char bufferTotalScore[512] = {0};
    sprintf(bufferTotalScore, "%d", score);
    Label* totalScore = Label::createWithTTF(bufferTotalScore, "HGEOSLAB.TTF", 32);
    totalScore->setPosition(Vec2(spEndGame->getPositionX(), spEndGame->getPositionY() + totalScore->getContentSize().height*1.6));
    totalScore->setTextColor(Color4B::WHITE);
    layerGameOver->addChild(totalScore,2);
    
    Label* lbTitleScore = Label::createWithTTF("Score:", "HGEOSLAB.TTF", 36);
    lbTitleScore->setPosition(Vec2(totalScore->getPositionX(), totalScore->getPositionY() + lbTitleScore->getContentSize().height*0.8));
    lbTitleScore->setTextColor(Color4B::YELLOW);
    layerGameOver->addChild(lbTitleScore,2);
    
    
    Label* lbTitleBestScore = Label::createWithTTF("Best score:", "HGEOSLAB.TTF", 36);
    lbTitleBestScore->setPosition(Vec2(spEndGame->getPositionX(), spEndGame->getPositionY() - totalScore->getContentSize().height/6));
    lbTitleBestScore->setTextColor(Color4B::YELLOW);
    layerGameOver->addChild(lbTitleBestScore,2);
    
    char bufferEndGame[512] = {0};
    sprintf(bufferEndGame, "%d", hightScore);
    Label* lbHightScoreEndGame = Label::createWithTTF(bufferEndGame, "HGEOSLAB.TTF", 32);
    lbHightScoreEndGame->setPosition(Vec2(totalScore->getPositionX(), lbTitleBestScore->getPositionY() - lbHightScoreEndGame->getContentSize().height*0.8));
    lbHightScoreEndGame->setTextColor(Color4B::WHITE);
    layerGameOver->addChild(lbHightScoreEndGame,2);
    
    
    /**
     Replay
     */
    auto btnReplay = ui::Button::create("button_replay_normal.png","","",ui::Widget::TextureResType::LOCAL);
    btnReplay->setPosition(Vec2(spEndGame->getPositionX() - 5.0f, spEndGame->getPositionY() - spEndGame->getContentSize().height*0.3));
    btnReplay->addClickEventListener(CC_CALLBACK_1(MainLayer::btnClickSound,this));
    btnReplay->setSwallowTouches(true);
    btnReplay->setZoomScale(0.1f);
    btnReplay->setTag(TAG_BTN_REPLAY);
    layerGameOver->addChild(btnReplay,3);
    
    auto btnHome = ui::Button::create("button_home_normal.png","","",ui::Widget::TextureResType::LOCAL);
    btnHome->setPosition(Vec2(btnReplay->getPositionX() - btnHome->getContentSize().width*1.4,btnReplay->getPositionY() + btnHome->getContentSize().height*0.3));
    btnHome->addClickEventListener(CC_CALLBACK_1(MainLayer::btnClickSound,this));
    btnHome->setSwallowTouches(true);
    btnHome->setZoomScale(0.1f);
    btnHome->setTag(TAG_BTN_HOME);
    layerGameOver->addChild(btnHome,3);
    
    auto btnShare = ui::Button::create("button_share_normal.png","","",ui::Widget::TextureResType::LOCAL);
    btnShare->setPosition(Vec2(btnReplay->getPositionX() + btnShare->getContentSize().width*1.4,btnReplay->getPositionY() + btnShare->getContentSize().height*0.3));
    btnShare->addClickEventListener(CC_CALLBACK_1(MainLayer::btnClickSound,this));
    btnShare->setSwallowTouches(true);
    btnShare->setZoomScale(0.1f);
    btnShare->setTag(TAG_BTN_SHARE);
    layerGameOver->addChild(btnShare,3);
    
    
    /*Add Touch Event*/
    auto touchGameOver = EventListenerTouchOneByOne::create();
    touchGameOver->setSwallowTouches(true);
    touchGameOver->onTouchBegan = [=](Touch* mtouch, Event* pEvent){
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchGameOver, layerGameOver);
}



void MainLayer::btnClickHomeHelpSoundButton(Ref* psender){
    int  tag =  ((ui::Button*)psender)->getTag();
    if(tag == TAG_BTN_HOME_POPUP)
    {
        Director::getInstance()->replaceScene(HomeScene::createHomeScene());
    }
    if(tag == TAG_BTN_SOUND_ON_POPUP){
        buttonSoundOff->setVisible(true);
        buttonSoundOn->setVisible(false);
         UserDefault::getInstance()->setBoolForKey("Sound-OnGame", false);
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
    }
    if(tag == TAG_BTN_SOUND_OFF_POPUP){
        buttonSoundOff->setVisible(false);
        buttonSoundOn->setVisible(true);
        UserDefault::getInstance()->setBoolForKey("Sound-OnGame", true);
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
    }
}

void MainLayer::createShowButtonRightLayout(){
    buttonHome = cocos2d::ui::Button::create("btn_home_normal.png","","",ui::Widget::TextureResType::LOCAL);
    buttonHome->setPosition(Vec2(visibleSize.width*0.9, visibleSize.height*0.86));
    buttonHome->setZoomScale(0.1f);
        buttonHome->setScale(1.2);
    buttonHome->setSwallowTouches(true);
    buttonHome->setTag(TAG_BTN_HOME_POPUP );
    buttonHome->addClickEventListener(CC_CALLBACK_1(MainLayer::btnClickHomeHelpSoundButton,this));
    buttonHome->setSwallowTouches(true);
    this->addChild(buttonHome,600);
    
    
    buttonSoundOn = cocos2d::ui::Button::create("btn_sound_on_normal.png","","",ui::Widget::TextureResType::LOCAL);
    buttonSoundOn->setPosition(Vec2(buttonHome->getPositionX(), buttonHome->getPositionY() - buttonSoundOn->getContentSize().height*1.4));
    buttonSoundOn->setSwallowTouches(true);
    buttonSoundOn->setScale(1.2);
    buttonSoundOn->setZoomScale(0.1f);
    buttonSoundOn->setTag(TAG_BTN_SOUND_ON_POPUP );
    buttonSoundOn->addClickEventListener(CC_CALLBACK_1(MainLayer::btnClickHomeHelpSoundButton,this));
    buttonSoundOn->setSwallowTouches(true);
    this->addChild(buttonSoundOn,600);
    
    
    buttonSoundOff = cocos2d::ui::Button::create("btn_sound_off_normal.png","","",ui::Widget::TextureResType::LOCAL);
    buttonSoundOff->setPosition(buttonSoundOn->getPosition());
    buttonSoundOff->setSwallowTouches(true);
    buttonSoundOff->setScale(1.2);
    buttonSoundOff->setZoomScale(0.1f);
    buttonSoundOff->setTag(TAG_BTN_SOUND_OFF_POPUP );
    buttonSoundOff->addClickEventListener(CC_CALLBACK_1(MainLayer::btnClickHomeHelpSoundButton,this));
    buttonSoundOff->setSwallowTouches(true);
    this->addChild(buttonSoundOff,600);
    
    
    if(UserDefault::getInstance()->getBoolForKey("Sound-OnGame", true))
    {
        buttonSoundOff->setVisible(false);
        buttonSoundOn->setVisible(true);
    }
    else
    {
        buttonSoundOff->setVisible(true);
        buttonSoundOn->setVisible(false);
    }
}

/*
 render physic use Draw cocos2d-x
 */

void MainLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags){
    Layer::draw(renderer, transform, flags);
    debugCommand.init(INT_MAX);
    debugCommand.func = CC_CALLBACK_0(MainLayer::drawPhysics, this, renderer, transform, flags);
    renderer->addCommand(&debugCommand);
}

void MainLayer::drawPhysics(Renderer *renderer, const Mat4 &transform, uint32_t flags){
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    // physicWorld->DrawDebugData();
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void MainLayer::onEnter()
{
    Layer::onEnter();
    EventListenerKeyboard *keyboardEvent = EventListenerKeyboard::create();
    keyboardEvent->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event*){
        if(keyCode == EventKeyboard::KeyCode::KEY_BACK){
            Director::getInstance()->replaceScene(HomeScene::createHomeScene());
        }
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardEvent, this);
}
void MainLayer::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}


