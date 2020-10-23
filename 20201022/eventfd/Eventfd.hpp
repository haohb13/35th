 ///
 /// @file    Eventfd.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-22 14:33:49
 ///
 
#ifndef __WD_EVENTFD_HPP__
#define __WD_EVENTFD_HPP__

#include <functional>

namespace wd
{

using EventCallback = std::function<void()>;

class Eventfd
{
public:
	Eventfd(EventCallback && cb);

	void start();
	void stop();

	void wakeup();
private:
	void handleRead();

	int createEventfd();

private:
	int _eventfd;
	EventCallback _cb;
	bool _isStarted;
};

}//end of namespace wd

#endif
