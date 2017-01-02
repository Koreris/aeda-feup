#include "LyFtEr.h"

/**
 * Prompts user to press enter, mimicking a paused state until user presses enter
 * @brief press enter to continue
 */
void
pressEnter ()
{
	cout << "Press Enter to continue..." << endl;
	getchar ();
}
/**
 * Uses windows related functions to clear console screen
 * @brief clears console screen
 */
void
cls ()
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle (STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo (console, &screen);
	FillConsoleOutputCharacterA (console, ' ',
									screen.dwSize.X * screen.dwSize.Y, topLeft,
									&written);
	FillConsoleOutputAttribute (console,
	FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
								screen.dwSize.X * screen.dwSize.Y, topLeft,
								&written);
	SetConsoleCursorPosition (console, topLeft);
}

/**
 * @brief Lyfter constructor
 * @param logic logic object
 */
Lyfter::Lyfter (Logic logic)
{
	l = logic;
	curr_state = signUpMenu;
	prev_state = signUpMenu;
}

///admin stuff
/**
 * Updates the address of a selected user, if user in inactive users hashtable, updates the hashtable entry too
 * @brief updates the address of a selected user
 * @return true on success update, false otherwise
 */
bool
Lyfter::updateAddress ()
{
	cls ();
	string index = "";
	string newAddress = "";
	bool validIndex = false;
	long index_;
	unsigned int i;
	displayRegisteredUsers ();
	cout << "Input the index of the user whose index you want to update " << endl;
	while (!validIndex)
	{

		getline (cin, index);
		cin.clear ();
		if (index == "F" || index == "f")
		{
			cls ();
			break;
		}
		index_ = stol (index);
		i = index_;
		if (i <= l.getRegUsers ().size () - 1 && i >= 0)
		{
			validIndex = true;
			cout << "Input the new address(Old Address:" << l.getRegUsers ()[i]->getAddress () << endl;
			getline (cin, newAddress);
			cin.clear ();
			RegHashTable::iterator it = l.getInactiveUsers ().find (
							l.getRegUsers ()[i]);
			if (it != l.getInactiveUsers ().end ())
			{
				l.getInactiveUsers ().erase (l.getRegUsers ()[i]);
			}
			l.getRegUsers ()[i]->setAddress (newAddress);
			cout << "Address updated successfully to:" << l.getRegUsers ()[i]->getAddress () << endl;
			l.getInactiveUsers ().insert (l.getRegUsers ()[i]);
			l.save_data ();
			return true;
		}
		cout << "Invalid index! Please input again." << endl;
	}
	return false;
}
/**
 * Displays destinations
 * @brief displays destinations
 */
void
Lyfter::displayDestinations ()
{
	for (unsigned int i = 0; i < l.getDestinations ().size (); i++)
	{
		cout << i << ":" << l.getDestinations ()[i]->toString () << endl;
	}
}
/**
 * Displays registered users
 * @brief displays registered
 */
void
Lyfter::displayRegisteredUsers ()
{
	for (unsigned int i = 0; i < l.getRegUsers ().size (); i++)
	{
		cout << i << ":";
		l.getRegUsers ()[i]->printPersonAdmin ();
	}
}
/**
 * Displays destinations and prompts user for an index of destination to delete
 * @brief prompts user for index of destination he wants to deletes
 */
bool
Lyfter::removeDestination ()
{
	string index = "";
	bool validIndex = false;
	long index_;
	unsigned int i;
	displayDestinations ();
	cout << "Input the index of the destination you want to remove:(or input F to leave) " << endl;
	while (!validIndex)
	{

		getline (cin, index);
		cin.clear ();
		if (index == "F" || index == "f")
		{
			cls ();
			break;
		}
		//cin.ignore(10000, '\n');
		index_ = stol (index);
		i = index_;
		if (i <= l.getDestinations ().size () - 1 && i >= 0)
		{
			validIndex = true;
			cout << "Destination " << l.getDestinations ()[i] << " removed successfully" << endl;
			l.deleteDestinations (i);
			l.save_data ();
			return true;
		}
		cout << "Invalid index! Please input again." << endl;
	}
	return false;
}
/**
 * Displays destinations and prompts user for an index of destination to update coordinates of
 * @brief prompts user for index of destination he wants to update the coordinates of
 */
bool
Lyfter::updateDestination ()
{
	string index = "";
	string x = "";
	string y = "";
	bool validIndex = false;
	long index_;
	unsigned int i;
	displayDestinations ();
	cout << "Input the index of the destination you want to update:(or input F to leave) " << endl;
	while (!validIndex)
	{
		getline (cin, index);
		cin.clear ();
		//cin.ignore(10000, '\n');
		index_ = stol (index);
		i = index_;
		if (i <= l.getDestinations ().size () - 1 && i >= 0)
		{
			cout << "Input x coord:(or input F to leave) " << endl;
			getline (cin, x);
			cin.clear ();
			cout << "Input y coord:(or input F to leave) " << endl;
			getline (cin, y);
			cin.clear ();
			l.getDestinations ()[i]->setCoords (stol (x), stol (y));
			l.save_data ();
			cout << l.getDestinations ()[i]->getName () << "(" << x << "," << y << ") " << " updated successfully" << endl;
		}
		cout << "Invalid index! Please input again." << endl;
	}
	return false;
}
/**
 * Prompts user to input necessary info to create a new destination, adds to destinations vector
 * @brief prompts user for info to create a new destination and adds it
 */
bool
Lyfter::addDestination ()
{
	string destname = "";
	string x = "";
	string y = "";
	bool found = false;
	while (!found)
	{
		cout << "Input the destination name:(or input F to leave) " << endl;
		getline (cin, destname);
		cin.clear ();
		cout << "Input x coord:(or input F to leave) " << endl;
		getline (cin, x);
		cin.clear ();
		cout << "Input y coord:(or input F to leave) " << endl;
		getline (cin, y);
		cin.clear ();
		Place * p = new Place (destname, pair<int, int> (stol (x), stol (y)));
		l.getDestinations ().push_back (p);
		l.save_data ();
		cout << destname << "(" << x << "," << y << ") " << " added successfully" << endl;
		return true;
	}
	return false;
}
/**
 * Prompts for admin credentials and returns true if valid credentials
 * @brief prompts for admin credentials
 * @return if admin credentials are correct or not
 */
bool
Lyfter::adminLogin ()
{
	string usr = "";
	string passw = "";

	cout << "Input your username: " << endl;
	getline (cin, usr);
	cin.clear ();
	cout << "Input your password: " << endl;
	getline (cin, passw);
	cin.clear ();
	return usr == "admin" && passw == "admin";
}
/**
 * Adds bill to all registered users of monthly maintenance fee
 * @brief charges maintenance fee
 */
