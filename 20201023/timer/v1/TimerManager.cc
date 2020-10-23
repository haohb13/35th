 ///
 /// @file    TimerManager.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-23 09:53:37
 ///
 
#include "TimerManager.hpp"

#include "TimerTask.hpp"

//#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/timerfd.h>
#include <poll.h>

#include <string>

namespace wd
{

TimerManager::TimerManager(TimerTask * timerTask)
: _fd(createTimerfd())
, _isStarted(false)
, _task(timerTask)

{}

void TimerManager::start()
{
	struct pollfd pfd;
	pfd.fd = _fd;
	pfd.events = POLLIN;

	//开启定时器
	setTimerfd(1, _task->getTimeInterval());

	_isStarted = true;
	while(_isStarted) {
		int nready = ::poll(&pfd, 1, 5000);
		if(nready == -1  &&  errno == EINTR)
			continue;
		else if(nready == -1) {
			perror("poll");
			return;
		} else if(nready == 0) {
			printf("poll timeout!\n");
		} else {
			handleRead();
			if(_task)
				_task->process();
		}
	}
}
	
void TimerManager::stop()
{
	setTimerfd(0, 0);
	if(_isStarted)
		_isStarted = false;
}

int TimerManager::createTimerfd()
{
	int fd = ::timerfd_create(CLOCK_REALTIME, 0);
	if(fd < 0) {
		perror("timerfd_create");
	}
	return fd;
}

void TimerManager::setTimerfd(int initialTime, int periodicTime)
{
	struct itimerspec value;
	value.it_value.tv_sec = initialTime;
	value.it_value.tv_nsec = 0;
	value.it_interval.tv_sec = periodicTime;
	value.it_interval.tv_nsec = 0;

	int ret = ::timerfd_settime(_fd, 0, &value, nullptr);
	if(ret < 0) {
		perror("timerfd_settime");
	}
}

void TimerManager::handleRead()
{
	uint64_t howmany = 0;
	//char buff[8] = {0};
	//int ret = ::read(_fd, buff, sizeof(buff));

	int ret = ::read(_fd, &howmany, sizeof(howmany));
	if(ret != sizeof(howmany)) {
		perror("read");
	}
}

}//end of namespace wd
