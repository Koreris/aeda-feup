#include "includes.h"
#include "Date.h"
#include "Place.h"
#include "Trip.h"
#include "Vehicle.h"
#include "Logic.h"

using namespace std;

Logic::Logic()
{
}

Logic::Logic(string dir){
	if (dir != "")
		dir += "\\";
	cfg_dir=dir;
	cfg_file_regusers=cfg_dir+CFG_FILE_REGUSERS;
	cfg_file_delregusers=cfg_dir+CFG_FILE_DEL_REGUSERS;
	cfg_file_destinations=cfg_dir+CFG_FILE_DESTINATIONS;
	cfg_file_deldestinations=cfg_dir+CFG_FILE_DEL_DESTINATIONS;
    cfg_file_curtrips=cfg_dir+CFG_FILE_CURTRIPS;
    cfg_file_deltrips=cfg_dir+CFG_FILE_DELTRIPS;

}
/**
 * Returns the current date, provided by the Date class
 * @brief Returns the current date and time
 * @return Date with the current date and time
 */
Date Logic::get_curDate() const
{
	return Date::curDate();
}

bool Logic::userLogin(string usr, string passw)
{
	for(int i=0;i<regUsers.size();i++)
	{
		if(regUsers[i]->getUsern()==usr && regUsers[i]->getPassw()==passw){
			curr_user=regUsers[i];
			UnregPerson* curr_unreg=NULL;
			cout << "Logged in with User: " << regUsers[i]->getUsern() << endl;
			return true;
		}
	}
	cout << "User not found " << endl;
	return false;
}



/**
 * Sorts vector of trips by date
 * @brief sort trips by date
 * @return vector of trips
 */
vector<Trip *> Logic::tripSortByDate(vector<Trip *>v)
{
	sort(v.begin(),v.end(),Trip::compareTrips);
	return v;
}
/**
 * Sorts vector of trips by driver name
 * @brief sort trips by driver name
 * @return vector of trips
 */
vector<Trip *> Logic::tripSortByDriverName(vector<Trip *>v)
{
	sort(v.begin(),v.end(),Trip::compareTripsDriverName);
	return v;
}


vector<Trip*>& Logic::getCurTrips ()
{
		return cur_trips;
}

void Logic::setCurTrips (vector<Trip*>& curTrips)
	{
		cur_trips = curTrips;
	}

vector<Place*>& Logic::getDelDestinations()
{
	return del_destinations;
}

void Logic::setDelDestinations (vector<Place*>& delDestinations)
{
	del_destinations = delDestinations;
}

vector<Trip*>& Logic::getDelTrips ()
{
	return del_trips;
}

void Logic::setDelTrips (vector<Trip*>& delTrips)
{
	del_trips = delTrips;
}

vector<Place*>& Logic::getDestinations()
{
	return destinations;
}

void Logic::setDestinations (vector<Place*>& destinations)
{
	this->destinations = destinations;
}

vector<RegPerson*>& Logic::getRegUsers ()
{
	return regUsers;
}

void Logic::setRegUsers (vector<RegPerson*>& regUsers)
{
	this->regUsers = regUsers;
}


void Logic::deleteDestinations(int index)
{
	if(index<0 || index >= destinations.size())
	{
		cout << "Invalid index chosen" << endl;
		return;
	}

	vector<Place *>::iterator it=destinations.begin();

	while (it!=destinations.end() && index != 0)
	{
		it++;
		index--;
	}
	del_destinations.push_back(destinations[index]);
	this->destinations.erase(it);
}

void Logic::deleteTrips(int index)
{
	if(index<0 || index >= cur_trips.size())
	{
		cout << "Invalid index chosen" << endl;
		return;
	}

	vector<Trip *>::iterator it=cur_trips.begin();

	while (it!=cur_trips.end() && index != 0)
	{
		it++;
		index--;
	}
	del_trips.push_back(cur_trips[index]);
	this->cur_trips.erase(it);
}
/**
 * Finds all the trips with vacancies that have a possible itenerary starting from place src and going through or ending in place dest
 * @brief finds trips with vacancies by giving start location and end location
 * @return vector of trips, empty if no trips found
 */
