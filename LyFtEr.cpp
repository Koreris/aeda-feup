#include "includes.h"
#include "Date.h"
#include "Person.h"
#include "Place.h"
#include "Trip.h"
#include "Vehicle.h"
#include "Logic.h"
#include <windows.h>

#include <algorithm>

void pressEnter(){
	cout << "Press Enter to continue..." << endl;
	getchar();
}

void cls() {
    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}
Logic l("config");

enum states
{
	mainMenu,
	loginMenu,
	searchTripMenu,
	searchTripMenuUnreg,
	historyMenu,
	historyMenuUnreg,
	paymentMenu,
	buddiesMenu,
	settingsMenu,
	chooseTripMenu,
	addBuddyState,
	removeBuddyState,
	allBuddiesState,
	payState,
	checkDebtState,
	addVehicleState,
	displayAllVehiclesState,
	rmVehicleState,
	changePasswState,
	createTripMenu
};
states curr_state = mainMenu;
states prev_state = mainMenu;

//login section
bool userLogin()
{
	string usr="";
	string passw="";

	cout << "Input your username: " << endl;
	getline(cin, usr);
	cin.clear();
	//cin.ignore(10000, '\n');
	cout << "Input your password: " << endl;
	getline(cin, passw);
	cin.clear();
	//cin.ignore(10000, '\n');
	return(l.userLogin(usr, passw));
}

void displayMainMenu()
{
	string user_in;
	long user_in_;
	bool validInput=false;
	while(!validInput)
	{
	cout << "\n Welcome to LyFtEr! \n\n" << endl
					<< " +============================================================================+" << endl <<
					" | 1.  Login!                                                                 |" << endl <<
					" | 2.  Search for next trip                                                   |" << endl <<
					" | 3.  Trip history                                                           |" << endl <<
					" | 4.  Payment options                                                        |" << endl <<
					" +============================================================================+\n" << endl;
	cout << "\n Selected number from menu:\n";

		getline(cin, user_in);
		cin.clear();
		//cin.ignore(10000, '\n');
		user_in_=stol(user_in);
		if(user_in_>= 1 && user_in_<= 4)
		{
			validInput=true;
			switch(user_in_)
			{
			case 1:
				if(userLogin())
				{
					prev_state=curr_state;
					curr_state=loginMenu;
					cls();
				}
				else
				{
					curr_state=prev_state;
					validInput=false;

				}
				break;
			case 2:
				prev_state=curr_state;
				curr_state=searchTripMenuUnreg;
				cls();
				break;
			case 3:
				prev_state=curr_state;
				curr_state=historyMenuUnreg;
				cls();
				break;
			case 4:
				prev_state=curr_state;
				curr_state=paymentMenu;
				cls();
				break;
			}
		}
	}
	return;
}

void displayLoginMenu()
{
	cls();
	string user_in;
	long user_in_;
	bool validInput=false;
	cout << "You are logged in! Here are your options:" << endl
					<< "|*****************************************************************|" << endl <<
					"| 1.  Search for your next trip                                   |" << endl <<
					"| 2.  Create a trip (driver's only)                               |" << endl <<
					"| 3.  Your trip history                                           |" << endl <<
					"| 4.  Your buddies                                                |" << endl <<
					"| 5.  Your payment options                                        |" << endl <<
					"| 6.  Your settings                                               |" << endl <<
					"| 7.  Log out                                                     |" << endl <<
					"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	while(!validInput)
	{
		getline(cin, user_in);
		cin.clear();
		//cin.ignore(10000, '\n');
		user_in_=stol(user_in);
		if(user_in_>= 1 && user_in_<= 7)
		{
			validInput=true;
			switch(user_in_)
			{
			case 1:
				prev_state=curr_state;
				curr_state=searchTripMenu;
				cls();
				break;
			case 2:
				prev_state=curr_state;
				curr_state=createTripMenu;
				cls();
				break;
			case 3:
				prev_state=curr_state;
				curr_state=historyMenu;
				cls();
				break;
			case 4:
				prev_state=curr_state;
				curr_state=buddiesMenu;
				cls();
				break;
			case 5:
				prev_state=curr_state;
				curr_state=paymentMenu;
				cls();
				break;
			case 6:
				prev_state=curr_state;
				curr_state=settingsMenu;
				cls();
				break;
			case 7:
				prev_state=curr_state;
				curr_state=mainMenu;
				cls();
				break;
			}
		}
	}
	return;
}
//end of login section

