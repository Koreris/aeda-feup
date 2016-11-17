#include "includes.h"
#include "BuddyList.h"
#include "Date.h"
#include "Person.h"
#include "Place.h"
#include "Trip.h"
#include "Vehicle.h"

void displayLogo()
{
//	__ __  __ ______ ______ ______ ____ 
//   / / \ \/ // ____//_  __// ____// __ \
//  / /   \  // /_     / /  / __/  / /_/ /
// / /___ / // __/    / /  / /___ / _, _/ 
///_____//_//_/      /_/  /_____//_/ |_|
}

void displayMainMenu()
{
	cout << "Welcome to LyFtEr!" << endl
		<< "|*****************************************************************|" << endl <<
		"| 1.  Login!                                                       |" << endl <<
		"| 2.  Search for next trip                                        |" << endl <<
		"| 3.  Trip history                                                |" << endl <<
		"| 4.  Payment options                                             |" << endl <<                                                    |" << endl <<
		"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
}

void displayLoginMenu()
{
	cout << "You are logged in! Here are your options:" << endl
		<< "|*****************************************************************|" << endl <<
		"| 1.  Search for your next trip                                   |" << endl <<
		"| 2.  Your trip history                                           |" << endl <<
		"| 3.  Your buddies                                                |" << endl <<
		"| 4.  Your payment options                                        |" << endl <<
		"| 4.  Your settings                                               |" << endl <<
		"| 5.  Log out                                                     |" << endl <<
		"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
}

void displayTripMenu()
{
	cout << "Let's find you your next trip! Pick your filters:" << endl
		<< "|*****************************************************************|" << endl <<
		"| +.  During your next trip you'll want to...                     |" << endl <<
		"| 1.  Smoke in the car                                            |" << endl <<
		"| 2.  Travel with buddy X                                         |" << endl <<
		"| 3.  Travel in X type of vehicle                                 |" << endl <<
		"| 4.  Go back to previous menu                                    |" << endl <<
		"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
}

void displayTripHistoryMenu()
{
	cout << "Do you want to filter your history? If so, pick your filters: " << endl
		<< "|*****************************************************************|" << endl <<
		"| 1.  By vehicle type                                             |" << endl <<
		"| 2.  By driver name                                              |" << endl <<
		"| 3.  By accompanying buddy name                                  |" << endl <<
		"| 4.  I don't want any of those, show me all of my trips          |" << endl <<
		"| 5.  Go back to previous menu                                    |" << endl <<
		"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
}

void displayBuddyMenu()
{
	cout << "Here are your buddies! If you want, be sure to add more! " << endl
		<< "|*****************************************************************|" << endl <<
		"| 1.  Add buddy                                                   |" << endl <<
		"| 2.  Remove buddy                                                |" << endl <<
		"| 3.  Display all buddies                                         |" << endl <<
		"| 4.  Go back to previous menu                                    |" << endl <<
		"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
}

void displayPaymentMenu()
{
	cout << "Here you can manage your wallet and payment options: " << endl
		<< "|*****************************************************************|" << endl <<
		"| 1.  Add funds                                                   |" << endl <<
		"| 2.  Consult all your payment                                    |" << endl <<
		"| 3.  Consults all your transactions                              |" << endl <<
		"| 4.  Go back to previous menu                                    |" << endl <<
		"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
}

