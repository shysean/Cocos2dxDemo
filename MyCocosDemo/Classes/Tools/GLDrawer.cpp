//
//  GLDrawer.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 6/29/14.
//
//

#include "GLDrawer.h"

void GLDrawer::drawRect(int sx, int sy, int ex, int ey, Color4B color)
{
    DrawPrimitives::setDrawColor4B(color.r,color.g,color.b,color.a);
    DrawPrimitives::drawRect(Point(sx, sy),Point(ex, ey));
    
    // 还原默认颜色
    DrawPrimitives::setDrawColor4F(1.0f ,1.0f, 1.0f, 1.0f);

}