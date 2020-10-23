 ///
 /// @file    Condition.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 09:55:28
 ///
 

#ifndef __WD_CONDITION_HPP__
#define __WD_CONDITION_HPP__

#include "Noncopyable.hpp"

#include <pthread.h>

namespace wd
{

class MutexLock;

class Condition
: Noncopyable
{
public:
	Condition(MutexLock &);
	~Condition();

	void wait();
	void notify();
	void notifyAll();

private:
	pthread_cond_t _cond;
	MutexLock & _mutex;
};

}//end of namespace wd


#endif
