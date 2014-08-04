//
//  FrameAniTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 08/03/14.
//
//

#include "FrameAniTest.h"

FrameAniTest::FrameAniTest()
: spriteIndex(0)
{
    
}

void FrameAniTest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
    
}

void FrameAniTest::initTestMenu()
{
    ADD_TEST_METHOD(testFrameAni);
    ADD_TEST_METHOD(testFadeAni);
}


// =============================
//        Test Funtion
// =============================

void FrameAniTest::testFadeAni()
{
    spriteFrom = Sprite::create("frameAni/ground.png", Rect(0, 0, 64, 16));
    spriteTo = Sprite::create("frameAni/ground.png", Rect(0, 16, 64, 16));
    
    changeSpriteByAni(spriteFrom, spriteTo);

    spriteFrom->setPosition(Point(200,200));
    spriteTo->setPosition(Point(200,200));
    
    spriteFrom->setScale(4);
    spriteTo->setScale(4);
    
    addChild(spriteFrom);
    addChild(spriteTo);
}

void FrameAniTest::actionCallBack()
{
    int fromIndex = spriteIndex;
    if (fromIndex >= 4 ) {
        fromIndex = 0;
        spriteIndex = 0;
    }
    
    int toIndex = fromIndex + 1;
    if (toIndex >= 4) {
        toIndex = 0;
    }
    
    spriteFrom->setTextureRect(Rect(0, fromIndex *16, 64, 16));
    spriteTo->setTextureRect(Rect(0, toIndex * 16, 64, 16));

    changeSpriteByAni(spriteFrom, spriteTo);
}

void FrameAniTest::changeSpriteByAni(Sprite* from, Sprite* to)
{
    spriteIndex++;

    from->setOpacity(255);
    to->setOpacity(0);
    
    
    auto fadeOut = FadeOut::create(1);
    
    auto fadeIn = Sequence::create(
                        FadeIn::create(1),
                        CallFunc::create( CC_CALLBACK_0(FrameAniTest::actionCallBack,this)),
                        NULL);
    
    from->runAction(fadeOut);
    to->runAction(fadeIn);
}


void FrameAniTest::testFrameAni()
{
    setInfo("testFrameAni");
    
    auto sprite = Sprite::create("frameAni/frameAni.png",Rect(0,0,32,32));
    if (sprite == nullptr) {
        CCLOGERROR("File not found!");
        return;
    }
    
    sprite->setScale(8);
    sprite->setPosition(Point(350,400));
    this->addChild(sprite,1);
    
    
    int width = 32;
    int height = 32;
    
    Vector<cocos2d::SpriteFrame *> frameArray;
    Animate *animate = nullptr;
    
    for (int i = 0; i < 6; i ++) {
        for (int j = 0; j < 8; j ++) {
            auto spriteFrame = SpriteFrame::create("frameAni/frameAni.png", Rect(j*width, i*height, width, height));
            frameArray.pushBack(spriteFrame);
        }
    }
    
    auto animation = Animation::createWithSpriteFrames(frameArray, 0.2f);
    animate = Animate::create(animation);

    auto spawn = Spawn::create(animate, NULL);
    sprite->runAction(RepeatForever::create(spawn));
    
    
}











