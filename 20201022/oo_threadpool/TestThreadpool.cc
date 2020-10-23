 ///
 /// @file    TestThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 10:55:57
 ///
 
#include "Threadpool.hpp"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

class Mytask
: public wd::Task
{
public:
	void process()
	{
		::srand(::time(nullptr));
		int number = ::rand() % 100;
		cout << "worker thread " << pthread_self()
			 << ": number " << number << endl;
		sleep(1);
	}
};


void test0()
{
	cout << "main thread: " <<  pthread_self() << endl;

	wd::Threadpool threadpool(6, 10);
	threadpool.start();
	unique_ptr<wd::Task> ptask(new Mytask());
	int cnt = 20;
	while(cnt-- > 0) {
		threadpool.addTask(ptask.get());
		cout << ">> cnt = " << cnt << endl;
	}

	threadpool.stop();
}

 
int main(void)
{
	test0();
	return 0;
}
