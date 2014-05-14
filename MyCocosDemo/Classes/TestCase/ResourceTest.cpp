//
//  ResourceTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 05/13/14.
//
//
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>

#include "ResourceTest.h"
#include "../Tools/UIUtil.h"
#include "../Tools/StringUtil.h"
#include "base64.h"

using namespace std;

ResourceTest::ResourceTest()
{
    
}

void ResourceTest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
}

void ResourceTest::initTestMenu()
{
    ADD_TEST_METHOD(testTexturePacker);
    ADD_TEST_METHOD(testStringBase64);
    ADD_TEST_METHOD(testPngBase64);
    ADD_TEST_METHOD(testCreateSpriteWithData);
    ADD_TEST_METHOD(testGetDataFromBinFile);
    ADD_TEST_METHOD(testReadIndexFile);
}


struct IndexFile {
    std::string filename;
    int offset;
    int size;
    
    IndexFile(std::string content)
    {
        vector<string> token;
        StringUtil::split(content, ',', token);
        
        filename = token.at(0);
        offset = StringUtil::intValue(token.at(1).c_str(), 0);
        size = StringUtil::intValue(token.at(2).c_str(), 0);
    }
    
    std::string info()
    {
        char info[1024];
        sprintf(info, "filename=%s offset=%d size=%d", filename.c_str(), offset, size);
        return info;
    }
};


void ResourceTest::showImageUsingData(unsigned char *data, unsigned long dataSize)
{
	if(data == NULL) {
		CCLOG("BigFileTest: data is null");
		return;
	}
	
	CCLOG("BigFileTest: data has read. size=%ld", dataSize);
	
	
	Image* image = new Image();
	bool flag;
//	flag = image->initWithImageData(data, dataSize, Image::Format::PNG);
    flag = image->initWithImageData(data, dataSize);
	CCLOG("BigFileTest: CCImage flag=%d", flag);
	
//	Director::getInstance()->getTextureCache()->addImage(image, "testImage");
	
	Texture2D* texture = new Texture2D();
	flag = texture->initWithImage(image);
	CCLOG("BigFileTest: Texture2D flag=%d", flag);
	
	Sprite* sprite = Sprite::create();
	sprite->setTexture(texture);
	
    
    Rect rect = Rect::ZERO;
    rect.size = texture->getContentSize();
    sprite->setTextureRect(rect);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    int x = rand()%(int)visibleSize.width;
    int y = rand()%(int)visibleSize.height;
    sprite->setPosition(Point(x, y));
	addChild(sprite);


}

// =============================
//        Test Funtion
// =============================

void ResourceTest::testReadIndexFile()
{
    const char* indexFile = "png.idx";
    const char* binFile = "png.bin";
    
    // sean: 防御式风格
    do
    {
        CC_BREAK_IF(FileUtils::getInstance()->isFileExist(indexFile) == false);
        std::string content = FileUtils::getInstance()->getStringFromFile(indexFile);
        //        CCLOG("%s", content.c_str());
        
        std::vector<string> lines;
        StringUtil::split(content, '\n', lines);
        
        std::vector<IndexFile *> vectorOfIndexFile;
        for (string line: lines)
        {
            //            CCLOG("%s", line.c_str());
            IndexFile* indexFile = new IndexFile(line);
            CCLOG("%s", indexFile->info().c_str());
            vectorOfIndexFile.push_back(indexFile);
        }
        
        std::ifstream fin(binFile, std::ios::binary);
        
        for (IndexFile *f: vectorOfIndexFile)
        {
            
            char png[f->size];
            
            fin.read(png, sizeof(char) * f->size);
            
            unsigned char *decodeData;
            int dataSize = base64Decode((unsigned char*)png, f->size, &decodeData);
            
            showImageUsingData(decodeData, dataSize);
            
        }
    }while (0);
}

void ResourceTest::testGetDataFromBinFile()
{
    std::ifstream fin("png.bin", std::ios::binary);
    
    char png1[8416] = {0};
    fin.read(png1, sizeof(char) * 8416);

    fin.close();
    
    
    unsigned char *decodeData;
    int len = base64Decode((unsigned char*)png1, 8416, &decodeData);

    showImageUsingData(decodeData, len);


}

void ResourceTest::testStringBase64()
{
    
    std::string data = "HELLO BASE64";

    char* encodedData = 0;
    base64Encode((unsigned char*)data.c_str(), data.length(), &encodedData);

    unsigned char *decodeData;
    int len = base64Decode((unsigned char*)encodedData, (unsigned int)strlen(encodedData), &decodeData);
    
    
    
    char info[1024];
    sprintf(info, "String=%s  Encoded=%s  Decode=%s", data.c_str(), encodedData, decodeData);
    CCLOG("%s,Lenth = %d",(const char*)decodeData, len);
    
    setInfo(info);

}

void ResourceTest::testPngBase64()
{
    const char* pngFile = "CloseSelected.png";
    Data fileData = FileUtils::getInstance()->getDataFromFile(pngFile);

    char *encodedData = 0;
    int encodeLen = base64Encode(fileData.getBytes(), fileData.getSize(), &encodedData);
    CCLOG("%s,%d",encodedData, encodeLen);
    
    char info[2024];
    sprintf(info, "encode data size = %d", encodeLen);
    setInfo(info);
}

void ResourceTest::testCreateSpriteWithData()
{
    const char* pngFile = "CloseSelected.png";
    
    Image* image = new Image();

//    sean: 2 way to get file data to create image.
//    #1
//    ssize_t pSize = 0;
//    unsigned char* fileData = FileUtils::getInstance()->getFileData(pngFile, "rb", &pSize);
//    image->initWithImageData(fileData, pSize);

//    #2
    Data fileData = FileUtils::getInstance()->getDataFromFile(pngFile);
    image->initWithImageData(fileData.getBytes(), fileData.getSize());

    Texture2D* texture = new Texture2D();
    texture->initWithImage(image);
    
    
	Sprite* sprite = CCSprite::create();
	sprite->setTexture(texture);
	sprite->setPosition(VisibleUtil::center());
    
    Rect rect = Rect::ZERO;
    rect.size = texture->getContentSize();
    sprite->setTextureRect(rect);
    
    addChild(sprite);
}


void ResourceTest::testTexturePacker()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texturePacker/data.plist","texturePacker/data.pvr.ccz");
    
//    sean: why create a spriteBatchNode?
//    
    auto *texture = Director::getInstance()->getTextureCache()->getTextureForKey("texturePacker/data.pvr.ccz");
    auto *node= SpriteBatchNode::createWithTexture(texture);
    addChild(node);
    
//    Test parent node different
//    for (int i = 0; i < 10000; i++) {
//        auto sprite = Sprite::createWithSpriteFrameName("HelloWorld.png");
//        Size visibleSize = Director::getInstance()->getVisibleSize();
//        int x = rand()%(int)visibleSize.width;
//        int y = rand()%(int)visibleSize.height;
//
//        sprite->setPosition(Point(x, y));
//        
////        node->addChild(sprite);         // 0.4s on mac
//        this->addChild(sprite);           // 0.4s on mac
////        sean: seem no different.
//
//    }
    
    auto *s1 = Sprite::createWithSpriteFrameName("HelloWorld.png");
    
    s1->setPosition(Point(355,325));
    s1->setAnchorPoint(Point::ZERO);

    node->addChild(s1);

    auto *s2 = Sprite::createWithSpriteFrameName("CloseNormal.png");

    s2->setPosition(Point(100,100));
    s2->setAnchorPoint(Point::ZERO);

    node->addChild(s2);

}

