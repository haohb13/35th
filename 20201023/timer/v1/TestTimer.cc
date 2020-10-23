 ///
 /// @file    TestTimer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-23 10:16:07
 ///
 
#include "TimerManager.hpp"

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

using namespace wd;

class MyTimerTask
: public TimerTask
{
public:
	MyTimerTask(int seconds)
	: TimerTask(seconds)
	{}

	void process()
	{
		::srand(::time(nullptr));
		int number = ::rand() % 100;
		cout << " >> number : " << number << endl;
	}
};

class PrintString
: public TimerTask
{
public:
	PrintString(int seconds)
	: TimerTask(seconds)
	{}

	void process()
	{
		cout << "hello,world" << endl;
	}
};

void test0()
{
	unique_ptr<TimerTask> timerTask(new MyTimerTask(3));
	TimerManager timer(timerTask.get());
	timer.start();
	timer.stop();
}
 
int main(void)
{
	test0();
	return 0;
}