void
Lyfter::chargeMonthlyFee ()
{
	for (int i = 0; i < l.getRegUsers ().size (); i++)
	{
		l.getRegUsers ()[i]->addBill ("monthly", 0);
	}
}
/**
 * @brief  Displays administration menu and changes states accordingly to user input
 */
void
Lyfter::displayAdminMenu ()
{
	string user_in;
	long user_in_;
	bool validInput = false;
	while (!validInput)
	{
		cout << "\n Administration Menu \n\n" << endl << " +============================================================================+" << endl << " | 1.  Add destinations                                                       |" << endl << " | 2.  Delete destinations                                                    |" << endl << " | 3.  Update destination coordinates                                         |" << endl << " | 4.  List Destinations                                                      |" << endl << " | 5.  List Registered Users                                                  |" << endl << " | 6.  Charge Registered Users Monthly Fee                                    |" << endl << " | 7.  Update Registered Users addresses                                      |" << endl << " | 8.  List Inactive Users                                                    |" << endl << " | 9.  Back to Sign Up                                                        |" << endl << " +============================================================================+\n" << endl;
		cout << "\n Selected number from menu:\n";

		getline (cin, user_in);
		cin.clear ();
		//cin.ignore(10000, '\n');
		user_in_ = stol (user_in);
		if (user_in_ >= 1 && user_in_ <= 9)
		{
			validInput = true;
			switch (user_in_)
			{
			case 1:
				addDestination ();
				pressEnter ();
				cls ();
				break;
			case 2:
				removeDestination ();
				pressEnter ();
				cls ();
				break;
			case 3:
				updateDestination ();
				pressEnter ();
				cls ();
				break;
			case 4:
				displayDestinations ();
				pressEnter ();
				cls ();
				break;
			case 5:
				displayRegisteredUsers ();
				pressEnter ();
				cls ();
				break;
			case 6:
				chargeMonthlyFee ();
				pressEnter ();
				cls ();
				break;
			case 7:
				updateAddress ();
				pressEnter ();
				cls ();
				break;
			case 8:
				l.printHash ();
				pressEnter ();
				cls ();
				break;
			case 9:
				prev_state = curr_state;
				curr_state = signUpMenu;
				cls ();
				break;
			}
		}
	}
	return;
}
///end of admin stuff

///login section
/**
 * Prompts for user credentials,validates them and does the actual login
 * @brief prompts for user credentials and logins
 * @return if successful login
 */
bool
Lyfter::userLogin ()
{
	string usr = "";
	string passw = "";

	cout << "Input your username: " << endl;
	getline (cin, usr);
	cin.clear ();
	//cin.ignore(10000, '\n');
	cout << "Input your password: " << endl;
	getline (cin, passw);
	cin.clear ();
	//cin.ignore(10000, '\n');
	return (l.userLogin (usr, passw));
}
/**
 * Prompts for guest credentials,creates guest, logins as guest
 * @brief prompts guest credentials and login as guest
 * @return if successful login
 */
bool
Lyfter::guestLogin ()
{
	string usr = "";
	string phone = "";
	long phonenr = 0;

	cout << "Input your Name: " << endl;
	getline (cin, usr);
	cin.clear ();
	if (usr == "")
	{
		cout << "Invalid name" << endl;
		return false;
	}
	//cin.ignore(10000, '\n');
	cout << "Input your telephone number: " << endl;
	getline (cin, phone);
	phonenr = stol (phone);
	cin.clear ();
	l.setLogin (false);
	l.curr_unreg = new UnregPerson (usr, phonenr);
	return true;
}
/**
 * Prompts for user credentials,creates new user and registers them if it doesn't exist
 * @brief prompts for user credentials and registers new user
 * @return if user succesfully registered
 */
bool
Lyfter::registerUser ()
{
	string usr = "";
	string passw = "";
	string name = "";
	string phone = "";
	string addr = "";
	long phonenr;
	bool validUser = false;
	cout << "Input your desired username: " << endl;
	while (!validUser)
	{
		getline (cin, usr);
		cin.clear ();
		if (l.usernameExists (usr))
			cout << "Username already exists, try another one" << endl;
		else
			validUser = true;
	}
	cout << "Input your password: " << endl;
	getline (cin, passw);
	cin.clear ();

	cout << "Input your address: " << endl;
	getline (cin, addr);
	cin.clear ();

	cout << "Input your real name: " << endl;
	getline (cin, name);
	cin.clear ();
	if (usr == "")
	{
		cout << "Invalid name" << endl;
		return false;
	}
	//cin.ignore(10000, '\n');
	cout << "Input your telephone number: " << endl;
	getline (cin, phone);
	phonenr = stol (phone);
	cin.clear ();
	RegPerson * user = new RegPerson (name, addr, phonenr, usr, passw,
										l.get_curDate ());
	l.getRegUsers ().push_back (user);
	l.save_data ();
	cout << "Added user: ";
	user->printPerson ();
	return true;
}
/**
 * @brief  Displays sign up menu and changes states accordingly to user input
 */
void
Lyfter::displaySignUpMenu ()
{
	string user_in;
	long user_in_;
	bool validInput = false;
	while (!validInput)
	{
		cout << "\n Welcome to LyFtEr! \n\n" << endl << " +============================================================================+" << endl << " | 1.  Login                                                                  |" << endl << " | 2.  Use as guest                                                           |" << endl << " | 3.  Create an account                                                      |" << endl << " | 4.  Administration                                                         |" << endl << " | 5.  Exit                                                                   |" << endl << " +============================================================================+\n" << endl;
		cout << "\n Selected number from menu:\n";

		getline (cin, user_in);
		cin.clear ();
		//cin.ignore(10000, '\n');
		user_in_ = stol (user_in);
		if (user_in_ >= 1 && user_in_ <= 5)
		{
			validInput = true;
			switch (user_in_)
			{
			case 1:
				if (userLogin ())
				{
					prev_state = curr_state;
					curr_state = loginMenu;
					cls ();
				}
				else
				{
					curr_state = prev_state;
					validInput = false;

				}
				break;
			case 2:
				if (guestLogin ())
				{
					prev_state = curr_state;
					curr_state = mainMenu;
				}
				cls ();
				break;
			case 3:
				registerUser ();
				pressEnter ();
				cls ();
				break;
			case 4:
				if (adminLogin ())
				{
					prev_state = curr_state;
					curr_state = adminMenu;
					cls ();
					break;
				}
				else
					cout << "Failed to login into admin" << endl;
				pressEnter ();
				cls ();
				break;
			case 5:
				exit (0);
			}
		}
	}
	return;
}
/**
 * @brief  Displays guest menu and changes states accordingly to user input
 */
