//
//  ScrollBackgroundTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 06/28/14.
//
//

#include "ScrollBackgroundTest.h"
#include "../Tools/UIUtil.h"


ScrollBackgroundTest::ScrollBackgroundTest()
: m_bg1(nullptr)
, m_bg2(nullptr)
{
    
}

void ScrollBackgroundTest::runThisTest()
{
    initScene();
    Director::getInstance()->replaceScene(this);
}

void ScrollBackgroundTest::initTestMenu()
{
//    ADD_TEST_METHOD(testFunction);
}

void ScrollBackgroundTest::initScene()
{
    Size contentSize = Director::getInstance()->getWinSize();
    
//    #1 使用Sprite
//    Rect rect;
//    rect.setRect(0, 0, contentSize.width, contentSize.height);
//    auto bg1 = Sprite::create("HelloWorld.png", rect);
    
//    #2 使用Scale9Sprite
    auto bg1 = Scale9Sprite::create("HelloWorld.png");
    bg1->setPreferredSize(contentSize);

    bg1->setContentSize(contentSize);
    bg1->setAnchorPoint(Point::ZERO);
    bg1->setPosition(Point::ZERO);
    addChild(bg1);
    
    auto bg2 = Scale9Sprite::create("HelloWorld.png");
    bg2->setPreferredSize(contentSize);
    
    bg2->setContentSize(contentSize);
    bg2->setAnchorPoint(Point::ZERO);
    bg2->setPosition(Point(0 - contentSize.width, 0));
    addChild(bg2);
    
    this->m_bg1 = bg1;
    this->m_bg2 = bg2;
    
    
    // Event
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = CC_CALLBACK_2(ScrollBackgroundTest::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(ScrollBackgroundTest::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(ScrollBackgroundTest::onTouchesEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    this->scheduleUpdate();
}

void ScrollBackgroundTest::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    
}
void ScrollBackgroundTest::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
//    if(touches.size() > 1)
    {
        Point delta = touches.at(0)->getDelta();
        
        Point orgBgPos1 = m_bg1->getPosition();
        Point endBgPos1 = Point(delta.x + orgBgPos1.x, orgBgPos1.y);
        m_bg1->setPosition(endBgPos1);
        

        Point orgBgPos2 = m_bg2->getPosition();
        Point endBgPos2 = Point(delta.x + orgBgPos2.x, orgBgPos2.y);
        m_bg2->setPosition(endBgPos2);
        
    }
}
void ScrollBackgroundTest::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    
}

void ScrollBackgroundTest::update(float delta)
{
    Size contentSize = Director::getInstance()->getWinSize();
    Point bgPos1 = m_bg1->getPosition();
    Point bgPos2 = m_bg2->getPosition();

    m_bg1->setPosition(Point(bgPos1.x + 5, bgPos1.y));
    m_bg2->setPosition(Point(bgPos2.x + 5, bgPos2.y));
    
    bgPos1 = m_bg1->getPosition();
    bgPos2 = m_bg2->getPosition();
    
    if (m_bg1)
    {
        if (bgPos1.x >= contentSize.width)
        {
            m_bg1->setPosition(Point(bgPos2.x - contentSize.width, 0));
        }
    }
    
    if (m_bg2)
    {
        if (bgPos2.x >= contentSize.width)
        {
            m_bg2->setPosition(Point(bgPos1.x - contentSize.width, 0));
        }
    }
    


}



// =============================
//        Test Funtion
// =============================
