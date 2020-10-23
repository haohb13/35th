 ///
 /// @file    Subject.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-15 16:25:53
 ///
 
#include "Subject.hpp" //实现文件中第一个头文件一定要是自己的头文件
#include "Observer.hpp"


#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;


void Subject::attach(Observer * ob)
{
	if(ob == nullptr)
		return;

	auto iter = std::find(_obList.begin(), _obList.end(), ob);
	if(iter == _obList.end()) {
		_obList.push_back(ob);
	}
}

void Subject::detach(Observer * ob)
{
	if(ob == nullptr)
		return;

	auto iter = std::find(_obList.begin(), _obList.end(), ob);
	if(iter != _obList.end()) {
		_obList.erase(iter);
	}
}

void Subject::notify()
{
	for(auto & ob : _obList) {
		ob->update();
	}
}

void Subject::setStatus(Status status)
{
	_status = status;
}

void Ring::setStatus(Status status)
{
	//_status = status;
	cout << ">> Ring is alarming!" << endl;
	notify();
}

Guest::Guest(const string & name)
: _name(name)
{}

void Guest::knockAt(Ring & ring)
{
	cout << "Guest " << _name << " is starting to knock at the door!" << endl;
	ring.setStatus(1);
}
