#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
    
    
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
    glview->setDesignResolutionSize(480, 350, ResolutionPolicy::NO_BORDER);
    // 其他参数，参考ResolutionPolicy的注释

    Size winSize = Director::getInstance()->getWinSize();
    CCLOG("WIN SIZE: %dx%d", (int)winSize.width, (int)winSize.height);
    // Result: winSize的大小为glview->setDesignResolutionSize()设置的值
    // 默认为FrameSize

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    CCLOG("VISIBLE SIZE/POINT: %dx%d/(%d,%d)", (int)visibleSize.width, (int)visibleSize.height,
          (int)origin.x, (int)origin.y);


//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//    
//	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                origin.y + closeItem->getContentSize().height/2));
//
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Point::ZERO);
//    this->addChild(menu, 1);
//
//    auto label = LabelTTF::create("Hello World", "Arial", 24);
//    
//    label->setPosition(Point(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    this->addChild(label, 1);
//    
//    // "HelloWorld.png" size is 480 × 320
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    this->addChild(sprite, 0);
    
    
    
    

    

    
    return true;
}


void HelloWorld::draw(cocos2d::Renderer *renderer, const kmMat4& transform, bool transformUpdated)
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




void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
