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

    void testFunction();

};

#endif /* defined(__MyCocosDemo__ActionTest__) */