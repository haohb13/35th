 ///
 /// @file    Subject.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-15 16:12:46
 ///
 
#ifndef __SUBJECT_HPP__
#define __SUBJECT_HPP__
//#include "Observer.hpp"

#include <list>
#include <string>

using std::string;

using Status = int;

class Observer;//类的前向声明

class Subject
{
public:
	void attach(Observer*);
	void detach(Observer*);
	void notify();

	virtual void setStatus(Status status);
	Status getStatus() const {	return _status;}

	virtual ~Subject() {}

protected:
	std::list<Observer *> _obList;//对观察者进行分类
	std::list<Observer *> _vipList;
	std::list<Observer *> _superVipList;
	Status _status;
};

class Ring : public Subject
{
public:
	void setStatus(Status status);

};

class Guest
{
public:
	Guest(const string & name);

	void knockAt(Ring & ring);

private:
	string _name;
};


#endif
