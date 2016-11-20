#ifndef LOGIC_H_
#define LOGIC_H_


#include "includes.h"
#include "Date.h"
#include "Person.h"
#include "Place.h"
#include "Trip.h"
#include "Vehicle.h"

using namespace std;


class Logic
{
private:
	vector<Person *> regUsers;
	vector<Person *> del_regUsers;
	vector<Place *> destinations;
	vector<Place *> del_destinations;
	vector<Trip *> cur_trips;
	vector<Trip *> del_trips;

public:
	Logic();
	bool userLogin(string usr, string passw);
	vector<Trip *> findDest(string dest);
	vector<Trip *> tripSortByDate();
	vector<Trip *> tripSortByDriverName();
	vector<Trip *> tripSortByScheduled();

	Date get_curDate() const;

	vector<Trip*>& getCurTrips ();
	void setCurTrips (vector<Trip*>& curTrips);

	vector<Place*>& getDelDestinations ();
	void setDelDestinations (vector<Place*>& delDestinations);

	vector<Person*>& getDelRegUsers ();
	void setDelRegUsers (vector<Person*>& delRegUsers);

	vector<Trip*>& getDelTrips ();
	void setDelTrips (vector<Trip*>& delTrips);

	vector<Place*>& getDestinations ();
	void setDestinations (vector<Place*>& destinations);

	vector<Person*>& getRegUsers ();
	void setRegUsers (vector<Person*>& regUsers);

	void deleteDestinations(int index);
};

#endif //LOGIC_H_