void
Lyfter::displayMainMenu ()
{
	string user_in;
	long user_in_;
	bool validInput = false;
	while (!validInput)
	{
		cout << "\n Welcome to LyFtEr! \n\n" << endl << " +============================================================================+" << endl << " | 1.  Search for next trip                                                   |" << endl << " | 2.  Trip history                                                           |" << endl << " | 3.  Payment options                                                        |" << endl << " | 4.  Exit guest                                                             |" << endl << " +============================================================================+\n" << endl;
		cout << "\n Selected number from menu:\n";

		getline (cin, user_in);
		cin.clear ();
		//cin.ignore(10000, '\n');
		user_in_ = stol (user_in);
		if (user_in_ >= 1 && user_in_ <= 4)
		{
			validInput = true;
			switch (user_in_)
			{

			case 1:
				prev_state = curr_state;
				curr_state = searchTripMenu;
				cls ();
				break;
			case 2:
				prev_state = curr_state;
				curr_state = historyMenu;
				cls ();
				break;
			case 3:
				prev_state = curr_state;
				curr_state = paymentMenu;
				cls ();
				break;
			case 4:
				if (l.curr_unreg->getBilling () > 0)
				{
					cout << "Sir/Madam " << l.curr_unreg->getName () << ", Pay your debts first!" << endl;
					pressEnter ();
					cls ();
					break;
				}
				cout << "Goodbye " << l.curr_unreg->getName () << endl;
				l.curr_unreg = NULL;
				prev_state = curr_state;
				curr_state = signUpMenu;
				pressEnter ();
				cls ();
				break;
			}
		}
	}
	return;
}
/**
 * @brief  Displays user logged in menu and changes states accordingly to user input
 */
void
Lyfter::displayLoginMenu ()
{
	cls ();
	string user_in;
	long user_in_;
	bool validInput = false;
	cout << "You are logged in! Here are your options:" << endl << "|*****************************************************************|" << endl << "| 1.  Search for your next trip                                   |" << endl << "| 2.  Create a trip (drivers only)                                |" << endl << "| 3.  Your trip history                                           |" << endl << "| 4.  Your buddies                                                |" << endl << "| 5.  Your payment options                                        |" << endl << "| 6.  Your settings                                               |" << endl << "| 7.  Log out                                                     |" << endl << "|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	while (!validInput)
	{
		getline (cin, user_in);
		cin.clear ();
		//cin.ignore(10000, '\n');
		user_in_ = stol (user_in);
		if (user_in_ >= 1 && user_in_ <= 7)
		{
			validInput = true;
			switch (user_in_)
			{
			case 1:
				prev_state = curr_state;
				curr_state = searchTripMenu;
				cls ();
				break;
			case 2:
				prev_state = curr_state;
				curr_state = createTripMenu;
				cls ();
				break;
			case 3:
				prev_state = curr_state;
				curr_state = historyMenu;
				cls ();
				break;
			case 4:
				prev_state = curr_state;
				curr_state = buddiesMenu;
				cls ();
				break;
			case 5:
				prev_state = curr_state;
				curr_state = paymentMenu;
				cls ();
				break;
			case 6:
				prev_state = curr_state;
				curr_state = settingsMenu;
				cls ();
				break;
			case 7:
				l.setLogin (false);
				prev_state = curr_state;
				curr_state = signUpMenu;
				cls ();
				break;
			}
		}
	}
	return;
}
///end of login section

///create trips section
/**
 * @brief Adds destinations to trip route vector
 * @param t trip we want to add destinations to
 */
void
Lyfter::addDestinationsTrip (Trip *t)
{
	string place = "";
	Place * dest;
	bool pressFtoPayRespects = false;
	vector<pair<Place *, int> > route = vector<pair<Place *, int> > ();
	//QUERYING FOR DESTINATIONS
	cout << "Input Route: One Destination at a time, input string 'F' to end input of destinations " << endl;
	while (!pressFtoPayRespects)
	{
		getline (cin, place);
		cin.clear ();
		//cin.ignore(10000, '\n');
		if (place == "F" || place == "f")
		{
			t->addRoute (route);
			pressFtoPayRespects = true;
			break;
		}
		if ((dest = l.findDest (place)) == NULL)
		{
			cout << "Destination isn't registered in the application yet, please register destination first" << endl;
			continue;
		}
		else
		{
			pair<Place*, int> p (dest, 0);
			route.push_back (p);
			cout << "Added " << dest->getName () << " to route." << endl;
		}

	}
}
/**
 * Prompts for user input of necessary data to create a new trip, user is the driver
 * @brief create a new trip, current user is driver
 */
bool
Lyfter::createTrip ()
{

	if (!(l.curr_user->getHasVehicle ()))
	{
		curr_state = prev_state;
		return false;
	}

	Date start_date;
	Date end_date;
	string usr = l.curr_user->getUsern ();
	string index = "";
	string begindate = "";
	string finishdate = "";
	string smoking = "";
	bool smk = false;
	unsigned long i;
	bool validIndex = false;
	bool validSmoke = false;
	bool validBeginDate = false;
	bool validEndDate = false;

	//QUERYING FOR SMOKING CONDITION
	cout << "Is smoking allowed on this trip? Input 0 for no, 1 for yes: " << endl;
	while (!validSmoke)
	{
		getline (cin, smoking);
		cin.clear ();
		//cin.ignore(10000, '\n');
		if (stol (smoking) != 0 && stol (smoking) != 1)
			continue;
		smk = stol (smoking);
		validSmoke = true;
	}

	//QUERYING TO CHOOSE VEHICLE
	displayVehicles (l.curr_user->getVehicles ());
	cout << "Input the index of the vehicle you want to use for this trip: " << endl;
	while (!validIndex)
	{
		getline (cin, index);
		cin.clear ();
		//cin.ignore(10000, '\n');
		i = stol (index);

		if (i <= l.curr_user->getVehicles ().size () - 1 && i >= 0)
		{
			validIndex = true;

		}
		if (!validIndex)
			cout << "Invalid index! Please input again." << endl;
	}

	//QUERYING TO TRIP START DATE

	cout << "Input the start date in format -> year month day hour minute second " << endl;
	while (!validBeginDate)
	{
		getline (cin, begindate);
		cout << begindate << endl;
		cin.clear ();
		//cin.ignore(10000, '\n');
		try
		{
			Date s (begindate);
			start_date = s;

		}
		catch (Date::InvalidDate &d)
		{
			cout << "Invalid input of Date format" << endl;
			continue;
		}
		if (start_date < l.get_curDate ())
			cout << "Cannot make trips in the past, try again" << endl;
		else
			validBeginDate = true;
	}

	//QUERYING TO TRIP END DATE

	cout << "Input the end date in format -> year month day hour minute second " << endl;
	while (!validEndDate)
	{
		getline (cin, finishdate);
		cin.clear ();
		cout << finishdate << endl;
		//cin.ignore(10000, '\n');
		try
		{
			Date e (finishdate);
			end_date = e;
		}
		catch (Date::InvalidDate &d)
		{
			cout << "Invalid input of Date format" << endl;
			continue;
		}
		if (end_date < start_date)
			cout << "Cannot have end date earlier than start date, try again" << endl;
		else
			validEndDate = true;
	}

	Trip * t = new Trip (
					usr, l.curr_user->getVehicles ().at (i)->getLicensePlate (),
					l.curr_user->getVehicles ()[i], smk, start_date, end_date);
	addDestinationsTrip (t);
	l.getCurTrips ().push_back (t);
	l.save_data ();
	cout << "Successfully added the trip: " << t->toString () << endl;
	curr_state = prev_state;
	pressEnter ();
	cls ();
	return true;
}
///end create trips section

