#ifndef TRIP_H_
#define TRIP_H_

#include "includes.h"
#include "Date.h"
#include "Person.h"
#include "Place.h"

using namespace std;

class Trip
{
private:
	unsigned int available_seats;
	float distance;
	vector<Place *> route;
	vector<Person *> travellers;
	bool smoking_allowed;

	Date start;
	Date end;

public:
	Trip();
	Trip(unsigned int a_s, float d, bool smoke, Date s, Date e);
	~Trip();

	unsigned int getAvailableSeats() const;
	float getDistance() const;
	vector<Place *> getRoute() const;
	vector<Person *> getTravellers() const;
	bool getSmokingSign() const;
	Date getStart() const;
	Date getEnd() const;

	void setAvailableSeats(unsigned int a_s);
	void setDistance(float d);
	void setSmokingSign(bool s);
	void setStart(Date s);
	void setEnd(Date e);
};

#endif //TRIP_H_
