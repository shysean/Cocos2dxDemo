//
//  GUITest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 05/10/14.
//
//

#include "GUITest.h"
#include "../Tools/UIUtil.h"

USING_NS_CC_EXT;


GUITest::GUITest()
: m_edit(nullptr)
{

}

void GUITest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
    
    m_uiLayer = Layer::create();
    m_uiLayer->setPosition(Point::ZERO);
    addChild(m_uiLayer);
}

void GUITest::initTestMenu()
{
    ADD_TEST_METHOD(addEditBox);
}

void GUITest::showUILayer()
{
}

void GUITest::addEditBox()
{
    if (m_edit == nullptr) {
        m_edit = UIUtil::createEditBox(m_uiLayer, 100, 100, "Input Name");
    }
}