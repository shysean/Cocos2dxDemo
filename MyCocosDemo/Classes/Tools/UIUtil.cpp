//
//  UIUtil.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 5/10/14.
//
//

#include "UIUtil.h"

EditBox* UIUtil::createEditBox(Node* parent, int x, int y, const char* placeHolder)
{
    auto editName = EditBox::create(Size(250,50), Scale9Sprite::create("image/textField.png"));
    editName->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    editName->setPosition(Point(x, y));
    editName->setFontName("Arial");
    editName->setFontSize(24);
    editName->setFontColor(Color3B::BLACK);
    editName->setPlaceHolder(placeHolder);
    editName->setPlaceholderFontColor(Color3B::GRAY);
    editName->setReturnType(EditBox::KeyboardReturnType::DONE);
    parent->addChild(editName);
    
    return editName;
}


Point VisibleUtil::leftBottom()
{
    return Director::getInstance()->getVisibleOrigin();
}
Point VisibleUtil::leftTop()
{
    Point originPoint = leftBottom();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    return Point(originPoint.x, originPoint.y + visibleSize.height);
}
Point VisibleUtil::rightBottom()
{
    Point originPoint = leftBottom();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    return Point(originPoint.x + visibleSize.width, originPoint.y);
}
Point VisibleUtil::rightTop()
{
    Point originPoint = leftBottom();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    return Point(originPoint.x + visibleSize.width, originPoint.y + visibleSize.height);
}
Point VisibleUtil::center()
{
    return Point(width() / 2, height() / 2);
}
int VisibleUtil::top()
{
    Point originPoint = leftBottom();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    return originPoint.y + visibleSize.height;
}
int VisibleUtil::down()
{
    Point originPoint = leftBottom();

    return originPoint.y;
}
int VisibleUtil::left()
{
    Point originPoint = leftBottom();

    return originPoint.x;
}
int VisibleUtil::right()
{
    Point originPoint = leftBottom();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    return originPoint.x + visibleSize.width;
}
int VisibleUtil::width()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return visibleSize.width;
}
int VisibleUtil::height()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return visibleSize.height;
}
