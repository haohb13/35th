 ///
 /// @file    Thread.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 10:10:07
 ///
 
#ifndef __WD_THREAD_HPP__
#define  __WD_THREAD_HPP__

#include "Noncopyable.hpp"

#include <pthread.h>

#include <functional>


namespace wd
{

class Thread
: Noncopyable
{
public:
	using ThreadCallback = std::function<void()>;

	Thread(ThreadCallback && cb);
	~Thread();

	void start();
	void join();

private:
	static void * threadFunc(void * arg);

private:
	pthread_t _pthid;
	bool _isRunning;
	ThreadCallback _cb;//回调函数
};

}//end of namespace wd



#endif
