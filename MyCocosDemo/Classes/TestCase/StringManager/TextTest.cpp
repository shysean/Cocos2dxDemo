//
//  TextTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 5/4/14.
//
//

#include "TextTest.h"
#include "../../Tools/GameText.h"

using namespace std;

TextTest::TextTest()
{
    
}

TextTest::~TextTest()
{
    
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

    // No key "H"
    string result2 = GameText::getInstance()->getText("H");
    CCLOG("TextTest::testGetText result = %s", result2.c_str());
    
}
