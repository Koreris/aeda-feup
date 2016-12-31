#include "Trip.h"
#include "Person.h"

/**
 * @brief Trip default constructor
* @param VehicleOwner vehicle owner's name
 * @param v vehicle
 * @param smoke smoking allowed or not
 * @param s start date
 * @param e end date
 */
Trip::Trip()
{
	vehicleOwner = "";
	vehicle = new Vehicle();
	plate = "";
	distance=0;
	available_seats=0;
	smoking_allowed=false;
	start=Date();
	end=Date();
	route= vector< pair<Place*,int> >();
	travellers=vector< pair<Person*,vector<Place*> > >();
}

Trip::Trip(string VehicleOwner, string p, Vehicle* v,bool smoke, Date s,Date e)
{
	vehicleOwner=VehicleOwner;
	vehicle = v;
	plate=p;
	available_seats=v->getCarSeats()-1;
	smoking_allowed=smoke;
	start = s;
	end = e;
	distance=0;
	route= vector< pair<Place*,int> >();
	travellers=vector< pair<Person*,vector<Place*> > >();
}

/**
 * @brief Trip constructor
 * @param VehicleOwner vehicle owner's name /driver's
 * @param seats car seats
 * @param smoke smoking allowed or not
 * @param s start date
 * @param e end date
 */
Trip::Trip(string VehicleOwner,string p,unsigned int seats,bool smoke, Date s,Date e)
{
	vehicleOwner=VehicleOwner;
	plate=p;
	available_seats=seats-1;
	smoking_allowed=smoke;
	start = s;
	end = e;
	distance=0;
	route= vector< pair<Place*,int> >();
	travellers=vector< pair<Person*,vector<Place*> > >();
}

/**
 * @brief Trip default destructor
 */
Trip::~Trip()
{
}

//setters

/**
 * @brief Sets the trip's available seats
 * @param a_s unsigned int with the trip's seats
 */
void Trip::setAvailableSeats(unsigned int a_s)
{
	available_seats=a_s;
}

/**
 * @brief Sets the trip's distance
 * @param d float with the trip's distance
 */
void Trip::setDistance(float d)
{
	distance=d;
}

/**
 * @brief Sets the trip's distance
 * @param s bool with value for allowing or disallowing smoking in the trip
 */
void Trip::setSmokingSign(bool s)
{
	smoking_allowed=s;
}

/**
 * @brief Sets the trip's start date
 * @param s Date with the trip's start date
 */
void Trip::setStart(Date s)
{
	start=s;
}

void Trip::setLicensePlate(string lp)
{
	plate=lp;
}
/**
 * @brief Sets the trip's end date
 * @param e Date with the trip's end date
 */
void Trip::setEnd(Date e)
{
	start=e;
}

//getters

/**
 * @brief Returns the name of the driver
 * @return string with the driver's name
 */
string Trip::getDriver() const
{
	return vehicleOwner;
}

/**
 * @brief Returns the vehicle's license plate
 * @return string with the license plate
 */
string Trip::getLicensePlate() const
{
	return plate;
}

/**
 * @brief Returns the number of available seats in the trip
 * @return unsigned int with the trip's available seats
 */
unsigned int Trip::getAvailableSeats() const
{
	return available_seats;
}

/**
 * @brief Returns the trip's distance
 * @return float with the trip's distance
 */
float Trip::getDistance() const
{
	return distance;
}

/**
 * @brief Returns the trip's route
 * @return vector<pair<Place*, int>> with the trip's route
 */
vector<pair<Place *,int> > Trip::getRoute() const
{
	return route;
}

/**
 * @brief Returns the trip's travellers
 * @return vector< pair <Person*, vector<Place*> > >  with the trip's travellers and routes
 */
vector< pair <Person*, vector<Place*> > > & Trip::getTravellers()
{
	return travellers;
}

/**
 * @brief Returns if the trip allows smoking
 * @return bool with the allow value
 */
bool Trip::getSmokingSign() const
{
	return smoking_allowed;
}

