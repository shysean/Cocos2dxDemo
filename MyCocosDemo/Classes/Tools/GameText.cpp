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

// text folder need add as references in Xcode
// Don't add as group, if not cocos will can't find the file.
const string STRING_XML_FILE = "text/string.xml";


GameText* GameText::m_instance = nullptr;
bool GameText::m_isReady = false;

GameText::GameText()
{
}

GameText::~GameText()
{
    m_stringMap.clear();
}

GameText* GameText::getInstance()
{
    if (nullptr == m_instance)
    {
        m_instance = new GameText();
        m_isReady = m_instance->init();
    }
    
    return m_instance;
}

bool GameText::init()
{
    m_stringMap.clear();
    
    bool isFileExist = FileUtils::getInstance()->isFileExist(STRING_XML_FILE);
    if (isFileExist == false)
    {
        CCLOGERROR("GameText.init: %s is not exist!", STRING_XML_FILE.c_str());
        return false;
    }
    
//    Code For Debug:
//    string fullPath = FileUtils::getInstance()->fullPathForFilename(STRING_XML_FILE);
//    CCLOG("GameText::init fullPath = %s", fullPath.c_str());
    
    
    XMLDocument *document = new XMLDocument();
    
    // TinyXml2's BUG: call LoadFile() will crash on Android.
    // return errorCode is XML_ERROR_FILE_NOT_FOUND(=3)
    // XMLError error = myDocument->LoadFile(fullPath.c_str());
    
    ssize_t size;
    char *pFileContent = (char*)FileUtils::getInstance()->getFileData(STRING_XML_FILE , "r", &size);
    
    // Parse() is OK!
    XMLError error = document->Parse(pFileContent);
    
    if(error != XML_SUCCESS)
    {
        CCLOGERROR("GameText.init: LoadFile Failed! Error Code = %d", error);
        return false;
    }
    
    XMLElement *rootElement = document->RootElement();
//    CCLOG("RootElement:%s",rootElement->Value());
    
    // 遍历rootElement下的所有子标签
    for( auto todoElement = rootElement->FirstChildElement();
        todoElement;
        todoElement = todoElement->NextSiblingElement())
    {
        
        string attribute = todoElement->Attribute("name");
        string value = todoElement->GetText();

//      CCLOG("attribute:%s",attribute.c_str());
//      CCLOG("value:%s",value.c_str());

        m_stringMap.insert(std::make_pair(attribute, value));
    }
    
    return true;
}


string GameText::getText(string key)
{
    string result;

    if (m_isReady == false) {
        CCLOGWARN("GameText.getText: GameText is not ready.");
#if defined COCOS2D_DEBUG
        result = "NO READY!";
#else
        result = "";
#endif    
        return result;
    }
    
    try {
        result = m_stringMap.at(key);
    } catch (exception e) {
        CCLOGWARN("GameText.getText: Throw exception");
        
#if defined COCOS2D_DEBUG
        result = "NO STRING RES!";
#else
        result = "";
#endif
        
    }
    return result;
}