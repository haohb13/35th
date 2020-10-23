 ///
 /// @file    Producer.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 14:46:09
 ///


#ifndef __WD_PRODUCER_HPP__
#define __WD_PRODUCER_HPP__

#include "Thread.hpp"
#include "TaskQueue.hpp"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
class Producer
:public Thread
{
public:
	Producer(TaskQueue & taskQueue)
	: _taskQueue(taskQueue)
	{}

private:
	void run()
	{
		::srand(::time(nullptr));
		int cnt = 20;
		while(cnt-- > 0) {
			int number = ::rand() % 100;
			_taskQueue.push(number);
			cout << "producer thread " << pthread_self()
				 << " : produce a number " << number << endl;
			::sleep(1);
		}
	}

private:
	TaskQueue & _taskQueue;
};

}//end of namespace wd

#endif
