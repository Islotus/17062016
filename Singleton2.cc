 ///
 /// @file    Singleton2.cc
 /// @author  Islotus(2791201278@qq.com)
 /// @date    2016-06-17 06:34:21
 ///
#include "Singleton2.h"
#include <stdio.h>
#include <stdlib.h>

using std::cin;
using std::cout;
using std::endl;

Singleton* Singleton::_pInstance = NULL;
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

//线程安全
Singleton* Singleton::getInstance()
{
	pthread_once(&_once, &Singleton::init);
	return _pInstance;
}

void Singleton::init()
{
	::atexit(&Singleton::destroy);
	if(_pInstance == NULL)
	{
		_pInstance = new Singleton;  //在类里面进行调用
	}
}

void Singleton::destroy()
{
	if(_pInstance != NULL)
		delete _pInstance;
}

Singleton::Singleton()
{
	cout << "Singleton()" << endl;
}

Singleton::~Singleton()
{
	cout << "~Singleton()" << endl;
}

int main()
{
	Singleton* p1 = Singleton::getInstance();
	Singleton* p2 = Singleton::getInstance();

	printf("p1 = %p\n",p1);
	printf("p2 = %p\n",p2);

	return 0;
}



