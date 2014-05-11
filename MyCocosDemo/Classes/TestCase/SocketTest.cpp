//
//  SocketTest.cpp
//  Cocos2dxDemo
//
//  Created by shihongyang on 4/27/14.
//
//

#include "SocketTest.h"

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
    log("SocketTest::testFunction");
}

void SocketTest::testFunction1()
{
    log("SocketTest::testFunction");
}


void SocketTest::testFunction2()
{
    log("SocketTest::testFunction");
}


void SocketTest::testFunction3()
{
    log("SocketTest::testFunction");
}




