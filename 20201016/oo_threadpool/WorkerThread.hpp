 ///
 /// @file    WorkerThread.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 17:50:29
 ///
 
#ifndef __WD_WORKERTHREAD_HPP__
#define  __WD_WORKERTHREAD_HPP__

#include "Thread.hpp"

namespace wd
{

class Threadpool;
class WorkerThread
: public Thread
{
public:
	WorkerThread(Threadpool & threadpool);
	~WorkerThread();

private:
	void run();

private:
	Threadpool & _threadpool;
};

}//end of namespace wd

#endif