void displayVehicles(vector<Vehicle *>v)
{
	for(int i=0;i<v.size();i++)
	{
		cout << i <<": " << v[i]->toString() << endl;
	}
}

void addDestinationsTrip(Trip *t)
{
	string place="";
	Place * dest;
	bool pressFtoPayRespects = false;
	vector< pair<Place *, int> > route=vector< pair<Place *, int> >();
	//QUERYING FOR DESTINATIONS
	cout << "Input Route: One Destination at a time, input string 'F' to end input of destinations " << endl;
	while(!pressFtoPayRespects){
		getline(cin, place);
		cin.clear();
		//cin.ignore(10000, '\n');
		if(place=="F")
		{
			t->addRoute(route);
			pressFtoPayRespects=true;
			break;
		}
		if((dest=l.findDest(place))==NULL){
			cout << "Destination isn't registered in the application yet, please register destination first" << endl;
			continue;
		}
		else
		{
			pair<Place*,int> p (dest,0);
			route.push_back(p);
			cout << "Added " << dest->getName() << " to route." << endl;
		}

	}
}

bool createTrip()
{

	if(!(l.curr_user->getHasVehicle())){
		curr_state=prev_state;
		return false;
	}

	Date start_date;
	Date end_date;
	string usr=l.curr_user->getUsern();
	string index="";
	string begindate="";
	string finishdate="";
	string smoking="";
	bool smk=false;
	unsigned long i;
	bool validIndex=false;
	bool validSmoke=false;
	bool validBeginDate=false;
	bool validEndDate=false;

	//QUERYING FOR SMOKING CONDITION
	cout << "Is smoking allowed on this trip? Input 0 for no, 1 for yes: " << endl;
	while(!validSmoke){
		getline(cin, smoking);
		cin.clear();
		//cin.ignore(10000, '\n');
		if(stol(smoking)!=0 && stol(smoking)!=1)
			continue;
		smk=stol(smoking);
		validSmoke=true;
	}

	//QUERYING TO CHOOSE VEHICLE
	displayVehicles(l.curr_user->getVehicles());
	cout << "Input the index of the vehicle you want to use for this trip: " << endl;
	while(!validIndex)
	{
		getline(cin, index);
		cin.clear();
		//cin.ignore(10000, '\n');
		i=stol(index);


		if(i<=l.curr_user->getVehicles().size()-1 && i>=0)
		{
			validIndex=true;

		}
		if(!validIndex)
			cout << "Invalid index! Please input again." << endl;
	}

	//QUERYING TO TRIP START DATE

	cout << "Input the start date in format -> year month day hour minute second " << endl;
	while(!validBeginDate)
	{
		getline(cin, begindate);
		cout << begindate << endl;
		cin.clear();
		//cin.ignore(10000, '\n');
		try {
				Date start_date(begindate);
			} catch (Date::InvalidDate &d) {
				cout << "Invalid input of Date format" << endl;
				continue;
			}

		if(start_date<l.get_curDate())
			cout  << "Cannot make trips in the past, try again" << endl;
		else validBeginDate=true;
	}

	//QUERYING TO TRIP END DATE

	cout << "Input the end date in format -> year month day hour minute second " << endl;
	while(!validEndDate)
	{
		getline(cin, finishdate);
		cin.clear();
		cout << finishdate << endl;
		//cin.ignore(10000, '\n');
		try {
			Date end_date(finishdate);
		} catch (Date::InvalidDate &d) {
			cout << "Invalid input of Date format" << endl;
			continue;
		}

		if(end_date<start_date)
			cout  << "Cannot have end date earlier than start date, try again" << endl;
		else validEndDate=true;
	}

	Trip * t = new Trip(usr, l.curr_user->getVehicles()[i], smk,start_date,end_date);
	addDestinationsTrip(t);
	l.getCurTrips().push_back(t);
	cout << "Successfully added the trip: " << t->toString() << endl;
	curr_state=prev_state;
	pressEnter();
	cls();
	return true;
}



//trip search section

