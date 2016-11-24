#ifndef PLACE_H_
#define PLACE_H_

#include "includes.h"

using namespace std;


/**
 * @brief Place class
 *
 * Contains the place related functions, including getters, setters and toString functions.
 */

class Place
{
private:
	string name;
	pair<int,int> coordinates;

public:
	Place();
	Place(string n,pair<int,int> coord);
	~Place();

	//setters
	void setName(string n);
	void setCoords(int x, int y);

	//getters
	string getName() const;
	pair<int,int> getCoords() const;

	string toString();
};

#endif //PLACE_H_
