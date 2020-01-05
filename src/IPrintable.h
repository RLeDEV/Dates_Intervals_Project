#ifndef IPrintable_h
#define IPrintable_h

#include <iostream>
using namespace std;

template<typename T>
class IPrintable {
public:
	friend ostream& operator<<(ostream& os, const T& t) { t.print(os); return os; }
	friend istream& operator>>(istream& in, T& t) { t.input(in); return in; }
	virtual void print(ostream& os) const = 0;
	virtual ~IPrintable() = 0;
};

template<typename T>
IPrintable<T>::~IPrintable() {};

#endif