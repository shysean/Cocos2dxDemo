//
//  ParticleTest.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 05/11/14.
//
//

#include "ParticleTest.h"
#include "../Tools/UIUtil.h"

ParticleTest::ParticleTest()
{
    
}

void ParticleTest::runThisTest()
{
    Director::getInstance()->replaceScene(this);
    
    m_particleLayer = Layer::create();
    addChild(m_particleLayer);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    
    // Add Touch Listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [=](Touch* touch, Event* event){
        
        Point touchPoint = touch->getLocation();
        testPlistFile(touchPoint);
        return true;
    };
    
    touchListener->onTouchMoved = [=](Touch* touch, Event* event){
        
        Point touchPoint = touch->getLocation();
        testPlistFile(touchPoint);
    };

    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

}

void ParticleTest::initTestMenu()
{
    ADD_TEST_METHOD(testFireworks);
    ADD_TEST_METHOD(testRains);
    ADD_TEST_METHOD(testSnow);
    ADD_TEST_METHOD(testSmoke);
    ADD_TEST_METHOD(testExplosion);
    ADD_TEST_METHOD(testSpiral);
    ADD_TEST_METHOD(testMeteor);
    ADD_TEST_METHOD(testGalaxy);
    ADD_TEST_METHOD(testSun);
    ADD_TEST_METHOD(testFire);
    
}

void ParticleTest::clear()
{
    m_particleLayer->removeAllChildren();
}


// =============================
//        Test Funtion
// =============================
void ParticleTest::testFireworks()
{
    clear();
    
    ParticleSystem* ps = ParticleFireworks::create();
    ps->setPosition(VisibleUtil::center());
    ps->setAutoRemoveOnFinish(true);

    m_particleLayer->addChild(ps);
    
    setInfo("ParticleFireworks");
}

void ParticleTest::testRains()
{
    clear();
    
    ParticleSystem* ps = ParticleRain::create();
    ps->setPosition(Point(VisibleUtil::width() / 2, VisibleUtil::top()));
    ps->setAutoRemoveOnFinish(true);

    m_particleLayer->addChild(ps);
    
    setInfo("ParticleRain");
}
void ParticleTest::testSnow()
{
    clear();
    
    ParticleSystem* ps = ParticleSnow::create();
    ps->setPosition(Point(VisibleUtil::width() / 2, VisibleUtil::top()));
    ps->setAutoRemoveOnFinish(true);

    m_particleLayer->addChild(ps);
    
    setInfo("ParticleSnow");
}
void ParticleTest::testSmoke()
{
    clear();
    
    ParticleSystem* ps = ParticleSmoke::create();
    ps->setPosition(VisibleUtil::center());
    ps->setAutoRemoveOnFinish(true);

    m_particleLayer->addChild(ps);
    
    setInfo("ParticleSmoke");
}
void ParticleTest::testExplosion()
{
    clear();
    
    ParticleSystem* ps = ParticleExplosion::create();
    ps->setPosition(VisibleUtil::center());
    ps->setAutoRemoveOnFinish(true);

    m_particleLayer->addChild(ps);
    
    setInfo("ParticleExplosion");
}
void ParticleTest::testSpiral()
{
    clear();
    
    ParticleSystem* ps = ParticleSpiral::create();
    ps->setPosition(VisibleUtil::center());
    ps->setAutoRemoveOnFinish(true);

    m_particleLayer->addChild(ps);
    
    setInfo("ParticleSpiral");
}
void ParticleTest::testMeteor()
{
    clear();
    
    ParticleSystem* ps = ParticleMeteor::create();
    ps->setPosition(VisibleUtil::center());
    ps->setAutoRemoveOnFinish(true);

    m_particleLayer->addChild(ps);
    
    setInfo("ParticleMeteor");
}
void ParticleTest::testGalaxy()
{
    clear();
    
    ParticleSystem* ps = ParticleGalaxy::create();
    ps->setPosition(VisibleUtil::center());
    ps->setAutoRemoveOnFinish(true);

    m_particleLayer->addChild(ps);
    
    setInfo("ParticleGalaxy");
}
void ParticleTest::testSun()
{
    clear();
    
    ParticleSystem* ps = ParticleSun::create();
    ps->setPosition(VisibleUtil::center());
    ps->setAutoRemoveOnFinish(true);

    m_particleLayer->addChild(ps);
    
    setInfo("ParticleSun");
}
void ParticleTest::testFire()
{
    clear();
    
    ParticleSystem* ps = ParticleFire::create();
    ps->setPosition(VisibleUtil::center());
    ps->setAutoRemoveOnFinish(true);

    m_particleLayer->addChild(ps);
    
    setInfo("ParticleFire");
}
void ParticleTest::testPlistFile(Point position)
{
    // sean: File "particleTexture.plist" made of http://particle2dx.com/
    auto *ps = ParticleSystemQuad::create("particle/particleTexture.plist");
    
    // sean: Importance! set this for auto release when finsih.
    ps->setAutoRemoveOnFinish(true);
    ps->setPosition(position);
    m_particleLayer->addChild(ps);
    
    setInfo("ParticleSystemQuad");
}

