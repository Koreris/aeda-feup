#ifndef LOGIC_H_
#define LOGIC_H_


#include "includes.h"
#include "Date.h"
#include "Person.h"
#include "Place.h"
#include "Trip.h"
#include "Vehicle.h"

using namespace std;

const string CFG_FILE_REGUSERS = "RegUsers.txt";
const string CFG_FILE_DEL_REGUSERS = "DelRegUsers.txt";
const string CFG_FILE_DESTINATIONS = "Destinations.txt";
const string CFG_FILE_DEL_DESTINATIONS = "DelDestinations.txt";
const string CFG_FILE_CURTRIPS = "Trips.txt";
const string CFG_FILE_DELTRIPS = "DelTrips.txt";


class Logic
{
private:
	vector<RegPerson *> regUsers;
	vector<Place *> destinations;
	vector<Place *> del_destinations;
	vector<Trip *> cur_trips;
	vector<Trip *> del_trips;
	string cfg_dir;
	string cfg_file_regusers;
	string cfg_file_delregusers;
	string cfg_file_destinations;
	string cfg_file_deldestinations;
	string cfg_file_curtrips;
	string cfg_file_deltrips;
public:
	Logic();

	Logic(string dir);

	RegPerson* curr_user;
	UnregPerson* curr_unreg;

	bool userLogin(string usr, string passw);

	vector<Trip *> tripSortByDate();
	vector<Trip *> tripSortByDriverName();
	vector<Trip *> tripSortByScheduled();

	Date get_curDate() const;

	vector<Trip*>& getCurTrips ();
	void setCurTrips (vector<Trip*>& curTrips);

	vector<Place*>& getDelDestinations ();
	void setDelDestinations (vector<Place*>& delDestinations);

	//vector<Person*>& getDelRegUsers ();
	//void setDelRegUsers (vector<Person*>& delRegUsers);

	vector<Trip*>& getDelTrips ();
	void setDelTrips (vector<Trip*>& delTrips);

	vector<Place*>& getDestinations ();
	void setDestinations (vector<Place*>& destinations);


	vector<RegPerson*>& getRegUsers ();
	void setRegUsers (vector<RegPerson*>& regUsers);

	void deleteDestinations(int index);

	void deleteTrips(int index);

	RegPerson * findRegPerson (string username);
	vector<RegPerson *> findRegPersonVec (string username);
	vector<Trip *> findTrips(string src, string dest);
	vector<Trip *> findFutureTrips(Person * p);
	Place * findDest(string destname, string f="");

	int load_regUsers();
	//int load_del_regUsers();
	int load_destinations();
	int load_del_destinations();
	int load_trips();
	int load_data();
};

/** @name Exceptions
 */
///@{
class CorruptedRegUser {
public:
	CorruptedRegUser() {
	}
};

class CorruptedDestination{
public:
	CorruptedDestination() {
	}
};

class CorruptedDelDestination {
public:
	CorruptedDelDestination() {
	}
};

class CorruptedTrip {
public:
	CorruptedTrip() {
	}
};

class CorruptedDelTrip {
public:
	CorruptedDelTrip() {
	}
};

class SaveFailed {
public:
	SaveFailed() {
	}
};
///@}

vector<Person*>& getRegUsers ();
void setRegUsers (vector<Person*>& regUsers);

void deleteDestinations(int index);





#endif //LOGIC_H_
