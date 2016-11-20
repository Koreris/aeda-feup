#include "includes.h"
#include "Date.h"
#include "Person.h"
#include "Place.h"
#include "Trip.h"
#include "Vehicle.h"
#include "Logic.h"

Logic l;
enum states {mainMenu, loginMenu, searchTripMenu, historyMenu, paymentMenu, buddiesMenu, settingsMenu};
states curr_state = mainMenu;
states prev_state = mainMenu;
//login section

long displayMainMenu()
{
	string user_in;
	long user_in_;
	bool validInput=false;
	cout << "\n Welcome to LyFtEr! \n\n" << endl
		<< " +============================================================================+" << endl <<
		" | 1.  Login!                                                                 |" << endl <<
		" | 2.  Search for next trip                                                   |" << endl <<
		" | 3.  Trip history                                                           |" << endl <<
		" | 4.  Payment options                                                        |" << endl <<
		" +============================================================================+\n" << endl;
	cout << "\n Selected number from menu:\n";
	while(!validInput)
	{
		getline(cin, user_in);
		cin.clear();
		cin.ignore(10000, '\n');
		user_in_=stol(user_in);
		if(user_in_>= 1 && user_in_<= 4)
		{
			validInput=true;
			switch(user_in_)
			{
			case 1:
				if(userLogin)
				{
					prev_state=curr_state;
					curr_state=loginMenu;
				}
				else
				{
					validInput=false;
				}
				break;
			case 2:
				prev_state=curr_state;
				curr_state=searchTripMenu;
				break;
			case 3:
				prev_state=curr_state;
				curr_state=historyMenu;
				break;
			case 4:
				prev_state=curr_state;
				curr_state=paymentMenu;
				break;
			}
		}
	}
	return user_in_;
}

bool userLogin()
{
	string usr="";
	string passw="";

	cout << "Input your username: " << endl;
	getline(cin, usr);
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "Input your password: " << endl;
	getline(cin, passw);
	cin.clear();
	cin.ignore(10000, '\n');
	return(l.userLogin(usr, passw));
}

void displayLoginMenu()
{
	string user_in;
	long user_in_;
	bool validInput=false;
	cout << "You are logged in! Here are your options:" << endl
					<< "|*****************************************************************|" << endl <<
					"| 1.  Search for your next trip                                   |" << endl <<
					"| 2.  Your trip history                                           |" << endl <<
					"| 3.  Your buddies                                                |" << endl <<
					"| 4.  Your payment options                                        |" << endl <<
					"| 5.  Your settings                                               |" << endl <<
					"| 6.  Log out                                                     |" << endl <<
					"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	while(!validInput)
	{
		getline(cin, user_in);
		cin.clear();
		cin.ignore(10000, '\n');
		user_in_=stol(user_in);
		if(user_in_>= 1 && user_in_<= 6)
		{
			validInput=true;
			switch(user_in_)
			{
			case 1:
				prev_state=curr_state;
				curr_state=searchTripMenu;
				break;
			case 2:
				prev_state=curr_state;
				curr_state=historyMenu;
				break;
			case 3:
				prev_state=curr_state;
				curr_state=buddiesMenu;
				break;
			case 4:
				prev_state=curr_state;
				curr_state=paymentMenu;
				break;
			case 5:
				prev_state=curr_state;
				curr_state=settingsMenu;
				break;
			case 6:
				prev_state=curr_state;
				curr_state=mainMenu;
				break;
			}
		}
	}
	return;
}
//end of login section

//trip search section
//vector<Trip *>
bool userDest()
{
	string dest="";
	cout << "Input your destination: " << endl;
	getline(cin, dest);
	cin.clear();
	cin.ignore(10000, '\n');
	return true;
	//(l.findDest(dest));
}

void displayVector(vector<Trip *>)
{
	//separate smoking from non smoking

}


long displayTripMenu()
{
	string user_in="";
	long user_in_;
	cout << "Let's find you your next trip! Pick your filter:" << endl
					<< "|*****************************************************************|" << endl <<
					"| +.  During your next trip you'll want to go to...               |" << endl <<
					"| 1.  X destination                                               |" << endl <<
					"| 2.  Go back to previous menu                                    |" << endl <<
					"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	getline(cin, user_in);
	cin.clear();
	cin.ignore(10000, '\n');
	user_in_=stol(user_in);
	return user_in_;
}
//end of trip search section

//trip history section
void tripSortByDate()
{
	//fazer cout/tostring
	l.tripSortByDate();
}

void tripSortByDriverName()
{
	//fazer cout/tostring
	l.tripSortByDriverName();
}

void tripSortByScheduled()
{
	l.tripSortByScheduled();
}

void allTrips()
{
	//cout
	l.getCurTrips();
	//to string trip
}

long displayTripHistoryMenu()
{
	string user_in="";
	long user_in_;
	cout << "Do you want to filter your history? If so, pick your filters: " << endl
		<< "|*****************************************************************|" << endl <<
		"| 1.  Sort by date (descending)                                   |" << endl <<
		"| 2.  By driver name                                              |" << endl <<
		"| 3.  Future trips                                                |" << endl <<
		"| 4.  I don't want any of those, show me all of my trips          |" << endl <<
		"| 5.  Go back to previous menu                                    |" << endl <<
		"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	getline(cin, user_in);
	cin.clear();
	cin.ignore(10000, '\n');
	user_in_=stol(user_in);
	return user_in_;
}

//end of trip history section

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

void displaySettingsMenu()
{
	cout << "Here you can manage your settings and account: " << endl
		<< "|*****************************************************************|" << endl <<
		"| 1.  Add vehicle/Become a driver                                 |" << endl <<
		"| 2.  Delete vehicle                                              |" << endl <<
		"| 3.  Display all vehicles                                        |" << endl <<
		"| 4.  Alter password                                              |" << endl <<
		"| 5.  Go back to previous menu                                    |" << endl <<
		"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
}
void atTripMenu()
{
	switch(displayTripMenu())
				{
					case 1:
						userDest();
						break;
					case 2:
						break;
					default:
						cout << "No valid option picked! Please try again." << endl;
						break;
				}
}

void atTripHistory()
{
	switch(displayTripHistoryMenu())
			{
				case 1:
				{
					tripSortByDate();
					break;
				}
				case 2:
				{
					tripSortByDriverName();
					break;
				}
				case 3:
				{
					tripSortByScheduled();
					break;
				}
				case 4:
				{
					allTrips();
					break;
				}
				case 5:
					break;
				default:
				{
					cout << "No valid option picked! Please try again." << endl;
					break;
				}
			}
}
int main()
{
	cout << "     __ __  __ ______ ______ ______ ____  " << endl;
	cout << "    / / \\ \\/ // ____//_  __// ____// __ \\ " << endl;
	cout << "   / /   \\  // /_     / /  / __/  / /_/ / " << endl;
	cout << "  / /___ / // __/    / /  / /___ / _, _/  " << endl;
	cout << " /_____//_//_/      /_/  /_____//_/ |_|   " << endl;
	while(true)
	{
		switch(displayMainMenu())
		{
			case 1:
			{
				displayLoginMenu();
				break;
			}
			case 2:
			{
				atTripMenu();
				break;
			}
			case 3:
			{
				atTripHistory();
				break;
			}
			case 4:
			{
				displayPaymentMenu();
				break;
			}
			default:
			{
				cout << "Invalid option, try again." << endl;
				break;
			}
		}
	}
}
