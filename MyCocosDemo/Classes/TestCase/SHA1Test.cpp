//
//  SHA1Test.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 09/22/14.
//
//

#include "SHA1Test.h"
#include "cocos2d.h"
#include "../Tools/sha1/sha1.h"

SHA1Test::SHA1Test()
{
    
}

void SHA1Test::runThisTest()
{
    Director::getInstance()->replaceScene(this);
}

void SHA1Test::initTestMenu()
{
    ADD_TEST_METHOD(testFunction);
}


// =============================
//        Test Funtion
// =============================

// 保存
void SHA1Test::testFunction()
{
    setInfo("testFunction");
    CCLOG("Save...");

    std::string testData = "Hello, I'm the data...";
    UserDefault::getInstance()->setStringForKey("teststr", testData);
    
    SHA1 * sha1 = new SHA1();
    
    sha1->addBytes(testData.c_str(), testData.length());
    unsigned char* digest = sha1->getDigest();
    SHA1::hexPrinter(digest, 20);
    printf("\n");

    delete sha1;
    sha1 = nullptr;
    free(digest);
    
    
    std::string loadData = UserDefault::getInstance()->getStringForKey("teststr");
    
    CCLOG("%s", loadData.c_str());

    sha1 = new SHA1();
    sha1->addBytes(loadData.c_str(), loadData.length());
    
    digest = sha1->getDigest();
    SHA1::hexPrinter(digest, 20);
    printf("\n");

    delete sha1;
    sha1 = nullptr;
    free(digest);
}