//
//  XdeltaTest.h
//  MyCocosDemo
//
//  Created by shihongyang on 05/17/14
//
//

#ifndef __MyCocosDemo__XdeltaTest__
#define __MyCocosDemo__XdeltaTest__

#include "BaseTestScene.h"

class XdeltaTest : public BaseTestScene
{
public:
    XdeltaTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();

    void testFunction();

	static int patch(const char *srcFile, const char *patchFile, const char *outFile);

};

#endif /* defined(__MyCocosDemo__XdeltaTest__) */