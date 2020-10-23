 ///
 /// @file    TestThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 10:55:57
 ///
 
#include "Producer.hpp"
#include "Consumer.hpp"
#include "TaskQueue.hpp"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;


void test0()
{
	cout << "main thread: " <<  pthread_self() << endl;
	
	wd::TaskQueue que(10);

	unique_ptr<wd::Thread> pProducer(new wd::Producer(que));
	unique_ptr<wd::Thread> pConsumer(new wd::Consumer(que));
	pProducer->start();
	pConsumer->start();
	pProducer->join();
	pConsumer->join();
}

 
int main(void)
{
	test0();
	return 0;
}
