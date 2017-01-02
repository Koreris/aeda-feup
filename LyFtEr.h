/*
 * LyFtEr.h
 *
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
				signUpMenu,
				advSearchOpt
			};
/**
 * @brief Lyfter class
 *
 * Class that defines the highest layer of the application, UI and user interaction handling
 * including the display of all the menus and listings, the crud functions that require user input.
 * Connects with logic class to be the main hub of the program
 */
class Lyfter
{
private:
	Logic l;
public:
	states curr_state;
	states prev_state;
	Lyfter(Logic logic);


	/** @name Contains the display functions of the UI
	 */
	///@{
	//all the menus
	void displayAdminMenu();
	void displaySignUpMenu();
	void displayMainMenu();
	void displayLoginMenu();
	void displayBuddyMenu();
	void displayPaymentMenu();
	long displayTripMenu();
	void displaySettingsMenu();
	///@}

	/** @name Menu display utilities, many with filters and sorted methods
	 */
	///@{
	//display utilities
	void displayVehicles(vector<Vehicle *>v);
	void displayDestinations();
	void displayRegisteredUsers();
	void displayBySmoking();
	void displayTripsDriving();
	void tripSortByDriverName();
	void displayFutureTrips();
	void displayPastTrips();
	void displayAllTrips();
	void displayTripHistoryMenu();
	void displayAdvSearchOptMenu();
	void displayBuddies(vector <RegPerson *> buds);
	///@}

	/** @name Menu functionalities - Including CRUDS and searching/choosing trips
	 */
	///@{
	//Admin functionalities
	bool removeDestination();
	bool updateDestination();
	bool addDestination();
	bool updateAddress();
	void chargeMonthlyFee();
	//Choose trips
	bool allVacantTrips();
	void chooseTrip(vector<Trip *> v,vector<Place*>p);
	bool userDest();
	bool createTrip();
	void addDestinationsTrip(Trip *t);
	//User functionalities
	bool registerUser();
	bool changePassword(RegPerson* p);
	bool adminLogin();
	bool userLogin();
	bool guestLogin();
	bool rmBuddyUsername();
	bool findBuddyUsername();
	Vehicle* makeVehicle();
	bool rmVehicle();
	bool transferVehicleTo();

	//BST Search

	bool BSTSearchByBrand();
	bool BSTSearchByModel();
	bool BSTSearchByYear();
	bool BSTSearchByType();

	///@}



};




#endif /* LYFTER_H_ */
