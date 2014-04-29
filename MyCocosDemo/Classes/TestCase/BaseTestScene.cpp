//
//  BaseTestScene.cpp
//  Cocos2dxDemo
//
//  Created by shihongyang on 4/27/14.
//
//

#include "BaseTestScene.h"
#include "TestCaseScene.h"
#include "ui/UIScrollView.h"

BaseTestScene::BaseTestScene()
{
    CCLOG("BaseTestScene Constructor.");
    Scene::init();

}

BaseTestScene::~BaseTestScene()
{
    CCLOG("BaseTestScene Destructor.");
}

void testScene_callback(Ref *sender )
{
    auto scene = Scene::create();
    
    auto layer = new TestCaseScene();
    scene->addChild(layer);
    layer->release();
    
    Director::getInstance()->replaceScene(scene);
    
}

void BaseTestScene::onEnter()
{
    CCLOG("BaseTestScene onEnter.");
    Scene::onEnter();
    
    //add the menu item for back to main menu
    auto label = Label::createWithSystemFont("<< Back", "Arial", 20);
    
    auto menuItem = MenuItemLabel::create(label, testScene_callback );
    auto menu = Menu::create(menuItem, NULL);
    menu->setPosition( Point::ZERO );

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point visibleOrgPoint = Director::getInstance()->getVisibleOrigin();
    
    menuItem->setAnchorPoint(Point(1,0));
    menuItem->setPosition( Point( visibleSize.width + visibleOrgPoint.x - 25,
                                 visibleOrgPoint.y + 25) );
    addChild(menu, 1);
    
    // add TestMenu for different testcase
    initTestMenu();
    
    auto testMenu = Menu::createWithArray(vectorOfMenu);
    testMenu->alignItemsVertically();
    
    // sean: doesn't work. why?
    // Because Layer and Scene m_bIgnoreAnchorPointForPosition = true;
    // Menu's superclass is Layer
//    testMenu->setAnchorPoint(Point(0,0));
    testMenu->setPosition(Point::ZERO);
    
    for( auto child : testMenu->getChildren() )
    {
        child->setAnchorPoint(Point(1, 0));
        int posY = child->getPositionY();
        child->setPosition(Point(visibleSize.width - 25, posY + visibleSize.height / 2));
    }
    
    addChild(testMenu);
}



