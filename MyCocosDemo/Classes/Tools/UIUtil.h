//
//  UIUtil.h
//  MyCocosDemo
//
//  Created by shihongyang on 5/10/14.
//
//

#ifndef __MyCocosDemo__UIUtil__
#define __MyCocosDemo__UIUtil__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class UIUtil
{
public:
    // widget
    static EditBox* createEditBox(Node* parent, int x, int y, const char* placeHolder = "");
    

    
};

class VisibleUtil
{
public:
    // point
    static Point leftBottom();
    static Point leftTop();
    static Point rightBottom();
    static Point rightTop();
    static Point center();
    static int top();
    static int down();
    static int left();
    static int right();
    static int height();
    static int width();
};
#endif /* defined(__MyCocosDemo__UIUtil__) */
