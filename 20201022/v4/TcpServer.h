 ///
 /// @file    TcpServer.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-20 17:50:22
 ///
 
#ifndef __WD_TCPSERVER_H__
#define __WD_TCPSERVER_H__

#include "Acceptor.h"
#include "EventLoop.h"
#include "TcpConnection.h"

namespace wd
{

class TcpServer
{
public:
	TcpServer(const string & ip, unsigned short port);
	void start();
	void stop();

	void setConnectionCallback(TcpConnectionCallback && cb);
	void setMessageCallback(TcpConnectionCallback && cb);
	void setCloseCallback(TcpConnectionCallback && cb);

private:
	Acceptor _acceptor;
	EventLoop _loop;
};

}//end of namespace wd

#endif
