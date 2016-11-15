#include "includes.h"
#include "Date.h"

class Trip
{
private:
	unsigned int available_seats;
	float distance;
	string from_point;
	string to_point;
	vector<string> route;
	vector<Person *> travellers;
	bool smoking_allowed;

	Date start;
	Date end;

public:
	Trip();
	Trip(unsigned int a_s, float d, string f_p, string t_p, bool smoke, Date s, Date e);
	~Trip();

	unsigned int getAvailableSeats() const;
	float getDistance() const;
	string getFromPoint() const;
	string getToPoint() const;
	vector<string> getRoute() const;
	vector<Person *> getTravellers() const;
	bool getSmokingSign() const;
	Date getStart() const;
	Date getEnd() const;

	void setAvailableSeats(unsigned int a_s);
	void setDistance(float d);
	void setFromPoint(string f_p);
	void setToPoint(string t_p);
	void setSmokingSign(bool s);
	void setStart(Date s);
	void setEnd(Date e);
};
