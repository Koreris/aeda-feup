#include "includes.h"
#include "Date.h"
#include "Place.h"
#include "Trip.h"
#include "Vehicle.h"
#include "Logic.h"
#include <algorithm>

using namespace std;
/*
 * @brief default logic constructor
 */
Logic::Logic() :
		bst_vehicles(VehicleWrapper()) {
}
/*
 * @brief logic constructor
 * @param dir directory of where the files for loading will be. Directory must be in same directory as program executable!
 */
Logic::Logic(string dir) :
		bst_vehicles(VehicleWrapper()) {
	if (dir != "")
		dir += "\\";
	cfg_dir = dir;
	cfg_file_regusers = cfg_dir + CFG_FILE_REGUSERS;
	cfg_file_delregusers = cfg_dir + CFG_FILE_DEL_REGUSERS;
	cfg_file_destinations = cfg_dir + CFG_FILE_DESTINATIONS;
	cfg_file_deldestinations = cfg_dir + CFG_FILE_DEL_DESTINATIONS;
	cfg_file_curtrips = cfg_dir + CFG_FILE_CURTRIPS;
	cfg_file_deltrips = cfg_dir + CFG_FILE_DELTRIPS;
	login = false;

}

/**
 * @brief Returns the current date and time
 * @return Date with the current date and time
 */
Date Logic::get_curDate() const {
	return Date::curDate();
}
/**
 * @brief Returns the vector of registered users
 * @return registered users vector
 */
vector<RegPerson*>& Logic::getRegUsers() {
	return regUsers;
}
/**
 * @brief Returns the vector of current trips
 * @return current trips vector
 */
vector<Trip*>& Logic::getCurTrips() {
	return cur_trips;
}
/**
 * @brief Returns the vector of old trips
 * @return old trips vector
 */
vector<Trip*>& Logic::getDelTrips() {
	return del_trips;
}
/**
 * @brief Returns the vector of destinations
 * @return destinations vector
 */
vector<Place*>& Logic::getDestinations() {
	return destinations;
}
/**
 * @brief Returns the vector of deleted destinations
 * @return deleted destinations vector
 */
vector<Place*>& Logic::getDelDestinations() {
	return del_destinations;
}
/**
 * @brief Returns the BST of vehicles
 * @return vehicle BST
 */
BST<VehicleWrapper>& Logic::getBST() {
	return bst_vehicles;
}
/**
 * @brief Returns the Hash Table of inactive users
 * @return inactive users hash
 */
RegHashTable& Logic::getInactiveUsers(){
	return hash_reg;
}
/**
 * @brief Sets current trips vector
 * @param Reference to vector of Trip *
 */
void Logic::setCurTrips(vector<Trip*>& curTrips) {
	cur_trips = curTrips;
}
/**
 * @brief Sets deleted trips vector
 * @param Reference to vector of Trip *
 */
void Logic::setDelTrips(vector<Trip*>& delTrips) {
	del_trips = delTrips;
}
/**
 * @brief Sets login boolean
 * @param b true or false
 */
void Logic::setLogin(bool b) {
	login = b;
}
/**
 * @brief Sets destinations vector
 * @param Reference to vector of Place *
 */
void Logic::setDestinations(vector<Place*>& destinations) {
	this->destinations = destinations;
}
/**
 * @brief Sets deleted destinations vector
 * @param Reference to vector of Place *
 */
void Logic::setDelDestinations(vector<Place*>& del) {
	del_destinations = del;
}
/**
 * @brief Sets RegUsers vector
 * @param Reference to vector of RegPerson *
 */
void Logic::setRegUsers(vector<RegPerson*>& regUsers) {
	this->regUsers = regUsers;
}

/**
 * Receives user and password combination and validates them, updates last login attribute and removes user from inactive users
 * if he was previously inactive for over 30 days
 * @brief Receives user and password combination and validates them
 * @param usr username to validate
 * @param passw password to validates
 * @return returns true if it found the user/password combination in registered users, false otherwise
 */
