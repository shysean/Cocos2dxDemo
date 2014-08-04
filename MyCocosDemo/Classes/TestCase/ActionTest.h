//
//  ActionTest.h
//  MyCocosDemo
//
//  Created by shihongyang on 05/22/14
//
//

#ifndef __MyCocosDemo__ActionTest__
#define __MyCocosDemo__ActionTest__

#include "BaseTestScene.h"

class ActionTest : public BaseTestScene
{
public:
    ActionTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();
    virtual void update(float delta) override;

    void testRunActionInScheduler();

protected:
    cocos2d::Sprite* m_sprite;
};

#endif /* defined(__MyCocosDemo__ActionTest__) */