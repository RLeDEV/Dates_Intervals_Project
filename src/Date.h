#pragma once
#include "IPrintable.h"
#include "IComparable.h"
#include <iostream>


using namespace std;


#ifndef DATE_H
class Date: 
	public IPrintable<Date>,
	public IComparable<Date>
{
protected:
	int day;
	int month;
	int year;
	int errorID;
public:
	Date(int, int, int);
	Date(const Date&);
	virtual ~Date();

	// Setters
	void setDay(int);
	void setMonth(int);
	void setYear(int);

	// Getters
	int getDay();
	int getMonth();
	int getYear();
	int getErrorID() const;

	// Operators
	virtual bool operator==(const Date&) const;
	virtual bool operator<=(const Date&) const;
	virtual bool operator>=(const Date&) const;
	virtual bool operator!=(const Date&) const;
	virtual bool operator<(const Date&) const;
	virtual bool operator>(const Date&) const;
	const Date& operator=(const Date &other);

	// input/output
	virtual void print(ostream& os) const;
	virtual void input(istream& in);

	// Error checkers
	bool isValid(int,int,int);
	void getProblem() const;

	// Parsers
	int parseDay(string dateInput) const;
	int parseMonth(string dateInput) const;
	int parseYear(string dateInput) const;
};
#endif