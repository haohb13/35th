 ///
 /// @file    EventLoop.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-20 15:59:01
 ///
 

#ifndef __WD_EVENTLOOP_H__
#define __WD_EVENTLOOP_H__

#include <sys/epoll.h>

#include <vector>
#include <map>
#include <memory>
#include <functional>

namespace wd
{

class TcpConnection;
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(const TcpConnectionPtr &)>;

class Acceptor;
class EventLoop
{
public:
	EventLoop(Acceptor &);

	void loop();
	void unloop();

	void setConnectionCallback(TcpConnectionCallback && cb) {	_onConnection = std::move(cb);}
	void setMessageCallback(TcpConnectionCallback && cb) {	_onMessage = std::move(cb);	}
	void setCloseCallback(TcpConnectionCallback && cb) {	_onClose = std::move(cb);	}

private:
	int createEpollfd();
	void addEpollReadFd(int fd);
	void delEpollReadFd(int fd);

	void waitEpollfd();
	void handleNewConnection();
	void handleMessage(int fd);
	bool isConnectionClose(int fd);
private:
	int _efd;
	Acceptor & _acceptor;
	std::vector<struct epoll_event> _evtList;
	std::map<int, TcpConnectionPtr> _conns;

	bool _isLooping;

	TcpConnectionCallback _onConnection;
	TcpConnectionCallback _onMessage;
	TcpConnectionCallback _onClose;
};

}//end of namespace wd


#endif
