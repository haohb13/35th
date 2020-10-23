 ///
 /// @file    Thread.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 10:10:07
 ///
 
#ifndef __WD_THREAD_HPP__
#define  __WD_THREAD_HPP__

#include "Noncopyable.hpp"

#include <pthread.h>


namespace wd
{

class Thread
: Noncopyable
{
public:
	Thread();
	virtual ~Thread();

	void start();
	void join();

private:
	virtual void run()=0;//实现任务

	static void * threadFunc(void * arg);

private:
	pthread_t _pthid;
	bool _isRunning;
};

}//end of namespace wd



#endif
