 ///
 /// @file    Eventfd.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-22 14:36:32
 ///
 

#include "Eventfd.hpp"

#include <unistd.h>
#include <sys/eventfd.h>
#include <poll.h>


namespace wd
{

Eventfd::Eventfd(EventCallback && cb)
: _eventfd(createEventfd())
, _cb(std::move(cb))
, _isStarted(false)
{
}

void Eventfd::start()
{
	struct pollfd pfd;
	pfd.fd = _eventfd;
	pfd.events = POLLIN;

	_isStarted = true;
	while(_isStarted) {
		int nready = ::poll(&pfd, 1, 5000);
		if(nready == -1 && errno == EINTR) {
			continue;
		} else if(nready == -1) {
			perror("poll");
			return;
		} else if(nready == 0) {
			printf("poll timeout!\n");
		} else {
			if(pfd.revents & POLLIN) {
				handleRead();//水平触发:只要不处理，poll会一直返回，一直通知
				if(_cb) 
					_cb();
			}
		}
	}
}

void Eventfd::stop()
{
	if(_isStarted) 
		_isStarted = false;
}

void Eventfd::wakeup()
{
	uint64_t one = 1;
	int ret = ::write(_eventfd, &one, sizeof(one));
	if(ret != sizeof(one)) {
		perror("write");
	}
}

int Eventfd::createEventfd()
{
	int ret = ::eventfd(0, 0);
	if(ret < 0) {
		perror("eventfd");
	}
	return ret;
}

void Eventfd::handleRead()
{
	uint64_t howmany = 0;
	int ret = ::read(_eventfd, &howmany, sizeof(howmany));
	if(ret != sizeof(howmany)) {
		perror("read");
	}
}

}//end of namespace wd
