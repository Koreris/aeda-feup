#include "includes.h"
#include "BuddyList.h"
#include "Date.h"
#include "Person.h"
#include "Place.h"
#include "Trip.h"
#include "Vehicle.h"


int userLogin(RegPerson p)
{
	string username="";
	string password="";

	cout << "Input your username: " << endl;
	getline(cin, username);

	cout << "Input your password: " << endl;
	getline(cin, password);

	if (p.getUsern()==username && p.getPassw()==password)
	{
		displayLoginMenu();
		return 0;
	}

	else
		cout << "Non matching user/password! Please try again" << endl;
	return 1;
}





















