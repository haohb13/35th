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

class Task;
using ElemType = Task*;

class TaskQueue
{
public:
	TaskQueue(size_t queSize);

	bool empty() const;
	bool full() const;
	void push(const ElemType & elem);
	ElemType pop();

	void wakeup();

private:
	size_t _queSize;
	queue<ElemType> _que;
	MutexLock _mutex;
	Condition _notEmpty;
	Condition _notFull;
	bool _flag;
};

}//end of namespace wd


#endif
