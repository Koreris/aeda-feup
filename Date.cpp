#include "Date.h"

/**
* Doesn't have error checking, assumes the string contains only digits and a possible minus sign in the beggining.
* @brief Converts string to long
* @param txt string to convert
* @return long with the value
*/
long stol(string txt)
{
	stringstream ss(txt);
	long num { };
	ss >> num;

	return num;
}

/**
 * This constructor leads to an invalid date, not possible with setters or the other constructors because of the exceptions
 * @brief Invalid Date empty constructor
 */
Date::Date()
{
	year = -1;
	month = -1;
	day = -1;
	hour = -1;
	minute = -1;
	second = -1;
}
/**
 * This constructor makes a date object out of a properly formatted string
 * @brief Constructor to make date object out of string
 * @param cfg_str formatted string to make a Date object
 */
Date::Date(string cfg_str)
{
	cfg_str += "\n";
	stringstream ss(cfg_str);

	string temp;

	getline(ss, temp, ' ');
	year = stol(temp);

	getline(ss, temp, ' ');
	month = stol(temp);

	getline(ss, temp, ' ');
	day = stol(temp);

	getline(ss, temp, ' ');
	hour = stol(temp);

	getline(ss, temp, ' ');
	minute = stol(temp);

	getline(ss, temp, ' ');
	second = stol(temp);

	if (year < 1900)
		throw InvalidDate();
	if (month < 1 || month > 12)
		throw InvalidDate();
	if (day < 1 || day > daysInMonth(month, year))
		throw InvalidDate();
	if (hour < 0 || hour > 23)
		throw InvalidDate();
	if (minute < 0 || minute > 59)
		throw InvalidDate();
	if (second < 0 || second > 59)
		throw InvalidDate();
}
/**
 * Throws an appropriate exception if any of the parameters are invalid
 * @brief Valid Date constructor
 *
 * @param year Year
 * @param month Month
 * @param day Day
 * @param hour Hour
 * @param minute Minute
 * @param second Second
 */
Date::Date(int year, int month, int day, int hour, int minute, int second)
{
	if (year < 1900)
		throw InvalidDate();
	if (month < 1 || month > 12)
		throw InvalidDate();
	if (day < 1 || day > daysInMonth(month, year))
		throw InvalidDate();
	if (hour < 0 || hour > 23)
		throw InvalidDate();
	if (minute < 0 || minute > 59)
		throw InvalidDate();
	if (second < 0 || second > 59)
		throw InvalidDate();

	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}

// Getters
/**
 * @brief Returns the year
 *
 * @return integer with the year
 */
int Date::getYear() const
{
	return this->year;
}
/**
 * @brief Returns the month
 *
 * @return integer with the month
 */
int Date::getMonth() const
{
	return this->month;
}
/**
 * @brief Returns the day
 *
 * @return integer with the day
 */
int Date::getDay() const
{
	return this->day;
}
/**
 * @brief Returns the hour
 *
 * @return integer with the hour
 */
int Date::getHour() const
{
	return this->hour;
}
/**
 * @brief Returns the minute
 *
 * @return integer with the minute
 */
int Date::getMinute() const
{
	return this->minute;
}
/**
 * @brief Returns the second
 *
 * @return integer with the second
 */
int Date::getSecond() const
{
	return this->second;
}

// Setters

/**
 * Throws InvalidDate exception if the year is invalid
 * @brief Sets the year
 *
 * @param year Year
 */
void Date::setYear(int year)
{
	if (year < 1900)
		throw InvalidDate();

	this->year = year;
}

/**
 * Throws InvalidDate exception if the month is invalid
 * @brief Sets the month
 *
 * @param month Month
 */
void Date::setMonth(int month)
{
	if (month < 1 || month > 12)
		throw InvalidDate();

	this->month = month;
}

/**
 * Throws InvalidDate exception if the day is invalid
 * @brief Sets the day
 *
 * @param day Day
 */
