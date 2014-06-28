//
//  ScrollBackgroundTest.h
//  MyCocosDemo
//
//  Created by shihongyang on 06/28/14
//
//

#ifndef __MyCocosDemo__ScrollBackgroundTest__
#define __MyCocosDemo__ScrollBackgroundTest__

#include "BaseTestScene.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

class ScrollBackgroundTest : public BaseTestScene
{
public:
    ScrollBackgroundTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();
    virtual void update(float delta) override;

    void testFunction();

private:
    void initScene();
    
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
private:
    cocos2d::extension::Scale9Sprite* m_bg1;
    cocos2d::extension::Scale9Sprite* m_bg2;
};

#endif /* defined(__MyCocosDemo__ScrollBackgroundTest__) */