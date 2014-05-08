//
//  TextTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 5/4/14.
//
//

#include "TextTest.h"
#include "../Tools/GameText.h"

using namespace std;

TextTest::TextTest()
{
    init();
}

TextTest::~TextTest()
{
    
}

bool TextTest::init()
{
    Scene::init();

    infoLabel = Label::create();
    infoLabel->setPosition(Point(50, 400));
    infoLabel->setString("Infomation Label");
    infoLabel->setSystemFontSize(30);
    infoLabel->setTextColor(Color4B::ORANGE);
    infoLabel->setAnchorPoint(Point(0,1));
    
    addChild(infoLabel);
    
    return true;
}

void TextTest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
}

void TextTest::initTestMenu()
{
    ADD_TEST_METHOD(vectorOfMenu, testGetText);
}

void TextTest::testGetText()
{
    CCLOG("TextTest::testGetText called.");

    // Has key "HELLO"
    string result1 = GameText::getInstance()->getText("HELLO");
    CCLOG("TextTest::testGetText result = %s", result1.c_str());
    
    infoLabel->setString(result1);

    // No key "H"
    string result2 = GameText::getInstance()->getText("H");
    CCLOG("TextTest::testGetText result = %s", result2.c_str());
    
}
