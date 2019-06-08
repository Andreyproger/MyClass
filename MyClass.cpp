#include <iostream>
#include <cstdlib>
#include <string.h>
#include <cassert>
#include <vector>
#include "MStrings.cpp"
//#include "MyClass.h"

using namespace std;

template<class T>
class MyClass
{
private:
	T * _array;
	int _size;

public:
	MyClass():
		_size(0),
		_array(0)
		{}

	~MyClass()
	{
		if(_size)
			delete [] _array;

		_array = 0;
		_size = 0;
	}

	MyClass(const MyClass<T> & copy_obj):
		_size(copy_obj._size),
		_array(new T[_size])
	{
		_array = copy_obj._array;
		memcpy(_array, copy_obj._array, _size * sizeof(T));
	}

	MyClass(const T* array, int size):
		_size(size)
	{
		_array = new T[_size];
		memcpy(_array, array, _size);
	}

	MyClass& operator=(const MyClass<T>& value)
	{
		if(this == &value)
			return *this;

		if(0 == value._size)
		{
			_array = 0;
			_size = 0;
			return *this;
		}

		if(_array)
			delete [] _array;

		_size = value._size;

		assert(0 <= _size);
		_array = value._array;
		return *this;
	}

	operator const T* const
	{
		return _array;
	}

	T func(T value)
	{
		return value;
	}
}

template<>
MyClass<int>::operator const int*() const
{
	return (const int*)(this->_array);
}

template<>
MyClass<int>&::MyClass<int>::operator=(const MyClass<int>& value)
{
	if(this == value)
		return *this;

	if(_array)
		delete [] _array;

	if(0 == value._size)
	{
		_array = 0;
		_size = 0;
		return * this;
	}

	_size = value._size;

	assert(0 <= _size);

	_array = value._array;

	return *this;
}

template<>
int MyClass<int>::func(int i)
{
	return i;
}

template<> class MyClass<char>
{
public:
	MyClass(const char* array, int size):
		_array(0),
		_size(0)
	{
		if(0 == array || 0 == size)
			return;

		MString str(array);
		_array[str.size()] = 0;
		_size = str.size();
	}

	~MyClass()
	{
		if(_size)
			delete [] _array;
		_array = 0;
		_size = 0;
	}

private:
	char* _array;
	int _size;
}

template<> class MyClass<std::vector<double> >
{
	public:
		MyClass(const std::vector<double> & vec, int size)
			: _vec(0)
			, _size(0)
		{
			if(0 == size)
				return;

			std::cout << "--------------VECTOR----------++++++++++++++++" << endl;

			_vec = vec;
			_size = vec.size();

			for(int i = 0; i < vec.size(); i++)
				cout << vec[i] << endl;
		}

		~MyClass()
		{};

	private:
		std::vector<double> _vec;
		int _size;
}

void test1()
{
  const char* str = "b";
  const std::string str = "abcdefg";
  
  MyClass<char> testValue(str, 1);
  //add additionaly functionality
}

int main()
{
  test1();
	return 0;
}
