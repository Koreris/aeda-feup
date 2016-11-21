#include "includes.h"
#include "Date.h"
#include "Place.h"
#include "Trip.h"
#include "Vehicle.h"
#include "Logic.h"

using namespace std;

Logic::Logic()
{}

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
 * @brief Returns the Library's current date and time
 * @return Date with the current date and time
 */
Date Logic::get_curDate() const
{
	return Date::curDate();
}

bool Logic::userLogin(string usr, string passw)
{
	return (usr == "test" && passw == "1234");
}

vector<Trip *> Logic::findDest(string dest)
{
	vector<Trip *> dests;
	return (dests);
	//returns true and
}

vector<Trip *> Logic::tripSortByDate()
{

}

vector<Trip *> Logic::tripSortByDriverName()
{

}

vector<Trip *> Logic::tripSortByScheduled()
{

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

RegPerson * Logic::findRegPerson (string username)
{
	for(int i=0;i<regUsers.size();i++){
		if(regUsers[i]->getUsern()==username)
			return regUsers[i];
	}
}

vector<RegPerson *> Logic::findRegPersonVec (string username)
{
	vector<RegPerson *> temp=vector<RegPerson *>();
	for(int i=0;i<regUsers.size();i++){
		if(regUsers[i]->getUsern()==username){
			temp.push_back(regUsers[i]);
			return temp;
		}
	}
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

//int Logic::load_trips();

/**
 * Loads all the program information from the files (their names are defined in the top of Library.h as constants).\n
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
 return 0;
}