void chooseTrip(vector<Trip *> v)
{
	//tentar inscrever  nesta trip
}
bool userDest()
{
	string dest="";
	string origin="";
	vector<Trip *> temp=vector<Trip *>();
	bool found=false;

	while(!found)
	{
		cout << "Input your destination: " << endl;
		getline(cin, dest);
		cin.clear();
		//cin.ignore(10000, '\n');
		cout << "Input your origin: " << endl;
		getline(cin, origin);
		cin.clear();
		//cin.ignore(10000, '\n');
		temp=l.findTrips(origin,dest);
		if(temp.size()>0)
		{
			found=true;
			chooseTrip(temp);
			return true;
		}
		cout << "Trips following that route not found! Please input new data." << endl;
	}
	return false;
}

long displayTripMenu()
{
	string user_in="";
	long user_in_;
	bool validInput=false;
	cout << "Let's find you your next trip! Pick your filter:" << endl
					<< "|*****************************************************************|" << endl <<
					"| +.  During your next trip you'll want to go to...               |" << endl <<
					"| 1.  X destination                                               |" << endl <<
					"| 2.  Go back to previous menu                                    |" << endl <<
					"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	while(!validInput)
	{
		getline(cin, user_in);
		cin.clear();
		//cin.ignore(10000, '\n');
		user_in_=stol(user_in);
		if(user_in_== 1 || user_in_== 2)
		{
			validInput=true;
			switch(user_in_)
			{
			case 1:
				if(userDest())
				{
					prev_state=curr_state;
					curr_state=chooseTripMenu;
				}
				break;
			case 2:
				prev_state=curr_state;
				curr_state=mainMenu;
				break;
			}
		}
	}
}
//end of trip search section

//trip history section

void tripSortByDriverName()
{
	vector<Trip *> future = vector<Trip*>();
	future = l.findFutureTrips(l.curr_user);
	l.tripSortByDriverName(future);
	for(int i=0;i<future.size();i++)
	{
		cout << "Future Trips:" << endl;
		cout <<i<<":"<< future[i]->toString() << endl;
	}
}


void displayFutureTrips()
{
	vector<Trip *> future = vector<Trip*>();
	future = l.findFutureTrips(l.curr_user);
	sort(future.begin(),future.end(),Trip::compareTrips);
	for(int i=0;i<future.size();i++)
	{
		cout << "Future Trips:" << endl;
		cout <<i<<":"<< future[i]->toString() << endl;
	}
}

void displayPastTrips()
{
	cout << "Past Trips:" << endl;
	l.curr_user->printTripHistory();
}

void displayAllTrips()
{
	displayFutureTrips();
	displayPastTrips();
}


void displayTripHistoryMenu()
{
	string user_in="";
	long user_in_;
	bool validInput=false;
	cout << "Do you want to filter your history? If so, pick your filters: " << endl
					<< "|*****************************************************************|" << endl <<
					"| 1.  Past Trips (from most recent to oldest)                     |" << endl <<
					"| 2.  By driver name                                              |" << endl <<
					"| 3.  Future trips (from most recent to oldest)                   |" << endl <<
					"| 4.  I don't want any of those, show me all of my trips          |" << endl <<
					"| 5.  Go back to previous menu                                    |" << endl <<
					"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	while(!validInput)
	{
		getline(cin, user_in);
		cin.clear();
		////cin.ignore(10000, '\n');
		user_in_=stol(user_in);
		if(user_in_>= 1 && user_in_<= 5)
		{
			validInput=true;
			switch(user_in_)
			{
			case 1:
				displayPastTrips();
				pressEnter();
				cls();
				break;
			case 2:
				tripSortByDriverName();
				pressEnter();
				cls();
				break;
			case 3:
				displayFutureTrips();
				pressEnter();
				cls();
				break;
			case 4:
				displayAllTrips();
				pressEnter();
				cls();
				break;
			case 5:
				prev_state=curr_state;
				curr_state=loginMenu;
				cls();
				break;
			}
		}
	}
}

//end of trip history section

//buddy section
void displayBuddies(vector <RegPerson *> buds)
{
	//cout
}

