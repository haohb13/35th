 ///
 /// @file    EventLoop.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-20 16:00:54
 ///
 
#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"

#include <stdio.h>
#include <assert.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

EventLoop::EventLoop(Acceptor & acceptor)
: _efd(createEpollfd())
, _acceptor(acceptor)
, _evtList(1024)
, _isLooping(false)
{
	//_evtList.reserve(1024);//预先开辟空间，但没有元素
	addEpollReadFd(_acceptor.fd());
}

void EventLoop::loop()
{
	_isLooping = true;
	while(_isLooping) {
		waitEpollfd();
	}
}

void EventLoop::unloop()
{
	if(_isLooping) {
		_isLooping = false;
	}
}

void EventLoop::waitEpollfd()
{
	//int nready = ::epoll_wait(_efd, &_evtList[0], _evtList.size(), 5000);
	int nready = 0;
	do {
	nready = ::epoll_wait(_efd, &*_evtList.begin(), _evtList.size(), 5000);
	}while(nready == -1 && errno == EINTR);

	if(nready == -1) {
		perror("epoll_wait");
		return;
	} else if(nready == 0) {
		printf(">> epoll_wait timeout!\n");
	} else {
		//进行扩容操作
		if(nready == _evtList.size()) {
			_evtList.resize(2 * nready);
		}
		
		for(int idx = 0; idx != nready; ++idx) {
			int fd = _evtList[idx].data.fd;

			if(fd == _acceptor.fd()) {
				//新连接的处理
				if(_evtList[idx].events & EPOLLIN) {
					handleNewConnection();
				}
			} else {
				//针对于已经建立了连接的处理
				if(_evtList[idx].events & EPOLLIN) {
					cout << "111" << endl;
					handleMessage(fd);
					cout << "222" << endl;
				}
			}
		}
	}
}


int EventLoop::createEpollfd()
{
	int ret = ::epoll_create1(0);
	if(ret == -1) {
		perror("epoll_create1");
	}
	return ret;
}

void EventLoop::addEpollReadFd(int fd)
{
	struct epoll_event value;
	value.data.fd = fd;
	value.events = EPOLLIN;
	int ret = ::epoll_ctl(_efd, EPOLL_CTL_ADD, fd, &value);
	if(ret == -1) {
		perror("epoll_ctl");
	}
}

void EventLoop::delEpollReadFd(int fd)
{
	struct epoll_event value;
	value.data.fd = fd;
	int ret = ::epoll_ctl(_efd, EPOLL_CTL_DEL, fd, &value);
	if(ret == -1) {
		perror("epoll_ctl");
	}
}

void EventLoop::handleNewConnection()
{
	int peerfd = _acceptor.accept();

	addEpollReadFd(peerfd);

	TcpConnectionPtr conn(new TcpConnection(peerfd));
	conn->setConnectionCallback(_onConnection);
	conn->setMessageCallback(_onMessage);
	conn->setCloseCallback(_onClose);

	_conns.insert(std::make_pair(peerfd, conn));
	//... do something
	
	//连接建立时，执行回调函数
	conn->handleConnectionCallback();
}

void EventLoop::handleMessage(int fd)
{
	auto iter = _conns.find(fd);
	assert(iter != _conns.end());

	//判断该连接是否断开
	auto isClosed = iter->second->isConnectionClose();	
	if(isClosed) {
		//...do something
		delEpollReadFd(fd);
		iter->second->handleCloseCallback();
		_conns.erase(iter);
	} else {
		//... do something
		iter->second->handleMessageCallback();
	}
}


}//end of namespace wd
