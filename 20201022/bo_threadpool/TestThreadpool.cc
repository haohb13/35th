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
{
public:
	void process()
	{
		::srand(::clock());
		int number = ::rand() % 100;
		//cout << "worker thread " << pthread_self()
		cout << "worker thread " << wd::current_thread::name  
			 << ": number " << number << endl;
		//sleep(2);
	}
};


void test0()
{
	cout << "main thread: " <<  pthread_self() << endl;


	wd::Threadpool threadpool(4, 10);
	threadpool.start();
	int cnt = 20;
	while(cnt-- > 0) {
		threadpool.addTask(std::bind(&Mytask::process, Mytask()));
		cout << ">> cnt = " << cnt << endl;
	}

	threadpool.stop();
}

 
int main(void)
{
	test0();
	return 0;
}
