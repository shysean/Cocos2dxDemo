//
//  ResourceTest.h
//  MyCocosDemo
//
//  Created by shihongyang on 05/13/14
//
//

#ifndef __MyCocosDemo__ResourceTest__
#define __MyCocosDemo__ResourceTest__

#include "BaseTestScene.h"

class ResourceTest : public BaseTestScene
{
public:
    ResourceTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();

    void testTexturePacker();
    void testStringBase64();
    void testPngBase64();
    void testCreateSpriteWithData();
    void testGetDataFromBinFile();
    void testReadIndexFile();

    
    void showImageUsingData(unsigned char *data, unsigned long dataSize);
};

#endif /* defined(__MyCocosDemo__ResourceTest__) */