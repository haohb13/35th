 ///
 /// @file    WorkerThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 17:52:20
 ///
 
#include "WorkerThread.hpp"
#include "Threadpool.hpp"
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

WorkerThread::WorkerThread(Threadpool & threadpool)
: _threadpool(threadpool)
{}

WorkerThread::~WorkerThread()
{
	cout << "~WorkerThread()" << endl;
}

void WorkerThread::run()
{
	_threadpool.threadFunc();
}

}//end of namespace wd
