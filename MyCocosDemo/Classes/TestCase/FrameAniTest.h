//
//  FrameAniTest.h
//  MyCocosDemo
//
//  Created by shihongyang on 08/03/14
//
//

#ifndef __MyCocosDemo__FrameAniTest__
#define __MyCocosDemo__FrameAniTest__

#include "BaseTestScene.h"

class FrameAniTest : public BaseTestScene
{
public:
    FrameAniTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();

    void testFrameAni();
    void testFadeAni();

    void actionCallBack();
    void changeSpriteByAni(Sprite* from, Sprite* to);
    
protected:
    int spriteIndex;
    Sprite* spriteFrom;
    Sprite* spriteTo;
};

#endif /* defined(__MyCocosDemo__FrameAniTest__) */