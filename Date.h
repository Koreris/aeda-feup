#include "includes.h"
#include <cmath>
#include <ctime>
#include <chrono>

class Date
{
private:
	unsigned int hour, minute, day, month, year;
public:
	Date();
	Date(unsigned int h, unsigned int min, unsigned int d, unsigned int m, unsigned int y);
	~Date();

	unsigned int getHour() const;
	unsigned int getMin() const;
	unsigned int getDay() const;
	unsigned int getMonth() const;
	unsigned int getYear() const;

	void setHour(unsigned int h);
	void setMin(unsigned int min);
	void setDay(unsigned int d);
	void setMonth(unsigned int m);
	void setYear(unsigned int y);

	//TODO - we'll prolly need operator overloading
};
