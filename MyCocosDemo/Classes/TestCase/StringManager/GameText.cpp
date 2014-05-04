//
//  GameText.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 4/30/14.
//
//

#include "GameText.h"
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

// text folder need add as references
// Don't add as group, if not cocos will can't find the file.
const string STRING_XML_FILE = "text/string.xml";


GameText* GameText::instance = nullptr;

GameText::GameText()
{
}

GameText::~GameText()
{
    stringMap.clear();
}

GameText* GameText::getInstance()
{
    if (nullptr == instance)
    {
        instance = new GameText();
        instance->init();
    }
    
    return instance;
}

void GameText::init()
{
    stringMap.clear();
    
    bool isFileExist = FileUtils::getInstance()->isFileExist(STRING_XML_FILE);
    if (isFileExist == false)
    {
        CCLOGERROR("GameText::init %s is not exist!", STRING_XML_FILE.c_str());
        return;
    }
    
//    Code For Test:
//    string fullPath = FileUtils::getInstance()->fullPathForFilename(stringFile);
//    CCLOG("GameText::init fullPath = %s", fullPath.c_str());
    
    
    XMLDocument *myDocument = new XMLDocument();
    myDocument->LoadFile(STRING_XML_FILE.c_str());
    
    XMLElement *rootElement = myDocument->RootElement();
//    CCLOG("RootElement:%s",rootElement->Value());
    
    // 遍历rootElement下的所有子标签
    for( auto todoElement = rootElement->FirstChildElement();
        todoElement;
        todoElement = todoElement->NextSiblingElement())
    {
        
        string attribute = todoElement->Attribute("name");
//        CCLOG("attribute:%s",attribute.c_str());
        string value = todoElement->GetText();
        
        stringMap.insert(std::make_pair(attribute, value));
    }
}


string GameText::getText(string key)
{
    return stringMap.at(key);
}