///trip search section
/**
 * Displays trips in vector v and prompts user to choose the index of the trip he wants to sign up for.
 * Adds the user as traveller in said trip's traveller vector
 * @brief sign up for a trip with destinations of choice
 * @param v vector of trips that the user can choose
 * @param p vector of places with start and end destinations of the user, needed to add traveller info to trip
 */
void
Lyfter::chooseTrip (vector<Trip *> v, vector<Place*> p)
{
	bool validIndex = false;
	string index = "";
	int i;
	for (unsigned int j = 0; j < v.size (); j++)
	{
		cout << j << ":" << v[j]->toString () << endl;
	}
	cout << "Input the index of the trip you want to sign up for: " << endl;
	while (!validIndex)
	{
		getline (cin, index);
		cin.clear ();
		//cin.ignore(10000, '\n');
		i = stol (index);

		if (i <= v.size () - 1 && i >= 0)
		{
			validIndex = true;
			if (p.size () == 0)
			{
				p.push_back (v[i]->getRoute ()[0].first);
				p.push_back (v[i]->getRoute ()[v[i]->getRoute ().size () - 1].first);
			}
			if (l.login)
			{
				p.push_back (v[i]->getRoute ()[0].first);
				v[i]->addTraveller (l.curr_user, p);
				l.curr_user->addBill ("trip", v[i]->getDistance ());
				l.save_data ();
			}
			else
			{
				v[i]->addTraveller (l.curr_unreg, p);
				l.curr_unreg->addBill ("trip", v[i]->getDistance ());
				l.save_data ();
			}
			pressEnter ();
		}
		if (!validIndex)
			cout << "Invalid index! Please input again." << endl;
	}

}
/**
 * Prompts user for desired begin destination and end destination
 * @brief choose begin and end destinations
 * @return true if destinations inputted are valid and exist and that there are trips with said destinations
 */
bool
Lyfter::userDest ()
{
	cls ();
	string dest = "";
	string origin = "";
	Place * place;
	vector<Trip *> temp = vector<Trip *> ();
	vector<Place *> places = vector<Place*> ();
	bool found = false;

	while (!found)
	{
		cout << "Input your origin:(or F to quit selection) " << endl;
		getline (cin, origin);
		cin.clear ();

		if (origin == "F" || origin == "f")
			break;
		cout << "Input your destination: " << endl;
		getline (cin, dest);
		cin.clear ();
		if (l.login)
			temp = l.findTrips (origin, dest, l.curr_user);
		else
			temp = l.findTrips (origin, dest, l.curr_unreg);
		if (temp.size () > 0)
		{
			cout << "Found possible trips" << endl;
			place = l.findDest (origin);
			places.push_back (place);
			place = l.findDest (dest);
			places.push_back (place);
			found = true;
			chooseTrip (temp, places);
			l.save_data ();
			cls ();
			return true;
		}
		cout << "Trips following that route not found! Please input new data." << endl;
	}
	return false;
}
/**
 * Displays all trips with vacancies
 * Prompts user to choose the index of the trip he wants to sign up for.
 * Adds the user as traveller in said trip's traveller vector
 * @brief sign up for a trip
 * @return true if signed up for trip, false if there are no currently vacant trips
 */
bool
Lyfter::allVacantTrips ()
{
	cls ();
	string dest = "";
	string origin = "";
	Place * place;
	vector<Trip *> temp = vector<Trip *> ();
	vector<Place *> places = vector<Place*> ();
	if (l.login)
		temp = l.findVacantTrips (l.curr_user);
	else
		temp = l.findVacantTrips (l.curr_unreg);
	if (temp.size () > 0)
	{
		cout << " found " << temp.size () << " trips" << endl;
		chooseTrip (temp, places);
		l.save_data ();
		pressEnter ();
		cls ();
		return true;
	}
	cout << "No vacant trips where you aren't currently signed up for found" << endl;
	pressEnter ();
	return false;

}

/**
 * Show vacant trips by brand
 * @brief finds vacant trips by car brand
 * @return true if found results, false otherwise
 */
bool
Lyfter::BSTSearchByBrand ()
{
	cls ();
	string brand = "";
	vector<Trip *> temp = vector<Trip *> ();
	vector<Trip *> valid_t = vector<Trip *> ();
	vector<Place *> places = vector<Place*> ();
	bool searched = false;

	if (l.login)
		temp = l.findVacantTrips (l.curr_user);
	else
		temp = l.findVacantTrips (l.curr_unreg);

	if (temp.size () > 0)
	{
		while (!searched)
		{
			cout << "Input the desired brand with first letter capitalised: (or F to quit selection) " << endl;
			getline (cin, brand);
			cin.clear ();

			if (brand == "F" || brand == "f")
				break;

			BSTItrIn<VehicleWrapper> it (l.getBST ());

			while (!it.isAtEnd ())
			{
				if (it.retrieve ()->getBrand () == brand)
				{
					cout << "Found possible trips" << endl;
					for (unsigned int i = 0; i < temp.size (); i++)
					{
						if (temp[i]->getLicensePlate () == it.retrieve ()->getLicensePlate ())
						{
							valid_t.push_back (temp[i]);
						}
					}
				}
				it.advance ();
			}
			if (valid_t.size () > 0)
			{
				chooseTrip (valid_t, places);
				l.save_data ();
			}
			searched = true;
		}
	}
	return searched;
}

/**
 * Show vacant trips by model
 * @brief finds vacant trips by car model
 * @return true if found results, false otherwise
 */
