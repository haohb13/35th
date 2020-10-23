 ///
 /// @file    EventfdThread.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-22 15:03:46
 ///
 
#ifndef __WD_EVENTFDTHREAD_HPP__ 
#define __WD_EVENTFDTHREAD_HPP__ 

#include "Eventfd.hpp"
#include "Thread.hpp"

namespace wd
{

class EventfdThread
{
public:
	EventfdThread(EventCallback && cb)
	: _event(std::move(cb))
	, _thread(std::bind(&Eventfd::start, &_event))
	{}

	void start()
	{
		_thread.start();
	}

	void stop()
	{
		_event.stop();
		_thread.join();
	}

	void wakeup()
	{
		_event.wakeup();
	}

private:
	Eventfd _event;
	Thread _thread;
};

}//end of namespace wd


#endif