bool Logic::userLogin(string usr, string passw) {
	for (int i = 0; i < regUsers.size(); i++) {
		if (regUsers[i]->getUsern() == usr
				&& regUsers[i]->getPassw() == passw) {
			curr_user = regUsers[i];
			if(Date::numDays(regUsers[i]->getLastLogin(),get_curDate())>30){
				RegHashTable::iterator it = hash_reg.find(regUsers[i]);
				if (it != hash_reg.end()) {
					hash_reg.erase(regUsers[i]);
				}
			}
			regUsers[i]->setlastLogin(get_curDate());
			UnregPerson* curr_unreg = NULL;
			cout << "Logged in with User: " << regUsers[i]->getUsern() << endl;
			setLogin(true);
			return true;
		}
	}
	cout << "User not found " << endl;
	return false;
}
/**
 * @brief Deletes destination in index of destinations vector and puts it in deleted destinations
 * @param index index of destination to delete
 */
void Logic::deleteDestinations(int index) {
	if (index < 0 || index >= destinations.size()) {
		cout << "Invalid index chosen" << endl;
		return;
	}

	vector<Place *>::iterator it = destinations.begin();

	while (it != destinations.end() && index != 0) {
		it++;
		index--;
	}
	del_destinations.push_back(destinations[index]);
	this->destinations.erase(it);
}
/**
 * @brief Deletes trip in index of current trips vector and puts it in deleted trips
 * @param index index of trip to delete
 */
void Logic::deleteTrips(int index) {
	if (index < 0 || index >= cur_trips.size()) {
		cout << "Invalid index chosen" << endl;
		return;
	}

	vector<Trip *>::iterator it = cur_trips.begin();

	while (it != cur_trips.end() && index != 0) {
		it++;
		index--;
	}
	del_trips.push_back(cur_trips[index]);
	this->cur_trips.erase(it);
}

/**
 * Sorts vector of trips by date
 * @brief sort trips by date
 * @return vector of trips
 */
vector<Trip *> Logic::tripSortByDate(vector<Trip *> v) {
	sort(v.begin(), v.end(), Trip::compareTrips);
	return v;
}
/**
 * Sorts vector of trips by driver name
 * @brief sort trips by driver name
 * @return vector of trips
 */
vector<Trip *> Logic::tripSortByDriverName(vector<Trip *> v) {
	sort(v.begin(), v.end(), Trip::compareTripsDriverName);
	return v;
}

/**
 * @brief checks is username exists
 * @param n username to check
 * @return true if username n exists, false otherwise
 */
bool Logic::usernameExists(string n) {
	for (unsigned int i = 0; i < regUsers.size(); i++) {
		if (regUsers[i]->getUsern() == n)
			return true;
	}
	return false;
}
/**
 * Finds all the trips with vacancies that have a possible itenerary starting from place src and going through or ending in place dest,
 * also only returns trips where youre not a traveller or a driver
 * @param src source destination
 * @param dest target destination
 * @param p Needed to check if already a traveller or driver in this trip
 * @brief finds trips with vacancies by giving start location and end location
 * @return vector of trips, empty if no trips found
 */
vector<Trip *> Logic::findTrips(string src, string dest, Person* p) {
	vector<Trip *> temp = vector<Trip *>();
	for (int i = 0; i < cur_trips.size(); i++) {
		if (cur_trips[i]->hasDestination(src, dest)) {
			if (!cur_trips[i]->isFull(src, dest))
				if (!cur_trips[i]->isTraveller(p))
					if (cur_trips[i]->getDriver() != p->getUsern())
						temp.push_back(cur_trips[i]);
		}
	}
	return temp;
}
/**
 * Finds all the trips with vacancies
 * returns trips where youre not already a traveller or a driver
 * @param p Needed to check if already a traveller or driver in this trip
 * @brief finds trips with vacancies
 * @return vector of trips, empty if no trips found
 */
vector<Trip *> Logic::findVacantTrips(Person* p) {

	vector<Trip *> temp = vector<Trip *>();
	for (unsigned int i = 0; i < cur_trips.size(); i++) {
		if (!cur_trips[i]->isFull(cur_trips[i]->getRoute()[0].first->getName(),
				cur_trips[i]->getRoute()[cur_trips[i]->getRoute().size() - 1].first->getName()))
			if (!cur_trips[i]->isTraveller(p))
				if (cur_trips[i]->getDriver() != p->getUsern())
					temp.push_back(cur_trips[i]);
	}

	return temp;
}
/**
 * Finds all the trips scheduled for user P
 * @brief find scheduled trips
 * @return vector of trips, empty if no trips found
 */