bool
Lyfter::BSTSearchByModel ()
{
	cls ();
	string model = "";
	vector<Trip *> temp = vector<Trip *> ();
	vector<Trip *> valid_t = vector<Trip *> ();
	vector<Place *> places = vector<Place*> ();
	bool searched = false;

	if (l.login)
		temp = l.findVacantTrips (l.curr_user);
	else
		temp = l.findVacantTrips (l.curr_unreg);

	if (temp.size () > 0)
	{
		while (!searched)
		{
			cout << "Input the desired model with first letter capitalised: (or F to quit selection) " << endl;
			getline (cin, model);
			cin.clear ();

			if (model == "F" || model == "f")
				break;

			BSTItrIn<VehicleWrapper> it (l.getBST ());

			while (!it.isAtEnd ())
			{
				if (it.retrieve ()->getModel () == model)
				{
					cout << "Found possible trips" << endl;
					for (unsigned int i = 0; i < temp.size (); i++)
					{
						if (temp[i]->getLicensePlate () == it.retrieve ()->getLicensePlate ())
						{
							valid_t.push_back (temp[i]);
						}
					}
				}
				it.advance ();
			}
			if (valid_t.size () > 0)
			{
				chooseTrip (valid_t, places);
				l.save_data ();
			}
			searched = true;
		}
		if (!searched)
			cout << "No trips with vehicles of the desired model found!" << endl;
	}
	return searched;
}

/**
 * Show vacant trips by car year
 * @brief finds vacant trips by car year
 * @return true if found results, false otherwise
 */
bool
Lyfter::BSTSearchByYear ()
{
	cls ();
	string year = "";
	vector<Trip *> temp = vector<Trip *> ();
	vector<Trip *> valid_t = vector<Trip *> ();
	vector<Place *> places = vector<Place*> ();
	bool searched = false;

	if (l.login)
		temp = l.findVacantTrips (l.curr_user);
	else
		temp = l.findVacantTrips (l.curr_unreg);

	if (temp.size () > 0)
	{
		while (!searched)
		{
			cout << "Input the desired year: (or F to quit selection) " << endl;
			getline (cin, year);
			cin.clear ();

			if (year == "F" || year == "f")
				break;

			int n_year = stol (year);

			BSTItrIn<VehicleWrapper> it (l.getBST ());

			while (!it.isAtEnd ())
			{
				if (it.retrieve ()->getYear () == n_year)
				{
					cout << "Found possible trips" << endl;
					for (unsigned int i = 0; i < temp.size (); i++)
					{
						if (temp[i]->getLicensePlate () == it.retrieve ()->getLicensePlate ())
						{
							valid_t.push_back (temp[i]);
						}
					}
				}
				it.advance ();
			}
			if (valid_t.size () > 0)
			{
				chooseTrip (valid_t, places);
				l.save_data ();
			}
			searched = true;
		}
		if (!searched)
			cout << "No trips with vehicles of the desired brand found!" << endl;
	}
	return searched;
}

/**
 * Show vacant trips by car type
 * @brief finds vacant trips by car type
 * @return true if found results, false otherwise
 */
bool
Lyfter::BSTSearchByType ()
{
	cls ();
		string type = "";
		vector<Trip *> temp = vector<Trip *> ();
		vector<Trip *> valid_t = vector<Trip *> ();
		vector<Place *> places = vector<Place*> ();
		bool searched = false;

		if (l.login)
			temp = l.findVacantTrips (l.curr_user);
		else
			temp = l.findVacantTrips (l.curr_unreg);

		if (temp.size () > 0)
		{
			while (!searched)
			{
				cout << "Input the desired type with first letter capitalised: (or F to quit selection) " << endl;
				getline (cin, type);
				cin.clear ();

				if (type == "F" || type == "f")
					break;

				BSTItrIn<VehicleWrapper> it (l.getBST ());

				while (!it.isAtEnd ())
				{
					if (it.retrieve ()->getType () == type)
					{
						cout << "Found possible trips" << endl;
						for (unsigned int i = 0; i < temp.size (); i++)
						{
							if (temp[i]->getLicensePlate () == it.retrieve ()->getLicensePlate ())
							{
								valid_t.push_back (temp[i]);
							}
						}
					}
					it.advance ();
				}
				if (valid_t.size () > 0)
				{
					chooseTrip (valid_t, places);
					l.save_data ();
				}
				searched = true;
			}
			if (!searched)
				cout << "No trips with vehicles of the desired type found!" << endl;
		}
		return searched;
}

/**
 * @brief  Displays the options menu for advanced vehicle search
 */
void
Lyfter::displayAdvSearchOptMenu ()
{
	string user_in = "";
	long user_in_;
	bool validInput = false;
	cout << "Here's the advanced vehicle search menu! Pick what you want to search for:" << endl << "|*****************************************************************|" << endl << "| +.  Vehicles by...                                              |" << endl << "| 1.  Brand                                                       |" << endl << "| 2.  Model                                                       |" << endl << "| 3.  Year                                                        |" << endl << "| 4.  Type                                                        |" << endl << "| 5.  Go back to previous menu                                    |" << endl << "|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	while (!validInput)
	{
		getline (cin, user_in);
		cin.clear ();
		user_in_ = stol (user_in);
		if (user_in_ >= 1 && user_in_ <= 5)
		{
			validInput = true;
			switch (user_in_)
			{
			case 1:
				if (BSTSearchByBrand ())
				{
					prev_state = curr_state;
					if (l.login)
						curr_state = loginMenu;
					else
						curr_state = mainMenu;
				}
				else
					cls ();
				break;
			case 2:
				if (BSTSearchByModel ())
				{
					prev_state = curr_state;
					if (l.login)
						curr_state = loginMenu;
					else
						curr_state = mainMenu;
				}
				else
					cls ();
				break;
			case 3:
				if (BSTSearchByYear ())
				{
					prev_state = curr_state;
					if (l.login)
						curr_state = loginMenu;
					else
						curr_state = mainMenu;
				}
				else
					cls ();
				break;
			case 4:
				if (BSTSearchByType ())
				{
					prev_state = curr_state;
					if (l.login)
						curr_state = loginMenu;
					else
						curr_state = mainMenu;
				}
				else
					cls ();
				break;
			case 5:
				prev_state = curr_state;
				if (l.login)
					curr_state = loginMenu;
				else
					curr_state = mainMenu;
				cls ();
				break;
			}
		}
	}
}

/**
 * @brief  Displays search for trips menu and changes states accordingly to user input
 */
long
Lyfter::displayTripMenu ()
{
	string user_in = "";
	long user_in_;
	bool validInput = false;
	cout << "Let's find you your next trip! Pick your filter:" << endl << "|*****************************************************************|" << endl << "| +.  During your next trip you'll want to go to...               |" << endl << "| 1.  X destination                                               |" << endl << "| 2.  Advanced vehicle search                                     |" << endl << "| 3.  I don't care where I go, show all trips with vacancies!     |" << endl << "| 4.  Go back to previous menu                                    |" << endl << "|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	while (!validInput)
	{
		getline (cin, user_in);
		cin.clear ();
		user_in_ = stol (user_in);
		if (user_in_ >= 1 && user_in_ <= 4)
		{
			validInput = true;
			switch (user_in_)
			{
			case 1:
				if (userDest ())
				{
					prev_state = curr_state;
					if (l.login)
						curr_state = loginMenu;
					else
						curr_state = mainMenu;
				}
				else
					cls ();
				break;
			case 2:
				prev_state = curr_state;
				curr_state = advSearchOpt;
				break;
			case 3:
				if (allVacantTrips ())
				{
					prev_state = curr_state;
					if (l.login)
						curr_state = loginMenu;
					else
						curr_state = mainMenu;
				}
				else
				{
					pressEnter ();
					cls ();
				}
				break;
			case 4:
				prev_state = curr_state;
				if (l.login)
					curr_state = loginMenu;
				else
					curr_state = mainMenu;
				cls ();
				break;
			}
		}
	}
}
///end of trip search section

