//
//  CppTest.h
//  MyCocosDemo
//
//  Created by shihongyang on 06/28/14
//
//

#ifndef __MyCocosDemo__CppTest__
#define __MyCocosDemo__CppTest__

#include "BaseTestScene.h"

class CppTest : public BaseTestScene
{
public:
    CppTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();

    void testDestructor();
    void testDoubleDimensionalArray();

};



class CppTestBase
{
public:
    CppTestBase(){ CCLOG("CppTestBase.()"); };
    
// Test Case 1:
// CppTestBase *c = new CppTestDerived();
// 不会执行子类的析构方法，造成内存泄露
//    
//    ~CppTestBase(){ CCLOG("CppTestBase.~()"); };
    
// Test Case 2:
// - 生成虚函数表，占用内存。
// - 增加keyword final解决上条问题
// - 先释放继承类的资源,再释放基类资源.
//
    virtual ~CppTestBase(){ CCLOG("CppTestBase.~()"); };
    
// - 没有virtual时：
//    CppTestBase *c = new CppTestDerived();
//    c->doSomething();
//    执行基类方法，不会执行派生类方法。
    virtual void doSomething() { CCLOG("CppTestBase do something."); };
};

class CppTestDerived : public CppTestBase
{
public:
    CppTestDerived(){ CCLOG("CppTestDerived.()"); };
    virtual ~CppTestDerived(){ CCLOG("CppTestDerived.~()"); };
    
// - override 显示声明覆盖
    virtual void doSomething() override { CCLOG("CppTestDerived do something."); };

};

#endif /* defined(__MyCocosDemo__CppTest__) */