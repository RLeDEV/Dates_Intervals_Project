#pragma once
#ifndef IPRINTABLE_H
#define IPRINTABLE_H
#include <iostream>
using namespace std;
template<typename T>
class IPrintable
{
public:
	friend ostream& operator<<(ostream& os, const T& t) { t.print(os); return os; };
	friend istream& operator>>(ostream& in, const T& t) { t.input(in); return in; };
	virtual void print(ostream& os) const = 0;
	virtual ~IPrintable() = 0 {};
};
#endif