///trip history section
/**
 * @brief  displays old and future trips of user sorted by driver name
 */
void
Lyfter::tripSortByDriverName ()
{
	vector<Trip *> trips = vector<Trip*> ();
	if (l.login)
	{
		trips = l.findFutureTrips (l.curr_user);
		for (unsigned int i = 0; i < l.curr_user->getTripHistory ().size ();
						i++)
		{
			trips.push_back (l.curr_user->getTripHistory ()[i]);
		}
	}
	else
		trips = l.findFutureTrips (l.curr_unreg);

	trips = l.tripSortByDriverName (trips);
	cout << "All Trips sorted by driver name:" << endl;
	for (unsigned int i = 0; i < trips.size (); i++)
	{
		cout << i << ":" << trips[i]->toString () << endl;
	}
}
/**
 * @brief  displays old and future trips of user organized by smoking rules
 */
void
Lyfter::displayBySmoking ()
{
	vector<Trip *> trips = vector<Trip*> ();
	if (l.login)
	{
		trips = l.findFutureTrips (l.curr_user);
		for (unsigned int i = 0; i < l.curr_user->getTripHistory ().size ();
						i++)
		{
			trips.push_back (l.curr_user->getTripHistory ()[i]);
		}
	}
	else
		trips = l.findFutureTrips (l.curr_unreg);
	sort (trips.begin (), trips.end (), Trip::compareTrips);
	for (unsigned int i = 0; i < trips.size (); i++)
	{
		if (trips[i]->getSmokingSign ())
			cout << "Smoking Allowed" << ":" << trips[i]->toString () << endl;
	}
	for (unsigned int i = 0; i < trips.size (); i++)
	{
		if (!trips[i]->getSmokingSign ())
			cout << "Smoking not Allowed" << ":" << trips[i]->toString () << endl;
	}
}
/**
 * @brief  displays future trips of user will be driving sorted by most recent
 */
void
Lyfter::displayTripsDriving ()
{
	vector<Trip *> future = vector<Trip*> ();
	for (unsigned int i = 0; i < l.getCurTrips ().size (); i++)
	{
		if (l.getCurTrips ()[i]->getDriver () == l.curr_user->getUsern ())
			future.push_back (l.getCurTrips ()[i]);
	}
	sort (future.begin (), future.end (), Trip::compareTrips);
	cout << "Future Trips Im driving:" << endl;
	for (int i = 0; i < future.size (); i++)
	{
		cout << i << ":" << future[i]->toString () << endl;
	}
}
/**
 * @brief  displays future trips of user sorted by most recent
 */
void
Lyfter::displayFutureTrips ()
{

	vector<Trip *> future = vector<Trip*> ();
	if (l.login)
		future = l.findFutureTrips (l.curr_user);
	else
		future = l.findFutureTrips (l.curr_unreg);
	sort (future.begin (), future.end (), Trip::compareTrips);
	for (int i = 0; i < future.size (); i++)
	{
		cout << "Future Trips:" << endl;
		cout << i << ":" << future[i]->toString () << endl;
	}
}
/**
 * @brief  displays past trips of user sorted by most recent to oldest
 */
void
Lyfter::displayPastTrips ()
{
	cout << "Past Trips:" << endl;
	l.curr_user->printTripHistory ();
}
/**
 * @brief  displays all of users trips unfiltered
 */
void
Lyfter::displayAllTrips ()
{
	displayFutureTrips ();
	displayPastTrips ();
}
/**
 * @brief  Displays trip history menu and changes states accordingly to user input
 */
void
Lyfter::displayTripHistoryMenu ()
{
	string user_in = "";
	long user_in_;
	bool validInput = false;
	if (l.login)
	{
		cout << "Do you want to filter your history? If so, pick your filters: " << endl << "|*****************************************************************|" << endl << "| 1.  Past Trips (from most recent to oldest)                     |" << endl << "| 2.  By driver name                                              |" << endl << "| 3.  Future trips (from most recent to oldest)                   |" << endl << "| 4.  Trips I'm driving in the future                             |" << endl << "| 5.  Trips by Smoking conditions                                 |" << endl << "| 6.  I don't want any of those, show me all of my trips          |" << endl << "| 7.  Go back to previous menu                                    |" << endl << "|*****************************************************************|" << endl;
		cout << "Selected number from menu: ";
	}
	else
	{
		cout << "Do you want to filter your history? If so, pick your filters: " << endl << "|*****************************************************************|" << endl << "| 1.  By driver name                                              |" << endl << "| 2.  Future trips (from most recent to oldest)                   |" << endl << "| 3.  Display by smoking and non Smoking		                   |" << endl << "| 4.  Go back to previous menu                                    |" << endl << "|*****************************************************************|" << endl;
		cout << "Selected number from menu: ";
		while (!validInput)
		{
			getline (cin, user_in);
			cin.clear ();
			////cin.ignore(10000, '\n');
			user_in_ = stol (user_in);
			if (user_in_ >= 1 && user_in_ <= 6)
			{
				validInput = true;
				switch (user_in_)
				{

				case 1:
					tripSortByDriverName ();
					pressEnter ();
					cls ();
					break;
				case 2:
					displayFutureTrips ();
					pressEnter ();
					cls ();
					break;
				case 3:
					displayBySmoking ();
					pressEnter ();
					cls ();
					break;
				case 4:
					prev_state = curr_state;
					curr_state = mainMenu;
					cls ();
					break;
				}
			}
		}

	}
	while (!validInput)
	{
		getline (cin, user_in);
		cin.clear ();
		////cin.ignore(10000, '\n');
		user_in_ = stol (user_in);
		if (user_in_ >= 1 && user_in_ <= 7)
		{
			validInput = true;
			switch (user_in_)
			{
			case 1:
				displayPastTrips ();
				pressEnter ();
				cls ();
				break;
			case 2:
				tripSortByDriverName ();
				pressEnter ();
				cls ();
				break;
			case 3:
				displayFutureTrips ();
				pressEnter ();
				cls ();
				break;
			case 4:
				displayTripsDriving ();
				pressEnter ();
				cls ();
				break;
			case 5:
				displayBySmoking ();
				pressEnter ();
				cls ();
				break;
			case 6:
				displayAllTrips ();
				pressEnter ();
				cls ();
				break;
			case 7:
				prev_state = curr_state;
				curr_state = loginMenu;
				cls ();
				break;
			}
		}
	}
}
///end of trip history section

