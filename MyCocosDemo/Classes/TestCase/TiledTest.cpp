//
//  TiledTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 05/22/14.
//
//

#include "TiledTest.h"
#include "../Tools/UIUtil.h"

enum
{
    TAG_MAP = 1,
};

TiledTest::TiledTest()
{
    
}

void TiledTest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(TiledTest::onTouchesMoved, this);

    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void TiledTest::initTestMenu()
{
    ADD_TEST_METHOD(testTiled);
}

void TiledTest::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    auto touch = touches[0];
    
    auto diff = touch->getDelta();
    auto node = getChildByTag(TAG_MAP);
    auto currentPos = node->getPosition();
    
    Point position;
    
    
    Point originPoint = VisibleUtil::leftBottom();
    Size mapSize = node->getContentSize();
    
    int x = 0;
    int y = 0;
    x = (diff + currentPos).x;
    y = (diff + currentPos).y;
    
    // 控制边界
    if (y >= originPoint.y)
    {
        y = originPoint.y;
    }
    if (y <= originPoint.y - (mapSize.height - VisibleUtil::height()))
    {
        y = originPoint.y - (mapSize.height - VisibleUtil::height());
    }
    if (x >= originPoint.x)
    {
        x = originPoint.x;
    }
    if (x <= originPoint.x - (mapSize.width - VisibleUtil::width()))
    {
        x = originPoint.x - (mapSize.width - VisibleUtil::width());
    }
    
    
    node->setPosition(Point(x,y));
}

// =============================
//        Test Funtion
// =============================
void TiledTest::testTiled()
{
    setInfo("testTiled");
    
    auto map = TMXTiledMap::create("tiled/testMap.tmx");
    addChild(map, 0, TAG_MAP);
}