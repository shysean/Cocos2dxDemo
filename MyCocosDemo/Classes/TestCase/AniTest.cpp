//
//  AniTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 05/27/14.
//
//

#include "AniTest.h"
#include "../Tools/UIUtil.h"

AniTest::AniTest():
m_aniIndex(0)
{
    
}

void AniTest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
    initAni();
    
    // Add Touch Listener
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [=](Touch* touch, Event* event){
        
        m_armature->stopAllActions();
        Point touchPoint = touch->getLocation();
        Point heroPoint = m_armature->getPosition();
        
        Point deltaPoint = touchPoint - heroPoint;
        
        float time = sqrt(deltaPoint.x * deltaPoint.x + deltaPoint.y * deltaPoint.y) * 0.002;
        ActionInterval *action = cocos2d::MoveBy::create(time, deltaPoint);
        FiniteTimeAction *actionCallBack = CallFuncN::create(CC_CALLBACK_1(AniTest::setNormal, this));
        m_armature->runAction(Sequence::create(action, actionCallBack, NULL));
        setRun();
        
        if(deltaPoint.x < 0){
            m_armature->setRotation3D(Vertex3F(0, 180, 0));
        }else
        {
            m_armature->setRotation3D(Vertex3F(0, 0, 0));
        }
        return true;
    };

    
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
void AniTest::setNormal(Node* node)
{
    m_armature->getAnimation()->playWithIndex(0);
}
void AniTest::setRun()
{
    m_armature->getAnimation()->playWithIndex(1);

}
void AniTest::initTestMenu()
{
    ADD_TEST_METHOD(nextAni);
    ADD_TEST_METHOD(lastAni);
    ADD_TEST_METHOD(playAni);
    ADD_TEST_METHOD(pauseAni);
    ADD_TEST_METHOD(changeWeapon);
}

void AniTest::initAni()
{
    // 同步加载
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo(
                            "HeroAni/Export/HeroAni/HeroAni0.png",
                            "HeroAni/Export/HeroAni/HeroAni0.plist",
                            "HeroAni/Export/HeroAni/HeroAni.ExportJson");
    
    // 异步加载 Crased on Android.
//    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(
//                            "HeroAni/Export/HeroAni/HeroAni0.png",
//                            "HeroAni/Export/HeroAni/HeroAni0.plist",
//                            "HeroAni/Export/HeroAni/HeroAni.ExportJson",
//                            this, schedule_selector(AniTest::onDataLoaded));
    
    cocostudio::Armature *armature = cocostudio::CCArmature::create("HeroAni");
    armature->getAnimation()->playWithIndex(m_aniIndex);
    armature->setPosition(VisibleUtil::center());
    armature->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    armature->setScale(1.0f);

    addChild(armature);
    
    m_armature = armature;
}

void AniTest::onDataLoaded(float percent)
{
    char info[100];
    sprintf(info, "%f", percent);
    CCLOG("percent = %s", info);
    setInfo("Data Load Complate!");
}


// =============================
//        Test Funtion
// =============================

void AniTest::nextAni()
{
    int mevementCount = m_armature->getAnimation()->getMovementCount();
    m_aniIndex ++;
    if (m_aniIndex >= mevementCount)
    {
        m_aniIndex = mevementCount - 1;
    }
    m_armature->getAnimation()->playWithIndex(m_aniIndex);
}

void AniTest::lastAni()
{
    m_aniIndex --;
    if (m_aniIndex < 0)
    {
        m_aniIndex = 0;
    }
    m_armature->getAnimation()->playWithIndex(m_aniIndex);
}
void AniTest::playAni()
{
    m_armature->getAnimation()->playWithIndex(m_aniIndex);
}
void AniTest::pauseAni()
{
    m_armature->getAnimation()->pause();
}
void AniTest::changeWeapon()
{
    cocostudio::Skin *skin = cocostudio::Skin::createWithSpriteFrameName(
                    "girl_arms1.png");
    
    m_armature->getBone("Layer17")->addDisplay(skin, 1);
    m_armature->getBone("Layer17")->changeDisplayWithIndex(1, true);
}


