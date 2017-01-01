#include "Person.h"
#include "Trip.h"
#include <algorithm>

/**
 * @brief Person default constructor
 */
Person::Person()
{
	telephone_nr=000000000;
	billing=0;
	name="emptyName";
}
/**
 * @brief Person constructor
 * @param n person's name
 * @param t_nr person's phone
 */
Person::Person(string n, unsigned long t_nr)
{
	name=n;
	telephone_nr=t_nr;
	billing = 0;
}
/**
 * @brief Person destructor
 **/
Person::~Person(){}
//setters

/**
 * @brief Sets the person's name
 * @param n string with the person's name
 */
void Person::setName(string n)
{
	name=n;
}
/**
 * @brief Sets the person's phone
 * @param t_nr unsigned long with the person's phone
 */
void Person::setTelNr(unsigned long t_nr)
{
	telephone_nr=t_nr;
}
/**
 * @brief Sets the person's billing debt
 * @param f float with wanted value
 */
void Person::setBilling(float f)
{
	billing=f;
}
/**
 * @brief Outputs message that bill was paid, resets billing to 0
 */
void Person::payBilling(){
	cout << "Paid " << billing << " € : All bills paid" << endl;
	billing = 0;
}
//getters

/**
 * @brief Returns the name
 * @return string with the person's name
 */
string Person::getName() const
{
	return name;
}
/**
 * @brief Returns the phone
 * @return long with the person's phone
 */
unsigned long Person::getTelNr() const
{
	return telephone_nr;
}
/**
 * @brief Returns the billing debt
 * @return float with billing debt
 */
float Person::getBilling() const
{
	return billing;
}

//RegPerson


/**
 * @brief RegPerson default constructor
 */
RegPerson::RegPerson()
:Person()
{
	username="empty";
}
/**
 * @brief RegPerson constructor
 * @param n person's name
 * @param a person's address
 * @param t_nr person's phone
 * @param uname person's username
 * @param passw person's password
 */
RegPerson::RegPerson(string n, string a, unsigned long t_nr, string uname,string passw,Date lastL)
:Person(n,t_nr)
{
	address=a;
	password=passw;
	username=uname;
	vehicles = vector<Vehicle *>();
	buddies = vector<RegPerson *>();
	tripHistory = vector<Trip *>();
	lastLogin=lastL;
}
/**
 * @brief RegPerson destructor
 */
RegPerson::~RegPerson(){}
//setters

/**
 * @brief Sets username to usrn
 */
void RegPerson::setUsern(string usrn)
{
	username=usrn;
}

/**
 * @brief Sets last login date
 */
void RegPerson::setlastLogin(Date date){
	lastLogin = date;
}

/**
 * @brief Sets address to addr
 */
void RegPerson::setAddress(string addr)
{
	address=addr;
}

/**
 * @brief Sets password to pw
 */
void RegPerson::setPassw(string pw)
{
	password=pw;
}


//getters

/**
 * @brief Returns the username
 * @return string with username
 */
string RegPerson::getUsern() const
{
	return username;
}

/**
 * @brief Returns the last login
 * @return Date of last login
 */
Date RegPerson::getLastLogin() const{
	return lastLogin;
}

/**
 * @brief Returns the password
 * @return string with password
 */
string RegPerson::getPassw() const
{
	return password;
}

/**
 * @brief Returns the address
 * @return string with address
 */
string RegPerson::getAddress() const
{
	return address;
}

/**
 * @brief returns buddies
 * @return vector of buddies
 */
vector<RegPerson*>& RegPerson::getBuddies()
{
	return buddies;
}
/**
 * @brief returns vehicles
 * @return vector of vehicles
 */
vector<Vehicle *>& RegPerson::getVehicles()
{
	return vehicles;
}
/**
 * @brief get user trip history
 * @return returns vector of trips
 */
vector<Trip*>& RegPerson::getTripHistory(){
	return tripHistory;
}
/**
 * @brief check if user has vehicles
 * @return bool true if he has vehicles, false otherwise
 */
bool RegPerson::getHasVehicle() const
{
	return vehicles.size()>0;
}


//crud

/**
 * @brief check if user is mutual buddy with other person
 * @return bool true if mutual buddies, false otherwise
 */
bool RegPerson::areMutualBuddies(RegPerson* other_person) const
{
	return (find(other_person->getBuddies().begin(),other_person->getBuddies().end(), this) != other_person->getBuddies().end());
}
/**
 * @brief get user notifications
 * @return return the vector of strings with notifications
 */
vector<string>& RegPerson::getNotifications()
{
	return notifications;
}
/**
 * @brief Add a trip to trip history vector
 */
void RegPerson::addTripHistory(Trip * t)
{
	tripHistory.push_back(t);
}
/**
 * @brief Add message to notifications vector
 */
void RegPerson::addNotifications(string message)
{
	notifications.insert(notifications.begin(),message);
}

/**
 * @brief Displays specified number of notifications
 * @param int howmany - number of notifications to display
 */
