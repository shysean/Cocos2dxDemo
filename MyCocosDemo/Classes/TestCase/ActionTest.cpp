//
//  ActionTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 05/22/14.
//
//

#include "ActionTest.h"

USING_NS_CC;

ActionTest::ActionTest()
: m_sprite(nullptr)
{
    
}

void ActionTest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
    
    m_sprite = Sprite::create("CloseNormal.png");
    m_sprite->setPosition(Point(100,200));
    addChild(m_sprite);
}

void ActionTest::initTestMenu()
{
    ADD_TEST_METHOD(testRunActionInScheduler);
}

void ActionTest::update(float delta)
{
//    CCLOG("update");

//    Case1:
//    auto move = MoveTo::create(5, Point(100,100));
//    move->setTag(20);
//    auto sprite = Sprite::create("CloseNormal.png");
//    addChild(sprite);
//    sprite->runAction(move);
    
//    Case2:
    auto action = m_sprite->getActionByTag(20);
    
    // Note: Maybe when action is done action is null
    if (action == nullptr || action->isDone()) {

        CCLOG("no action or action is Done");
        m_sprite->setPosition(Point(100,200));
        auto move = MoveTo::create(5, Point(1000,200));
        move->setTag(20);
        
        m_sprite->runAction(move);
    }
    
    
}

// =============================
//        Test Funtion
// =============================
void ActionTest::testRunActionInScheduler()
{
    setInfo("testSchedulerAndAction");
    
    scheduleUpdate();

}