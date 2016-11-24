#ifndef DATE_H_
#define DATE_H_

#include "includes.h"
#include <cmath>
#include <ctime>

using namespace std;

long stol(string txt);

/**
 * @brief Date class
 *
 *  * A date object consists of basically 6 integers, which hold the year, month, day, hour, minute and second.\n
 * It has the necessary member functions for handling those variables, compare dates, and misc functions.
 */
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
	/** @name Constructors
	 */
	///@{
	Date();
	Date(string cfg_str);
	Date(int year, int month, int day, int hour, int minute, int second);
	///@}
	/** @name Getters
	*/
	///@{
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	int getHour() const;
	int getMinute() const;
	int getSecond() const;
	///@}
	/** @name Setters
	*/
	///@{
	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);
	void setHour(int hour);
	void setMinute(int minute);
	void setSecond(int second);
	///@}

	/** @name Operator overloads
	 */
	///@{
	bool operator<(Date date2) const;
	bool operator>(Date date2) const;
	bool operator==(Date date2) const;
	friend ostream& operator<<(ostream& os, const Date& d);
	friend istream& operator>>(istream &is, Date& date);
	///@}

	string str() const;
	string cfg_str() const;


	/** @name Static functions
	 */
	///@{
	static int daysInMonth(int month, int year);
	static bool isLeapYear(int year);
	static Date curDate();
	static int numDays(Date d1, Date d2);
	///@}

	/** @name Exceptions
	 */
	///@{
	class InvalidDate
	{
	public:
		InvalidDate()
	{
	}
	};
	///@}
};

#endif //_DATE_H_
