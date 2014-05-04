//
//  TextTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 5/4/14.
//
//

#include "TextTest.h"
#include "GameText.h"

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

    string result = GameText::getInstance()->getText("HELLO");
    
    CCLOG("testGetText::result = %s", result.c_str());
    
}
