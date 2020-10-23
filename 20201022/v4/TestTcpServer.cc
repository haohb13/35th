 ///
 /// @file    TestEventLoop.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-20 17:30:55
 ///
 
#include "TcpServer.h"
#include "Threadpool.hpp"

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

wd::Threadpool * gThreadpool = nullptr;

class Task
{
public:
	Task(const string & msg, const wd::TcpConnectionPtr & conn)
	: _msg(msg)
	, _conn(conn)
	{}

	//由一个线程池中的子线程进行的
	void process()
	{
		//业务逻辑的处理，交给线程池进行
		//
		//(关键字推荐)
		//  hello -->  hello/ helloworld
		//decode
		//compute    // threadName --> 缓存  
		//encode
		//
	
		string response;
		//当拿到了返回结果时，不能直接在这里发送，因为此时还在计算线程；
		//这不是计算线程的职责； 按照我们的设计，数据的发送是IO线程来进行的
		//所以在这里要通知IO线程进行发送
		//_conn->send(response);  //要将该语句看成是一个回调函数，注册给IO线程
		cout << "threadpool's sub thread " << wd::current_thread::name << endl; 
		_conn->sendInLoop(_msg);
	}

private:
	string _msg;
	wd::TcpConnectionPtr _conn;
};

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
	//conn->send(msg);
	
	//得到了要交给客户端的结果, 此时如果业务的处理时间较长，就不适合在IO线程
	//直接处理； 
	//
	//应该将收到的数据封装成一个任务，交给线程池进行处理
	Task task(msg, conn);
	gThreadpool->addTask(std::bind(&Task::process, task));
}

void onClose(const wd::TcpConnectionPtr & conn)
{
	cout << "> " << conn->toString() << " has closed!" << endl;
}


class EchoServer
{
public:
	EchoServer(const string & ip, unsigned short port)
	: _threadpool(4, 10)
	, _tcpserver(ip, port)
	{}

	void start();

	void onConnection(const wd::TcpConnectionPtr & conn);
	void onMessage(const wd::TcpConnectionPtr & conn);
	void onClose(const wd::TcpConnectionPtr & conn);

private:
	wd::Threadpool _threadpool;
	wd::TcpServer _tcpserver;
};
 
int main(void)
{
	wd::Threadpool threadpool(4, 10);
	threadpool.start();
	gThreadpool = &threadpool;

	wd::TcpServer server("192.168.30.128", 9999);

	server.setConnectionCallback(onConection);
	server.setMessageCallback(onMessage);
	server.setCloseCallback(onClose);
	server.start();
	
	return 0;
}
