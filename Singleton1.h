 ///
 /// @file    Singleton1.h
 /// @author  Islotus(2791201278@qq.com)
 /// @date    2016-06-17 19:15:31
 ///

//单例模式，自动释放内存
//实现方法：嵌套类 + 静态变量
//优点：可以跨平台使用
//原理：在Singleton类中创建一个子类AutoRelease，并在Singleton类中创建一个类AutoRelease的静态成员变量
//在函数执行结束时，静态成员变量的生命周期结束，即要销毁静态成员变量对象，此时会调用静态成员变量对象
//的析构函数。在这个对象的析构函数中，就可以加入回收内存空间的语句。
#ifndef __Singleton1_h__
#define __Singleton1_h__

#include <iostream>
#include <stdio.h>
using std::cin;
using std::cout;
using std::endl;

class Singleton
{
private:
	class AutoRelease
	{
	public:
		AutoRelease()
		{
			cout << "AutoRelease()" << endl;
		}
		~AutoRelease()
		{
			cout << "~AutoRelease()" << endl;
			if(_pInstance != NULL)
				delete _pInstance;
		}
	};
public:
	static Singleton* getInstance();
	void destroy();
private:
	Singleton();  //
	~Singleton();  //构造函数和析构函数都放在private区，是为了让一个类只能创建一个对象。
private:
	static Singleton* _pInstance;
	static AutoRelease _autoRelease;
};


#endif
 
