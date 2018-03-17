

#include "cocos2d.h"
#include "MonsterLayer.h"
#include "MyListenner.h"
#include "GameDefineState.h"
#include "Character.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"
USING_NS_CC;



class MainLayer : public cocos2d::Layer, DelegateListener, DelegateCharacter
{
private:
    int indexRandomNotMonster;
    int level;
    int indexTouch;
    Size visibleSize;
    Vec2 origin;
    Vec2 positionStartBarrier;
    MonsterLayer* monsterLayer;
    b2World* physicWorld;
    Character* character;
    CustomCommand debugCommand;
    
    cocos2d::ui::Button* buttonSoundOn;
    cocos2d::ui::Button* buttonSoundOff;
    cocos2d::ui::Button* buttonHome;
    
    bool isGameOver;
    bool isReadyTouch;
    Label* lbScore;
    bool isStartGame;
    float heightCenterScreen;
    bool isTouchContinue;
    int score;
    bool isUpdatePhyic;
    float centerDirertor;
    GameManager* gameManager;
    bool isUpdate;
public:
    virtual bool init();
    CREATE_FUNC(MainLayer);
    void update(float dt);
    void onEnter();
    void onExit();
    /*
     Create character for game
     */
    void creacreateCharacter();
    
    
    /*
     Render Body i can see real contact for every thing
     */
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    virtual void drawPhysics(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    
    void createStartGame();
    
    /*
     Delegate Character
     */
    virtual void jumpCharacterComplete(bool complete);
    virtual void jumpCharacterReadyTouch();
    virtual void dieCharacterForgame();
    virtual void resetTouch();
    
    
    /*
     Delegate contact
     */
    void restoreIndexListener(int stdLister);
    virtual void contactWithLanding();
    virtual void contactWithWall();
    
    /*
     Touch
     */
    bool onTouchOneByOneBegan(Touch* mTouch, Event* pEvent);
    void onTouchOneByOneEnd(Touch* mTouch, Event* pEvent);
    
    /*
     Event when click sound on - sound off
     */
    void btnClickSound(Ref* psender);
    
    /*
     Create GameOverScene
     */
    void createGameOverLayer();
    
    void createShowButtonRightLayout();
    /*
     Event when click sound on - sound off
     */
    void btnClickHomeHelpSoundButton(Ref* psender);
    
};

