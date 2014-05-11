//
//  ScreenTest.h
//  MyCocosDemo
//
//  Created by shihongyang on 5/9/14.
//
//

#ifndef __MyCocosDemo__ScreenTest__
#define __MyCocosDemo__ScreenTest__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "BaseTestScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ScreenTest : public BaseTestScene
{
public:
    ScreenTest();
    ~ScreenTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();
    
    virtual bool init() override;
    virtual void draw(cocos2d::Renderer *renderer, const kmMat4& transform, bool transformUpdated);

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    void onMouseScroll(Event *event);

private:
    float m_scale;
    double m_distance;    //两个触摸点之间的距离
    
    EditBox* m_editWidth;
    EditBox* m_editHeight;
    
    int m_designWidth;
    int m_designHeight;

private:
    void drawRect(int sx, int sy, int ex, int ey, Color4B color);
    void drawVisibleRect();
    void drawDesignRect();
    void refeshInfo();
    
    void resetDesignSize();
};
#endif /* defined(__MyCocosDemo__ScreenTest__) */
