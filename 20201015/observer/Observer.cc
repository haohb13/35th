 ///
 /// @file    Observer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-15 16:40:30
 ///
 
#include "Observer.hpp"

#include <stdlib.h>
#include <time.h>

#include <iostream>
using std::cout;
using std::endl;

Observer::Observer(const string & name)
: _name(name)
{}

Baby::Baby(const string & name)
: Observer(name)
{}


Baby::~Baby(){	cout << "~Baby()" << endl;	}

void Baby::update()
{
	//Status tmp = _subject->getStatus();//主动获取主题的信息
	::srand(::clock());
	int random = ::rand() % 100;

	if(random < 30) {
		cout << "Baby " << _name << " is starting to cry loudly!" << endl;
	} else {
		cout << "Baby " << _name << " is sleeping sweetly!" << endl;
	}
}

Nurse::Nurse(const string & name)
: Observer(name)
{}


Nurse::~Nurse(){	cout << "~Nurse()" << endl;	}

void Nurse::update()
{
	::srand(::time(nullptr));
	int random = ::rand() % 100;

	if(random < 70) {
		cout << "Nurse " << _name << " is starting to open the door!" << endl; 
	} else {
		cout << "Nurse " << _name << " is sleeping sweetly!" << endl;
	}
}
