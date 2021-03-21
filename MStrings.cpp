/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <cstring>
#include <string.h>
#include <cmath>
#include <cassert>
#include <exception>

#include "MyString.h"
using namespace std;

MyString::MyString(const char* chstr) {
    if (0 == chstr) {
        _size = 0;
        _str = 0;
        return;
    }

    _size = strlen(chstr);
    _str = new char[_size + 1];
    memcpy(_str, chstr, _size);
    _str[_size] = 0;
}

MyString::MyString(const MyString & copy_str) {
    if (0 == copy_str.size()) {
        _size = 0;
        _str = 0;
        return;
    }

    _size = copy_str._size;
    _str = new char[_size + 1];
    memcpy(_str, (const char*)copy_str, _size);
    _str[_size] = 0;
}

MyString::~MyString()
{
    if(_str)
        delete[] _str;
    _str = 0;
    _size = 0;
}

MyString& MyString::operator= (const MyString& copy_str)
{
    if(this == &copy_str)
        return *this;
    
    if(_str)
        delete[] _str;
    
    if(0 == copy_str.size())
    {
        _str = 0;
        _size = 0;
        return *this;
    }
    
    _size = copy_str._size;
    _str = new char[_size + 1];
    memcpy(_str, static_cast<const char*>(copy_str), _size);
    _str[_size] = 0;
    
    return *this;
}

size_t MyString::size() const
{
    return _size;
}

MyString::operator const char* () const
{
    return _str;
}

const char& MyString::operator[](const int i) const
{
    //assert(i > _size);
    try{
        if(i > _size)
        throw ("i > size");
    } 
    catch(const char* value)
    {
        std::cout << "Failed: " << value << std::endl;
        terminate();
    }
            
    return operator const char*()[i];
}

//char MyString::operator[](const int i)
//{
//   // assert(i > _size);
//    
//    return _str[i];
//}

bool operator== (const MyString& str1, const MyString& str2)
{
    return (0 == strcmp(str1, str2));
}

bool operator!= (const MyString & str1, const MyString & str2)
{
    return !(str1 == str2);
}

bool operator< (const MyString & str1, const MyString & str2)
{
    return (0 > strcmp(str1, str2));
}

bool operator> (const MyString & str1, const MyString & str2)
{
    return (0 < strcmp(str1, str2));
}

bool operator<= (const MyString & str1, const MyString & str2)
{
    return ((str1 < str2) || (str1 == str2));
}

bool operator>= (const MyString & str1, const MyString & str2)
{
    return ((str1 > str2) || (str1 == str2));
}

int MyString::index (char ch) const
{
    if(!size())
        return -1;
    
    for (int i = 0; i < _size; ++i)
        if(ch == _str[i])
            return (i+1);
}

MyString & MyString::operator +=(const MyString& str)
{
    int size = str._size + _size + 1;
    
    char * p = new char[size];
    strcat(p, _str);
    strcat(p, str);
    _str = p;
    _str[size] = 0;
    _size = size-1;
    return *this;
}

MyString operator +(const MyString & firstStr, const MyString & secondStr)
{
    MyString s (firstStr);
    
    s += secondStr;
    return s; // for value
}

MyString & MyString::operator -=(const MyString& delStr)
{
    
    char * p = new char[_size + 1];
    memset(p, 0, _size + 1);
    char * foundStr = strstr(_str, delStr._str);
    
    if (!foundStr)
        return *this;
        
    ptrdiff_t pos = 0;
    char* newP = _str;
    
    while((newP) && (*newP))
    {
        if (!foundStr)
        {
            strncat(p, newP, strlen(newP));
            break;
        }
            
        pos =  ptrdiff_t(foundStr - newP);
        
        if (pos > _size)
            break;
        
        strncat(p, newP, pos);
        
        newP += (pos + delStr._size);

        foundStr = strstr(newP, delStr._str);
    }
    
    _size = strlen(p);
    
    if (_str)
        delete [] _str;
    
    _str = p;
    
    return *this;    
}

