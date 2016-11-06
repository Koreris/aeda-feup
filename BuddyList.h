#pragma once

#include <map>
#include <unordered_set>
#include "Person.h"

using namespace std;

class BuddyList
{

private:

	void removeVertex(const Person& personA);
	void removeEdge(const Person& personA, const Person& personB);
	void insertEdge(const Person& personA, const Person& personB);

public:

	BuddyList()
	{
	}

	virtual ~BuddyList()
	{
	}

	void removeUser(const Person& personA);
	void insertBuddies(const Person& personA, const Person& personB);
	void removeBuddies(const Person& personA, const Person& personB);

	unordered_set<Person> getBuddies(const Person& personA) const;

	bool areBuddies(const Person& personA, const Person& personB) const;

private:

	map<Person, unordered_set<Person>> buddies;
};
