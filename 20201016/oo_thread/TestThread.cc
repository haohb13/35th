 ///
 /// @file    TestThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 10:55:57
 ///
 
#include "Thread.hpp"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

class Mythread
: public wd::Thread
{
	void run()
	{
		::srand(::time(nullptr));
		int cnt = 20;
		while(cnt-- > 0) {
			int number = ::rand() % 100;
			cout << "threadid " << pthread_self() 
				 << ": number = " << number << endl;

			::sleep(1);
		}
	}
};

void test0()
{
	cout << "main thread: " <<  pthread_self() << endl;
	unique_ptr<wd::Thread> mythread(new Mythread());
	mythread->start();
	mythread->join();
}

void test1()
{
	Mythread thread1;

	//C++语言天生就是支持值语义
	//
	//值语义 --> 值传递 --> 可以进行复制 ==>函数(拷贝构造函数、赋值运算符函数)
	//对象语义 --> 不可以进行复制

	//但线程是属于系统资源，是不能进行复制的
	Mythread thread2 = thread1;//在语法形式上，线程可以复制

}
 
int main(void)
{
	test0();
	return 0;
}
