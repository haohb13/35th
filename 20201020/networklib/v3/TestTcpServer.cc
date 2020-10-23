 ///
 /// @file    TestEventLoop.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-20 17:30:55
 ///
 
#include "TcpServer.h"

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


	//decode
	//compute
	//encode
}

void onClose(const wd::TcpConnectionPtr & conn)
{
	cout << "> " << conn->toString() << " has closed!" << endl;
}
 
int main(void)
{
	wd::TcpServer server("192.168.30.128", 9999);

	server.setConnectionCallback(onConection);
	server.setMessageCallback(onMessage);
	server.setCloseCallback(onClose);
	server.start();
	
	return 0;
}
