//
//  ParticleTest.h
//  MyCocosDemo
//
//  Created by shihongyang on 05/11/14
//
//

#ifndef __MyCocosDemo__ParticleTest__
#define __MyCocosDemo__ParticleTest__

#include "BaseTestScene.h"

class ParticleTest : public BaseTestScene
{
public:
    ParticleTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();

protected:
    void testFireworks();
    void testRains();
    void testSnow();
    void testSmoke();
    void testExplosion();
    void testSpiral();
    void testMeteor();
    void testGalaxy();
    void testSun();
    void testFire();
    void testPlistFile(Point position);
    
    void clear();
    
private:
    cocos2d::Layer* m_particleLayer;
};

#endif /* defined(__MyCocosDemo__ParticleTest__) */