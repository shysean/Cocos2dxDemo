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

// sean: create test menuItem and add to vector for create menu.
// @param __vectorOfMenu__  Vector<cocos2d::MenuItem *>
// @param __funcName__      callback method name also as title
#define ADD_TEST_METHOD(__vectorOfMenu__, __funcName__) \
auto __funcName__##Label = Label::createWithSystemFont(#__funcName__, "Arial", 50); \
auto __funcName__##MenuItem = MenuItemLabel::create(__funcName__##Label, [=](Ref * sender){ __funcName__();}); \
__vectorOfMenu__.pushBack(__funcName__##MenuItem);\

class BaseTestScene : public Scene
{
public:
    BaseTestScene();
    virtual ~BaseTestScene();
    
    virtual void onEnter() override;
    
    virtual void runThisTest() = 0;
    virtual void initTestMenu() = 0;
protected:
    Vector<cocos2d::MenuItem *> vectorOfMenu;

};

#endif /* defined(__Cocos2dxDemo__BaseTestScene__) */
