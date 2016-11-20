#include "includes.h"
#include "Date.h"
#include "Person.h"
#include "Place.h"
#include "Trip.h"
#include "Vehicle.h"
#include "Logic.h"

using namespace std;

Logic::Logic()
{}

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




















