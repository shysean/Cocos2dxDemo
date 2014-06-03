//
//  DataStructure.h
//  MyCocosDemo
//
//  Created by shihongyang on 05/28/14
//
//

#ifndef __MyCocosDemo__DataStructure__
#define __MyCocosDemo__DataStructure__

#include "BaseTestScene.h"

class DataStructure : public BaseTestScene
{
public:
    DataStructure();
    
    virtual void runThisTest();
    virtual void initTestMenu();

    void traversalMap();

};

#endif /* defined(__MyCocosDemo__DataStructure__) */