void RegPerson::showNotifications(int howmany)
{
	if(howmany<0)
		return;
	if(howmany>notifications.size()-1)
		for(unsigned int i=0;i<notifications.size();i++){
			cout << notifications[i] << endl;
		}
	else for(int i=0;i<howmany;i++){
		cout << notifications[i] << endl;
	}
}

/**
 * @brief Add other_person to user's buddy vector
 * @param RegPerson* other_person - buddy to add
 */
void RegPerson::insertBuddy(RegPerson* other_person)
{
	buddies.push_back(other_person);
}

/**
 * @brief Remove a buddy from vector
 * @param int index - index of buddy to delete from vector
 */
void RegPerson::removeBuddy(int index)
{
	if(index<0 || index >= buddies.size()){
		cout << "Invalid index chosen" << endl;
		return;
	}

	vector<RegPerson *>::iterator it=buddies.begin();

	while (it!=buddies.end() && index != 0) {
		it++;
		index--;
	}

	this->buddies.erase(it);
}


/**
 * @brief Add vehicle to user's vehicle vector
 * @param Vehicle * v - vehicle to add
 */
void RegPerson::addVehicle(Vehicle* v)
{
	this->vehicles.push_back(v);
}

/**
 * @brief Remove a vehicle from vector
 * @param int index - index of vehicle to delete from vector
 */
void RegPerson::removeVehicle(int index)
{
	if(index<0 || index >= vehicles.size()){
		cout << "Invalid index chosen" << endl;
		return;
	}

	vector<Vehicle *>::iterator it=vehicles.begin();

	while (it!=vehicles.end() && index != 0) {
		it++;
		index--;
	}

	this->vehicles.erase(it);
}

/**
 * @brief Prints registered person's information
 */
void RegPerson::printPerson()
{
	stringstream ss,ssn;
	ss << "Name:" << name << " | Address:" << address << " | Phone:" << telephone_nr << " | Username:" << username << " | Password:" << password;
	cout << ss.str() << endl;
	for(int i=0;i<vehicles.size();i++)
	{
		cout << vehicles[i]->toString() << endl;
	}
}

/**
 * @brief Prints registered person's information with login data
 */
void RegPerson::printPersonAdmin()
{
	stringstream ss,ssn;
	ss << "Name:" << name << " | Address:" << address << " | Phone:" << telephone_nr << " | Username:" << username << " | Password:" << password << " | Last active at:" << lastLogin;
	cout << ss.str() << endl;
	for(int i=0;i<vehicles.size();i++)
	{
		cout << vehicles[i]->toString() << endl;
	}
}

/**
 * @brief Adds bill to billing, if user has vehicles, trips are free of charge
 * @param string fee - what kind of fee to charge
 * @param float triplength - distance of the trip produces higher charges
 */
void RegPerson::addBill(string fee, float triplength)
{
	float prevbilling { billing };
	if(fee=="monthly")
	{
		billing+=10;
	}

	if(fee=="trip")
	{
		if(!this->getHasVehicle())
		{
			billing+=4+triplength*0.2;
		}
	}
	cout << "Charged " << billing-prevbilling << " -> Total billing : " << billing << endl;
}

/**
 * @brief prints the vector of trip history of user
 */
void RegPerson::printTripHistory()
{
	sort(tripHistory.begin(),tripHistory.end(),Trip::compareTrips);
	for(int i=0;i<tripHistory.size();i++)
	{
		if(username!=tripHistory[i]->getDriver())
		cout <<i <<":" <<tripHistory[i]->toStringByPerson(name,telephone_nr) << endl;
		else cout <<i <<":" <<tripHistory[i]->toString() << endl;
	}
}

bool RegPerson::operator<(RegPerson* a){
	for(int i = 0; i < buddies.size(); i++){
		if(buddies[i] == a){
			return true;
		}
	}
	return false;
}



//UnregPerson

/**
 * @brief UnregPerson default constructor
 */
UnregPerson::UnregPerson()
:Person()
{
}
/**
 * @brief UnregPerson constructor
 * @param n name of unregistered person
 * @param t_nr phone number of unregistered person
 */
UnregPerson::UnregPerson(string n, unsigned long t_nr)
:Person(n,t_nr)
{
}
/**
 * @brief UnregPerson destructor
 */
UnregPerson::~UnregPerson(){}

/**
 * @brief Prints unregistered person's information
 */
void UnregPerson::printPerson()
{
	stringstream ss;
	ss << "Name:" << name << "| Phone:" << telephone_nr;
	cout << ss.str();
}



/**
 * @brief Adds bill to billing of unregistered person
 * @param string fee - what kind of fee to charge
 * @param float triplength - distance of the trip produces higher charges
 */
void UnregPerson::addBill(string fee, float triplength){
	float prevbilling { billing };
	if(fee=="trip"){
		billing+=5+triplength*0.4;
	}
	cout << "Charged " << billing-prevbilling << " -> Total billing : " << billing << endl;
}

