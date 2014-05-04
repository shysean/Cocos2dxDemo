//
//  TestCaseScene.cpp
//  Cocos2dxDemo
//
//  Created by shihongyang on 4/27/14.
//
//

#include "TestCaseScene.h"
#include "SocketTest/SocketTest.h"
#include "StringManager/TextTest.h"


Controller g_aTestNames[] = {
    CREATE_TEST_SCENE("SocketTest", SocketTest)
    CREATE_TEST_SCENE("TextTest", TextTest)
};

static int g_testCount = sizeof(g_aTestNames) / sizeof(g_aTestNames[0]);
static Point s_tCurPos = Point::ZERO;

TestCaseScene::TestCaseScene()
:m_menu(nullptr)
,m_beginPos(Point::ZERO)
{
    CCLOG("TestCaseScene");
    
    m_menu = createMenu();
    addChild(m_menu);
    
    
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(TestCaseScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(TestCaseScene::onTouchMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

TestCaseScene::~TestCaseScene()
{
    CCLOG("~TestCaseScene");
}


Menu* TestCaseScene::createMenu()
{
    auto menu = Menu::create();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // add menu items for tests
    for (int i = 0; i < g_testCount; ++i)
    {
        
        // sean: For SystemFont
        // @see http://zh.wikipedia.org/zh-cn/Mac_OS_X%E5%AD%97%E4%BD%93%E5%88%97%E8%A1%A8
        auto label = Label::createWithSystemFont(g_aTestNames[i].test_name, "Arial", 24);
        label->setColor(Color3B::GREEN);
        
        auto menuItem = MenuItemLabel::create(label, CC_CALLBACK_1(TestCaseScene::menuCallback, this));
        menuItem->setAnchorPoint(Point(1, 0));
        menu->addChild(menuItem, i + 10000);
        menuItem->setPosition( Point( visibleSize.width - 20,  (visibleSize.height - (i + 1) * LINE_SPACE) ));
        
    }
    
    menu->setContentSize(Size(visibleSize.width, (g_testCount + 1) * (LINE_SPACE)));
    menu->setPosition(Point::ZERO);
    
    return menu;
}

void TestCaseScene::menuCallback(Ref * sender)
{
	Director::getInstance()->purgeCachedData();
    
    // get the userdata, it's the index of the menu item clicked
    auto menuItem = static_cast<MenuItem *>(sender);
    int idx = menuItem->getLocalZOrder() - 10000;
    
    // create the test scene and run it
    auto scene = g_aTestNames[idx].callback();
    
    if (scene)
    {
        scene->runThisTest();
        scene->release();
    }
}


bool TestCaseScene::onTouchBegan(Touch* touch, Event  *event)
{
    m_beginPos = touch->getLocation();
    return true;
}

void TestCaseScene::onTouchMoved(Touch* touch, Event  *event)
{
    auto touchLocation = touch->getLocation();
    float nMoveY = touchLocation.y - m_beginPos.y;
    
    auto curPos  = m_menu->getPosition();
    auto nextPos = Point(curPos.x, curPos.y + nMoveY);
    
    if (nextPos.y < 0.0f)
    {
        m_menu->setPosition(Point::ZERO);
        return;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    if (nextPos.y > ((g_testCount + 1)* LINE_SPACE - visibleSize.height))
    {
        m_menu->setPosition(Point(0, ((g_testCount + 1)* LINE_SPACE - visibleSize.height)));
        return;
    }
    
    m_menu->setPosition(nextPos);
    m_beginPos = touchLocation;
    s_tCurPos   = nextPos;
}
