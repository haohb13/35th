 ///
 /// @file    TestObserver.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-15 16:13:47
 ///

#include "Subject.hpp"
#include "Observer.hpp"

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

void test0()
{
	unique_ptr<Observer> baby1(new Baby("biao zi"));
	unique_ptr<Observer> baby2(new Baby("xiao wang"));
	unique_ptr<Observer> nurse1(new Nurse("liu yi fei"));
	unique_ptr<Observer> nurse2(new Nurse("cui hua"));

	unique_ptr<Guest> guest(new Guest("zhao si"));
	Ring ring;
	ring.attach(baby1.get());
	ring.attach(baby2.get());
	ring.attach(nurse1.get());
	ring.attach(nurse2.get());

	guest->knockAt(ring);
	ring.detach(nurse2.get());
	cout << endl;

	guest->knockAt(ring);

}
 
int main(void)
{
	test0();
	return 0;
}
