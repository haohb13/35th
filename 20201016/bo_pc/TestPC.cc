 ///
 /// @file    TestThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 10:55:57
 ///
 
#include "Thread.hpp"
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
	unique_ptr<wd::Producer> p(new wd::Producer());
	unique_ptr<wd::Consumer> c(new wd::Consumer());

	unique_ptr<wd::Thread> pProducer(new wd::Thread(
		std::bind(&wd::Producer::produce, p.get(), std::ref(que))));

	unique_ptr<wd::Thread> pConsumer(new wd::Thread(
		//std::bind绑定参数时，默认采用的是值传递；
		//如果希望传递引用，需要使用引用的包装器std::ref
		std::bind(&wd::Consumer::consume, c.get(), std::ref(que))));
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