/**
 * @brief Returns the trip's start date
 * @return Date with the trip's start date
 */
Date Trip::getStart() const
{
	return start;
}

/**
 * @brief Returns the trip's end date
 * @return Date with the trip's end date
 */
Date Trip::getEnd() const
{
	return end;
}

/**
 * @brief sets a route to the trip and the corresponding distance
 * @param rota vector< pair<Place*,int> > with the trip's route
 */
void Trip::addRoute(vector< pair<Place*,int> > rota)
{
	route=rota;
	setDistance(calculateDistance((*route.begin()).first,(*(route.end()-1)).first));
}

/**
 * @brief calculates the distance between two places through the coordinate values
 * @param begin Place * initial place
 * @param end Place * final destination
 * @return float the distance between two places
 */
float Trip::calculateDistance(Place * begin, Place * end)
{
	  float distancex = abs((end->getCoords().first-begin->getCoords().first));
	  distancex*=distancex;
	  float distancey = abs((end->getCoords().second-begin->getCoords().second));
	  distancey*=distancey;
	  float calcdistance = sqrt(abs(distancex - distancey));

	  return calcdistance;
}

/**
 * @brief Must be called if changeTravellerRoute or addTraveller or removeTraveller is called,
 * goes through travellers vector and changes available seats for each place in route vector
 */
void Trip::recalculateRouteSeats()
{
	int beginning { };
	int end { };
	for(unsigned int i=0;i<route.size();i++)
	{
		route[i].second=0;
	}
	for(unsigned int i=0;i<travellers.size();i++)
	{
		beginning=findPlaceIndex(travellers[i].second[0]);
		end=findPlaceIndex(travellers[i].second[travellers[i].second.size()-1]);
		incrementVacancies(beginning,end);
	}
}

/**
 * @brief finds a place's index in the route
 * @param p Place * place to know index of
 * @return int index, in case of success, else -1
 */
int Trip::findPlaceIndex(Place * p)
{
	for(unsigned int i=0;i<route.size();i++)
	{
		if(route[i].first==p)
			return i;
	}
	return -1;
}

/**
 * @brief increments the number of vacant seats in a trip
 * @param b int index of beginning place to alter
 * @param e int index of end place to alter
 */
void Trip::incrementVacancies(int b, int e)
{
	for(int i=b; i<=e; i++)
	{
		route[i].second++;
	}
}

//CRUD for travellers participating in trip

/**
 * @brief adds a traveller to a trip, recalculates the number of available seats
 * @param t Person * person to be added
 * @param r vector<Place *> person's itinerary
 */
void Trip::addTraveller(Person * t,vector<Place *> r)
{
	pair<Person * ,vector<Place*> > p(t,r);
	travellers.push_back(p);
	recalculateRouteSeats();
}

/**
 * @brief removes a traveller from a trip, recalculates the number of available seats
 * @param t Person * person to be removed
 */
void Trip::removeTraveller(Person * t)
{
	for(unsigned int i=0;i<travellers.size();i++)
	{
		if(travellers[i].first==t)
			travellers.erase(travellers.begin()+i);
	}
	recalculateRouteSeats();
}

/**
 * @brief updates a traveller's trip
 * @param t Person * person which trip should be altered
 * @param r vector<Place *> person's itinerary
 */
void Trip::updateTravellerRoute(Person *t,vector<Place *>r)
{
	for(unsigned int i=0;i<travellers.size();i++)
	{
		if(travellers[i].first==t)
			travellers[i].second=r;
	}
}

/**
 * @brief Writes all the information about a trip's travellers to a string
 * @return string with the traveller's information
 */
void Trip::printTravellers()
{
	stringstream ss;
	for (unsigned int i = 0; i < travellers.size(); i++)
	{
		ss << "Person: " << travellers[i].first << " Route: ";
		for (unsigned int j = 0; j < route.size(); j++)
		{
			if (j == travellers[i].second.size() - 1)
				ss << travellers[i].second[j]->toString();
			else
				ss << travellers[i].second[j]->toString() << "->";
		}
		ss << endl;
	}
	cout << ss.str();
}

