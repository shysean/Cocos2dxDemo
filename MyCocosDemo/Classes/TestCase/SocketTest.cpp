//
//  SocketTest.cpp
//  Cocos2dxDemo
//
//  Created by shihongyang on 4/27/14.
//
//

#include "SocketTest.h"
#include "../Tools/TimeUtil.h"
#include "../Tools/GameSocket.h"

SocketTest::SocketTest()
: m_socket(nullptr)
{
}

void SocketTest::runThisTest()
{
    CCLOG("SocketTest::runThisTest");
    
    Director::getInstance()->replaceScene(this);
    
    m_socket = new CGameSocket();
    
    while (true)
    {
        char buffer[_MAX_MSGSIZE] = { 0 };
        int nSize = sizeof(buffer);
        char* pbufMsg = buffer;
        if(m_socket == NULL)
        {
            break;
        }
        if (!m_socket->ReceiveMsg(pbufMsg, nSize)) {
            break;
        }
    }
}


void SocketTest::initTestMenu()
{
    ADD_TEST_METHOD(testCreatSocket);
    ADD_TEST_METHOD(testSend);
    ADD_TEST_METHOD(testSimpleSend);
    ADD_TEST_METHOD(testFunction3);
}


void SocketTest::testCreatSocket()
{
//    long long time = TimeUtil::currentTimeMillis();
//    char info[255];
//    sprintf(info, "TIME=%lld", time);
//    setInfo(info);
    
    bool isCreated = m_socket->Create("127.0.0.1", 1234);
    if (isCreated) {
        setInfo("Created SCCUESS!");
    }else{
        setInfo("NOT CREATED!");
    }
}

void SocketTest::testSend()
{
//    time_t t = time( 0 );
//    char info[255];
//    strftime(info, 255, "%Y-%m-%d %H:%M:%S", localtime(&t));
//    setInfo(info);
    
    
    // \n 用于Ruby的Server脚本读取行
    char data[10] = "HELLO!\n";
    int dataLen = sizeof(data);
    
	char *str = (char *) malloc(dataLen + 1);
	memcpy(str, data, dataLen);
	str[dataLen] = '\0';
    
    // 放入缓存
    m_socket->SendMsg((void*)str, dataLen);
    
    // 发送
    m_socket->Flush();

}



void SocketTest::testSimpleSend()
{
    
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    

    portno = 1234;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    server = gethostbyname("127.0.0.1");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
    
    log("SocketTest::testFunction");

    char data[15] = "HELLO Socket\n";
    int dataLen = sizeof(data);
    
	char *str = (char *) malloc(dataLen + 1);
	memcpy(str, data, dataLen);
	str[dataLen] = '\0';
    send(sockfd, ((void*)str), dataLen, 0);
}


void SocketTest::testFunction3()
{
    log("SocketTest::testFunction");
}