void Date::setDay(int day)
{
	if (day < 1 || day > daysInMonth(month, year))
		throw InvalidDate();

	this->day = day;
}

/**
 * Throws InvalidDate exception if the hour is invalid
 * @brief Sets the hour
 *
 * @param hour Hour
 */
void Date::setHour(int hour)
{
	if (hour < 0 || hour > 23)
		throw InvalidDate();

	this->hour = hour;
}

/**
 * Throws InvalidDate exception if the minute is invalid
 * @brief Sets the minute
 *
 * @param minute Minute
 */
void Date::setMinute(int minute)
{
	if (minute < 0 || minute > 59)
		throw InvalidDate();

	this->minute = minute;
}

/**
 * Throws InvalidDate exception if the second is invalid
 * @brief Sets the second
 *
 * @param second Second
 */
void Date::setSecond(int second)
{
	if (second < 0 || second > 59)
		throw InvalidDate();

	this->second = second;
}

// Operator overloads
/**
 * @brief Less than operator
 *
 * @param date2 Right hand side date
 * @return Returns true if left hand side date is previous in time from the right hand side one, false otherwise.
 */
bool Date::operator<(Date date2) const
{
	if (this->year < date2.year)
		return true;
	else if (this->year > date2.year)
		return false;
	else if (this->month < date2.month)
		return true;
	else if (this->month > date2.month)
		return false;
	else if (this->day < date2.day)
		return true;
	else if (this->day > date2.day)
		return false;
	else if (this->hour < date2.hour)
		return true;
	else if (this->hour > date2.hour)
		return false;
	else if (this->minute < date2.minute)
		return true;
	else if (this->minute > date2.minute)
		return false;
	else if (this->second < date2.second)
		return true;
	else
		return false;
}
/**
 * @brief Greater than operator
 *
 * @param date2 Right hand side date
 * @return Returns true if left hand side date is after the right hand side one in time, false otherwise.
 */
bool Date::operator>(Date date2) const
{
	if (this->year > date2.year)
		return true;
	else if (this->year < date2.year)
		return false;
	else if (this->month > date2.month)
		return true;
	else if (this->month < date2.month)
		return false;
	else if (this->day > date2.day)
		return true;
	else if (this->day < date2.day)
		return false;
	else if (this->hour > date2.hour)
		return true;
	else if (this->hour < date2.hour)
		return false;
	else if (this->minute > date2.minute)
		return true;
	else if (this->minute < date2.minute)
		return false;
	else if (this->second > date2.second)
		return true;
	else
		return false;
}
/**
 * @brief Equal comparison operator
 *
 * @param date2 Right hand side date
 * @return Returns true if the dates are the same, false otherwise
 */
bool Date::operator== (Date date2) const
{
	return (year == date2.year && month == date2.month && day == date2.day && hour == date2.hour && minute == date2.minute && second == date2.second);
}
/**
 * Sends to the output stream the string with the date, returned by cfg_str()
 * @brief Bitshift operator <<
 * @param os left hand side output stream
 * @param d right hand side date
 * @return the output stream os
 */
ostream& operator<<(ostream& os, const Date& d)
{
	return os << d.cfg_str();
}
/**
 * Reads a date from the input stream is in the format YYYY MM DD hh mm ss
 * @brief Bitshift operator >>
 * @param is left hand side input stream
 * @param date right hand side date
 * @return the input stream is
 */
istream& operator >>(istream &is, Date& date)
{
	char c1 { ' ' };
	int year { };
	int month { };
	int day { };
	int hour { };
	int minute { };
	int second { };

	is >> year >> c1 >> month >> c1 >> day >> c1 >> hour >> c1 >> minute >> c1 >> second;

	Date d(year, month, day, hour, minute, second);

	date = d;

	return is;
}
/**
 * Returns a string with a date in the format YYYY/MM/DD - hh:mm:ss
 * @brief Formatted date string
 *
 * @return a string with the formatted date
 */
