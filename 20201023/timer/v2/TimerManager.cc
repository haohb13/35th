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
#include <algorithm>
#include <iostream>

namespace wd
{

TimerManager::TimerManager()
: _fd(createTimerfd())
, _isStarted(false)
{}

void TimerManager::start()
{
	struct pollfd pfd;
	pfd.fd = _fd;
	pfd.events = POLLIN;

	//开启定时器
	setTimerfd(1, 1);//每一秒超时一次

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
			std::cout << "111" << std::endl;
			handleRead();
			handleTask();
		}
	}
}
	
void TimerManager::stop()
{
	setTimerfd(0, 0);
	if(_isStarted)
		_isStarted = false;
}

void TimerManager::addTask(TimerTask * timerTask)
{
	if(timerTask) {
		_taskList.push_back(timerTask);
	}
}

void TimerManager::removeTask(TimerTask * timerTask)
{
	if(timerTask) {
		auto iter = std::find(_taskList.begin(), _taskList.end(), timerTask);
		if(iter != _taskList.end()) {
			_taskList.erase(iter);
		}
	}
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
	int ret = ::read(_fd, &howmany, sizeof(howmany));
	if(ret != sizeof(howmany)) {
		perror("read");
	}
}

void TimerManager::handleTask()
{
	
	for(TimerTask * ptask : _taskList) {
		ptask->decreaseCount();	
		if(ptask->getCount() <= 0) {
			ptask->process();		
			ptask->initCount();		
		}
	}

	//...删除任务

	//...添加新的任务
}

}//end of namespace wd
