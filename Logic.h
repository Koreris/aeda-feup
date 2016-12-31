#ifndef LOGIC_H_
#define LOGIC_H_


#include "includes.h"
#include "Date.h"
#include "Person.h"
#include "Place.h"
#include "Trip.h"
#include "Vehicle.h"
#include "VehicleWrapper.h"

using namespace std;

const string CFG_FILE_REGUSERS = "RegUsers.txt";
const string CFG_FILE_DEL_REGUSERS = "DelRegUsers.txt";
const string CFG_FILE_DESTINATIONS = "Destinations.txt";
const string CFG_FILE_DEL_DESTINATIONS = "DelDestinations.txt";
const string CFG_FILE_CURTRIPS = "Trips.txt";
const string CFG_FILE_DELTRIPS = "DelTrips.txt";

/**
 * @brief Logic class
 *
 * Contains all of the programs main information(including login stuff),
 * functioning as a sort of database having utilities to filter
 * information in different ways and methods to look up
 * data in the vectors with conditions.
 * Contains all the methods that read data from files.
 */
class Logic
{
private:
	vector<RegPerson *> regUsers;
	vector<Place *> destinations;
	vector<Place *> del_destinations;
	vector<Trip *> cur_trips;
	vector<Trip *> del_trips;
	BST<VehicleWrapper> bst_vehicles;

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
	bool login;
	RegPerson* curr_user;
	UnregPerson* curr_unreg;

	/** @name Getters
	*/
	///@{

	Date get_curDate() const;
	vector<Trip*>& getCurTrips ();
	vector<Place*>& getDelDestinations ();
	vector<Trip*>& getDelTrips ();
	vector<Place*>& getDestinations ();
	vector<RegPerson*>& getRegUsers ();
	BST<VehicleWrapper>& getBST();

	///@}

	/** @name Setters
	*/
	///@{
	void setDestinations (vector<Place*>& destinations);
	void setDelTrips (vector<Trip*>& delTrips);
	void setDelDestinations (vector<Place*>& delDestinations);
	void setCurTrips (vector<Trip*>& curTrips);
	void setRegUsers (vector<RegPerson*>& regUsers);
	void setLogin(bool p);

	void deleteDestinations(int index);
	void deleteTrips(int index);
	bool userLogin(string usr, string passw);
	///@}


	/** @name Lookups
	*/
	///@{
	RegPerson * findRegPerson (string username);
	vector<RegPerson *> findRegPersonVec (string username);
	vector<Trip *> findTrips(string src, string dest,Person*p);
	vector<Trip *> findFutureTrips(Person * p);
	vector<Trip *> findVacantTrips(Person * p);
	Place * findDest(string destname, string f="");
	bool usernameExists(string n);
	bool isUniqueLicensePlate(string n_lp);
	///@}

	/** @name sorting
	 */
	///@{
	vector<Trip *> tripSortByDate(vector<Trip*>v);
	vector<Trip *> tripSortByDriverName(vector<Trip*>v);
	///@}

	/** @name File loading
	 */
	///@{
	int load_regUsers();
	//int load_del_regUsers();
	int load_destinations();
	int load_del_destinations();
	int load_trips();
	int load_data();
	///@}

	/** @name Saving to file
	 */
	///@{
	int save_regUsers();
	//int save_del_regUsers();
	int save_destinations();
	int save_del_destinations();
	int save_trips() const;
	int save_data();
	///@}
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






#endif //LOGIC_H_
