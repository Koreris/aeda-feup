#include "Date.h"

Date::Date()
{
	hour=0;
	minute=0;
	day=1;
	month=1;
	year=2016;
}

Date::Date(unsigned int h, unsigned int min, unsigned int d, unsigned int m, unsigned int y)
{
	hour=h;
	minute=min;
	day=d;
	month=m;
	year=y;
}

Date::~Date()
{
}

//getters
unsigned int Date::getHour() const
{
	return hour;
}

unsigned int Date::getMin() const
{
	return minute;
}

unsigned int Date::getDay() const
{
	return day;
}

unsigned int Date::getMonth() const
{
	return month;
}

unsigned int Date::getYear() const
{
	return year;
}

//setters
void Date::setHour(unsigned int h)
{
	hour=h;
}

void Date::setMin(unsigned int min)
{
	minute=min;
}

void Date::setDay(unsigned int d)
{
	day=d;
}

void Date::setMonth(unsigned int m)
{
	month=m;
}

void Date::setYear(unsigned int y)
{
	year=y;
}
