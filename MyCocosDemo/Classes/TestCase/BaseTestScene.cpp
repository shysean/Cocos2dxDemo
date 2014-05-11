//
//  BaseTestScene.cpp
//  Cocos2dxDemo
//
//  Created by shihongyang on 4/27/14.
//
//

#include "BaseTestScene.h"
#include "../TestCaseScene.h"
#include "ui/UIScrollView.h"
#include "../Tools/UIUtil.h"

BaseTestScene::BaseTestScene()
{
//    CCLOG("BaseTestScene Constructor.");
    Scene::init();

}

BaseTestScene::~BaseTestScene()
{
//    CCLOG("BaseTestScene Destructor.");
}

void testScene_callback(Ref *sender )
{
    auto scene = new TestCaseScene();
    
    Director::getInstance()->replaceScene(scene);
    
}

void BaseTestScene::onEnter()
{
//    CCLOG("BaseTestScene onEnter.");
    Scene::onEnter();
    
    //add the menu item for back to main menu
    auto label = Label::createWithSystemFont("<< Back", "Arial", 50);
    
    m_menuBack = MenuItemLabel::create(label, testScene_callback );
    auto menu = Menu::create(m_menuBack, NULL);
    menu->setPosition( Point::ZERO );

    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    m_menuBack->setAnchorPoint(Point(1,0));
    m_menuBack->setPosition(VisibleUtil::rightBottom());
    addChild(menu, 1);
    
    // add TestMenu for different testcase
    initTestMenu();
    
    m_testMenu = Menu::createWithArray(m_vectorOfMenu);
    m_testMenu->alignItemsVertically();
    
    // sean: doesn't work. why?
    // Layer and Scene m_bIgnoreAnchorPointForPosition = true;
    // Menu's superclass is Layer
//    testMenu->setAnchorPoint(Point(0,0));
    m_testMenu->setPosition(Point::ZERO);
    m_testMenu->setContentSize(visibleSize);

    for( auto child : m_testMenu->getChildren() )
    {
        child->setAnchorPoint(Point(1, 0));
        int posY = child->getPositionY();
        child->setPosition(Point(VisibleUtil::right() - 25, posY + visibleSize.height / 2));
    }
    
    addChild(m_testMenu);
    
    m_infoLabel = Label::create();
    m_infoLabel->setContentSize(Size(visibleSize.width, 30));
    m_infoLabel->setPosition(VisibleUtil::leftTop());
    m_infoLabel->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    m_infoLabel->setSystemFontName("Arial");
    m_infoLabel->setSystemFontSize(24);
    m_infoLabel->setTextColor(Color4B::ORANGE);
    m_infoLabel->setString("DEBUG INFO...");
    addChild(m_infoLabel);
}

void BaseTestScene::resetUIPosition()
{
    m_infoLabel->setPosition(VisibleUtil::leftTop());
    m_menuBack->setPosition(VisibleUtil::rightBottom());
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    m_testMenu->alignItemsVertically();

    m_testMenu->setPosition(Point::ZERO);
    m_testMenu->setContentSize(visibleSize);

    for( auto child : m_testMenu->getChildren() )
    {
        child->setAnchorPoint(Point(1, 0));
        int posY = child->getPositionY();
        child->setPosition(Point(VisibleUtil::right() - 25, posY + visibleSize.height / 2));
    }
}

void BaseTestScene::addTestMenuItem(cocos2d::MenuItem *menuItem)
{
    m_vectorOfMenu.pushBack(menuItem);
}
void BaseTestScene::setInfo(std::string info)
{
    m_infoLabel->setString(info);
}


