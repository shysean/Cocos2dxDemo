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


Point UIUtil::visibleLeftBottom()
{
    return Director::getInstance()->getVisibleOrigin();
}
Point UIUtil::visibleLeftTop()
{
    Point leftBottom = visibleLeftBottom();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    return Point(leftBottom.x, leftBottom.y + visibleSize.height);
}
Point UIUtil::visibleRightBottom()
{
    Point leftBottom = visibleLeftBottom();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    return Point(leftBottom.x + visibleSize.width, leftBottom.y);
}
Point UIUtil::visibleRightTop()
{
    Point leftBottom = visibleLeftBottom();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    return Point(leftBottom.x + visibleSize.width, leftBottom.y + visibleSize.height);
}