//
//  SHA1Test.h
//  MyCocosDemo
//
//  Created by shihongyang on 09/22/14
//
//

#ifndef __MyCocosDemo__SHA1Test__
#define __MyCocosDemo__SHA1Test__

#include "BaseTestScene.h"

class SHA1Test : public BaseTestScene
{
public:
    SHA1Test();
    
    virtual void runThisTest();
    virtual void initTestMenu();

    void testFunction();

};

#endif /* defined(__MyCocosDemo__SHA1Test__) */