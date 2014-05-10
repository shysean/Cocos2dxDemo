//
//  ScreenTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 5/9/14.
//
//
#include <iostream>
#include <sstream>

#include "ScreenTest.h"
#include "../Tools/UIUtil.h"

const int DESIGN_WIDHT = 800;
const int DESIGN_HEIGHT = 500;

ScreenTest::ScreenTest()
: m_scale(1)
, m_distance(0)
{
    init();
}
ScreenTest::~ScreenTest()
{
    
}

void ScreenTest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
}
void ScreenTest::initTestMenu()
{
    ADD_TEST_METHOD(vectorOfMenu, resetDesignSize);
}

bool ScreenTest::init()
{
    // 物理分辨率
    GLView *glview = Director::getInstance()->getOpenGLView();
    Size frameSize = glview->getFrameSize();
    
    CCLOG("FRAME SIZE: %dx%d", (int)frameSize.width, (int)frameSize.height);
    // Result:
    // iPhone(3.5-inch)         960x640             1.5
    // iPhone(4-inch)           1136x640            1.775
    // iPad                     1024x768            1.333
    // iPad Retina              2048x1536           1.333
    
    // 设置逻辑上的游戏屏幕大小
    // ResolutionPolicy::EXACT_FIT为了保持了全屏显示，对画面进行了拉伸（不推荐！）
    //    glview->setDesignResolutionSize(400, 480, ResolutionPolicy::EXACT_FIT);
    
    // ResolutionPolicy::SHOW_ALL为了保持设计画面比例对四周进行留黑边处理，使得不同比例下画面不能全屏。
    //    glview->setDesignResolutionSize(400, 480, ResolutionPolicy::SHOW_ALL);
    
    // ResolutionPolicy::NO_BORDER为了填补留下的黑边，将画面稍微放大，以至于能够正好补齐黑边
    glview->setDesignResolutionSize(DESIGN_WIDHT, DESIGN_HEIGHT, ResolutionPolicy::NO_BORDER);
    // 其他参数，参考ResolutionPolicy的注释
    
    Size winSize = Director::getInstance()->getWinSize();
    CCLOG("WIN SIZE: %dx%d", (int)winSize.width, (int)winSize.height);
    // Result: winSize的大小为glview->setDesignResolutionSize()设置的值
    // 默认为FrameSize
    
    
    

    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // Add Touch Listener
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = CC_CALLBACK_2(ScreenTest::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(ScreenTest::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(ScreenTest::onTouchesEnded, this);
    touchListener->onTouchesCancelled = CC_CALLBACK_2(ScreenTest::onTouchesCancelled, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    
    // Add Mouse Listener
    auto mouseListener = EventListenerMouse::create();
//    mouseListener->onMouseMove = CC_CALLBACK_1(ScreenTest::onMouseMove, this);
//    mouseListener->onMouseUp = CC_CALLBACK_1(ScreenTest::onMouseUp, this);
//    mouseListener->onMouseDown = CC_CALLBACK_1(ScreenTest::onMouseDown, this);
    mouseListener->onMouseScroll = CC_CALLBACK_1(ScreenTest::onMouseScroll, this);
    dispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
#endif
    
    m_editWidth = UIUtil::createEditBox(this, 100, 160, "Design Width");
    m_editHeight = UIUtil::createEditBox(this, 100, 100, "Design Height");
    
    m_editHeight->setInputMode(EditBox::InputMode::NUMERIC);
    m_editWidth->setInputMode(EditBox::InputMode::NUMERIC);
    
    char width[32];
    sprintf(width, "%d", (int)winSize.width);
    m_editWidth->setText(width);
    
    char height[32];
    sprintf(height, "%d", (int)winSize.height);
    m_editHeight->setText(height);

    return true;
}

// =============================
//        Test Function
// =============================
void ScreenTest::resetDesignSize()
{
    const char* strHeight = m_editHeight->getText();
    std::stringstream strHeightValue;
    strHeightValue << strHeight;
    
    unsigned int intHeight;
    strHeightValue >> intHeight;
    
    
    
    const char* strWidth = m_editWidth->getText();
    std::stringstream strWidthValue;
    strWidthValue << strWidth;
    
    unsigned int intWidth;
    strWidthValue >> intWidth;
    
    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(intWidth, intHeight, ResolutionPolicy::NO_BORDER);
}


void ScreenTest::refeshInfo()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    Size designSize = Director::getInstance()->getWinSize();
    
    Point visibleOrigin = Director::getInstance()->getVisibleOrigin();
    char info[1024];
    sprintf(info, "Frame:%dx%d Design(Y):%dx%d Visible(G):%dx%d,(%d,%d)",
            (int)frameSize.width, (int)frameSize.height,
            (int)designSize.width, (int)designSize.height,
            (int)visibleSize.width, (int)visibleSize.height,
            (int)visibleOrigin.x, (int)visibleOrigin.y);
    
    infoLabel->setString(info);
}


// =============================
//        Draw Function
// =============================
void ScreenTest::draw(cocos2d::Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
    glLineWidth(3);
    
    drawVisibleRect();
    drawDesignRect();
}

void ScreenTest::drawVisibleRect()
{
    // ResolutionPolicy::NO_BORDER下绘制VisibleSize
    // 1.visibleSize <= winSize
    // 2.visibleSize是frameSize的比例
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    int startX = (int)(visibleSize.width * (1 - m_scale) / 2 + origin.x);
    int startY = (int)(visibleSize.height * (1 - m_scale) / 2 + origin.y);
    int endX = (int)visibleSize.width * m_scale + startX;
    int endY = (int)visibleSize.height * m_scale + startY;
    
    // draw visible size
    drawRect(startX, startY, endX, endY, Color4B::GREEN);
}

void ScreenTest::drawDesignRect()
{
    Size winSize = Director::getInstance()->getWinSize();

    int startX = (int)winSize.width * (1 - m_scale) / 2;
    int startY = (int)winSize.height * (1 - m_scale) / 2;
    int endX = (int)winSize.width * m_scale + startX;
    int endY = (int)winSize.height * m_scale + startY;

    // draw design size
    drawRect(startX, startY, endX, endY, Color4B::YELLOW);
}

void ScreenTest::drawRect(int sx, int sy, int ex, int ey, Color4B color)
{
    DrawPrimitives::setDrawColor4B(color.r,color.g,color.b,color.a);
    DrawPrimitives::drawRect(Point(sx, sy),Point(ex, ey));
}




// =============================
//          Touch Event
// =============================
void ScreenTest::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
//    sean: It's hardly to get 2 point in same time.
}
void ScreenTest::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
//    CCLOG("onTouchesMoved  ...");

    if(touches.size()>=2)  //如果触摸点不少于两个
    {
        Point mPoint1=touches.at(0)->getLocationInView();
        mPoint1 = CCDirector::getInstance()->convertToGL(mPoint1);
        
        Point mPoint2=touches.at(1)->getLocationInView();
        mPoint2 = CCDirector::getInstance()->convertToGL(mPoint2);
        
        double distance = sqrt((mPoint2.x-mPoint1.x)*(mPoint2.x-mPoint1.x)+(mPoint2.y-mPoint1.y)*(mPoint2.y-mPoint1.y));//计算两个触摸点距离

        if (m_distance == 0) {
            m_distance = distance;
        }
        
        m_scale = distance / m_distance;
    }
    
    refeshInfo();
}
void ScreenTest::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    m_distance = 0;
}
void ScreenTest::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    m_distance = 0;
}

void ScreenTest::onMouseScroll(Event *event)
{
    EventMouse* e = (EventMouse*)event;

    float scrolly = e->getScrollY();
    m_scale += scrolly / 10;
    
    if(m_scale < 0)
    {
        m_scale = 0;
    }

    refeshInfo();
}


