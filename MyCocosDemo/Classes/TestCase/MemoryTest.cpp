//
//  MemoryTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 06/25/14.
//
//

#include "MemoryTest.h"

MemoryTest::MemoryTest():
m_testObj(nullptr),
m_testNode(nullptr),
m_testLayer(nullptr),
m_updateCount(0)
{
    
}

void MemoryTest::runThisTest()
{
    
    Director::getInstance()->replaceScene(this);
}

void MemoryTest::initTestMenu()
{
    ADD_TEST_METHOD(testCreate);
    ADD_TEST_METHOD(testAutorelease);
    ADD_TEST_METHOD(testRetain);
    ADD_TEST_METHOD(testRelease);
    ADD_TEST_METHOD(testWorngUsage1);
    ADD_TEST_METHOD(testWorngUsage2);
    
    ADD_TEST_METHOD(testMemory);

}

void MemoryTest::update(float delta)
{
    if (m_updateCount < 3)
    {
        m_updateCount++;
        CCLOG("--- update index: %d start ---", m_updateCount);

        switch (m_updateCount) {
            case 1:
                m_testNode = TestNode::create();
                addChild(m_testNode);
                m_testObj = TestObject::create();
                break;
            case 2:
                removeChild(m_testNode);
                break;
            case 3:
                ;
                break;
                
            default:
                break;
        }
        
        CCLOG("--- update index: %d end   ---", m_updateCount);

    }
    
    unscheduleUpdate();
}


// =============================
//        Test Funtion
// =============================
void MemoryTest::testAutorelease()
{
    TestObject *obj = new TestObject();
    CCLOG("obj referenceCount=%d",obj->getReferenceCount());
    
    // 不会立刻release,所以会调用到之后的retain,延时释放的作用。
    obj->autorelease();
    CCLOG("obj is add in currentpool %s",PoolManager::getInstance()->getCurrentPool()->contains(obj)?"true":"false");
    CCLOG("obj referenceCount=%d",obj->getReferenceCount());
    obj->retain();
    CCLOG("obj referenceCount=%d",obj->getReferenceCount());
    obj->release();
    CCLOG("obj referenceCount=%d",obj->getReferenceCount());
}

void MemoryTest::testRetain()
{
    if (m_testObj == nullptr) {
        m_testObj = new TestObject();
    }
    
    m_testObj->retain();
    
    char info[1024];
    sprintf(info, "testObject referenceCount=%d", m_testObj->getReferenceCount());
    setInfo(info);
    
    CCLOG("%s", info);
}

void MemoryTest::testRelease()
{
    if (m_testObj == nullptr) {
        m_testObj = new TestObject();
    }
    
    m_testObj->release();
    
    if (m_testObj == nullptr) {
        CCLOG("m_testObj is null");
        return;
    }
    
    char info[1024];
    sprintf(info, "testObject referenceCount=%d", m_testObj->getReferenceCount());
    setInfo(info);
    
    CCLOG("%s",info);
}

void MemoryTest::testWorngUsage1()
{
    // crate方法调用autorelease方法
    auto testObj = TestObject::create();
    
    char info[1024];
    sprintf(info, "testObj referenceCount=%d", testObj->getReferenceCount());
    CCLOG("%s", info);
    setInfo(info);

    // Correct usage:
    // testObj->retain();
    
    // 由线程池负责释放
    testObj->release();
}
void MemoryTest::testWorngUsage2()
{
    auto testObj = TestObject::create();
    
    char info[1024];
    sprintf(info, "testObj referenceCount=%d", testObj->getReferenceCount());
    CCLOG("%s", info);
    setInfo(info);

    // Correct usage:
    // testObj->retain();
    testObj->autorelease();
}

void MemoryTest::testCreate()
{
    auto testLayer = TestLayer::create();
    addChild(testLayer);
    
    // result:
    //cocos2d: TestLayer.()
    //cocos2d: TestLayer.init()
    //cocos2d: TestNode.()
    //cocos2d: TestNode.init()
    //cocos2d: TestObject.()
    //cocos2d: TestObject.init()
    //cocos2d: TestObject.~()
    
// Sean:    无用对象（TestObject）会被释放掉（autorelease）。
//          如果init之后没有retain,而调用testObject会导致空指针。
}

void MemoryTest::testMemory()
{
    m_updateCount = 0;
    this->scheduleUpdate();

    //reslut:
    //cocos2d: --- update index: 1 start ---
    //cocos2d: TestNode.()
    //cocos2d: TestNode.init()
    //cocos2d: TestObject.()
    //cocos2d: TestObject.init()
    //cocos2d: --- update index: 1 end   ---
    //cocos2d: TestObject.~()                   // 每帧结束时释放无用对象
    //cocos2d: --- update index: 2 start ---
    //cocos2d: TestNode.~()                     // 每帧开始时释放管理对象
    //cocos2d: --- update index: 2 end   ---
    //cocos2d: --- update index: 3 start ---
    //cocos2d: --- update index: 3 end   ---
    
//    Sean：内存管理过程
//    1.创建时，引用计数为1（自引用），加入自动释放池（array）
//    2.帧过度时引用池调用pop()里的clear()方法，解除自引用，如果没有使用就释放掉。
//    3.链式反应+树形结构。

}
