//
//  CppTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 06/28/14.
//
//

#include "CppTest.h"

CppTest::CppTest()
{
    
}

void CppTest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
}

void CppTest::initTestMenu()
{
    ADD_TEST_METHOD(testDestructor);
}


// =============================
//        Test Funtion
// =============================
void CppTest::testDestructor()
{
    setInfo("testDestructor");
    
    CCLOG("----- Test Base Class -----");
    CppTestBase* a = new CppTestBase();
    a->doSomething();
    delete a;
    
    CCLOG("----- Test Derived Class -----");
    CppTestDerived* b = new CppTestDerived();
    b->doSomething();
    delete b;
    
    CCLOG("----- Test Case 1 -----");
    CppTestBase *c = new CppTestDerived();
    c->doSomething();
    delete c;
}