 ///
 /// @file    Singleton.cc
 /// @author  Islotus(2791201278@qq.com)
 /// @date    2016-06-17 04:24:32
 ///
 
#include "Singleton1.h"

//Singleton* Singleton:: _pInstance = NULL;  //静态变量指针初始化//非线程安全的
Singleton* Singleton::_pInstance = getInstance();  
	//线程安全的.执行这条语句时，就已经申请好空间了，并给指针_pInstance赋初值了，故内存中所有线程只能共用一个内存空间
Singleton::AutoRelease Singleton::_autoRelease;  //创建子类AutoRelease的对象

Singleton::Singleton()  //构造函数
{
	cout << "Singleton()" << endl;
}

Singleton::~Singleton()  //析构函数
{
	cout << "~Singleton()" << endl;
}

Singleton* Singleton::getInstance()  //类Singleton 初始化函数
{
	if(_pInstance == NULL)
	{
		_pInstance = new Singleton;  //在类里面进行调用
	}
	return _pInstance;
}

void Singleton::destroy()  //类Singleton 销毁函数
{
	if(_pInstance != NULL)
	{
		delete _pInstance;
	}
}


int main()
{
//	Singleton* p1 = new Singleton;  //在类外进行调用
	Singleton* p1 = Singleton::getInstance();
	Singleton* p2 = Singleton::getInstance();
	printf("p1 = %p\n",p1);
	printf("p2 = %p\n",p2);

	return 0;
}