vector<Trip *> Logic::findFutureTrips(Person * p) {
	vector<Trip *> temp = vector<Trip *>();
	for (int i = 0; i < cur_trips.size(); i++) {
		if (cur_trips[i]->isTraveller(p)) {
			temp.push_back(cur_trips[i]);
		}
		if (cur_trips[i]->getDriver() == ((RegPerson*) p)->getUsern()) {
			temp.push_back(cur_trips[i]);
		}
	}
	return temp;
}
/**
 * Finds RegPerson pointer of user with username
 * @brief find a RegPerson by username
 * @return pointer to the RegPerson,NULL if not found
 */
RegPerson * Logic::findRegPerson(string username) {
	for (int i = 0; i < regUsers.size(); i++) {
		if (regUsers[i]->getUsern() == username)
			return regUsers[i];
	}
	return NULL;
}
/**
 * Finds RegPerson pointer of user with username
 * @brief find a RegPerson by username
 * @return vector with RegPerson or empty vector  if not found
 */
vector<RegPerson *> Logic::findRegPersonVec(string username) {
	vector<RegPerson *> temp = vector<RegPerson *>();
	for (int i = 0; i < regUsers.size(); i++) {
		if (regUsers[i]->getUsern() == username) {
			temp.push_back(regUsers[i]);
			return temp;
		}
	}
	return temp;
}
/**
 * Finds Place* of name destname
 * @brief find a RegPerson by username
 * @param destname The place name
 * @param f optional argument, if "loading", gets destinations from deleted destinations
 * @return pointer to the found place or NULL if not found
 */
Place * Logic::findDest(string destname, string f) {
	for (int i = 0; i < destinations.size(); i++) {
		if (destinations[i]->getName() == destname)
			return destinations[i];
	}
	if (f == "loading")
		for (int i = 0; i < del_destinations.size(); i++) {
			if (del_destinations[i]->getName() == destname)
				return del_destinations[i];
		}
	return NULL;
}
/**
 * @brief check if license plate already exists
 * @param n_lp license plate to check
 * @return true if unique license plate, false otherwise
 */
bool Logic::isUniqueLicensePlate(string n_lp) {
	if (n_lp == "-1")
		return false;

	for (int i = 0; i < regUsers.size(); i++) {
		vector<Vehicle *> usr_v = regUsers[i]->getVehicles();

		for (int j = 0; j < usr_v.size(); j++) {
			if (usr_v.at(j)->getLicensePlate() == n_lp) {
				return false;
			}
		}
	}
	return true;
}


/**
 * @brief Lists all the regPerson objects in the hash_reg HashTable
 *
 * Used in the RegHashTable.
 */
void Logic::printHash(){
	tr1::unordered_set<RegPerson*,hstr,eqstr>::iterator it = hash_reg.begin();
	   while (it!=hash_reg.end()) {
	       ((RegPerson*)*it)->printPersonAdmin();
	       it++;
	   }
}


/**
 * Loads RegPerson data members from file and creates RegPerson * objects
 * to push_back into the applications vector of registered users
 * Will add inactive users to hashtable (users who havent logged in for over 30 days)
 * Will add vehicles to the BST
 * @brief loads RegPerson objects from file
 * @return 0 on success, -1 otherwise
 */