/**
 * @brief Checks if a trip has a certain itinerary
 * @param src string with the origin place's name
 * @param dest string with the end place's name
 * @return if the itinerary was found
 */
bool Trip::hasDestination(string src,string dest)
{
	bool srcfound=false;
	bool destfound=false;
	for(int i=0;i<route.size();i++)
	{
		if(route[i].first->getName()==src)
			srcfound=true;
		if(srcfound)
			if(route[i].first->getName()==dest)
				destfound=true;
	}
	if(srcfound && destfound)
		return true;
	return false;
}

/**
 * @brief Checks if a trip is full for a certain itinerary
 * @param src string with the origin place's name
 * @param dest string with the end place's name
 * @return if the itinerary is full
 */
bool Trip::isFull(string src, string dest)
{
	int bi;
	int ei;
	for(unsigned int i=0;i<route.size();i++)
	{
		if(route[i].first->getName()==src)
			bi=i;
		if(route[i].first->getName()==dest)
			ei=i;
	}
	for(int j=bi;j<=ei;j++){
		//if not full
		if(route[j].second<available_seats)
			return false;
	}
	return true;
}

/**
 * @brief Checks if a person is a traveller
 * @param p Person * with the person to check
 * @return if the person is a traveller
 */
bool Trip::isTraveller(Person * p)
{
	for(unsigned int i=0;i<travellers.size();i++)
	{
		if(travellers[i].first->getName()==p->getName())
			if(travellers[i].first->getTelNr()==p->getTelNr())
			return true;
	}
	return false;
}

/**
 * @brief Compares the start dates of two trips
 * @param i Trip* trip to compare
 * @param j Trip* other trip to compare the first one to
 * @return if the first trip is more recent than the other one
 */
bool Trip::compareTrips (Trip* i,Trip* j)
{
	return (j->getStart() < i->getStart());
}

/**
 * @brief Compares the driver names of two trips
 * @param i Trip* trip to compare
 * @param j Trip* other trip to compare the first one to
 * @return if the first trip's driver has a name with alphabetical precedence over the other
 */
bool Trip::compareTripsDriverName (Trip* i,Trip* j)
{
	return (i->getDriver())<(j->getDriver());
}

/**
 * @brief Writes all the information about a trip to a string
 * @return string with the trip's information
 */
string Trip::toString()
{
	stringstream ss;
	ss << "Driver: " << vehicleOwner << " |Route: ";
	for (unsigned int i = 0; i < route.size (); i++)
	{
		if (i == route.size () - 1)
			ss << route[i].first->toString ();
		else
			ss << route[i].first->toString () << "->";
	}
	ss << " |Initial Date: " << start.str () << " |End Date: " << end.str ();
	return ss.str ();
}

/**
 * @brief Writes all the information about a trip of a person to a string
 * @param name string with the person's name
 * @param nr long with the person's telephone number
 * @return string with the person's trip information
 */
string Trip::toStringByPerson (string name, long nr)
{
	stringstream ss;
	unsigned int index = -1;
	ss << "Driver: " << vehicleOwner << " |Route: ";
	for (unsigned int i = 0; i < travellers.size (); i++)
	{
		if (travellers[i].first->getName () == name && travellers[i].first->getTelNr () == nr)
		{
			index = i;
			break;
		}

	}
	for (unsigned int j = 0; j < travellers[index].second.size (); j++)
	{
		if (j == travellers[index].second.size () - 1)
			ss << travellers[index].second[j]->getName ();
		else
			ss << travellers[index].second[j]->getName () << "->";
	}
	ss << "|Initial Date: " << start.str () << " |End Date: " << end.str ();

	return ss.str ();
}

priority_queue<Person*, vector<Person*>, greater<Person*> > Trip::addtopriorityQ(RegPerson* a){
	return travellerQueue;
}
