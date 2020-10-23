 ///
 /// @file    TestEventLoop.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-20 17:30:55
 ///
 
#include "Acceptor.h"
#include "EventLoop.h"
#include "TcpConnection.h"

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

void onConection(const wd::TcpConnectionPtr & conn)
{
	cout << ">> " << conn->toString() << " has connected!" << endl;
	conn->send("welcome to server!");
}

void onMessage(const wd::TcpConnectionPtr & conn)
{
	string msg = conn->receive();
	cout << ">>> receive:" << msg << endl;
	//回显操作
	conn->send(msg);
}

void onClose(const wd::TcpConnectionPtr & conn)
{
	cout << "> " << conn->toString() << " has closed!" << endl;
}
 
int main(void)
{
	wd::Acceptor acceptor("192.168.30.128", 9999);
	acceptor.ready();

	wd::EventLoop loop(acceptor);

	loop.setConnectionCallback(onConection);
	loop.setMessageCallback(onMessage);
	loop.setCloseCallback(onClose);

	loop.loop();
	
	return 0;
}
