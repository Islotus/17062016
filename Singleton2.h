 ///
 /// @file    Singleton2.h
 /// @author  Islotus(2791201278@qq.com)
 /// @date    2016-06-17 06:29:13
 ///

//单例模式：自动释放内存
//方法：pthread_once + atexit  
//缺点：平台相关，只能在linux上使用
//
//注意：编译时要加上-lpthread，才可以

#ifndef __Singleton2_h__
#define __Singleton2_h__

#include <iostream>
#include <pthread.h>
//using std::cin;
//using std::cout;
//using std::endl;

class Singleton
{
public:
	static Singleton* getInstance();
	static void init();
	static void destroy();
private:
	Singleton();
	~Singleton();
private:
	static Singleton* _pInstance;
	static pthread_once_t _once;
};
#endif
 
