#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include <iomanip>
#include <iostream>
#include <string>

using std::string;
using namespace std;

// C'tor w/ 3 integers as parameters
Date::Date(int dayGiven, int monthGiven, int yearGiven) {
	this->day = dayGiven;
	this->month = monthGiven;
	this->year = yearGiven;
	this->errorID = -1;
}

// Copy C'tor
Date::Date(const Date& otherDate) {
	this->day = otherDate.day;
	this->month = otherDate.month;
	this->year = otherDate.year;
	this->errorID = otherDate.errorID;
}

Date::~Date() {

}

// Setters
void Date::setDay(int newDay) {
	if(isValid(newDay,this->month,this->year))
		this->day = newDay;
}

void Date::setMonth(int newMonth) {
	if(isValid(this->day,newMonth,this->year))
		this->month = newMonth;
}

void Date::setYear(int newYear) {
	if(isValid(this->day,this->month,newYear))
		this->year = newYear;
}

// Getters
int Date::getDay() {
	return day;
}

int Date::getMonth() {
	return month;
}

int Date::getYear() {
	return year;
}

int Date::getErrorID() const {
	return errorID;
}


// input/output functions

void Date::print(ostream& os) const{
	if (getErrorID() == -1) {
		if (day < 10)
			cout << '0';
		cout << day << '/';
		if (month < 10) 
			cout << '0';
		cout << month << '/';
		cout << year;
	}
	else {
		getProblem();
	}
}

void Date::input(istream& in){
	int day, month, year;
	string dateInput;
	getline(in, dateInput);
	day = parseDay(dateInput);
	month = parseMonth(dateInput);
	year = parseYear(dateInput);
	*this = Date(day, month, year);
}

// Parsers
int Date::parseDay(string dateInput) const {
	string day = "";
	int i,finalDay;
	for (i = 0; i < 2; i++) {
		if(dateInput[i] != '/')
			day += dateInput[i];
	}
	finalDay = stoi(day);
	return finalDay;
}

int Date::parseMonth(string dateInput) const {
	string month = "";
	int i, finalMonth;
	char *dup = _strdup(dateInput.c_str());
	dateInput = strtok(dup, "/");
	for (i = 0; i < 2; i++) {
		if (dateInput[i] != '/')
			month += dateInput[i];
	}
	finalMonth = stoi(month);
	delete []dup;
	return finalMonth;
}

int Date::parseYear(string dateInput) const {
	string year = "";
	int i, finalYear;
	char *dup = _strdup(dateInput.c_str());
	dateInput = strtok(dup, "/");
	dateInput = strtok(NULL, "/");
	for (i = 0; i < 4; i++) {
		year += dateInput[i];
	}
	finalYear = stoi(year);
	delete []dup;
	return finalYear;
}

// Operators
const Date& Date::operator=(const Date &other) {
	if (isValid(other.day, other.month, other.year)) {

		errorID = 0;
	}
	day = other.day;
	month = other.month;
	year = other.year;
	return *this;
}

bool Date::operator==(Date& otherDate) const {
	if (day == otherDate.day && month == otherDate.month && year == otherDate.year)
		return true;
	return false;
}

bool Date::operator<=(Date& otherDate) const {
	if (this == &otherDate)
		return true;
	else if (this->year < otherDate.year)
		return true;
	else if (this->year == otherDate.year && this->month < otherDate.month)
		return true;
	else if (this->year == otherDate.year && this->month == otherDate.month && this->day < otherDate.day)
		return true;
	return false;
}

bool Date::operator>=(Date& otherDate) const {
	if (this == &otherDate)
		return true;
	else if (!(this <= &otherDate))
		return true;
	return false;
}

bool Date::operator!=(Date& otherDate) const {
	if (!(this == &otherDate))
		return true;
	return false;
}

bool Date::operator<(Date& otherDate) const {
	if (year < otherDate.year)
		return true;
	else if (year == otherDate.year && month < otherDate.month)
		return true;
	else if (year == otherDate.year && month == otherDate.month && day < otherDate.day)
		return true;
	return false;
}

bool Date::operator>(Date& otherDate) const {
	if (this == &otherDate)
		return false;
	else if (!(this < &otherDate))
		return true;
	return false;
}

bool Date::isValid(int day, int month, int year) {
	try {
		if (day < 1 || day > 31) // invalid day
			throw 1;
		if (month < 1 || month > 12) // invalid month
			throw 2;
		if (month == 9 || month == 6 || month == 11 || month == 4) { // months with 30 days only
			if (day > 30)
				throw 1;
		}
		if (month == 2) {
			if (year % 4 != 0 && day > 28) // months with 28 days only (only in leap years)
				throw 3;
			else if (day > 29)
				throw 1;
		}
		return true;
	}
	catch (int errorSign) {
		errorID = errorSign;
		return false;
	}
}

void Date::getProblem() const {
	switch (errorID) {
	case -1:
		cout << "There's no error";
		break;
	case 1:
		cout << "Invalid day";
		break;
	case 2:
		cout << "Invalid month";
		break;
	case 3:
		cout << "Not a leap year";
		break;
	default:;
	}
}