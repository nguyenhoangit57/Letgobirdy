//
//  GameDefineState.h
//  JumpingSnail
//
//  Created by Hoang Nguyen on 1/16/17.
//
//

#ifndef GameDefineState_h
#define GameDefineState_h

#define MAX_BARRIER_LEVEL 10
#define DELTA_CHARARTER 7.4
#define DELTA_MONSTER_A 5
#define PTM_RATIO 32.0f
#define BUFFER_SIZE_HEIGHT 50.0f
#define WIDTH_RUN_BUFFER 60.0f
#define TIME_RUN_ACTION_SCREEN 0.6f
#define RATIO_SCALE_CHARACTER 0.104f
#define RATIO_SCALE_MONSTER 0.086f
#define START_VEC_START Vec2(-140,-140)

#define GRAVITY b2Vec2(0.0f, -80.0f)
#define VECLOCITY_JUMP_X  6.0f
#define VECLOCITY_ONE_JUMP_Y 16.2f
#define VECLOCITY_DOUBLE_JUMP_Y 11
#define SCALE_X_BIRD 1.6
#define SCALE_Y_BIRD 2.08

typedef enum
{
    RUNNING = 0,
    PAUSING = 1,
    IDLE = 2,
} STATE_BARRIER;



typedef enum
{
    C_RUNNING = 0,
    C_PAUSING = 1,
    C_DIE = 2,
    C_IDLE = 3,
} STATE_CHARACTER;


typedef enum
{
    LEFT = 1,
    RIGHT = 2,
    CONTACT_LANDING = 3,
    CONTACT_WALL = 4,
    FLYING = 5,
    PAUSE = 6,
    CONTACT_BARRIER = 7,
    IDLE_CHARACTER = 8,
    DIE_CHARACTER  = 9,
}DIRECTOR_MONSTER;



enum{
    kCharactorCatBit = 1 << 0,    // nhan vat
    kLandCatBit = 1 << 1,       // mat dat
    kBarrierCatBit = 1 << 2,  // vat can
    kNewChacracterCatBit = 1<< 3, // nhan vat moi
    kWallFiniteCatBit = 1 << 4,
    
};

enum{
    kCharactorMaskBit =  kWallFiniteCatBit | kLandCatBit ,
    kLandMaskBit =  kNewChacracterCatBit | kCharactorCatBit,
    kBarrierMaskBit = kNewChacracterCatBit,
    kNewCharacterMaskBit = kBarrierCatBit |kLandCatBit | kWallFiniteCatBit,
    kWallFiniteMasBit = kCharactorCatBit | kNewChacracterCatBit ,
};




typedef enum
{
    TAG_BTN_MENU_POPUP = 501,
    TAG_BTN_HOME_POPUP = 503,
    TAG_BTN_SOUND_ON_POPUP = 504,
    TAG_BTN_SOUND_OFF_POPUP = 505,
}TAG_POP_UP;


#define HEIGHT_DISTANCE 200.0f
#define HALF_PASS_HEIGHT_LANGDING 58.0f
#endif /* GameDefineState_h */
