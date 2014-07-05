//
//  JniTest.h
//  MyCocosDemo
//
//  Created by shihongyang on 07/04/14
//
//

#ifndef __MyCocosDemo__JniTest__
#define __MyCocosDemo__JniTest__

#include "BaseTestScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

class JniTest : public BaseTestScene
{
public:
    JniTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();

    void testJniVoidFunction();
    void startSensor();
    void stopSensor();
    
    void CallStaticVoidMethod(std::string package, std::string method);

};

#endif /* defined(__MyCocosDemo__JniTest__) */