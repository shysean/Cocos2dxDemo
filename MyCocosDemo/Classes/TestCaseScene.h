//
//  TestCaseScene.h
//  Cocos2dxDemo
//
//  Created by shihongyang on 4/27/14.
//
//

#ifndef __Cocos2dxDemo__TestCaseScene__
#define __Cocos2dxDemo__TestCaseScene__

#include "cocos2d.h"
#include "TestCase.h"

USING_NS_CC;

#define LINE_SPACE          60

#define CREATE_TEST_SCENE(varTitle, varClassName)    \
{ varTitle, []() { return new varClassName(); } },

class BaseTestScene;

typedef struct _Controller{
	const char *test_name;
	std::function<BaseTestScene*()> callback;
} Controller;

class TestCaseScene : public Scene
{
public:
    TestCaseScene();
    virtual ~TestCaseScene();
    
    virtual bool init();
    
    bool onTouchBegan(Touch* touches, Event  *event);
    void onTouchMoved(Touch* touches, Event  *event);
    
private:
    Menu* m_menu;
    Point m_beginPos;

    
private:
    Menu* createMenu();
    void menuCallback(Ref * sender);

};

#endif /* defined(__Cocos2dxDemo__TestCaseScene__) */
