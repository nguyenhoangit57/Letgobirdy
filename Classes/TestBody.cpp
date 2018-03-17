//
//  TestBody.cpp
//  KidsKid
//
//  Created by Nguyễn Chí Hoàng on 5/26/15.
//
//

#include "TestBody.h"
#include "GameDefineState.h"

TestBody::TestBody(){
    
    this->SetFlags(e_shapeBit);
    
}

/// Draw a closed polygon provided in CCW order.
void TestBody::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
    log("DrawPolygon");
    
}

/// Draw a solid closed polygon provided in CCW order.
void TestBody::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
   // log("DrawSolidPolygon");
    Vec2* points = new Vec2[vertexCount];
    for(int i=0;i<vertexCount;i++){
        points[i].x = vertices[i].x * 32.0f;
        points[i].y = vertices[i].y * 32.0f;
    }
    
    DrawPrimitives::drawSolidPoly(points, vertexCount, Color4F(217/255.0f, 208/255.0f , 208/255.0f, 100.0f));
    //delete points;
}

/// Draw a circle.
void TestBody::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color){
    DrawPrimitives::setDrawColor4B(217/255.0f, 208/255.0f , 208/255.0f, 100.0f);
    DrawPrimitives::drawCircle(Vec2(center.x*PTM_RATIO, center.y*PTM_RATIO), radius*PTM_RATIO, 360.0f, 100, true, 1.0f, 1.0f);
}

/// Draw a solid circle.
void TestBody::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color){
    DrawPrimitives::setDrawColor4B(217/255.0f, 208/255.0f , 208/255.0f, 100.0f);
    DrawPrimitives::drawSolidCircle(Vec2(center.x*PTM_RATIO, center.y*PTM_RATIO), radius*PTM_RATIO, 360.0f, 100, 1.0f, 1.0f);
}

/// Draw a line segment.
void TestBody::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color){
    
}

/// Draw a transform. Choose your own length scale.
/// @param xf a transform.
void TestBody::DrawTransform(const b2Transform& xf){
    
}