string Date::str() const
{
	stringstream ss;

	ss << year << "/" << month << "/" << day << " - " << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute << ":"  << setfill('0')<< setw(2) << second;

	return ss.str();
}
/**
 * Returns a string in the format YYYY MM DD hh mm ss to be used in the config file
 * @brief Space separated date
 * @return a string with the date
 */
string Date::cfg_str() const
{
	stringstream ss;

	ss << year << " " << month << " " << day << " " << hour << " " << minute << " " << second;

	return ss.str();
}

/// Static function
/**
 * Returns the number of days in a month, taking into account if it is a leap year or not
 * @brief Number of days in a month
 * @param month month (1-12)
 * @param year year
 * @return number of days
 */
int Date::daysInMonth(int month, int year)
{
	if (month == 4 || month == 6 || month == 9 || month == 11)
		return 30;
	else if (month == 2) {
		if (isLeapYear(year))
			return 29;
		else
			return 28;
	} else
		return 31;
}

/**
 * @brief Checks if year is leap year
 * @param year year
 * @return true if it is leap year, false otherwise
 */
bool Date::isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * Returns a date with the current computer local date and time
 * @brief Current local date and time
 * @return date corresponding to the current date
 */
Date Date::curDate()
{
	time_t t = time(0); // Get current time
	struct tm *t_now = localtime(&t);

	int year { t_now->tm_year + 1900 };
	int month { t_now->tm_mon + 1 };
	int day { t_now->tm_mday };
	int hour { t_now->tm_hour };
	int minute { t_now->tm_min };
	int second { t_now->tm_sec };

	Date temp(year, month, day, hour, minute, second);

	return temp;
}
/**
 * Returns the number of days difference between two dates
 * @brief Number of days difference between two dates
 * @param d1 a date
 * @param d2 a date
 * @return number of days
 */
int Date::numDays(Date d1, Date d2)
{
	if (d1.getYear() == d2.getYear())
	{ //same year?
		if (d1.getMonth() == d2.getMonth())
		{  //same month?
			if (d1.getDay() > d2.getDay())
			{ //same month
				return d1.getDay() - d2.getDay();
			} else
				return d2.getDay() - d1.getDay();
		} else
		{ //different month
			int somadaysbetweenmonths { 0 };
			if (d1.getMonth() > d1.getMonth())
			{
				for (int i = d2.getMonth() + 1;
						i < (d1.getMonth() - d2.getMonth()) + d2.getMonth(); i++)
				{
					somadaysbetweenmonths = somadaysbetweenmonths
							+ Date::daysInMonth(i, d1.getYear());
				}
				return somadaysbetweenmonths
						+ (Date::daysInMonth(d1.getMonth(), d1.getYear()) - d1.getDay())
						+ d2.getDay();
			} else
			{
				for (int i = d1.getMonth() + 1;
						i < (d2.getMonth() - d1.getMonth()) + d1.getMonth(); i++)
				{
					somadaysbetweenmonths = somadaysbetweenmonths
							+ Date::daysInMonth(i, d2.getYear());
				}
				return somadaysbetweenmonths
						+ (Date::daysInMonth(d2.getMonth(), d2.getYear()) - d2.getDay())
						+ d1.getDay();
			}
		}
	} else
	{
		Date date1(d1);
		Date date2(d2);

		if (d1.getYear() > d2.getYear())
		{
			Date date3(d2);
			date2 = d1;
			date1 = date3;
		}


		int days { Date::daysInMonth(date1.getMonth(), date1.getYear())
				- date1.getDay() };


		for (unsigned int i = date1.getMonth() + 1; i <= 12; i++)
		{
			days += Date::daysInMonth(i, date1.getYear());
		}


		for (int i = date1.getYear() + 1; i < date2.getYear(); i++)
		{
			if (Date::isLeapYear(i))
				days += 366;
			else
				days += 365;
		}


		for (int i = 1; i < date2.getMonth(); i++)
		{
			days += Date::daysInMonth(i, date2.getYear());
		}


		days += date2.getDay();

		return days;
	}
}