int Logic::load_regUsers() {
	ifstream fin;
	stringstream ss;

	// -------------------
	// RegUsers file
	// -------------------

	fin.open(cfg_file_regusers.c_str());

	if (fin.fail()) {
		cout << "Opening file failed " << cfg_file_regusers.c_str() << endl;
		return -1;
	} else {
		string line;

		string key = "";
		string value = "";

		string name = "";
		unsigned long phone = -1;
		string username = "";
		string password = "";
		string address = "";
		string lastLogin = "";
		vector<Vehicle *> userVehicle = vector<Vehicle *>();

		//vehicle stuff
		string owner = "";
		string type = "";
		string brand = "";
		string model = "";
		unsigned short int year = -1;
		string license_plate = "";
		unsigned long seats = -1;

		while (!fin.eof()) {
			getline(fin, line);
			if (line == "[RegUser]") {
				name = "";
				phone = -1;
				lastLogin = "";
				userVehicle.clear();
				username = "";
				password = "";
				address = "";
			} else if (line == "[/RegUser]") {

				try {
					Date last_login(lastLogin);
				} catch (Date::InvalidDate &d) {
					cout << "Invalid login Date in file" << endl;
					throw CorruptedRegUser();
				}

				Date login_date(lastLogin);
				if (name == "" || phone == -1 || username == ""
						|| password == "")
					throw CorruptedRegUser();
				RegPerson *user = new RegPerson(name, address, phone, username,
						password, login_date);
				int nrDays = Date::numDays(login_date, get_curDate());
				if ( nrDays > 30) {
					hash_reg.insert(user);
				}
				for (int i = 0; i < userVehicle.size(); i++) {
					user->getVehicles().push_back(userVehicle[i]);
				}
				regUsers.push_back(user);
				regUsers[regUsers.size() - 1]->printPerson();
			} else if (line == "[Vehicle]") {
				owner = "";
				type = "";
				brand = "";
				model = "";
				year = -1;
				license_plate = "";
				unsigned long seats = -1;
			} else if (line == "[/Vehicle]") {
				if (owner == "" || type == "" || brand == "" || model == ""
						|| year == -1 || license_plate == "" || seats == -1)
					throw CorruptedRegUser();
				Vehicle *v = new Vehicle(owner, type, brand, model, year,
						license_plate, seats);
				bst_vehicles.insert(v);
				userVehicle.push_back(v);
			}

			else {
				ss.str("");
				ss.str(line + "\n");
				getline(ss, key, '=');
				getline(ss, value);

				if (key == "name")
					name = value;
				else if (key == "phone")
					phone = stol(value);
				else if (key == "username")
					username = value;
				else if (key == "password")
					password = value;
				else if (key == "address")
					address = value;
				else if (key == "owner")
					owner = value;
				else if (key == "brand")
					brand = value;
				else if (key == "model")
					model = value;
				else if (key == "year")
					year = stol(value);
				else if (key == "plate")
					license_plate = value;
				else if (key == "seats")
					seats = stol(value);
				else if (key == "type")
					type = value;
				else if (key == "lastLogin")
					lastLogin = value;
			}
		}
	}
	fin.close();
	return 0;
}
/**
 * Loads place data members from file and creates Place * objects
 * to push_back into the applications vector of destinations
 * @brief loads Place objects from file
 * @return 0 on success, -1 otherwise
 */
int Logic::load_destinations() {
	ifstream fin;
	stringstream ss;

	// -------------------
	// Destinations file
	// -------------------

	fin.open(cfg_file_destinations.c_str());

	if (fin.fail()) {
		cout << "Opening file failed " << cfg_file_destinations.c_str() << endl;
		return -1;
	} else {
		string line;

		string key = "";
		string value = "";

		string name = "";
		int x = -1;
		int y = -1;

		while (!fin.eof()) {
			getline(fin, line);
			if (line == "[Place]") {
				name = "";
				x = -1;
				y = -1;
			} else if (line == "[/Place]") {
				if (name == "" || x == -1 || y == -1)
					throw CorruptedDestination();

				pair<int, int> coord(x, y);
				Place *pl = new Place(name, coord);
				destinations.push_back(pl);
				cout << destinations[destinations.size() - 1]->toString()
						<< endl;
			} else {
				ss.str("");
				ss.str(line + "\n");
				getline(ss, key, '=');
				getline(ss, value);

				if (key == "name")
					name = value;
				else if (key == "x")
					x = stol(value);
				else if (key == "y")
					y = stol(value);

			}
		}
	}

	fin.close();
	return 0;

}
/**
 * Loads place data members from file and creates Place * objects
 * to push_back into the applications vector of deleted destinations
 * These deleted destinations are useful to mantain integrity of trip history
 * for each user in case a Place entry is deleted by the application admnistration
 * @brief loads "deleted" Place objects from file
 * @return 0 on success, -1 otherwise
 */
