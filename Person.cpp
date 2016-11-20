#include "Person.h"
#include "Trip.h"
#include <algorithm>

Person::Person()
{
	telephone_nr=000000000;
	billing=0;
	name="emptyName";
}

Person::Person(string n, unsigned long t_nr)
{
	name=n;
	telephone_nr=t_nr;
	billing = 0;
}
Person::~Person(){}
//setters
void Person::setName(string n)
{
	name=n;
}

void Person::setTelNr(unsigned long t_nr)
{
	telephone_nr=t_nr;
}

void Person::setBilling(float f)
{
	billing=f;
}

void Person::payBilling(){
	cout << "Paid " << billing << " € : All bills paid" << endl;
	billing = 0;
}
//getters
string Person::getName() const
{
	return name;
}

unsigned long Person::getTelNr() const
{
	return telephone_nr;
}

float Person::getBilling() const
{
	return billing;
}

//RegPerson
RegPerson::RegPerson()
{
	Person();
}
RegPerson::RegPerson(string n, unsigned long t_nr,string passw, string uname)
{
	Person(n,t_nr);
	password=passw;
	username=uname;
	vehicles = vector<Vehicle *>();
	buddies = vector<RegPerson *>();
	tripHistory = vector<Trip *>();
}
RegPerson::~RegPerson(){}
//setters

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

//crud
bool RegPerson::areMutualBuddies(RegPerson* other_person) const
{
	return (find(other_person->getBuddies().begin(),other_person->getBuddies().end(), this) != other_person->getBuddies().end());
}

vector<string>& RegPerson::getNotifications()
{
	return notifications;
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
		for(int i=0;i<notifications.size();i++){
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

void RegPerson::addBill(float bill,string fee, float triplength){
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

void RegPerson::printTripHistory(){
	for(int i=0;i<tripHistory.size();i++)
	{
		cout << tripHistory[i]->toString() << endl;
	}
}

//UnregPerson
UnregPerson::UnregPerson()
{
	Person();
}
UnregPerson::UnregPerson(string n, unsigned long t_nr)
{
	Person(n,t_nr);
}
UnregPerson::~UnregPerson(){}
void UnregPerson::addBill(float bill,string fee, float triplength){
	float prevbilling { billing };
	if(fee=="trip"){
		billing+=5+triplength*0.4;
	}
	cout << "Charged " << billing-prevbilling << " -> Total billing : " << billing << endl;
}

