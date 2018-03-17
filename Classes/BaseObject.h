//
//  BaseObject.h
//  JumpingSnail
//
//  Created by Hoang Nguyen on 12/13/16.
//
//

#ifndef BaseObject_h
#define BaseObject_h

#include <stdio.h>
#include "cocos2d.h"
#include <Box2D/Box2D.h>
USING_NS_CC;

class BaseObject : public Sprite
{
protected:
    bool isPhysic;
    int state;
    bool isFlip;
    float vecloCity;
    bool isUpdateStatus;
public:
    BaseObject();
    virtual ~BaseObject();
    virtual void createWithFileName(const char* fileName);
    virtual void createWithFrameName(const char* fileName);
    virtual void createWithAnimation();
    void setNewState(int newstate);
    int getStateCurrent();
    void setFlipSprite(bool isFlip);
    void onEnter();
    void onExit();
    virtual void update(float dt);
    void setPositionObject(const Vec2& pos);
    Vec2 getPositionObject();
    
    void setVeclocity(float vecity);
    float getVeclocity();
    void setScaleVeclocity(float scale);

    void setIsPhyic(bool isPhySic);
    bool getIsPhysic();
    
    void setEnableUpdate(bool isStart);
    bool getEnableUpdate();
    

};


#endif /* BaseObject_h */