int Logic::load_del_destinations() {
	ifstream fin;
	stringstream ss;

	// -------------------
	// Destinations file
	// -------------------

	fin.open(cfg_file_deldestinations.c_str());

	if (fin.fail()) {
		cout << "Opening file failed " << cfg_file_deldestinations.c_str()
				<< endl;
		return -1;
	} else {
		string line;

		string key = "";
		string value = "";

		string name = "";
		int x = -1;
		int y = -1;

		while (!fin.eof()) {
			getline(fin, line);
			if (line == "[DelPlace]") {
				name = "";
				x = -1;
				y = -1;
			} else if (line == "[/DelPlace]") {
				if (name == "" || x == -1 || y == -1)
					throw CorruptedDelDestination();

				pair<int, int> coord(x, y);
				Place *pl = new Place(name, coord);
				del_destinations.push_back(pl);
				cout
						<< del_destinations[del_destinations.size() - 1]->toString()
						<< endl;
			} else {
				ss.str("");
				ss.str(line + "\n");
				getline(ss, key, '=');
				getline(ss, value);

				if (key == "name")
					name = value;
				else if (key == "x")
					x = stol(value);
				else if (key == "y")
					y = stol(value);

			}
		}
	}

	fin.close();
	return 0;
}
/**
 * Loads trip data members from file and creates Trip * objects
 * to push_back into the applications vector of trips, if the trip's
 * start date is lower than the current date, it will be added into the
 * deleted trips vector instead and push_backed into the vector of tripHistory
 * of the participants  of said trip
 * @brief loads Trip objects from file
 * @return 0 on success, -1 otherwise
 */
int Logic::load_trips() {
	ifstream fin;
	stringstream ss;

	// -------------------
	// Trips file
	// -------------------

	fin.open(cfg_file_curtrips.c_str());

	if (fin.fail()) {
		cout << "Opening file failed " << cfg_file_curtrips.c_str() << endl;
		return -1;
	} else {
		string line;

		string key = "";
		string value = "";

		string vehicleowner = "";
		string plate = "";
		unsigned long seats = -1;
		string place = "";
		bool smoking = false;
		string beginDate = "";
		string endDate = "";

		vector<pair<Place *, int> > route = vector<pair<Place *, int> >();

		Person * driverP;
		//Traveller stuff
		string tuser = "";
		string tplace = "";
		vector<Place *> tplaces = vector<Place*>();
		vector<pair<Person *, vector<Place *> > > travellers = vector<
				pair<Person *, vector<Place *> > >();

		while (!fin.eof()) {
			getline(fin, line);
			if (line == "[Trip]") {
				plate = "";
				vehicleowner = "";
				seats = -1;
				smoking = false;
				place = "";
				beginDate = "";
				endDate = "";
				route.clear();
				travellers.clear();
			} else if (line == "[/Trip]") {
				if (vehicleowner == "" || plate == "" || seats == -1
						|| route.size() == 0)
					throw CorruptedTrip();
				try {
					Date start_date(beginDate);
				} catch (Date::InvalidDate &d) {
					cout << "Invalid start Date in file" << endl;
					throw CorruptedTrip();
				}

				try {
					Date end_date(endDate);
				} catch (Date::InvalidDate &d) {
					cout << "Invalid  finish in file" << endl;
					throw CorruptedTrip();
				}
				//make dates after confirming they're valid
				Date start_date(beginDate);
				Date end_date(endDate);

				Trip *trip = new Trip(vehicleowner, plate, seats, smoking,
						start_date, end_date);
				trip->addRoute(route);
				if (driverP != NULL) {
					driverP->addTripHistory(trip);
				}
				for (int i = 0; i < travellers.size(); i++) {
					trip->addTraveller(travellers[i].first,
							travellers[i].second);
					travellers[i].first->addTripHistory(trip);

				}

				if (trip->getStart() < get_curDate()) {
					del_trips.push_back(trip);
					cout << "OLD_TRIP:" << trip->toString() << endl;
				} else {
					cur_trips.push_back(trip);
					cout << "CUR_TRIP:" << trip->toString() << endl;
				}
			} else if (line == "[Traveller]") {
				tuser = "";
				tplace = "";
				tplaces.clear();
			} else if (line == "[/Traveller]") {
				if (tuser == "" || tplace == "")
					throw CorruptedTrip();
				Person * passenger;
				if (tuser == "unregistered") {

					passenger = new UnregPerson();
				} else {
					passenger = findRegPerson(tuser);
					if (passenger == NULL) {
						cout << "Invalid traveler: " << tuser << endl;
						throw CorruptedTrip();
					}
				}
				pair<Person *, vector<Place *> > traveler(passenger, tplaces);
				travellers.push_back(traveler);

			}

			else {
				ss.str("");
				ss.str(line + "\n");
				getline(ss, key, '=');
				getline(ss, value);

				if (key == "vehicleOwner") {
					vehicleowner = value;
					driverP = findRegPerson(value);

				} else if (key == "plate")
					plate = value;
				else if (key == "seats")
					seats = stol(value);
				else if (key == "place") {
					place = value;
					Place * p = findDest(value, "loading");
					if (p == NULL) {
						cout << "Invalid place in trips file " << endl;
						throw CorruptedTrip();
					}
					pair<Place *, int> r(p, 0);
					route.push_back(r);
				} else if (key == "tplace") {
					tplace = value;
					Place * p = findDest(value, "loading");
					if (p == NULL) {
						cout << "Invalid place in trips file " << endl;
						throw CorruptedTrip();
					}
					tplaces.push_back(p);
				} else if (key == "smoking") {
					smoking = stol(value);
				}

				else if (key == "begindate")
					beginDate = value;
				else if (key == "finishdate")
					endDate = value;
				else if (key == "traveller")
					tuser = value;
			}
		}
	}

	fin.close();
	return 0;
}
/**
 * Loads all the program information from the files (their names are defined in the top of Logic.h as constants).\n
 * This includes the registeredUsers, destinations(the ones that exist and a record of deleted ones) and trips \n\n
 *
 * @brief Loads all the Program information from files
 * @return 0 upon success, non-zero otherwise
 */
