//
//  TextTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 5/4/14.
//
//

#include "TextTest.h"
#include "../Tools/GameText.h"
#include "../Tools/UIUtil.h"

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
    return true;
}

void TextTest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
}

void TextTest::initTestMenu()
{
    ADD_TEST_METHOD(testGetText);
    ADD_TEST_METHOD(testCustomFont);
    

}

void TextTest::testGetText()
{
    CCLOG("TextTest::testGetText called.");

    // Has key "HELLO"
    string result1 = GameText::getInstance()->getText("HELLO");
    CCLOG("TextTest::testGetText result = %s", result1.c_str());
    
    setInfo(result1);

    // No key "H"
    string result2 = GameText::getInstance()->getText("H");
    CCLOG("TextTest::testGetText result = %s", result2.c_str());
    
}

void TextTest::testCustomFont()
{
    string fontFile = "fonts/MSYH.ttf";
    if(FileUtils::getInstance()->isFileExist(fontFile) == false)
    {
        CCLOGWARN("%s is not exist!", fontFile.c_str());
        return;
    }
    
    Label* label = Label::createWithTTF(GameText::getInstance()->getText("FONTTESTINFO"), fontFile, 30);
    label->setPosition(VisibleUtil::center());
    
    // sean: Notice:This method can effect outline.
    // label->setColor(Color3B::RED);
    
    label->setTextColor(Color4B::RED);
    label->enableOutline(Color4B::WHITE, 2);
    addChild(label);
    
}

