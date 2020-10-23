 ///
 /// @file    Consumer.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 14:51:29
 ///
 
#ifndef __WD_CONSUMER_HPP__
#define __WD_CONSUMER_HPP__ 
#include "TaskQueue.hpp"

#include <unistd.h>

#include <iostream>

using std::cout;
using std::endl;

namespace wd
{
class Consumer
{
public:
	void consume(TaskQueue & taskQueue)
	{
		int cnt = 20;
		while(cnt-- > 0) {
			int number = taskQueue.pop();
			cout << ">> consumer thread " << pthread_self()
			     << " : consume a number " << number << endl;
			::sleep(2);
		}
	}
};

}//end of namespace wd

#endif
