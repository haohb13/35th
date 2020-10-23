 ///
 /// @file    TaskQueue.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 14:32:06
 ///
 
#ifndef __WD_TASKQUEUE_HPP__
#define __WD_TASKQUEUE_HPP__

#include "MutexLock.hpp"
#include "Condition.hpp"
#include <queue>

using std::queue;

namespace wd
{



class TaskQueue
{
public:
	TaskQueue(size_t queSize);

	bool empty() const;
	bool full() const;
	void push(int);
	int pop();

private:
	size_t _queSize;
	queue<int> _que;
	MutexLock _mutex;
	Condition _notEmpty;
	Condition _notFull;

};

}//end of namespace wd


#endif
