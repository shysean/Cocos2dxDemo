//
//  MemoryTest.h
//  MyCocosDemo
//
//  Created by shihongyang on 06/25/14
//
//

#ifndef __MyCocosDemo__MemoryTest__
#define __MyCocosDemo__MemoryTest__

#include "BaseTestScene.h"

//
// Test Object class
//
class TestObject : public Ref
{
public:
    TestObject()
    {
        CCLOG("TestObject.()");
    };
    
    virtual ~TestObject()
    {
        CCLOG("TestObject.~()");
    };
    virtual bool init()
    {
        CCLOG("TestObject.init()");
        return true;
    };
    
    CREATE_FUNC(TestObject);
};

//
// Test Node class
//
class TestNode : public Node
{
public:
    TestNode()
    {
        CCLOG("TestNode.()");
    };
    
    virtual ~TestNode()
    {
        CCLOG("TestNode.~()");
    };
    virtual bool init() override
    {
        CCLOG("TestNode.init()");
        return true;
    };
    
    virtual void onEnter() override
    {
        Node::onEnter();
        CCLOG("TestNode.onEnter()");
    }
    
    virtual void onExit() override
    {
        Node::onExit();
        CCLOG("TestNode.onExit()");
    }
    CREATE_FUNC(TestNode);
};

//
// Test Layer class
//
class TestLayer : public Layer
{
public:
    TestLayer()
    {
        CCLOG("TestLayer.()");
    };
    ~TestLayer()
    {
        CCLOG("TestLayer.~()");
    };
    virtual bool init()
    {
        CCLOG("TestLayer.init()");
        
        TestNode* node = TestNode::create();
        addChild(node);

        /*TestObject* object = */TestObject::create();
        
        return true;
    };
    
    CREATE_FUNC(TestLayer);
};

//
// Memory Test
//
class MemoryTest : public BaseTestScene
{
public:
    MemoryTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();
    virtual void update(float delta) override;

    void testRetain();
    void testRelease();
    void testAutorelease();
    void testWorngUsage1();
    void testWorngUsage2();
    void testCreate();
    void testMemory();
    
private:
    TestObject* m_testObj;
    TestLayer* m_testLayer;
    TestNode* m_testNode;

    int m_updateCount;
};




#endif /* defined(__MyCocosDemo__MemoryTest__) */