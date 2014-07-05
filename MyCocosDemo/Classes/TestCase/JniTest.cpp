//
//  JniTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 07/04/14.
//
//

#include "JniTest.h"

JniTest::JniTest()
{
    
}

void JniTest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
}

void JniTest::initTestMenu()
{
    ADD_TEST_METHOD(testJniVoidFunction);
    ADD_TEST_METHOD(startSensor);
    ADD_TEST_METHOD(stopSensor);
}


// =============================
//        Test Funtion
// =============================
void JniTest::testJniVoidFunction()
{
    setInfo("testJniVoidFunction");
    CallStaticVoidMethod("com/sean/test/jni/JniTest", "jniTest1");
}

void JniTest::startSensor()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getActivity", "()Ljava/lang/Object;");
    jobject activityObj;
    
    if (isHave)
    {
        activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    
    isHave = JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "startSensor", "()V");
    
    if (isHave)
    {
        minfo.env->CallVoidMethod(activityObj, minfo.methodID);
    }
    
#endif
}
void JniTest::stopSensor()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;           
    
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getActivity", "()Ljava/lang/Object;");
    jobject activityObj;

    if (isHave)
    {
        activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    
    isHave = JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "stopSensor", "()V");
    
    if (isHave)
    {
        minfo.env->CallVoidMethod(activityObj, minfo.methodID);
    }

#endif
}

void JniTest::CallStaticVoidMethod(std::string package, std::string method)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    
    bool isHave = JniHelper::getStaticMethodInfo(minfo, package.c_str(), method.c_str(), "()V");
    
    if (isHave)
    {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
#endif
}
