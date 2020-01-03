#pragma once
#ifndef ICOMPARABLE_H
#define ICOMPARABLE_H
#include <iostream>
template<typename T>
class IComparable
{
public:
	virtual ~IComparable() = 0 {};
	virtual bool operator==(T&)const = 0;
	virtual bool operator<=(T&)const = 0;
	virtual bool operator>=(T&)const = 0;
	virtual bool operator!=(T&)const = 0;
	virtual bool operator<(T&)const = 0;
	virtual bool operator>(T&)const = 0;
};
#endif

