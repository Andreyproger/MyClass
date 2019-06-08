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

using namespace std;

MStrings::MStrings(const MStrings& copy_str)
{
    if (0 == copy_str.size())
    {
        _size = 0;
        _str = 0;
        return;
    }

    _size = copy_str._size;
    _str = new char[_size + 1];
    memcpy(_str, (const char*)copy_str, _size);
    _str[_size] = 0;
}

MStrings::MStrings(const char* str)
{
    if(0 == str)
    {
        _size = 0;
        _str = 0;
        return;
    }
    
    _size = strlen(str);
    _str = new char[_size + 1];
    memcpy(_str, str, _size);
    _str[_size] = 0;
}

MStrings::~MStrings() 
{
    if(_str)
        delete [] _str;
    
    _str = 0;
    _size = 0;
}

MStrings& MStrings::operator= (const MStrings& copy)
{
    if(this == &copy)
        return *this;
    
    if(_str)
        delete[] _str;
    
    if(0 == copy.size())
    {
        _str = 0;
        _size = 0;
        return *this;
    }
    
    _size = copy._size;
    _str = new char[_size + 1];
    //memcpy(_str, static_cast<const char*>(copy), _size);
    memcpy(_str, (const char*)(copy), _size);
    _str[_size] = 0;
    
    return *this;
}

size_t MStrings::size() const
{
    return _size;
}

MStrings::operator const char* () const
{
    return _str;
}

const char& MStrings::operator[](const int i) const
{
    try{
        if(i > _size)
        throw ("All failed!");
    } 
    catch(const char* value)
    {
        
        terminate();
    }
            
    return operator const char*()[i];
}

//char MStrings::operator[](const int i)
//{
//   // assert(i > _size);
//    
//    return _str[i];
//}

bool operator== (const MStrings& str1, const MStrings& str2)
{
    return (0 == strcmp(str1, str2));
}

bool operator!= (const MStrings & str1, const MStrings & str2)
{
    return !(str1 == str2);
}

bool operator< (const MStrings & str1, const MStrings & str2)
{
    return (0 > strcmp(str1, str2));
}

bool operator> (const MStrings & str1, const MStrings & str2)
{
    return (0 < strcmp(str1, str2));
}

bool operator<= (const MStrings & str1, const MStrings & str2)
{
    return ((str1 < str2) || (str1 == str2));
}

bool operator>= (const MStrings & str1, const MStrings & str2)
{
    return ((str1 > str2) || (str1 == str2));
}

int MStrings::index (char ch) const
{
    if(!size())
        return -1;
    
    for (int i = 0; i < _size; ++i)
        if(ch == _str[i])
            return (i+1);
}

MStrings & MStrings::operator +=(const MStrings& str)
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

MStrings operator +(const MStrings & firstStr, const MStrings & secondStr)
{
    MStrings s (firstStr);
    
    s += secondStr;
    return s; // for value
}

MStrings & MStrings::operator -=(const MStrings& delStr)
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
