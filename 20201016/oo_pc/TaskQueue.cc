 ///
 /// @file    TaskQueue.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 14:36:51
 ///

#include "TaskQueue.hpp"

namespace wd
{

TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _que()
, _mutex()
, _notEmpty(_mutex)
, _notFull(_mutex)
{}

bool TaskQueue::empty() const
{
	return _que.size() == 0;
}

bool TaskQueue::full() const
{
	return _que.size() == _queSize;
}

//RAII  (Resouce Acquisition Is Initialization)
/* 该方法运行在生产者线程*/
void TaskQueue::push(int elem)
{
	//1. 对互斥锁进行保护，防止发生死锁
	MutexLockGuard autoLock(_mutex);
	//_mutex.lock();
	while(full()) {//使用while可以防止虚假唤醒的情况出现
		_notFull.wait();//虚假唤醒
	}

	//......return
	_que.push(elem);

	_notEmpty.notify();//一个notify唤醒了几个线程(有概率出现)
}

/* 该方法运行在消费者线程*/
int TaskQueue::pop()
{
	MutexLockGuard autoLock(_mutex);
	while(empty()) {
		_notEmpty.wait();
	}

	int number = _que.front();
	_que.pop();

	_notFull.notify();
	return number;
}

}//end of namespace wd
 
