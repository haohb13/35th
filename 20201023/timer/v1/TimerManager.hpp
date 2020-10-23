 ///
 /// @file    TimerManager.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-23 09:51:33
 ///
 
#ifndef __WD_TIMERMANAGER_HPP__
#define __WD_TIMERMANAGER_HPP__

#include "TimerTask.hpp"

namespace wd
{

class TimerManager
{
public:
	TimerManager(TimerTask * timerTask);

	void start();
	void stop();

private:
	int createTimerfd();
	void setTimerfd(int initialTime, int periodicTime);
	void handleRead();

private:
	int _fd;
	bool _isStarted;
	TimerTask * _task;
};

}//end of namespace wd

#endif
