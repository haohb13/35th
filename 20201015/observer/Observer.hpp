 ///
 /// @file    Observer.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-15 16:16:08
 ///
 
#ifndef  __OBSERVER_HPP__
#define  __OBSERVER_HPP__

#include <string>
using std::string;

class Observer
{
public:
	Observer(const string & name);

	//观察者可以主动获取信息 --> 拉模式
	virtual void update()=0;

	//被动接受信息 --> 推模式
	virtual void update(string & message)=0;

	virtual ~Observer() {}
protected:
	string _name;
	//Subject * _subject;//保存的是主题的指针
};

class Baby : public Observer
{
public:
	Baby(const string & name);
	~Baby();

	void update();
};

class Nurse : public Observer
{
public:
	Nurse(const string & name);
	~Nurse();

	void update();

};



#endif
