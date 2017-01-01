#ifndef PERSON_H_
#define PERSON_H_

#include "includes.h"
#include "Vehicle.h"
#include "Trip.h"
#include "Place.h"
#include "Person.h"



using namespace std;

class Trip;
/**
 * @brief Person class
 *
 * A generic person class, functions as superclass to RegPerson and UnregPerson
 */
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
	void payBilling();
	/** @name Polymorphic functions
	*/
	///@{
	virtual void addBill(string fee, float triplength){};
	virtual void printPerson(){};
	virtual void addTripHistory(Trip * t) {};
	virtual string getUsern() const{};
	///@}


};

/**
 * @brief UnregPerson class
 *
 * Person subclass, represents registered users in the application
 */
class RegPerson: public Person
{
private:
	string password;
	string username;
	string address;
	Date lastLogin;
	vector <RegPerson*> buddies;
	vector <Vehicle *> vehicles;
	vector <Trip*> tripHistory;
	vector<string> notifications;
public:
	RegPerson();
	RegPerson(string n, string a, unsigned long t_nr, string uname, string passw,Date lastL);
	~RegPerson();

	//setters
	void setPassw(string pw);
	void setUsern(string usrn);
	void setAddress(string ad);
	void setlastLogin(Date date);
	//getters
	string getPassw() const;
	string getUsern() const;
	string getAddress() const;
	bool getHasVehicle() const;
	Date getLastLogin() const;
	vector<RegPerson*>& getBuddies();
	vector<Vehicle *>& getVehicles();
	vector<string>& getNotifications();
	vector<Trip*>& getTripHistory();

	//crud
	void insertBuddy(RegPerson* other_person);
	void removeBuddy(int index);
	void addTripHistory(Trip * t);
	void addVehicle(Vehicle* v);
	void removeVehicle(int index);

	//features
	bool areMutualBuddies(RegPerson* other_person) const;
	void addNotifications(string message);
	void showNotifications(int howmany);
	void addBill(string fee, float triplength);

	//Printing functions
	void printPerson();
	void printPersonAdmin();
	void printTripHistory();

	//operators
		bool operator<(RegPerson*);
};

/**
 * @brief UnregPerson class
 *
 * Person subclass, represents unregistered users in the application
 */
class UnregPerson: public Person
{

public:
	UnregPerson();
	UnregPerson(string n, unsigned long t_nr);
	~UnregPerson();

	//polymorphic methods
	void addBill(string fee, float triplength);
	void addTripHistory(Trip * t) {};
	string getUsern() const{
		return "";
	}
	void printPerson();
};

/**
 * @brief Equal operator and Hash function to RegPerson* objects
 *
 * Used in the RegHashTable.
 */
struct eqstr {
    bool operator() (const RegPerson* s1, const RegPerson* s2) const {
        return s1->getUsern()==s2->getUsern();
    }
};

/**
 * @brief Hash function to RegPerson* objects
 *
 * Used in the RegHashTable.
 */
struct hstr {
    int operator() (const RegPerson* s1) const {
        int v = 0;
        string u_name=s1->getUsern();
        for ( unsigned int i=0; i< u_name.size(); i++ )
            v = 37*v + u_name[i];
        return v;
    }
};

/**
 * RegPerson* Hashtable
 */
typedef tr1::unordered_set<RegPerson*, hstr, eqstr> RegHashTable;


#endif //PERSON_H_
