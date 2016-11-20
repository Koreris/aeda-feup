#ifndef LOGIC_H_
#define LOGIC_H_


#include "includes.h"
#include "Date.h"
#include "Person.h"
#include "Place.h"
#include "Trip.h"
#include "Vehicle.h"

using namespace std;

class Logic
{
public:
	Logic();
	bool userLogin(string usr, string passw);
	vector<Trip *> findDest(string dest);
};

#endif //LOGIC_H_
