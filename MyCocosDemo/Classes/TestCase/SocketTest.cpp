//
//  SocketTest.cpp
//  Cocos2dxDemo
//
//  Created by shihongyang on 4/27/14.
//
//

#include "SocketTest.h"
#include "../Tools/TimeUtil.h"

SocketTest::SocketTest()
{
}

void SocketTest::runThisTest()
{
    CCLOG("SocketTest::runThisTest");
    
    Director::getInstance()->replaceScene(this);
}

void SocketTest::initTestMenu()
{
    ADD_TEST_METHOD(testFunction);
    ADD_TEST_METHOD(testFunction1);
    ADD_TEST_METHOD(testFunction2);
    ADD_TEST_METHOD(testFunction3);
}


void SocketTest::testFunction()
{
    long long time = TimeUtil::currentTimeMillis();
    char info[255];
    sprintf(info, "TIME=%lld", time);
    setInfo(info);
}

void SocketTest::testFunction1()
{
    time_t t = time( 0 );
    char info[255];
    strftime(info, 255, "%Y-%m-%d %H:%M:%S", localtime(&t));
    setInfo(info);

}


void SocketTest::testFunction2()
{
    log("SocketTest::testFunction");
}


void SocketTest::testFunction3()
{
    log("SocketTest::testFunction");
}




