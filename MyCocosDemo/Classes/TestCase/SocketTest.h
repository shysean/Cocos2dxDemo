//
//  SocketTest.h
//  Cocos2dxDemo
//
//  Created by shihongyang on 4/27/14.
//
//

#ifndef __Cocos2dxDemo__SocketTest__
#define __Cocos2dxDemo__SocketTest__

#include "BaseTestScene.h"

class CGameSocket;

class SocketTest : public BaseTestScene
{
public:
    SocketTest();
    
    virtual void runThisTest();
    virtual void initTestMenu();

    
    void testCreatSocket();
    void testSend();
    void testSimpleSend();
    void testFunction3();
    
    
protected:
    CGameSocket* m_socket;
};



#endif /* defined(__Cocos2dxDemo__SocketTest__) */
