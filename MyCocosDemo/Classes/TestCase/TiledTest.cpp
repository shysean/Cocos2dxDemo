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
    ADD_TEST_METHOD(testMoveGird);
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
//    auto map = TMXTiledMap::create("tiled/map1.tmx");
    addChild(map, 0, TAG_MAP);
}

void TiledTest::testMoveGird()
{
    m_canMovePoint.clear();

    //113,204
    Rect rect;
    int pos = 4;
    int width = 103;
    int height = /*103; //*/122;
    
    rect.setRect((pos-1)*width+1, 50, width, height);
    auto role = Sprite::create("tiled/ortho-test1.png", rect);
    role->setPosition(VisibleUtil::center());
    int step = 5;
    
    Point rolePoint = role->getPosition();
    m_canMovePoint.push_back(rolePoint);
    createMoveRange(rolePoint, width, height, step);
    addChild(role);

}

void TiledTest::createMoveRange(Point orgPoint, int width, int height, int step)
{
    if (step == 0) {
        return;
    }
    
    // up
    Point upPoint = Point(orgPoint.x, orgPoint.y + height);
    if (isCanDraw(upPoint)) {
        drawGird(upPoint.x, upPoint.y, width, height);
    }
    
    
    // left
    Point leftPoint = Point(orgPoint.x - width, orgPoint.y);
    if (isCanDraw(leftPoint)) {
        drawGird(leftPoint.x, leftPoint.y, width, height);
    }
    
    // down
    Point downPoint = Point(orgPoint.x, orgPoint.y - height);
    if (isCanDraw(downPoint)) {
        drawGird(downPoint.x, downPoint.y, width, height);
    }

    // right
    Point rightPoint = Point(orgPoint.x + width, orgPoint.y);
    if (isCanDraw(rightPoint)) {
        drawGird(rightPoint.x, rightPoint.y, width, height);
    }
    
    int remainStep = step - 1;
    createMoveRange(upPoint, width, height, remainStep);
    createMoveRange(leftPoint, width, height, remainStep);
    createMoveRange(downPoint, width, height, remainStep);
    createMoveRange(rightPoint, width, height, remainStep);
}

bool TiledTest::isCanDraw(Point point)
{
    for (Point p: m_canMovePoint)
    {
        if (p.x == point.x && p.y == point.y) {
            return false;
        }
    }
    
    return true;
}


void TiledTest::drawGird(int x, int y, int width, int height)
{
    auto gird = Sprite::create("image/textField.png");
    Size size = gird->getContentSize();
    float scaleX = width / size.width;
    float scaleY = height / size.height;
    gird->setScaleX(scaleX);
    gird->setScaleY(scaleY);

    gird->setPosition(Point(x, y));
    addChild(gird);

    m_canMovePoint.push_back(Point(x,y));
    
}
