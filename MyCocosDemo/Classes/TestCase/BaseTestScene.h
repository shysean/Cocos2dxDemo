//
//  BaseTestScene.h
//  Cocos2dxDemo
//
//  Created by shihongyang on 4/27/14.
//
//

#ifndef __Cocos2dxDemo__BaseTestScene__
#define __Cocos2dxDemo__BaseTestScene__

#include "cocos2d.h"

USING_NS_CC;

const int TEST_SCENE_TAG = 1000;

class BaseTestScene : public Scene
{
public:
    BaseTestScene();
    virtual ~BaseTestScene();
    
    virtual void onEnter() override;
    
    virtual void runThisTest() = 0;
};

#endif /* defined(__Cocos2dxDemo__BaseTestScene__) */
