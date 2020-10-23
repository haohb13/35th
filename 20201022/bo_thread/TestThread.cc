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

//static map<pthread_t, string> 
//一个任务
void run()
{
	::srand(::time(nullptr));
	int cnt = 20;

	/* 需求: 获取当前子线程的名字 */
	//1. 方案一： 只能获取线程对象的指针或者引用，
	//然后再去调用getThreadName() 方法，才能获取到  [不行]
	
	//2. 方案二： 定义一个静态的 map<pthread_t, string>;
	//
	//3. 方案三： 线程局部存储(Thread Local Storage)
	cout << "sub thread name: " << wd::current_thread::name << endl;

	while(cnt-- > 0) {
		int number = ::rand() % 100;
		cout << "threadid " << pthread_self() 
			 << ": number = " << number << endl;

		::sleep(1);
	}
}

class Task
{
public:
	void process()
	{
		cout << "Task::process()" << endl;
		run();
	}

	void execute(int x, int y)
	{
		cout << "Task::execute(int,int)" << x << "," << y << endl;
	}
};

void test00()
{
	//函数类型   R(Args...)
	std::function<void()> f = run;
	//f();

	unique_ptr<Task> ptask(new Task());
	auto f2 = std::bind(&Task::process, ptask.get());
	f2();
}

void test0()
{
	
	cout << "main thread: " <<  pthread_self() << endl;
	//unique_ptr<wd::Thread> mythread(new wd::Thread(run));
	
	unique_ptr<Task> ptask(new Task());

	//基于对象的写法会更灵活
	unique_ptr<wd::Thread> mythread(new wd::Thread(
		std::bind(&Task::process, ptask.get()), "Test thread"));
		//std::bind(&Task::execute, ptask.get(), 1, 2)));
		//
		//提前绑定参数时， bind采用的是值传递, 会对Task() 临时对象进行复制
		//std::bind(&Task::execute, Task(), 1, 2)));

	mythread->start();

	cout << "sub thread id :" << mythread->getThreadId() << endl;
	cout << "sub thread name: " << mythread->getThreadName() << endl;
	mythread->join();
}
 
int main(void)
{
	//test00();
	test0();
	return 0;
}
