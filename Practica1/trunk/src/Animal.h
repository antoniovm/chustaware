/*
 * Animal.h
 *
 *  Created on: 16/03/2011
 *      Author: Miguel
 */

#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <cstring>
#include <cstdlib>

using namespace std;

class Animal {
private:
	char name[50];
	bool hair, feathers, eggs, milk, airborne, aquatic, predator, toothed,
			backbone, breathes, venomous, fins, tail, domestic, catsize;
	int legs, type;
public:
	Animal();
	Animal(char* name, bool hair, bool feathers, bool eggs, bool milk,
			bool airborne, bool aquatic, bool predator, bool toothed,
			bool backbone, bool breathes, bool venomous, bool fins, int legs,
			bool tail, bool domestic, bool catsize, int type);
	virtual ~Animal();
};

#endif /* ANIMAL_H_ */
