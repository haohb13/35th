 ///
 /// @file    TimerManager.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-23 09:51:33
 ///
 
#ifndef __WD_TIMERMANAGER_HPP__
#define __WD_TIMERMANAGER_HPP__

#include "TimerTask.hpp"
#include "MutexLock.hpp"

#include <list>

namespace wd
{

class TimerManager
{
public:
	TimerManager();

	void start();
	void stop();

	void addTask(TimerTask * timerTask);
	void removeTask(TimerTask * timerTask);

private:
	int createTimerfd();
	void setTimerfd(int initialTime, int periodicTime);
	void handleRead();
	void handleTask();

private:
	int _fd;
	bool _isStarted;
	std::list<TimerTask *> _taskList;

	MutexLock _mutex1;
	std::list<TimerTask *> _pendingTaskList;

	MutexLock _mutex2;
	std::list<TimerTask *> _pendingRemoveList;
};

}//end of namespace wd

#endif