bool rmBuddyUsername()
{
	string index="";
	bool validIndex=false;
	long index_;
	unsigned int i;

	while(!validIndex)
	{
		cout << "Input the index of the friend you want to remove: " << endl;
		getline(cin, index);
		cin.clear();
		//cin.ignore(10000, '\n');
		index_=stol(index);
		i=index_;
		displayBuddies(l.curr_user->getBuddies());
		if(i<=l.curr_user->getBuddies().size())
		{
			validIndex=true;
			l.curr_user->removeBuddy(i);
			return true;
		}
		cout << "Invalid index! Please input again." << endl;
	}
	return false;
}
bool findBuddyUsername()
{
	string usrn="";
	vector<RegPerson *> buddies=vector<RegPerson *>();
	bool found=false;
	RegPerson * empty=new RegPerson();

	while(!found)
	{
		cout << "Input the username you want to search for: " << endl;
		getline(cin, usrn);
		cin.clear();
		//cin.ignore(10000, '\n');
		buddies=l.findRegPersonVec(usrn);
		RegPerson * user= buddies[0];
		if(buddies.size()>0)
		{
			found=true;
			displayBuddies(buddies);
			l.curr_user->insertBuddy(user);
			return true;
		}
		cout << "Username not found! Please input again." << endl;
	}
	return false;
}

void displayBuddyMenu()
{
	string user_in="";
	long user_in_;
	bool validInput=false;
	cout << "Here are your buddies! If you want, be sure to add more! " << endl
					<< "|*****************************************************************|" << endl <<
					"| 1.  Add buddy                                                   |" << endl <<
					"| 2.  Remove buddy                                                |" << endl <<
					"| 3.  Display all buddies                                         |" << endl <<
					"| 4.  Go back to previous menu                                    |" << endl <<
					"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	while(!validInput)
	{
		getline(cin, user_in);
		cin.clear();
		//cin.ignore(10000, '\n');
		user_in_=stol(user_in);
		if(user_in_>= 1 && user_in_<= 4)
		{
			validInput=true;
			switch(user_in_)
			{
			case 1:
				findBuddyUsername();
				prev_state=curr_state;
				curr_state=addBuddyState;
				break;
			case 2:
				rmBuddyUsername();
				prev_state=curr_state;
				curr_state=removeBuddyState;
				break;
			case 3:
				displayBuddies(l.curr_user->getBuddies());
				prev_state=curr_state;
				curr_state=allBuddiesState;
				break;
			case 4:
				prev_state=curr_state;
				curr_state=mainMenu;
				break;
			}
		}
	}
}
//end of buddies section

//payment section
void displayPaymentMenu()
{
	string user_in="";
	long user_in_;
	bool validInput=false;
	cout << "Here you can manage your wallet and payment options: " << endl
					<< "|*****************************************************************|" << endl <<
					"| 1.  Pay bills                                                   |" << endl <<
					"| 2.  Consult debts                                               |" << endl <<
					"| 3.  Go back to previous menu                                    |" << endl <<
					"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	while(!validInput)
	{
		getline(cin, user_in);
		cin.clear();
		//cin.ignore(10000, '\n');
		user_in_=stol(user_in);
		if(user_in_>= 1 && user_in_<= 3)
		{
			validInput=true;
			switch(user_in_)
			{
			case 1:
				l.curr_user->payBilling();
				prev_state=curr_state;
				curr_state=payState;
				break;
			case 2:
				cout << "Your current debt is: " << l.curr_user->getBilling() << endl;
				prev_state=curr_state;
				curr_state=checkDebtState;
				break;
			case 3:
				prev_state=curr_state;
				curr_state=mainMenu;
				break;
			}
		}
	}
}
//end of payment section

//settings section
Vehicle* makeVehicle()
{
	string type="";
	string brand="";
	string license_plate="";
	string seats="";
	unsigned int car_seats;

	cout << "Input the car type (either van, sedan or hatchback): " << endl;
	getline(cin,type);
	cin.clear();
	//cin.ignore(10000, '\n');

	cout << "Input the car brand: " << endl;
	getline(cin,brand);
	cin.clear();
	//cin.ignore(10000, '\n');

	cout << "Input the car license plate: " << endl;
	getline(cin,license_plate);
	cin.clear();
	//cin.ignore(10000, '\n');

	cout << "Input the car's number of seats: " << endl;
	getline(cin,seats);
	car_seats=stol(seats);
	cin.clear();
	//cin.ignore(10000, '\n');

	Vehicle* v=new Vehicle(l.curr_user->getName(),type,brand,license_plate,car_seats);

	return v;
}