vector<Trip *> Logic::findTrips(string src,string dest)
{
	vector<Trip *> temp=vector<Trip *>();
	for(int i=0;i<cur_trips.size();i++){
		if(cur_trips[i]->hasDestination(src,dest)){
			if(!cur_trips[i]->isFull(src,dest))
				temp.push_back(cur_trips[i]);
		}
	}
	return temp;
}
/**
 * Finds all the trips scheduled for user P
 * @brief find scheduled trips
 * @return vector of trips, empty if no trips found
 */
vector<Trip *> Logic::findFutureTrips(Person * p)
{
	vector<Trip *> temp=vector<Trip *>();
	for(int i=0;i<cur_trips.size();i++){
		if(cur_trips[i]->isTraveller(p)){
			temp.push_back(cur_trips[i]);
		}
		if(cur_trips[i]->getDriver()==((RegPerson*)p)->getUsern()){
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
RegPerson * Logic::findRegPerson (string username)
{
	for(int i=0;i<regUsers.size();i++){
		if(regUsers[i]->getUsern()==username)
			return regUsers[i];
	}
	return NULL;
}

/**
 * Finds RegPerson pointer of user with username
 * @brief find a RegPerson by username
 * @return vector with RegPerson or empty vector  if not found
 */
vector<RegPerson *> Logic::findRegPersonVec (string username)
{
	vector<RegPerson *> temp=vector<RegPerson *>();
	for(int i=0;i<regUsers.size();i++){
		if(regUsers[i]->getUsern()==username){
			temp.push_back(regUsers[i]);
			return temp;
		}
	}
	return temp;
}

Place * Logic::findDest(string destname,string f)
{
	for(int i=0;i<destinations.size();i++){
			if(destinations[i]->getName()==destname)
				return destinations[i];
		}
	if(f=="loading")
	for(int i=0;i<del_destinations.size();i++){
				if(del_destinations[i]->getName()==destname)
					return del_destinations[i];
			}
		return NULL;
}
int Logic::load_regUsers()
{
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

		string name ="";
		unsigned long phone=-1;
		string username="";
		string password="";

		vector<Vehicle *> userVehicle = vector<Vehicle *>();

		//vehicle stuff
		string owner="";
		string type="";
		string brand="";
		string license_plate="";
		unsigned long seats = -1;



		while (!fin.eof()) {
			getline(fin, line);
			if (line == "[RegUser]") {
				name ="";
				phone=-1;
				userVehicle.clear();
				username="";
				password="";
			} else if (line == "[/RegUser]") {
				if (name == "" || phone == -1 || username == "" || password=="")
					throw CorruptedRegUser();
				RegPerson *user = new RegPerson(name, phone, username, password);
				for(int i=0;i<userVehicle.size();i++)
				{
					user->getVehicles().push_back(userVehicle[i]);
				}
				regUsers.push_back(user);
				regUsers[regUsers.size()-1]->printPerson();
			}
			else if (line == "[Vehicle]") {
				owner="";
				type="";
				brand="";
				license_plate="";
				unsigned long seats = -1;
			} else if (line == "[/Vehicle]") {
				if (owner == "" || type == "" || brand == "" || license_plate=="" || seats==-1)
					throw CorruptedRegUser();
				Vehicle *v = new Vehicle(owner, type, brand, license_plate,seats);
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
				else if (key == "owner")
					owner = value;
				else if (key == "brand")
					brand = value;
				else if (key == "plate")
					license_plate = value;
				else if (key == "seats")
					seats = stol(value);
				else if (key == "type")
					type = value;
			}
		}
	}

	fin.close();
	return 0;
}

int Logic::load_destinations(){
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

		string name ="";
		int x=-1;
		int y=-1;

		while (!fin.eof()) {
			getline(fin, line);
			if (line == "[Place]") {
				name ="";
				x=-1;
				y=-1;
			} else if (line == "[/Place]") {
				if (name == "" ||x == -1 || y == -1)
					throw CorruptedDestination();

				pair<int,int> coord(x,y);
				Place *pl = new Place(name,coord);
				destinations.push_back(pl);
				cout << destinations[destinations.size()-1]->toString() << endl;
			}
			else {
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

int Logic::load_del_destinations(){
	ifstream fin;
	stringstream ss;

	// -------------------
	// Destinations file
	// -------------------

	fin.open(cfg_file_deldestinations.c_str());

	if (fin.fail()) {
		cout << "Opening file failed " << cfg_file_deldestinations.c_str() << endl;
		return -1;
	} else {
		string line;

		string key = "";
		string value = "";

		string name ="";
		int x=-1;
		int y=-1;

		while (!fin.eof()) {
			getline(fin, line);
			if (line == "[DelPlace]") {
				name ="";
				x=-1;
				y=-1;
			} else if (line == "[/DelPlace]") {
				if (name == "" ||x == -1 || y == -1)
					throw CorruptedDelDestination();

				pair<int,int> coord(x,y);
				Place *pl = new Place(name,coord);
				del_destinations.push_back(pl);
				cout << del_destinations[del_destinations.size()-1]->toString() << endl;
			}
			else {
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

int Logic::load_trips()
{
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

		string vehicleowner ="";
		unsigned long seats=-1;
		string place="";
		bool smoking=false;
		string beginDate = "";
		string endDate = "";

		vector<pair<Place *,int> > route = vector<pair<Place *,int> >();

		Person * driverP;
		//Traveller stuff
		string tuser="";
		string tplace="";
		vector<Place *> tplaces = vector<Place*>();
		vector<pair<Person *,vector<Place *> > > travellers = vector<pair<Person *,vector<Place *> > >();


		while (!fin.eof()) {
			getline(fin, line);
			if (line == "[Trip]") {
				vehicleowner ="";
				seats=-1;
				smoking=false;
				place="";
				beginDate = "";
				endDate = "";
				route.clear();
				travellers.clear();
			} else if (line == "[/Trip]") {
				if (vehicleowner == "" || seats == -1 || route.size()==0)
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

				Trip *trip = new Trip(vehicleowner, seats, smoking,start_date,end_date);
				trip->addRoute(route);
				if(driverP!=NULL)
				{
					driverP->addTripHistory(trip);
				}
				for(int i=0;i<travellers.size();i++)
				{
					trip->addTraveller(travellers[i].first,travellers[i].second);
					travellers[i].first->addTripHistory(trip);

				}


				if(trip->getStart()<get_curDate()){
					del_trips.push_back(trip);
					cout <<"OLD_TRIP:"<<trip->toString() << endl;
				}
				else
				{
					cur_trips.push_back(trip);
					cout <<"CUR_TRIP:"<<trip->toString() << endl;
				}
			}
			else if (line == "[Traveler]") {
				tuser="";
				tplace="";
				tplaces.clear();
			} else if (line == "[/Traveler]") {
				if (tuser == "" || tplace == "")
					throw CorruptedTrip();
				Person * passenger;
				if(tuser=="unregistered")
				{

					passenger= new UnregPerson();
				}
				else
				{
					passenger = findRegPerson(tuser);
					if(passenger==NULL){
						cout << "Invalid traveler: " << tuser << endl;
						throw CorruptedTrip();
					}
				}
				pair<Person *,vector<Place *> > traveler(passenger,tplaces);
				travellers.push_back(traveler);

			}

			else {
				ss.str("");
				ss.str(line + "\n");
				getline(ss, key, '=');
				getline(ss, value);

				if (key == "vehicleOwner"){
					vehicleowner = value;
					driverP=findRegPerson(value);

				}
				else if (key == "seats")
					seats = stol(value);
				else if (key == "place"){
					place = value;
					Place * p = findDest(value,"loading");
					if(p==NULL)
					{
						cout << "Invalid place in trips file " << endl;
						throw CorruptedTrip();
					}
					pair <Place *, int> r(p,0);
					route.push_back(r);
				}
				else if (key == "tplace"){
					tplace = value;
					Place * p = findDest(value,"loading");
					if(p==NULL)
					{
						cout << "Invalid place in trips file " << endl;
						throw CorruptedTrip();
					}
					tplaces.push_back(p);
				}
				else if (key == "smoking")
				{
					smoking=stol(value);
				}

				else if (key == "begindate")
					beginDate = value;
				else if (key == "finishdate")
					endDate = value;
				else if (key == "traveller")
					tuser=value;
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

try{
	load_regUsers();
}
catch(CorruptedRegUser e){
	return -1;
}

try{
	load_destinations();
}
catch(CorruptedDestination e){
	return -1;
}

try{
	load_del_destinations();
}
catch(CorruptedDelDestination e){
	return -1;
}

try{
	load_trips();
}
catch(CorruptedTrip e){
	return -1;
}
 return 0;
}







