#include "BuddyList.h"

void BuddyList::insertEdge(const Person& personA, const Person& personB)
{
	auto it = buddies.find(personA);

	if (it == buddies.end())
	{
		buddies.emplace(personA, std::unordered_set<Person> { personB });
	}
	else
	{
		it->second.insert(personB);
	}
}

void BuddyList::removeEdge(const Person& personA, const Person& personB)
{
	auto it = buddies.find(personA);

	if (it != buddies.end())
	{
		it->second.erase(personB);
	}
}

void BuddyList::removeVertex(const Person& personA)
{
	auto it = buddies.find(personA);

	if (it != buddies.end())
	{
		buddies.erase(it);
	}
}

void BuddyList::insertBuddies(const Person& personA, const Person& personB)
{
	insertEdge(personA, personB);
	insertEdge(personB, personA);
}

void BuddyList::removeBuddies(const Person& personA, const Person& personB)
{
	removeEdge(personA, personB);
	removeEdge(personB, personA);
}

void BuddyList::removeUser(const Person& personA)
{
	removeVertex(personA);

	for (auto& people : buddies)
	{
		people.second.erase(personA);
	}
}

bool BuddyList::areBuddies(const Person& personA, const Person& personB) const
{
	const auto it = buddies.find(personA);

	if (it == buddies.end())
	{
		return false;
	}

	return it->second.find(personB) != it->second.end();
}

unordered_set<Person> BuddyList::getBuddies(const Person& personA) const
{
	const auto it = buddies.find(personA);

	if (it != buddies.end())
	{
		return it->second;
	}
	else
	{
		return unordered_set<Person>();
	}
}
