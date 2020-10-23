 ///
 /// @file    MutexLock.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 09:46:21
 ///
 
#ifndef __WD_MUTEXLOCK_HPP__
#define __WD_MUTEXLOCK_HPP__
#include "Noncopyable.hpp"

#include <pthread.h>

namespace wd
{

class MutexLock
: Noncopyable
{
public:
	MutexLock();
	~MutexLock();

	void lock();
	void unlock();

	pthread_mutex_t * getMutexLockPtr() {	return &_mutex;	}

private:
	pthread_mutex_t _mutex;
};

}

#endif
