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
 * @brief RegPerson constructor
 */
RegPerson::RegPerson()
:Person()
{
	username="empty";
}
/**
 * @brief RegPerson constructor
 * @param n person's name
 * @param t_nr person's phone
 * @param uname person's username
 * @param passw person's password
 */
RegPerson::RegPerson(string n, unsigned long t_nr, string uname,string passw)
:Person(n,t_nr)
{
	password=passw;
	username=uname;
	vehicles = vector<Vehicle *>();
	buddies = vector<RegPerson *>();
	tripHistory = vector<Trip *>();
}
/**
 * @brief RegPerson destructor
 */
RegPerson::~RegPerson(){}
//setters

/**
 * @brief RegPerson destructor
 */
void RegPerson::setUsern(string usrn)
{
	username=usrn;
}

void RegPerson::setPassw(string pw)
{
	password=pw;
}


//getters

string RegPerson::getUsern() const
{
	return username;
}

string RegPerson::getPassw() const
{
	return password;
}

bool RegPerson::getHasVehicle() const
{
	return vehicles.size()>0;
}



vector<RegPerson*>& RegPerson::getBuddies()
{
	return buddies;
}

vector<Vehicle *>& RegPerson::getVehicles()
{
	return vehicles;
}
vector<Trip*>& RegPerson::getTripHistory(){
	return tripHistory;
}
//crud
bool RegPerson::areMutualBuddies(RegPerson* other_person) const
{
	return (find(other_person->getBuddies().begin(),other_person->getBuddies().end(), this) != other_person->getBuddies().end());
}

vector<string>& RegPerson::getNotifications()
{
	return notifications;
}
void RegPerson::addTripHistory(Trip * t)
{
	tripHistory.push_back(t);
}
void RegPerson::addNotifications(string message)
{
	notifications.insert(notifications.begin(),message);
}

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

void RegPerson::insertBuddy(RegPerson* other_person)
{
	buddies.push_back(other_person);
}

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

void RegPerson::addVehicle(Vehicle* v)
{
	this->vehicles.push_back(v);
}

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

void RegPerson::printPerson()
{
	stringstream ss,ssn;
	ss << "Name:" << name << "| Phone:" << telephone_nr << "| Username:" << username << "| Password:" << password;
	cout << ss.str() << endl;
	for(int i=0;i<vehicles.size();i++)
	{
		cout << vehicles[i]->toString() << endl;
	}
}

void RegPerson::addBill(string fee, float triplength){
	float prevbilling { billing };
	if(fee=="monthly"){
		billing+=10;
	}

	if(fee=="trip"){
		if(!this->getHasVehicle()){
			billing+=4+triplength*0.2;
		}
	}
	cout << "Charged " << billing-prevbilling << " -> Total billing : " << billing << endl;
}

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

//UnregPerson
UnregPerson::UnregPerson()
:Person()
{
}
UnregPerson::UnregPerson(string n, unsigned long t_nr)
:Person(n,t_nr)
{
}
UnregPerson::~UnregPerson(){}

void UnregPerson::printPerson()
{
	stringstream ss;
	ss << "Name:" << name << "| Phone:" << telephone_nr;
	cout << ss.str();
}

void UnregPerson::addBill(string fee, float triplength){
	float prevbilling { billing };
	if(fee=="trip"){
		billing+=5+triplength*0.4;
	}
	cout << "Charged " << billing-prevbilling << " -> Total billing : " << billing << endl;
}

