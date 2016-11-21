#ifndef PERSON_H_
#define PERSON_H_

#include "includes.h"
#include "Vehicle.h"
#include "Trip.h"
#include "Place.h"
#include "Person.h"


using namespace std;

class Trip;
class Person
{

protected:
	string name;
	unsigned long telephone_nr;
	float billing;

public:
	Person();
	Person(string n, unsigned long t_nr);
	virtual ~Person();

	//setters
	void setName(string n);
	void setTelNr(unsigned long t_nr);
	void setBilling(float f);

	//getters
	string getName() const;
	unsigned long getTelNr() const;
	float getBilling() const;

	//billing
	virtual void addBill(float bill,string fee, float triplength){};
	virtual void printPerson(){};
	void payBilling();
};

class RegPerson: public Person
{
private:
	string password;
	string username;
	vector <RegPerson*> buddies;
	vector <Vehicle *> vehicles;
	vector <Trip*> tripHistory;
	vector<string> notifications;
public:
	RegPerson();
	RegPerson(string n, unsigned long t_nr, string uname, string passw);
	~RegPerson();

	//setters
	void setPassw(string pw);
	void setUsern(string usrn);



	//getters
	string getPassw() const;
	string getUsern() const;
	bool getHasVehicle() const;
	vector<RegPerson*>& getBuddies();
	vector<Vehicle *>& getVehicles();
	vector<string>& getNotifications();
	//crud
	void insertBuddy(RegPerson* other_person);
	void removeBuddy(int index);
	bool areMutualBuddies(RegPerson* other_person) const;


	void addVehicle(Vehicle* v);
	void removeVehicle(int index);
	void printTripHistory();

	void addNotifications(string message);
	void showNotifications(int howmany);

	void addBill(float bill,string fee, float triplength);
	void printPerson();
};

class UnregPerson: public Person
{

public:
	UnregPerson();
	UnregPerson(string n, unsigned long t_nr);
	~UnregPerson();

	//crud
	void addBill(float bill, string fee, float triplength);
	void printPerson();
};

#endif //PERSON_H_
