#include "Person.h"
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
	buddies = vector<const RegPerson *>();
}

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



vector<const RegPerson*> RegPerson::getBuddies() const
{
	return buddies;
}

vector<Vehicle *> RegPerson::getVehicles() const
{
	return vehicles;
}

//crud
bool RegPerson::areBuddies(const RegPerson* other_person) const
{
	/*
	vector <RegPerson *> other_p_buddies=other_person->getBuddies();
	return (find(other_p_buddies.begin(),other_p_buddies.end(), this) != other_p_buddies.end());
	*/
}

void RegPerson::insertBuddy(RegPerson* other_person)
{
	buddies.push_back(other_person);
	other_person->getBuddies().push_back(this);
}

void RegPerson::removeBuddy(RegPerson* other_person)
{
	/*
	vector <RegPerson *>::iterator it;
	vector <RegPerson *>::iterator ita;

	vector <RegPerson *> bud=this->getBuddies();
	vector <RegPerson *> other_p_buddies=other_person->getBuddies();

	for(it=other_p_buddies.begin(); it!=other_p_buddies.end(); it++)
	{
		if((*it)==this)
		{
			other_p_buddies.erase(it);
			break;
		}
	}

	for(ita=bud.begin(); ita!=bud.end(); ita++)
	{
		if((*ita)==other_person)
		{
			bud.erase(ita);
			break;
		}
	}
	*/
}

void RegPerson::addVehicle(Vehicle* v)
{
	this->vehicles.push_back(v);
}

void RegPerson::removeVehicle(Vehicle* v)
{
	//
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

//UnregPerson
UnregPerson::UnregPerson()
{
	Person();
}
UnregPerson::UnregPerson(string n, unsigned long t_nr)
{
	Person(n,t_nr);
}

void UnregPerson::addBill(float bill,string fee, float triplength){
	float prevbilling { billing };
	if(fee=="trip"){
		billing+=5+triplength*0.4;
	}
	cout << "Charged " << billing-prevbilling << " -> Total billing : " << billing << endl;
}