///buddy section
/**
 * @brief  Displays vector of buddies
 * @param buds vector of buddies to display
 */
void
Lyfter::displayBuddies (vector<RegPerson *> buds)
{
	for (unsigned int i = 0; i < buds.size (); i++)
	{
		cout << "Buddy username: " << buds[i]->getUsern () << endl;
	}
}
/**
 * Displays list of the user's current buddies and prompts for index of the one to delete
 * @brief  remove a budy with inputted index
 * @return if buddy successfully deleted
 */
bool
Lyfter::rmBuddyUsername ()
{
	string index = "";
	bool validIndex = false;
	long index_;
	unsigned int i;
	displayBuddies (l.curr_user->getBuddies ());
	cout << "Input the index of the friend you want to remove:(or input F to leave) " << endl;
	while (!validIndex)
	{

		getline (cin, index);
		cin.clear ();
		if (index == "F" || index == "f")
		{
			cls ();
			break;
		}
		//cin.ignore(10000, '\n');
		index_ = stol (index);
		i = index_;
		if (i <= l.curr_user->getBuddies ().size ())
		{
			validIndex = true;
			l.curr_user->removeBuddy (i);
			cout << "Buddy removed successfully" << endl;
			pressEnter ();
			cls ();
			return true;
		}
		cout << "Invalid index! Please input again." << endl;
	}
	return false;
}
/**
 * Prompts for the username of buddy to add
 * @brief  finds and adds buddy
 * @return if buddy successfully found and added
 */
bool
Lyfter::findBuddyUsername ()
{
	string usrn = "";
	vector<RegPerson *> buddies = vector<RegPerson *> ();
	bool found = false;
	while (!found)
	{
		cout << "Input the username you want to search for:(or input F to leave) " << endl;
		getline (cin, usrn);
		cin.clear ();
		if (usrn == "F" || usrn == "f")
		{
			cls ();
			break;
		}
		//cin.ignore(10000, '\n');
		buddies = l.findRegPersonVec (usrn);

		if (buddies.size () > 0)
		{
			RegPerson * user = buddies[0];
			displayBuddies (buddies);
			cout << "Added " << user->getUsern () << " successfully" << endl;
			l.curr_user->insertBuddy (user);
			pressEnter ();
			cls ();
			return true;
		}
		cout << "Username not found! Please input again." << endl;
	}
	return false;
}
/**
 * @brief  Displays buddy menu and changes states accordingly to user input
 */
void
Lyfter::displayBuddyMenu ()
{
	string user_in = "";
	long user_in_;
	bool validInput = false;
	cout << "Here are your buddies! If you want, be sure to add more! " << endl << "|*****************************************************************|" << endl << "| 1.  Add buddy                                                   |" << endl << "| 2.  Remove buddy                                                |" << endl << "| 3.  Display all buddies                                         |" << endl << "| 4.  Go back to previous menu                                    |" << endl << "|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	while (!validInput)
	{
		getline (cin, user_in);
		cin.clear ();
		//cin.ignore(10000, '\n');
		user_in_ = stol (user_in);
		if (user_in_ >= 1 && user_in_ <= 4)
		{
			validInput = true;
			switch (user_in_)
			{
			case 1:
				findBuddyUsername ();
				l.save_data ();
				break;
			case 2:
				rmBuddyUsername ();
				l.save_data ();
				break;
			case 3:
				displayBuddies (l.curr_user->getBuddies ());
				pressEnter ();
				cls ();
				break;
			case 4:
				prev_state = curr_state;
				curr_state = loginMenu;
				break;
			}
		}
	}
}
///end of buddies section

///payment section
/**
 * @brief  Displays payments menu,executes commands and changes states accordingly to user input
 */
///payment section
void
Lyfter::displayPaymentMenu ()
{
	string user_in = "";
	long user_in_;
	bool validInput = false;
	cout << "Here you can manage your wallet and payment options: " << endl << "|*****************************************************************|" << endl << "| 1.  Pay bills                                                   |" << endl << "| 2.  Consult debts                                               |" << endl << "| 3.  Go back to previous menu                                    |" << endl << "|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	while (!validInput)
	{
		getline (cin, user_in);
		cin.clear ();
		//cin.ignore(10000, '\n');
		user_in_ = stol (user_in);
		if (user_in_ >= 1 && user_in_ <= 3)
		{
			validInput = true;
			switch (user_in_)
			{
			case 1:
				if (l.login)
					l.curr_user->payBilling ();
				else
					l.curr_unreg->payBilling ();
				pressEnter ();
				cls ();
				break;
			case 2:
				if (l.login)
					cout << "Your current debt is: " << l.curr_user->getBilling () << endl;
				else
					cout << "Your current debt is: " << l.curr_unreg->getBilling () << endl;
				pressEnter ();
				cls ();
				break;
			case 3:
				prev_state = curr_state;
				if (l.login)
					curr_state = loginMenu;
				else
					curr_state = mainMenu;
				cls ();
				break;
			}
		}
	}
}
///end of payment section

///settings section
/**
 * Prompts user for necessary data to create a new vehicle, creates it
 * @brief create new vehicle for user
 * @return pointer to created vehicle
 */
Vehicle*
Lyfter::makeVehicle ()
{
	string type = "";
	string brand = "";
	string model = "";
	string s_year = "";
	unsigned short int year = -1;
	string license_plate = "-1";
	string seats = "";
	unsigned int car_seats;

	cout << "Input the vehicle type (either van, sedan, hatchback, supercar or bike): " << endl;
	getline (cin, type);
	cin.clear ();
	//cin.ignore(10000, '\n');

	cout << "Input the vehicle brand: " << endl;
	getline (cin, brand);
	cin.clear ();
	//cin.ignore(10000, '\n');

	cout << "Input the vehicle model: " << endl;
	getline (cin, model);
	cin.clear ();
	//cin.ignore(10000, '\n');

	cout << "Input the vehicle year: " << endl;
	getline (cin, s_year);
	cin.clear ();
	//cin.ignore(10000, '\n');
	year = stol (s_year);

	while (!l.isUniqueLicensePlate (license_plate))
	{
		cout << "Input the vehicle license plate: " << endl;
		getline (cin, license_plate);
		cin.clear ();
		//cin.ignore(10000, '\n');
	}

	cout << "Input the car's number of seats: " << endl;
	getline (cin, seats);
	car_seats = stol (seats);
	cin.clear ();
	//cin.ignore(10000, '\n');

	Vehicle* v = new Vehicle (l.curr_user->getUsern (), type, brand, model,
								year, license_plate, car_seats);
	l.save_data ();
	l.getBST ().insert (v);
	return v;
}
/**
 * @brief Displays vector of vehicles
 * @param v vector of vehicles to display
 */
