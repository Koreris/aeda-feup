/*
 * LyFtEr.h
 *
 *  Created on: Nov 24, 2016
 *      Author: Holykael1
 */

#ifndef LYFTER_H_
#define LYFTER_H_
#include "includes.h"
#include "Date.h"
#include "Person.h"
#include "Place.h"
#include "Trip.h"
#include "Vehicle.h"
#include "Logic.h"
#include <windows.h>

#include <algorithm>
enum states
			{
				mainMenu,
				loginMenu,
				searchTripMenu,
				historyMenu,
				paymentMenu,
				buddiesMenu,
				settingsMenu,
				chooseTripMenu,
				adminMenu,
				createTripMenu,
				signUpMenu
			};


class Lyfter
{
private:
	Logic l;
public:
	states curr_state;
	states prev_state;
	Lyfter(Logic logic);
	void displayDestinations();
	void displayRegisteredUsers();
	bool removeDestination();
	bool updateDestination();
	bool addDestination();
	bool adminLogin();
	void chargeMonthlyFee();
	void displayAdminMenu();
	bool userLogin();
	bool guestLogin();
	bool registerUser();
	void displaySignUpMenu();
	void displayMainMenu();
	void displayLoginMenu();
	void displayVehicles(vector<Vehicle *>v);
	void addDestinationsTrip(Trip *t);
	bool createTrip();
	void chooseTrip(vector<Trip *> v,vector<Place*>p);
	bool userDest();
	bool allVacantTrips();
	long displayTripMenu();
	void tripSortByDriverName();
	void displayBySmoking();
	void displayTripsDriving();
	void displayFutureTrips();
	void displayPastTrips();
	void displayAllTrips();
	void displayTripHistoryMenu();
	void displayBuddies(vector <RegPerson *> buds);
	bool rmBuddyUsername();
	bool findBuddyUsername();
	void displayBuddyMenu();
	void displayPaymentMenu();
	Vehicle* makeVehicle();
	bool rmVehicle();
	bool changePassword(RegPerson* p);
	void displaySettingsMenu();


};




#endif /* LYFTER_H_ */
