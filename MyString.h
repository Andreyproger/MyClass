#ifndef MYSTRING_H
#define MYSTRING_H

#include <limits>
#include <cstddef>
#include <iostream>

class MyString{
private:
    char * _str;
    size_t _size;
    
public:
    MyString(const char* chstr);
    MyString(const MyString &str);
    
    ~MyString();
    
    size_t size() const;
    inline char* data() {return _str;}
    MyString& operator=(const MyString &);
    
    friend bool operator==(const MyString & str1, const MyString & str2);
    friend bool operator!=(const MyString & str1, const MyString & str2);
    
    friend bool operator<(const MyString & str1, const MyString & str2);  
    friend bool operator>(const MyString & str1, const MyString & str2);
    
    
    friend bool operator>=(const MyString & str1, const MyString & str2);
    friend bool operator<=(const MyString & str1, const MyString & str2);
    
    int index (char ch) const;
    
    const char& operator[](const int i) const;
   // char operator[](const int j); 
    
    MyString & operator += (const MyString& str);
    friend MyString operator +(const MyString & origStr, const MyString & secondStr);
    
    MyString & operator -= (const MyString& str);
    
    friend MyString operator -(const MyString & origStr, const MyString & delStr);
    
    operator const char*() const;
    
    //ToDo operator+=, operator-=, operator+, append, insert
    
    MyString & insert(size_t pos, const MyString & origstr, size_t countSymbols);
    
    MyString appendif(size_t pos, const MyString & origstr, size_t countSymbols);
    
    MyString & push_back(const MyString& str);
    
    MyString & push_front(const MyString& str);
    
    MyString & remove(size_t pos, size_t n);
    
    MyString & pop_front();
    
    MyString & pop_back();
    
    friend MyString operator,(const MyString& str1,
                              const MyString& str2);
    
    //встроенные операторы не перегружаются
    //friend MyString operator,,(const MyString& str1, const MyString& str2);
    
    //
    //friend MyString operator.(const MyString& str1, const MyString& str2);

    MyString & replace(const MyString & fromFormatStr, 
                       const MyString & toFormatStr, 
                       const int numberEntries = std::numeric_limits<int>::max());
    
};

#endif /* MYSTRING_H */