bool rmVehicle()
{
	string index="";
	bool validIndex=false;
	long index_;
	unsigned int i;

	while(!validIndex)
	{
		cout << "Input the index of the vehicle you want to remove: " << endl;
		getline(cin, index);
		cin.clear();
		//cin.ignore(10000, '\n');
		index_=stol(index);
		i=index_;
		displayVehicles(l.curr_user->getVehicles());
		if(i<=l.curr_user->getVehicles().size())
		{
			validIndex=true;
			l.curr_user->removeVehicle(i);
			return true;
		}
		cout << "Invalid index! Please input again." << endl;
	}
	return false;
}

bool changePassword(RegPerson* p)
{
	string curr_passw="";
	string new_passw="";

	cout << "Input your current password: " << endl;
	getline(cin, curr_passw);
	cin.clear();
	//cin.ignore(10000, '\n');
	cout << "Input your new password: " << endl;
	getline(cin, new_passw);
	cin.clear();
	//cin.ignore(10000, '\n');
	if(l.userLogin(p->getUsern(), curr_passw))
	{
		p->setPassw(new_passw);
		return true;
	}
	cout << "Current password is incorrect! Try again later." << endl;
}

void displaySettingsMenu()
{
	string user_in="";
	long user_in_;
	bool validInput=false;
	cout << "Here you can manage your settings and account: " << endl
					<< "|*****************************************************************|" << endl <<
					"| 1.  Add vehicle/Become a driver                                 |" << endl <<
					"| 2.  Delete vehicle                                              |" << endl <<
					"| 3.  Display all vehicles                                        |" << endl <<
					"| 4.  Alter password                                              |" << endl <<
					"| 5.  Go back to previous menu                                    |" << endl <<
					"|*****************************************************************|" << endl;
	cout << "Selected number from menu: ";
	while(!validInput)
	{
		getline(cin, user_in);
		cin.clear();
		//cin.ignore(10000, '\n');
		user_in_=stol(user_in);
		if(user_in_>= 1 && user_in_<= 5)
		{
			validInput=true;
			switch(user_in_)
			{
			case 1:
				makeVehicle();
				l.curr_user->addVehicle(makeVehicle());
				prev_state=curr_state;
				curr_state=addVehicleState;
				break;
			case 2:
				rmVehicle();
				prev_state=curr_state;
				curr_state=rmVehicleState;
				break;
			case 3:
				displayVehicles(l.curr_user->getVehicles());
				prev_state=curr_state;
				curr_state=displayAllVehiclesState;
				break;
			case 4:
				changePassword(l.curr_user);
				prev_state=curr_state;
				curr_state=changePasswState;
				break;
			case 5:
				prev_state=curr_state;
				curr_state=mainMenu;
				break;
			}
		}
	}
}

int main()
{

	l.load_data();
	cout << "     __ __  __ ______ ______ ______ ____  " << endl;
	cout << "    / / \\ \\/ // ____//_  __// ____// __ \\ " << endl;
	cout << "   / /   \\  // /_     / /  / __/  / /_/ / " << endl;
	cout << "  / /___ / // __/    / /  / /___ / _, _/  " << endl;
	cout << " /_____//_//_/      /_/  /_____//_/ |_|   " << endl;
	while(true)
	{
		switch(curr_state)
		{
		case mainMenu:
			displayMainMenu();
			break;
		case loginMenu:
			displayLoginMenu();
			break;
		case searchTripMenu:
			displayTripMenu();
			break;
		case historyMenu:
			displayTripHistoryMenu();
			break;
		case paymentMenu:
			displayPaymentMenu();
			break;
		case buddiesMenu:
			displayBuddyMenu();
			break;
		case settingsMenu:
			displaySettingsMenu();
			break;
		case chooseTripMenu:
			userDest();
			break;
		case createTripMenu:
			createTrip();
			break;
		case addBuddyState:
			break;
		case removeBuddyState:
			break;
		case allBuddiesState:
			break;
		case payState:
			break;
		case checkDebtState:
			break;
		case addVehicleState:
			break;
		case displayAllVehiclesState:
			break;
		case rmVehicleState:
			break;
		case changePasswState:
			break;
		}
	}
}

