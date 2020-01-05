#pragma once
#ifndef INTERVAL_H
#define INTERVAL_H
#include "IPrintable.h"
#include <iostream>

template<typename T>
class Interval : public IPrintable<Interval<T>>
{
private:
	T start;
	T end;
public:
	Interval(T, T);
	Interval(const Interval<T>&);
	~Interval() {};
	bool isEmpty() const;
	bool isBefore(const Interval<T>&) const;
	bool isAfter(const Interval<T>&) const;
	bool intersects(const Interval<T>&) const;
	bool contains(T) const;

	// Operators
	const Interval<T> operator&&(const Interval<T>&) const;
	const Interval<T> operator||(const Interval<T>&) const;
	
	// Output
	virtual void print(ostream&) const;
};

// C'tor
template<typename T>
Interval<T>::Interval(T start, T end) {
	this->start = start;
	this->end = end;
}

// Copy c'tor
template<typename T>
Interval<T>::Interval(const Interval<T>& otherInterval) {
	start = otherInterval.start;
	end = otherInterval.end;
}

// Functions
template <typename T>
bool Interval<T>::isEmpty() const {
	if (this->start == this->end) {
		return true; // An empty group
	}
	return false; // Not an empty group
}

template <typename T>
bool Interval<T>::isBefore(const Interval<T>& otherInterval) const {
	if (this->end < otherInterval.end && otherInterval.start >= this->end) { 
		return true;
	}
	return false;
}

template <typename T>
bool Interval<T>::isAfter(const Interval<T>& otherInterval) const {
	if (this->start >= otherInterval.end && otherInterval.end < this->end)
		return true;
	return false;
}

template <typename T>
bool Interval<T>::intersects(const Interval<T>& otherInterval) const {
	if (this->isAfter(otherInterval) == true || this->isBefore(otherInterval) == true) {
		return false;
	}
	return true;
}

template <typename T>
bool Interval<T>::contains(T organ) const {
	if (!(this->start >= organ || this->end <= organ)) {
		return true;
	}
	return false;
}

// Operators
template <typename T>
const Interval<T> Interval<T>::operator||(const Interval<T>& otherInterval) const {
	T newStart, newEnd;
	if (start >= otherInterval.end || end <= otherInterval.start) {
		return Interval(2, 1); // returns illegal interval
	}
	else {
		if (start < otherInterval.start) // checking who is the start of the consolidation between them
			newStart = start;
		else 
			newStart = otherInterval.start;
		if (end > otherInterval.end) // checking who is the end of the consolidation between them
			newEnd = end;
		else
			newEnd = otherInterval.end;
	}
	return Interval(newStart, newEnd); // returns the consolidation between them
}

template<typename T>
const Interval<T> Interval<T>::operator&&(const Interval<T>& otherInterval) const {
	T newStart, newEnd;
	if (this->intersects(otherInterval) == false)
		return Interval(0, 0); // returns an empty interval, there's no cut between them
	else {
		// checking if this->start contains otherInterval.start to set start & end of the cut
		if (this->start < otherInterval.start && this->contains(otherInterval.start)) {
			newStart = otherInterval.start;
			if (this->end < otherInterval.end)
				newEnd = end;
			else
				newEnd = otherInterval.end;
		}
		// checking if otherInterval.start contains this->start to set start & end of the cut
		else if (otherInterval.start < this->start && otherInterval.contains(this->start)) {
			newStart = start;
			if (otherInterval.end < this->end)
				newEnd = otherInterval.end;
			else
				newEnd = end;
		}
		// if start is equal, checks who is the end of the cut
		else if (start == otherInterval.start) {
			newStart = start;
			if (this->contains(otherInterval.end))
				newEnd = otherInterval.end;
			else
				newEnd = end;
		}
	}
	// returns an interval of the cut between this & otherInterval
	return Interval(newStart, newEnd);
}

// Output
template <typename T>
void Interval<T>::print(ostream& out) const {
	if (!isEmpty()) {
		if (this->start > this->end) {
			cout << "Invalid interval";
			return;
		}
		else { // prints the interval
			cout << '(' << this->start << ", " << this->end << ')';
			return;
		}
	}
	// if the interval is empty i.e. (0,0)
	cout << "EMPTY";
}

#endif // !INTERVAL_H

