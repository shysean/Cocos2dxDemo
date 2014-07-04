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
}


// =============================
//        Test Funtion
// =============================
void JniTest::testJniVoidFunction()
{
    setInfo("testJniVoidFunction");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;            //定义Jni函数信息结构体
    
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/sean/test/jni/JniTest","jniTest1", "()V");
    
    if (!isHave)
    {
        CCLOG("testJniVoidFunction::函数不存在");
    }
    else
    {
        CCLOG("testJniVoidFunction::函数存在");
        //调用
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
#endif
}