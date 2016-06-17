 ///
 /// @file    singleton.h
 /// @author  Islotus(2791201278@qq.com)
 /// @date    2016-06-17 05:50:18
 ///

//单例模式：
//自己重写一遍


#include <iostream>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class singleton
{
private:
	class autorelease  //子类
	{
	public:
		autorelease()
		{
			cout << "autorelease()" << endl;
		}
		~autorelease()
		{
			if(_pInstance != NULL)
				delete _pInstance;
		}
	};

public:
	static singleton* getInstance()  //创建对象指针  //要申明静态，只有类名才能调用它
	{
		if(_pInstance == NULL)
			_pInstance = new singleton;
		return _pInstance;
	}
	void destroy()
	{
		if(_pInstance != NULL)
			delete _pInstance;
	}
private:
	singleton()  //constructor
	{
		cout << "singleton()" << endl;
	}
	~singleton()  //destructor
	{
		cout << "~singleton()" << endl;
	}
private:
	static singleton* _pInstance;
	static autorelease _autorelease;

};
 
singleton* singleton::_pInstance = getInstance();  //静态成员变量初始化
singleton::autorelease singleton::_autorelease;  //静态成员对象初始化

int main()
{
	singleton* p1 = singleton::getInstance();
	singleton* p2 = singleton::getInstance();
	printf("p1 = %p\n",p1);
	printf("p2 = %p\n",p2);
	
	return 0;
}
