 ///
 /// @file    singleton2.cc
 /// @author  Islotus(2791201278@qq.com)
 /// @date    2016-06-17 07:06:34
 ///

//单例模式：pthread_once + atexit实现
//练习

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class singleton
{
public:
	static singleton* getInstance();
	static void init();
	static void destroy();
private:
	singleton();
	~singleton();
private:
	static singleton* _pInstance;
	static pthread_once_t _once;
};

singleton* singleton::_pInstance = NULL;
pthread_once_t singleton::_once = PTHREAD_ONCE_INIT;

singleton* singleton::getInstance()
{
	pthread_once(&_once, &singleton::init);
	return _pInstance;
}

void singleton::init()
{
	::atexit(&singleton::destroy);
	if(_pInstance == NULL)
		_pInstance = new singleton;  //在类里面进行调用
}

void singleton::destroy()
{
	if(_pInstance != NULL)
		delete _pInstance;
}

singleton::singleton()
{
	cout << "singleton()" << endl;
}

singleton::~singleton()
{
	cout << "~singleton()" << endl;
}

int main()
{
	singleton* p1 = singleton::getInstance();
	singleton* p2 = singleton::getInstance();

	printf("p1 = %p\n",p1);
	printf("p2 = %p\n",p2);

	return 0;
}


