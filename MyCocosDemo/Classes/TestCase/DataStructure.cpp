//
//  DataStructure.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 05/28/14.
//
//

#include "DataStructure.h"

DataStructure::DataStructure()
{
    
}

void DataStructure::runThisTest()
{
    Director::getInstance()->replaceScene(this);
}

void DataStructure::initTestMenu()
{
    ADD_TEST_METHOD(traversalMap);
}


// =============================
//        Test Funtion
// =============================
void DataStructure::traversalMap()
{
    cocos2d::Map<std::string, cocos2d::Node*> nodeMap;
    for (int i = 0; i < 10; i++) {
        Node* node = Node::create();
        char key[4];
        sprintf(key, "%d", i);
        nodeMap.insert(key, node);
    }
    
    for( auto e : nodeMap)
    {
        //e.first获得键
        auto key = e.first;
        //e.second获得值
        auto node = e.second;
        
        CCLOG("KEY=%s VALUE=%d", key.c_str(), node->_ID);
    }
}