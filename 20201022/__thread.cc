 ///
 /// @file    __thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-22 09:57:02
 ///
 
#include <errno.h>
#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;

int gNumber = 1;
//__thread变量的位置是 全局位置
__thread int tNumber = 10;


void * func1(void * arg)
{
	cout << pthread_self() << " gNumber: " << gNumber << endl;
	cout << pthread_self() << " &gNumber:" << &gNumber << endl;

	tNumber = 100;
	cout << pthread_self() << " tNumber: " << tNumber << endl;
	cout << pthread_self() << " &tNumber:" << &tNumber << endl;

	cout << pthread_self() << " &errno: " << &errno << endl;

	return nullptr;
}

void * func2(void * arg)
{
	cout << pthread_self() << " gNumber: " << gNumber << endl;
	cout << pthread_self() << " &gNumber:" << &gNumber << endl;

	tNumber = 1000;
	cout << pthread_self() << " tNumber: " << tNumber << endl;
	cout << pthread_self() << " &tNumber:" << &tNumber << endl;
	//errno也是一个 __thread变量
	cout << pthread_self() << " &errno: " << &errno << endl;

	return nullptr;
}
 
int main(void)
{
	pthread_t pthid1, pthid2;
	cout << pthread_self() << " gNumber: " << gNumber << endl;
	cout << pthread_self() << " &gNumber:" << &gNumber << endl;

	cout << pthread_self() << " tNumber: " << tNumber << endl;
	cout << pthread_self() << " &tNumber:" << &tNumber << endl;
	cout << pthread_self() << " &errno: " << &errno << endl;

	pthread_create(&pthid1, nullptr, func1, nullptr);
	pthread_create(&pthid2, nullptr, func2, nullptr);

	pthread_join(pthid1, nullptr);
	pthread_join(pthid2, nullptr);

	return 0;
}
 
