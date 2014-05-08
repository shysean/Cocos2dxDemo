//
//  TextTest.h
//  MyCocosDemo
//
//  Created by shihongyang on 5/4/14.
//
//

#ifndef __MyCocosDemo__TextTest__
#define __MyCocosDemo__TextTest__

#include "cocos2d.h"
#include "BaseTestScene.h"

class TextTest : public BaseTestScene
{
public:
    TextTest();
    ~TextTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();
    
    virtual bool init() override;
    
    void testGetText();
    
private:
    Label* infoLabel;
};

#endif /* defined(__MyCocosDemo__TextTest__) */
