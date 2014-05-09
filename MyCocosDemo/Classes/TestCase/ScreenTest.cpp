//
//  ScreenTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 5/9/14.
//
//

#include "ScreenTest.h"

ScreenTest::ScreenTest()
: m_scale(1)
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
//    ADD_TEST_METHOD(vectorOfMenu, testGetText);
}

bool ScreenTest::init()
{
    // 物理分辨率
    GLView *glview = Director::getInstance()->getOpenGLView();
    Size frameSize = glview->getFrameSize();
    
    CCLOG("FRAME SIZE: %dx%d", (int)frameSize.width, (int)frameSize.height);
    // Result:
    // iPhone(3.5-inch)         960x640
    // iPhone(4-inch)           1136x640
    // iPad                     1024x768
    // iPad Retina              2048x1536
    
    // 设置逻辑上的游戏屏幕大小
    // ResolutionPolicy::EXACT_FIT为了保持了全屏显示，对画面进行了拉伸（不推荐！）
    //    glview->setDesignResolutionSize(400, 480, ResolutionPolicy::EXACT_FIT);
    
    // ResolutionPolicy::SHOW_ALL为了保持设计画面比例对四周进行留黑边处理，使得不同比例下画面不能全屏。
    //    glview->setDesignResolutionSize(400, 480, ResolutionPolicy::SHOW_ALL);
    
    // ResolutionPolicy::NO_BORDER为了填补留下的黑边，将画面稍微放大，以至于能够正好补齐黑边
    glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
    // 其他参数，参考ResolutionPolicy的注释
    
    Size winSize = Director::getInstance()->getWinSize();
    CCLOG("WIN SIZE: %dx%d", (int)winSize.width, (int)winSize.height);
    // Result: winSize的大小为glview->setDesignResolutionSize()设置的值
    // 默认为FrameSize

    return true;
}


void ScreenTest::draw(cocos2d::Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    int startX = (int)origin.x + 1;
    int startY = (int)origin.y + 1;
    int endX = (int)visibleSize.width + startX - 2;
    int endY = (int)visibleSize.height + startY - 2;
    
    glLineWidth(3);
    DrawPrimitives::setDrawColor4B(255,255,255,255);
    
    // ResolutionPolicy::NO_BORDER下绘制VisibleSize
    // 1.visibleSize <= winSize
    // 2.visibleSize是frameSize的比例
    DrawPrimitives::drawRect(Point(startX,startY),Point(endX,endY));
    
}