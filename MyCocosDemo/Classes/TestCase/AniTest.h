//
//  AniTest.h
//  MyCocosDemo
//
//  Created by shihongyang on 05/27/14
//
//

#ifndef __MyCocosDemo__AniTest__
#define __MyCocosDemo__AniTest__

#include "BaseTestScene.h"
#include "cocostudio/CocoStudio.h"


class AniTest : public BaseTestScene
{
public:
    AniTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();

    void nextAni();
    void lastAni();
    void playAni();
    void pauseAni();

    void initAni();
    void setNormal(Node* node);
    void setRun();
    
protected:
    cocostudio::Armature* m_armature;
    int m_aniIndex;
};

#endif /* defined(__MyCocosDemo__AniTest__) */