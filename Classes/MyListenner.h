//
//  MyListender.h
//  KidsKid
//
//  Created by Nguyễn Chí Hoàng on 5/22/15.
//
//

#ifndef __KidsKid__MyListender__
#define __KidsKid__MyListender__

#include "cocos2d.h"
#include <Box2D/Box2D.h>

class DelegateListener
{
public:
   virtual void restoreIndexListener(int stdLister) = 0;
   virtual void contactWithLanding() = 0;
   virtual void contactWithWall() = 0;
};


class MyListender : public b2ContactListener{
public:
    DelegateListener* delegate;
public:
    MyListender();
    void BeginContact(b2Contact* contact); // When we first contact
    void EndContact(b2Contact* contact); // When we end contact
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void setDelegate(DelegateListener* mDelegate);
};

#endif /* defined(__KidsKid__MyListender__) */