void
Lyfter::displayVehicles (vector<Vehicle *> v)
{
	for (int i = 0; i < v.size (); i++)
	{
		cout << i << ": " << v[i]->toString () << endl;
	}
}
/**
 * Displays users vehicles and prompts for index of vehicle to delete
 * @brief Delete user vehicle
 * @return if vehicle successfully deleted
 */
bool
Lyfter::rmVehicle ()
{
	string index = "";
	bool validIndex = false;
	long index_;
	unsigned int i;
	cout << "Input the index of the vehicle you want to remove: " << endl;
	displayVehicles (l.curr_user->getVehicles ());
	while (!validIndex)
	{
		getline (cin, index);
		cin.clear ();
		//cin.ignore(10000, '\n');
		index_ = stol (index);
		i = index_;

		if (i <= l.curr_user->getVehicles ().size ())
		{
			validIndex = true;
			string lp_to_rm = l.curr_user->getVehicles ().at (i)->getLicensePlate ();
			l.curr_user->removeVehicle (i);
			l.save_data ();
			BSTItrIn<VehicleWrapper> it (l.getBST ());
			while (!it.isAtEnd ())
			{
				if (it.retrieve ()->getLicensePlate () == lp_to_rm)
				{
					l.getBST ().remove (it.retrieve ().operator -> ());
				}
				it.advance ();
			}
			return true;
		}
		cout << "Invalid index! Please input again." << endl;
	}
	return false;
}
/**
 * Prompts for new password and changes password
 * @brief Change user password
 * @param p user to change the password of
 * @return if password successfully changed
 */
bool
Lyfter::changePassword (RegPerson* p)
{
	cls ();
	string curr_passw = "";
	string new_passw = "";

	cout << "Input your current password: " << endl;
	getline (cin, curr_passw);
	cin.clear ();
	//cin.ignore(10000, '\n');
	cout << "Input your new password: " << endl;
	getline (cin, new_passw);
	cin.clear ();
	//cin.ignore(10000, '\n');
	if (l.userLogin (p->getUsern (), curr_passw))
	{
		p->setPassw (new_passw);
		l.save_data ();
		cout << "Changed password successfully" << endl;
		pressEnter ();
		cls ();
		return true;
	}
	cout << "Current password is incorrect! Try again later." << endl;
	pressEnter ();
	cls ();
	return false;
}

/**
 * Prompts for new password and changes password
 * @brief Change user password
 * @param p user to change the password of
 * @return if password successfully changed
 */
bool
Lyfter::transferVehicleTo ()
{
	cls ();
	string usern_to_transfer = "";
	string v_index = "-1";
	int v_ind = -1;

	int v_size = l.curr_user->getVehicles ().size ();
	displayVehicles (l.curr_user->getVehicles ());

	while (v_ind == -1)
	{

		cout << "Input the index of the vehicle you want to transfer: " << endl;
		getline (cin, v_index);
		cin.clear ();
		v_ind = stol (v_index);

		if (v_ind >= 0 && v_ind < v_size)
		{
			cout << "Input the username of the user you want to transfer ownership to: " << endl;
			getline (cin, usern_to_transfer);
			cin.clear ();
			//cin.ignore(10000, '\n');

			if (l.usernameExists (usern_to_transfer))
			{
				Vehicle* v = l.curr_user->getVehicles ().at (v_ind);
				v->setOwner (usern_to_transfer);
				RegPerson* other_user = l.findRegPerson (usern_to_transfer);
				other_user->getVehicles ().push_back (v);
				l.curr_user->removeVehicle (v_ind);
				l.save_data ();
				return true;
			}
			else
				cout << "Username inexistent!" << endl;
		}
		cout << "Invalid index!" << endl;
	}
}
/**
 * @brief  Displays user settings menu and changes states accordingly to user input
 */
void
Lyfter::displaySettingsMenu ()
{
	string user_in = "";
	long user_in_;
	bool validInput = false;
	cout << "Here you can manage your settings and account: " << endl << "|*****************************************************************|" << endl << "| 1.  Add vehicle/Become a driver                                 |" << endl << "| 2.  Delete vehicle                                              |" << endl << "| 3.  Display all vehicles                                        |" << endl << "| 4.  Alter password                                              |" << endl << "| 5.  Transfer Vehicle Ownership                                  |" << endl << "| 6.  Go back to previous menu                                    |" << endl << "|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	while (!validInput)
	{
		getline (cin, user_in);
		cin.clear ();
		//cin.ignore(10000, '\n');
		user_in_ = stol (user_in);
		if (user_in_ >= 1 && user_in_ <= 6)
		{
			validInput = true;
			switch (user_in_)
			{
			case 1:
				l.curr_user->addVehicle (makeVehicle ());
				l.save_data ();
				pressEnter ();
				cls ();
				break;
			case 2:
				rmVehicle ();
				pressEnter ();
				cls ();
				break;
			case 3:
				displayVehicles (l.curr_user->getVehicles ());
				pressEnter ();
				cls ();
				break;
			case 4:
				changePassword (l.curr_user);
				break;
			case 5:
				transferVehicleTo ();
				break;
			case 6:
				prev_state = curr_state;
				curr_state = loginMenu;
				break;
			}
		}
	}
}
///end settings section

int
main ()
{
	Logic l ("config");
	l.load_data ();
	Lyfter menu = Lyfter (l);
	cout << "     __ __  __ ______ ______ ______ ____  " << endl;
	cout << "    / / \\ \\/ // ____//_  __// ____// __ \\ " << endl;
	cout << "   / /   \\  // /_     / /  / __/  / /_/ / " << endl;
	cout << "  / /___ / // __/    / /  / /___ / _, _/  " << endl;
	cout << " /_____//_//_/      /_/  /_____//_/ |_|   " << endl;
	while (true)
	{
		switch (menu.curr_state)
		{
		case signUpMenu:
			menu.displaySignUpMenu ();
			break;
		case mainMenu:
			menu.displayMainMenu ();
			break;
		case loginMenu:
			menu.displayLoginMenu ();
			break;
		case searchTripMenu:
			menu.displayTripMenu ();
			break;
		case historyMenu:
			menu.displayTripHistoryMenu ();
			break;
		case paymentMenu:
			menu.displayPaymentMenu ();
			break;
		case buddiesMenu:
			menu.displayBuddyMenu ();
			break;
		case settingsMenu:
			menu.displaySettingsMenu ();
			break;
		case chooseTripMenu:
			menu.userDest ();
			break;
		case createTripMenu:
			menu.createTrip ();
			break;
		case adminMenu:
			menu.displayAdminMenu ();
			break;
		case advSearchOpt:
			menu.displayAdvSearchOptMenu ();
		}
	}
}