MyString & MyString::insert(size_t pos, const MyString & origstr, size_t countSymbols)
{
    if(pos > _size)
        pos = _size;
    
    if(countSymbols > origstr._size)
        countSymbols = origstr._size;
    
    char * p = new char[_size + countSymbols + 1];
    
    memset (p, 0, (_size + countSymbols + 1));
    memcpy(p, _str, pos); // скопировал текущую строку в p до позиции pos
    strncat(p,origstr, countSymbols); // вставляем строку origstr с позиции pos(смотри выше) 
    strncat(p, _str + pos , _size - pos);
    
    delete [] _str;
    
    _str = p;
    _size += countSymbols;
    
    return *this;
}

MyString & MyString::push_back(const MyString& str)
{
    return operator +=(str);
}

MyString & MyString::push_front(const MyString& str)
{
    return insert(0, str, str._size);
}

MyString & MyString::remove(size_t pos, size_t n)
{
    if(pos > _size)
        pos = _size;
    
    if(n > _size)
        n = _size;
        
    //cout << "_size - n = " << _size - n << endl;
    char * p = new char[_size + 1];
    memset(p, 0,_size + 1);
    memcpy(p, _str, pos);
    _size -= (pos + n);
    strncat(p, _str + pos + n, _size);
    delete[] _str;
    _str = p;
    _size = strlen(p);
    
    return *this;
}

MyString & MyString::pop_front()
{
    return remove(0,1);
}

MyString & MyString::pop_back()
{
    return remove(_size-1,1);
}


//not delete function
/*MyString operator,(const MyString& str1, const MyString& str2)
{
    return MyString(str1 + MyString(",") + str2);
}*/

MyString operator,(const MyString& str1, const MyString& str2)
{
    MyString s1(str1);
    MyString s2(str2);
    
    if(s1._size > 0)
    {
        for(int i = 0; i < s1._size-1; i+=2)
            s1.insert(i+1, ",", 2);
    }
    
    
    if(s1._size > 0)
    {
        for(int i = 0; i < s2._size-1; i+=2)
            s2.insert(i+1, ",", 2);
    }
    
    return MyString(MyString("[") + s1 + "] "  + MyString(" [") + s2 + "]");
}

MyString MyString::appendif(size_t pos, const MyString & origstr, size_t countSymbols)
{
    MyString copy_str(*this);
    
    copy_str.insert(pos, origstr, countSymbols);
    return copy_str;
}

MyString & MyString::replace(const MyString & fromFormatStr, 
                             const MyString & toFormatStr, 
                             const int numberEntries)
{
   if(0 > numberEntries)
        return *this;
    
     const char *foundStr = strstr(_str, fromFormatStr._str);
    
    if (!foundStr)
        return *this;
     
     if ( (toFormatStr.size() > _size) || 
          (fromFormatStr.size() < toFormatStr._size))
     {
         cout << "Exit!" << endl;
         return *this;
     }
    
    ptrdiff_t pos = 0;
    ptrdiff_t posResult = pos;
        
    int count = 0;
    
    
    while(numberEntries > count)
    {
        foundStr = strstr(_str + pos, fromFormatStr._str);
        
        if(!foundStr)
            break;
        
        pos = ptrdiff_t(foundStr - _str);
        cout << pos << ", Newp = " << (_str + pos) << " : " << pos << endl;
        
        posResult = pos;
        ++pos;
        ++count;
    }
    
    cout << "count " << count << endl;
    //cout << "foundStr" << ptrdiff_t(foundStr) << endl;
    if(numberEntries != count)
        return *this;
    
    cout << "end pos: "<< posResult << endl;
    remove(posResult, fromFormatStr._size);
    return insert(posResult, toFormatStr, toFormatStr._size);
}

/*MyString operator.(const MyString& str1, const MyString& str2)
{
    return MyString(str1 + "." + str2);
}*/
