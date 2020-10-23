 ///
 /// @file    Threadpool.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 17:42:05
 ///
 
#ifndef __WD_THREADPOOL_HPP__
#define __WD_THREADPOOL_HPP__

#include "TaskQueue.hpp"
#include "Task.hpp"

#include "Thread.hpp"

#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;

namespace wd
{

class Thread;

class Threadpool
{
	friend class WorkerThread;
public:
	Threadpool(size_t threadNum, size_t queSize);
	~Threadpool();

	void start();
	void stop();
	void addTask(Task && task);
private:
	Task getTask();
	void threadFunc();//要交给农民工兄弟做的事儿

private:
	size_t _threadNum;
	size_t _queSize;
	vector<unique_ptr<Thread>> _threads;
	TaskQueue _taskQueue;
	bool _isExit;
};

}//end of namespace wd
#endif
