 ///
 /// @file    copy_on_write.cc
 /// @author  Islotus(2791201278@qq.com)
 /// @date    2016-06-17 07:53:00
 ///

//写时拷贝（完整版）

#include <iostream>
#include <string.h>

using std::cout;
using std::endl;
using std::ostream;

class String
{
private:
	class CharProxy
	{
	public:
		CharProxy(String& str, int idx);

		char & operator =(char ch);

		operator char()
		{  //类型转换，由CharProxy转向char
			return _str._pstr[_idx];
		}
		//friend ostream& operator <<(ostream& os, const CharProxy &rhs);
	private:
		String& _str;  //定义类String 对象的引用
		int _idx;
	};
	//friend ostream& operator <<(ostream& os, const CharProxy &ths);
	
public:
	String();  //无参构造函数
	String(const char* pstr);  //带一个参数的构造函数
	String(const String& rhs);  //复制构造函数
	String& operator =(const String& rhs);  //赋值运算符重载
	~String();  //析构函数

	int useCount()  //返回引用计数值
	{	return _pstr[length() + 1];	}

	int length()  //返回字符串长度
	{	return strlen(_pstr);	}

	CharProxy operator [](int idx);  //取地址运算符重载 //返回CharProxy对象，proxy,代理
	char& operator[](int idx) const;  //取地址运算符重载
private:
	void initRefcount()  //引用计数初始化为1
	{	_pstr[length() + 1] = 1;	}

	void increaseRefcount()  //引用计数加1
	{	++_pstr[length() + 1];	}

	void decreaseRefcount()  //引用计数减1
	{	--_pstr[length() + 1];	}

	
private:
	char* _pstr;
};

String::String()  //类String无参构造函数实现
:_pstr(new char[2])  //默认开辟两个空间
{
	cout << "String()" << endl;
	initRefcount();
}

String::String(const char *pstr)  //类String带一个参数构造函数
{
	int len = strlen(pstr);
	_pstr = new char[len + 2];  //申请空间，多出两个空间放'\0'和引用计数值
	strcpy(_pstr, pstr);
	initRefcount();  //将引用计数值设置为1
	cout << "String(const char *)" << endl;
}

String::String(const String& rhs)  //类String复制构造函数实现
:_pstr(rhs._pstr)
{
	increaseRefcount();
	cout << "String(const String& rhs)" << endl;
}

String& String::operator =(const String& rhs)  //赋值运算符重载
{
	if(this != &rhs)
	{
		decreaseRefcount();  //将原来_pstr指向空间引用计数减1
		if(useCount() == 0)
			delete [] _pstr;
		_pstr = rhs._pstr;  //进行浅拷贝
		increaseRefcount();  //将新_pstr指向空间引用计数减1
	}
	return *this;
}

String::~String()
{
	decreaseRefcount();
	if(useCount() ==0)
	{
		delete [] _pstr;
		cout << "~String()" << endl;
	}
}

char& String::operator [](int idx) const  //不能区分是读还是写操作
{
	cout << "operator [](int) const" << endl;
	return _pstr[idx];
}

String::CharProxy String::operator [](int idx)  //返回一个CharProxy对象
{
	return CharProxy(*this, idx);  //类CharProxy构造函数被调用
}

String::CharProxy::CharProxy(String& str, int idx)
:_str(str)
,_idx(idx)
{
}

char& String::CharProxy::operator =(char ch)
{
	if(_idx >= 0 && _idx < _str.length())
	{
		if(_str.useCount() == 1)  //1.当对象没有共享内存时
		{
			_str._pstr[_idx] = ch;  //进行修改
			return _str._pstr[_idx];
		}
		_str.decreaseRefcount();  //2.当对象共享内存时
		char* ptmp = new char[_str.length() + 2];
		strcpy(ptmp, _str._pstr);  //进行复制
		_str._pstr = ptmp;  //
		_str.initRefcount();
		_str._pstr[_idx] = ch;  //进行修改
		return _str._pstr[_idx];
	}
	else
	{
		static char nullchar = '\0';  //定义常量字符
		cout << "下标越界" << endl;
		return nullchar;  //不能直接返回0，因为汗水返回类型为引用，要有一个常量
	}
}


int main()
{
	String s1 = "hello, world";
	String s2 = s1;
	String s3 = s2;

	cout << "s1'useCnt = " << s1.useCount() << endl;
	cout << "s2'useCnt = " << s2.useCount() << endl;
	cout << "s3'useCnt = " << s3.useCount() << endl;
	cout << endl;

	String s4 = "shenzhen";
	cout << "s4'useCnt = " << s4.useCount() << endl;
	cout << endl;

	s4 = s2;
	cout << "s1'useCnt = " << s1.useCount() << endl;
	cout << "s2'useCnt = " << s2.useCount() << endl;
	cout << "s3'useCnt = " << s3.useCount() << endl;
	cout << "s4'useCnt = " << s4.useCount() << endl;
	cout << endl;

	//写操作时会发生写时复制
	s4[0] = 'X';
	cout << "s1'useCnt = " << s1.useCount() << endl;
	cout << "s2'useCnt = " << s2.useCount() << endl;
	cout << "s3'useCnt = " << s3.useCount() << endl;
	cout << "s4'useCnt = " << s4.useCount() << endl;
	cout << endl;

	//读草操作时也会发生复制
	cout << s3[0] << endl;
	cout << "s1'useCnt = " << s1.useCount() << endl;
	cout << "s2'useCnt = " << s2.useCount() << endl;
	cout << "s3'useCnt = " << s3.useCount() << endl;
	cout << endl;

	return 0;	
}

