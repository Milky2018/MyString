#pragma once
//version 1.1
//by Lei Zhengyu
//following are statements

#include <iostream>

class MyString
{
private:
	char *data;
	int length;
	int maxlen;
	void GetNext(const MyString &, int[]) const;
	int KMP(const MyString&, int start, int next[])const;
public:
	MyString(int max=1);
	MyString(const MyString &);
	MyString(const char *s);
	char *GetData() const { return data; }
	int GetLen() const { return length; }
	int GetMax() const { return maxlen; }
	int ThereIs(char,int=0) const;
	int ThereIs(const MyString &, int=0)const;
	void CharIns(char);
	//void CharIns(char, int pos);
	MyString& operator=(const MyString &);
	MyString& operator=(const char *);
	MyString operator+(const MyString &)const;
	MyString operator+(const char *)const;
	MyString& operator+=(const MyString &);
	MyString& operator+=(char *);
	inline int operator<(const MyString &s)const;
	inline int operator>(const MyString &s)const;
	inline int operator<=(const MyString &s)const;
	inline int operator>=(const MyString &s)const;
	inline int operator==(const MyString &)const;
	void ClearString();
	int StrEmpty ()const { return length == 0; }
	void ReverseString();
	char operator[](const int i)const
	{
		return data[i];
	}
	friend MyString operator+(const char *, MyString &);
	//friend istream& operator>>(istream &, MyString &);
	~MyString() {
		delete []data;
	}
};

std::ostream& operator<<(std::ostream &, const MyString &);
int StrLen(const char *);
void StrCpy(char *, const char *);
void Reverse(char *s);
int StrCmp(const char *s, const char *t);
int StrCmp(const MyString&, const MyString&);

//following are function definitions

int StrLen(const char *s)
{
	int i = 0;
	if (s) {
		while (s[i])
			++i;
		return i;
	}
	return -1;
}

void StrCpy(char *s, const char *t)
{
	while (*s++ = *t++)
		;
}

void Reverse(char *s)
{
	int i, j, t;
	for (i = 0, j = StrLen(s) - 1; i < j; i++, j--)
		t = s[i], s[i] = s[j], s[j] = t;
}

int StrCmp(const MyString &s, const MyString &t)
{
	return StrCmp(s.GetData(), t.GetData());
}

int StrCmp(const char *s, const char *t)
{
	for (int i = 0; i <= StrLen(s); i++) {
		if (*(s + i) < *(t + i))
			return -1;
		else if (*(s + i) > *(t + i))
			return 1;
		else if (*(s + i) == *(t + i) && *(t + i) == '\0')
			return 0;
		else
			continue;
	}
	return -1;
}

int MyString::KMP(const MyString &t, int start, int next[])const
{
	int i = start;
	int j = 0;
	int v;
	while (i < length&&j < t.length) {
		if (data[i] == t.data[j]) {
			i++;
			j++;
		} else if (j == 0)
			i++;
		else
			j = next[j];
	}
	if (j == t.length)
		v = i - j;
	else
		v = -1;
	return v;
}

void MyString::GetNext(const MyString &t, int next[])const
{
	int j = 1;
	int k = 0;
	next[0] = -1;
	next[1] = 0;
	while (j < t.length - 1) {
		if (t.data[j] == t.data[k])
			next[++j] = ++k;
		else if (k == 0)
			next[++j] = 0;
		else
			k = next[k];
	}
}

MyString::MyString(int max)
{
	length = 0;
	maxlen = max;
	data = new char[max];
	*data = '\0';
}

MyString::MyString(const MyString &s)
{
	maxlen = s.maxlen;
	length = s.length;
	data = new char[maxlen];
	StrCpy(data, s.data);
}

MyString::MyString(const char *s)
{
	length = StrLen(s);
	maxlen = length + 1;
	data = new char[maxlen];
	StrCpy(data, s);
}

void MyString::ClearString()
{
	maxlen = 1;
	length = 0;
	delete[] data;
	data = new char;
	data[0] = '\0';
}

MyString &MyString::operator=(const MyString &s)
{
	if (this == &s)
		return *this;
	delete[] data;
	maxlen = s.maxlen;
	length = s.length;
	data = new char[maxlen];
	StrCpy(data, s.data);
	return *this;
}

MyString& MyString::operator=(const char *s)
{
	delete[] data;
	length = StrLen(s);
	maxlen = length + 1;
	data = new char[maxlen];
	StrCpy(data, s);
	return *this;
}

MyString MyString::operator+(const MyString &s) const
{
	MyString newstr;
	newstr.length = length + s.length;
	newstr.maxlen = newstr.length + 1;
	newstr.data = new char[newstr.maxlen];
	StrCpy(newstr.data, data);
	StrCpy(newstr.data + length, s.data);
	return newstr;
}

MyString& MyString::operator+=(const MyString &s)
{
	*this = *this + s;
	return *this;
}

MyString MyString::operator+(const char *s)const
{
	MyString newstr;
	newstr.length = length + StrLen(s);
	newstr.maxlen = newstr.length + 1;
	newstr.data = new char[newstr.maxlen];
	StrCpy(newstr.data, data);
	StrCpy(newstr.data + length, s);
	return newstr;
}

MyString& MyString::operator+=(char *s)
{
	*this = *this + s;
	return *this;
}

MyString operator+(const char *s, MyString &t)
{
	MyString newstr;
	newstr.length = StrLen(s) + t.length;
	newstr.maxlen = newstr.length + 1;
	newstr.data = new char[newstr.maxlen];
	StrCpy(newstr.data, s);
	StrCpy(newstr.data + StrLen(s), t.data);
	return newstr;
}

std::ostream& operator<<(std::ostream &os, const MyString &s)
{
	return os << s.GetData();
}

void MyString::ReverseString()
{
	int t, i, j;
	for (i = 0, j = length - 1; i < j; i++, j--)
		t = data[i], data[i] = data[j], data[j] = t;
}

int MyString::ThereIs(char c, int start) const
{
	for (int i = start; i < length; i++) 
		if (data[i] == c)
			return i + start;
	return -1;
}

inline int MyString::ThereIs(const MyString &t, int start) const
{
	int *next = new int[t.length];
	GetNext(t, next);
	int v = KMP(t, start, next);
	delete[] next;
	return v;
}

void MyString::CharIns(char c)
{
	if (length + 1 >= maxlen) {
		maxlen += 10;
		char *newdata = new char[maxlen];
		StrCpy(newdata, data);
		delete[] data;
		data = newdata;
	}
	data[length++] = c;
	data[length] = '\0';
	return;
}

inline int MyString::operator<(const MyString &s)const
{
	return StrCmp(*this, s) == -1;
}

inline int MyString::operator>(const MyString &s)const
{
	return StrCmp(*this, s) == 1;
}

inline int MyString::operator<=(const MyString &s)const
{
	return StrCmp(*this, s) < 1;
}

inline int MyString::operator>=(const MyString &s)const
{
	return StrCmp(*this, s) > -1;
}

inline int MyString::operator==(const MyString &s)const
{
	return StrCmp(*this, s) == 1;
}

//v1.0 includes the definition of class MyString and basic functions
//	operators overloading of plus, substraction, comparation, assignment
//	operators overloading of output streams
//	function of reserving
//	function of addition of one single charater
//v1.01 new operator == overloading (be equal to) added
//v1.1 KMP added, including three functions in class MyString
//	private:KMP
//	private:GetNext
//	public:ThereIs overloading