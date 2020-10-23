 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 10:11:51
 ///
 

#include "Thread.hpp"
#include <stdio.h>


namespace wd
{

Thread::Thread()
: _pthid(0)
, _isRunning(false)
{
}

Thread::~Thread()
{
	if(_isRunning) {
		pthread_detach(_pthid);
	}
}



void Thread::start()
{
	if(pthread_create(&_pthid, nullptr, threadFunc, this)) {
		perror("pthread_create");
		return;
	}
	_isRunning = true;
}

void Thread::join()
{
	if(_isRunning) {
		pthread_join(_pthid, nullptr);
		_isRunning = false;
	}
}

void * Thread::threadFunc(void * arg)
{
	Thread * p = static_cast<Thread *>(arg);
	if(p) {
		p->run();
	}
	return nullptr;
}

}//end of namespace wd
