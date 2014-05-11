//
//  GUITest.h
//  MyCocosDemo
//
//  Created by shihongyang on 05/10/14
//
//

#ifndef __MyCocosDemo__GUITest__
#define __MyCocosDemo__GUITest__

#include "BaseTestScene.h"

class GUITest : public BaseTestScene
{
public:
    GUITest();
    
    virtual void runThisTest();
    virtual void initTestMenu();

    void showUILayer();

private:
    Layer* m_uiLayer;
    cocos2d::extension::EditBox* m_edit;
    
private:
    void addEditBox();
};

#endif /* defined(__MyCocosDemo__GUITest__) */