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

private:
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);

};

#endif /* defined(__MyCocosDemo__TiledTest__) */