int Logic::load_data() {
	try {
		load_regUsers();
	} catch (CorruptedRegUser& e) {
		return -1;
	}

	try {
		load_destinations();
	} catch (CorruptedDestination& e) {
		return -1;
	}

	try {
		load_del_destinations();
	} catch (CorruptedDelDestination& e) {
		return -1;
	}

	try {
		load_trips();
	} catch (CorruptedTrip& e) {
		return -1;
	}
	return 0;
}

////////////////--fix comments from here

/**
 * Loads RegPerson data members from file and creates RegPerson * objects
 * to push_back into the applications vector of registered users
 * @brief loads RegPerson objects from file
 * @return 0 on success, -1 otherwise
 */
int Logic::save_regUsers() {
	ofstream fout;

	// -------------------
	// RegUsers file
	// -------------------

	fout.open(cfg_file_regusers.c_str());

	if (fout.fail()) {
		cout << "Opening file failed " << cfg_file_regusers.c_str() << endl;
		throw CorruptedRegUser();
	}

	else {
		for (int i = 0; i < regUsers.size(); i++) {
			fout << "[RegUser]\n";
			fout << "name=" << regUsers[i]->getName() << endl;
			fout << "address=" << regUsers[i]->getAddress() << endl;
			fout << "phone=" << regUsers[i]->getTelNr() << endl;
			fout << "username=" << regUsers[i]->getUsern() << endl;
			fout << "password=" << regUsers[i]->getPassw() << endl;
			fout << "lastLogin=" << regUsers[i]->getLastLogin() << endl;
			if (regUsers[i]->getHasVehicle()) {
				for (int j = 0; j < regUsers[i]->getVehicles().size(); j++) {
					fout << "[Vehicle]\n";
					fout << "owner="
							<< regUsers[i]->getVehicles().at(j)->getOwner()
							<< endl;
					fout << "type="
							<< regUsers[i]->getVehicles().at(j)->getType()
							<< endl;
					fout << "brand="
							<< regUsers[i]->getVehicles().at(j)->getBrand()
							<< endl;
					fout << "model="
							<< regUsers[i]->getVehicles().at(j)->getModel()
							<< endl;
					fout << "year="
							<< regUsers[i]->getVehicles().at(j)->getYear()
							<< endl;
					fout << "plate="
							<< regUsers[i]->getVehicles().at(j)->getLicensePlate()
							<< endl;
					fout << "seats="
							<< regUsers[i]->getVehicles().at(j)->getCarSeats()
							<< endl;
					fout << "[/Vehicle]\n";
				}
			}
			fout << "[/RegUser]\n";
		}
	}
	fout.close();
	return 0;
}

/**
 * Loads place data members from file and creates Place * objects
 * to push_back into the applications vector of destinations
 * @brief loads Place objects from file
 * @return 0 on success, -1 otherwise
 */
