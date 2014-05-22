//
//  TiledTest.h
//  MyCocosDemo
//
//  Created by shihongyang on 05/22/14
//
//

#ifndef __MyCocosDemo__TiledTest__
#define __MyCocosDemo__TiledTest__

#include "BaseTestScene.h"

class TiledTest : public BaseTestScene
{
public:
    TiledTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();

    void testTiled();
    void testMoveGird();
    
private:
    std::vector<Point> m_canMovePoint;
private:
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
    void createMoveRange(Point orgPoint, int width, int height, int step);
    void drawGird(int x, int y, int width, int height);
    bool isCanDraw(Point point);
};

#endif /* defined(__MyCocosDemo__TiledTest__) */