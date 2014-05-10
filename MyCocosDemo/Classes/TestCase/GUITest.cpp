//
//  GUITest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 05/10/14.
//
//

#include "GUITest.h"
#include "extensions/cocos-ext.h"
#include "../Tools/UIUtil.h"

USING_NS_CC_EXT;


GUITest::GUITest()
{
    
}

void GUITest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
}

void GUITest::initTestMenu()
{
    ADD_TEST_METHOD(vectorOfMenu, testFunction);
}

void GUITest::testFunction()
{
    infoLabel->setString("testFunction");
    
//    auto uiLayer = Layer::create();
//    uiLayer->setPosition(Point::ZERO);
    
    auto edit1 = UIUtil::createEditBox(this, 100, 100, "info1");
    auto edit2 = UIUtil::createEditBox(this, 100, 160, "info2");
    auto edit3 = UIUtil::createEditBox(this, 100, 220, "info3");
    auto edit4 = UIUtil::createEditBox(this, 100, 280, "info4");

//    addChild(_editName);
    
    
}