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
    
    menuItem->setPosition( Point( visibleSize.width + visibleOrgPoint.x - 50,
                                 visibleOrgPoint.y + 25) );
    
    addChild(menu, 1);
}



