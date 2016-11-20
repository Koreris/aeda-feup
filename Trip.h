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
	string vehicleOwner;
	Vehicle vehicle;
	unsigned int available_seats;
	float distance;
	vector<pair<Place *,int>> route;
	vector<pair<Person *,vector<Place*>>> travellers;
	bool smoking_allowed;

	Date start;
	Date end;
public:
	Trip();
	Trip(string VehicleOwner,Vehicle vehicle, bool smoke, Date s, Date e);
	~Trip();

	unsigned int getAvailableSeats() const;
	float getDistance() const;
	vector<pair<Place *,int>> getRoute() const;
	bool getSmokingSign() const;
	Date getStart() const;
	Date getEnd() const;
	vector<Person *> getTravellers() const;
	string getDriver() const;
	Vehicle getVehicle() const;

	void setAvailableSeats(unsigned int a_s);
	void setVehicle(Vehicle * v);
	void setDistance(float d);
	void setSmokingSign(bool s);
	void setStart(Date s);
	void setEnd(Date e);
	void addRoute(vector<pair<Place*,int>>);
	void calculateDistance(Place * begin, Place * end); //call upon addingRoute

	 /*
		Must be called if changeTravellerRoute or addTraveller or removeTraveller is called,
		goes through travellers vector and changes available
		seats for each place in route vector
	*/
	void recalculateRouteSeats();

	//CRUD for travellers participating in trip
	void addTraveller(Person * t,vector<Place *>);
	void removeTraveller(Person * t,vector<Place *>);
	void updateTravellerRoute(Person *,vector<Place *>);

    stringstream toString();
};

#endif //TRIP_H_
