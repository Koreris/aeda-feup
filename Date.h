#pragma once
#include "includes.h"
#include <cmath>
#include <ctime>
#include <chrono>
#include <time>

class Date
{
private:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

public:
	Date();
	Date(string cfg_str);
	Date(int year, int month, int day, int hour, int minute, int second);

	int getYear() const;
	int getMonth() const;
	int getDay() const;
	int getHour() const;
	int getMinute() const;
	int getSecond() const;

	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);
	void setHour(int hour);
	void setMinute(int minute);
	void setSecond(int second);

	bool operator<(Date date2) const;
	bool operator>(Date date2) const;
	bool operator==(Date date2) const;
	friend ostream& operator<<(ostream& os, const Date& d);
	friend istream& operator>>(istream &is, Date& date);

	string str() const;
	string cfg_str() const;

	static int daysInMonth(int month, int year);
	static bool isLeapYear(int year);
	static Date curDate();
	static int numDays(Date d1, Date d2);

	class InvalidDate
	{
	public:
		InvalidDate()
	{
	}
	};
};
