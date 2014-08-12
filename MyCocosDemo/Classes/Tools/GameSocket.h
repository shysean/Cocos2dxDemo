//
//  GameSocket.h
//  MyCocosDemo
//
//  Created by shihongyang on 8/12/14.
//
//

#ifndef __MyCocosDemo__GameSocket__
#define __MyCocosDemo__GameSocket__


/**
 * code from http://blog.csdn.net/langresser/article/details/8646088
 * 2013-07-21
 */

/**
 * cross socket for iOS, android,...
 * read the end
 */

#pragma once

#ifdef WIN32
#include <windows.h>
#include <WinSock.h>
#else
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

#endif

#ifndef CHECKF
#define CHECKF(x) \
do \
{ \
if (!(x)) { \
return 0; \
} \
} while (0)
#endif

#define _MAX_MSGSIZE 16 * 1024		// 暂定一个消息最大为16k
#define BLOCKSECONDS	30			// INIT函数阻塞时间
#define INBUFSIZE	(64*1024)		//?	具体尺寸根据剖面报告调整  接收数据的缓存
#define OUTBUFSIZE	(8*1024)		//? 具体尺寸根据剖面报告调整。 发送数据的缓存，当不超过8K时，FLUSH只需要SEND一次

class CGameSocket {
public:
	CGameSocket(void);
	bool	Create(const char* pszServerIP, int nServerPort, int nBlockSec = BLOCKSECONDS, bool bKeepAlive = false);
	bool	SendMsg(void* pBuf, int nSize);
	bool	ReceiveMsg(void* pBuf, int& nSize);
	bool	Flush(void);
	bool	Check(void);
	void	Destroy(void);
	SOCKET	GetSocket(void) const { return m_sockClient; }
private:
	bool	recvFromSock(void);		// 从网络中读取尽可能多的数据
	bool    hasError();			// 是否发生错误，注意，异步模式未完成非错误
	void    closeSocket();
    
	SOCKET	m_sockClient;
    
	// 发送数据缓冲
	char	m_bufOutput[OUTBUFSIZE];	//? 可优化为指针数组
	int		m_nOutbufLen;
    
	// 环形缓冲区
	char	m_bufInput[INBUFSIZE];
	int		m_nInbufLen;
	int		m_nInbufStart;				// INBUF使用循环式队列，该变量为队列起点，0 - (SIZE-1)
};

/**
 * DEMO
 
 // 发送消息
 bSucSend = m_pSocket->SendMsg(buf, nLen);
 
 // 接收消息处理（放到游戏主循环中，每帧处理）
 if (!m_pSocket) {
 return;
 }
 
 if (!m_pSocket->Check()) {
 m_pSocket = NULL;
 // 掉线了
 onConnectionAbort();
 return;
 }
 
 // 发送数据（向服务器发送消息）
 m_pSocket->Flush();
 
 // 接收数据（取得缓冲区中的所有消息，直到缓冲区为空）
 while (true)
 {
 char buffer[_MAX_MSGSIZE] = { 0 };
 int nSize = sizeof(buffer);
 char* pbufMsg = buffer;
 if(m_pSocket == NULL)
 {
 break;
 }
 if (!m_pSocket->ReceiveMsg(pbufMsg, nSize)) {
 break;
 }
 
 while (true)
 {
 MsgHead* pReceiveMsg = (MsgHead*)(pbufMsg);
 uint16	dwCurMsgSize = pReceiveMsg->usSize;
 //			CCLOG("msgsize: %d", dwCurMsgSize);
 
 if((int)dwCurMsgSize > nSize || dwCurMsgSize <= 0) {	// broken msg
 break;
 }
 
 CMessageSubject::instance().OnMessage((const char*)pReceiveMsg, pReceiveMsg->usSize);
 
 pbufMsg	+= dwCurMsgSize;
 nSize	-= dwCurMsgSize;
 if(nSize <= 0) {
 break;
 }
 }
 }
 */

/**
 * some chinese tips:
 * 	这样的一个Socket封装，适用于windows mac ios android等平台，
 * 	Socket处理是异步非阻塞的，所以可以放心的放到主线程处理消息，
 *	最大支持64k的接收消息缓冲（一般一个消息不可能大于3k）。
 *
 * 1. 	非阻塞模型，这样我才放心把消息处理放到主线程，多线程处理消息
 * 	其实很浪费。不知道得多大型的mmo才会用到。
 *
 * 2.	消息接收缓存处理，避免大消息被截掉。
 *
 * 3. 	没了，剩下的一些特殊处理应该是上层逻辑来考虑的。比如掉线重连等。
 *
 * 4.	游戏接收消息时是异步的，会阻塞的其实就是最开始连接服务器的一次
 * 	轮询操作(select)。我个人认为，不需要特殊处理，因为如果连接服务器
 *	还需要几秒钟的话，那么这个网络游戏没没法玩了。正常情况来说这个
 *	阻塞只会有几百毫秒。
 */

#endif /* defined(__MyCocosDemo__GameSocket__) */