int Logic::save_destinations() {
	ofstream fout;

	// -------------------
	// Destinations file
	// -------------------

	fout.open(cfg_file_destinations.c_str());

	if (fout.fail()) {
		cout << "Opening file failed " << cfg_file_destinations.c_str() << endl;
		throw CorruptedDestination();
	} else {
		for (int i = 0; i < destinations.size(); i++) {
			fout << "[Place]\n";
			fout << "name=" << destinations[i]->getName() << endl;
			fout << "x=" << destinations[i]->getCoords().first << endl;
			fout << "y=" << destinations[i]->getCoords().second << endl;
			fout << "[/Place]\n";
		}
	}
	fout.close();
	return 0;
}
/**
 * Loads place data members from file and creates Place * objects
 * to push_back into the applications vector of deleted destinations
 * These deleted destinations are useful to mantain integrity of trip history
 * for each user in case a Place entry is deleted by the application admnistration
 * @brief loads "deleted" Place objects from file
 * @return 0 on success, -1 otherwise
 */
int Logic::save_del_destinations() {
	ofstream fout;

	// -------------------
	// Destinations file
	// -------------------

	fout.open(cfg_file_deldestinations.c_str());

	if (fout.fail()) {
		cout << "Opening file failed " << cfg_file_deldestinations.c_str()
				<< endl;
		throw CorruptedDelDestination();
	} else {
		for (int i = 0; i < del_destinations.size(); i++) {
			fout << "[DelPlace]\n";
			fout << "name=" << del_destinations[i]->getName() << endl;
			fout << "x=" << del_destinations[i]->getCoords().first << endl;
			fout << "y=" << del_destinations[i]->getCoords().second << endl;
			fout << "[/DelPlace]\n";
		}
	}
	fout.close();
	return 0;
}
/**
 * Loads trip data members from file and creates Trip * objects
 * to push_back into the applications vector of trips, if the trip's
 * start date is lower than the current date, it will be added into the
 * deleted trips vector instead and push_backed into the vector of tripHistory
 * of the participants  of said trip
 * @brief loads Trip objects from file
 * @return 0 on success, -1 otherwise
 */
int Logic::save_trips() const {
	ofstream fout;

	// -------------------
	// Trips file
	// -------------------

	fout.open(cfg_file_curtrips.c_str());

	if (fout.fail()) {
		cout << "Opening file failed " << cfg_file_curtrips.c_str() << endl;
		throw CorruptedTrip();
	} else {

		for (int i = 0; i < cur_trips.size(); i++) {
			fout << "[Trip]\n";
			fout << "vehicleOwner=" << cur_trips[i]->getDriver() << endl;
			fout << "plate=" << cur_trips[i]->getLicensePlate() << endl;
			fout << "seats=" << cur_trips[i]->getAvailableSeats() << endl;

			unsigned int route_size = cur_trips[i]->getRoute().size();

			for (int k = 0; k < route_size; k++) {
				fout << "place="
						<< cur_trips[i]->getRoute().at(k).first->getName()
						<< endl;
			}

			if (cur_trips[i]->getSmokingSign() == true) {
				fout << "smoking=1" << endl;
			}

			else if (cur_trips[i]->getSmokingSign() == false) {
				fout << "smoking=0" << endl;
			}

			fout << "begindate=" << cur_trips[i]->getStart() << endl;
			fout << "finishdate=" << cur_trips[i]->getEnd() << endl;

			vector<pair<Person*, vector<Place*> > >::iterator it=cur_trips[i]->getTravellers().begin();
			vector<pair<Person*, vector<Place*> > >::iterator ita=cur_trips[i]->getTravellers().end();

			for (;it!=ita; it++) {
				fout << "[Traveller]\n";
				fout << "traveller=" << (*it).first->getUsern() << endl;

				for (int t = 0; t < (*it).second.size(); t++) {
					fout << "tplace=" << (*it).second.at(t)->getName() << endl;
				}
				fout << "[/Traveller]\n";
			}
			fout << "[/Trip]\n";
		}
	}
	fout.close();
	return 0;
}
/**
 * Loads all the program information from the files (their names are defined in the top of Logic.h as constants).\n
 * This includes the registeredUsers, destinations(the ones that exist and a record of deleted ones) and trips \n\n
 *
 * @brief Loads all the Program information from files
 * @return 0 upon success, non-zero otherwise
 */
int Logic::save_data() {
	try {
		save_regUsers();
	} catch (CorruptedRegUser& e) {
		return -1;
	}

	try {
		save_destinations();
	} catch (CorruptedDestination& e) {
		return -1;
	}

	try {
		save_del_destinations();
	} catch (CorruptedDelDestination& e) {
		return -1;
	}

	try {
		save_trips();
	} catch (CorruptedTrip& e) {
		return -1;
	}
	return 0;
}

