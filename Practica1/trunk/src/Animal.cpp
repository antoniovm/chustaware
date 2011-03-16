/*
 * Animal.cpp
 *
 *  Created on: 16/03/2011
 *      Author: Miguel
 */

#include "Animal.h"

Animal::Animal() {
	// TODO Auto-generated constructor stub

}

Animal::Animal(char *name, bool hair, bool feathers, bool eggs, bool milk,
		bool airborne, bool aquatic, bool predator, bool toothed,
		bool backbone, bool breathes, bool venomous, bool fins, int legs,
		bool tail, bool domestic, bool catsize, int type) {

	strcpy(this->name, name);
	this->hair = hair;
	this->feathers = feathers;
	this->eggs = eggs;
	this->milk = milk;
	this->airborne = airborne;
	this->aquatic = aquatic;
	this->predator = predator;
	this->toothed = toothed;
	this->backbone = backbone;
	this->breathes = breathes;
	this->venomous = venomous;
	this->fins = fins;
	this->legs = legs;
	this->tail = tail;
	this->domestic = domestic;
	this->catsize = catsize;
	this->type = type;
}

Animal::~Animal() {
	// TODO Auto-generated destructor stub
}
