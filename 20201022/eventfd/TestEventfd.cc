 ///
 /// @file    TestEventfd.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-22 14:50:13
 ///
 
/* #include "Eventfd.hpp" */
/* #include "Thread.hpp" */
#include "EventfdThread.hpp"

#include <unistd.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
using std::cout;
using std::endl;

void getNumber()
{
	::srand(::time(nullptr));
	int number = ::rand() % 100;

	cout << " number : " << number << endl;
}

void test0()
{
	using namespace wd;
	Eventfd event(getNumber);
//	event.start();// 子线程运行start方法

	Thread thread(std::bind(&Eventfd::start, &event));
	thread.start();

	int count = 20;
	while(count-- > 0) {
		event.wakeup();//主线程通知子线程执行任务
		cout << "count " << count << endl;
		::sleep(1);
	}

	thread.join();
}

void test1()
{
	cout << "test1() ..." << endl;
	using namespace wd;
	EventfdThread event(getNumber);
	event.start();

	int count = 20;
	while(count-- > 0) {
		event.wakeup();//主线程通知子线程执行任务
		cout << "count " << count << endl;
		::sleep(1);
	}

	event.stop();
}
 
int main(void)
{
	/* test0(); */
	test1();
	return 0;
}
