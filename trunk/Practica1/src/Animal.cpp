/*
 * Animal.cpp
 *
 *  Created on: 16/03/2011
 *  Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#include "Animal.h"

Animal::Animal() {
	// TODO Auto-generated constructor stub

}

Animal::Animal(char *name, char hair, char feathers, char eggs, char milk,
		char airborne, char aquatic, char predator, char toothed,
		char backbone, char breathes, char venomous, char fins, int legs,
		char tail, char domestic, char catsize, int type) {

	strcpy(this->name, name);
	this->hair = isTrue(hair);
	this->feathers = isTrue(feathers);
	this->eggs = isTrue(eggs);
	this->milk = isTrue(milk);
	this->airborne = isTrue(airborne);
	this->aquatic = isTrue(aquatic);
	this->predator = isTrue(predator);
	this->toothed = isTrue(toothed);
	this->backbone = isTrue(backbone);
	this->breathes = isTrue(breathes);
	this->venomous = isTrue(venomous);
	this->fins = isTrue(fins);
	this->legs = legs;
	this->tail = isTrue(tail);
	this->domestic = isTrue(domestic);
	this->catsize = isTrue(catsize);
	this->type = type;
}

Animal::~Animal() {
	// TODO Auto-generated destructor stub
}

bool Animal::isTrue(char caracter) {
	if (caracter == '0') {
		return false;
	}
	return true;
}

bool Animal::getAirborne() const
{
    return airborne;
}

bool Animal::getAquatic() const
{
    return aquatic;
}

bool Animal::getBackbone() const
{
    return backbone;
}

bool Animal::getBreathes() const
{
    return breathes;
}

bool Animal::getCatsize() const
{
    return catsize;
}

bool Animal::getDomestic() const
{
    return domestic;
}

bool Animal::getEggs() const
{
    return eggs;
}

bool Animal::getFeathers() const
{
    return feathers;
}

bool Animal::getFins() const
{
    return fins;
}

bool Animal::getHair() const
{
    return hair;
}

int Animal::getLegs() const
{
    return legs;
}

bool Animal::getMilk() const
{
    return milk;
}

char* Animal::getName()
{
	char* cadena;
	cadena = new char[50];
	strcpy(cadena, name);
    return cadena;
}

bool Animal::getPredator() const
{
    return predator;
}

bool Animal::getTail() const
{
    return tail;
}

bool Animal::getToothed() const
{
    return toothed;
}

int Animal::getType() const
{
    return type;
}

bool Animal::getVenomous() const
{
    return venomous;
}

void Animal::setAirborne(bool airborne)
{
    this->airborne = airborne;
}

void Animal::setAquatic(bool aquatic)
{
    this->aquatic = aquatic;
}

void Animal::setBackbone(bool backbone)
{
    this->backbone = backbone;
}

void Animal::setBreathes(bool breathes)
{
    this->breathes = breathes;
}

void Animal::setCatsize(bool catsize)
{
    this->catsize = catsize;
}

void Animal::setDomestic(bool domestic)
{
    this->domestic = domestic;
}

void Animal::setEggs(bool eggs)
{
    this->eggs = eggs;
}

void Animal::setFeathers(bool feathers)
{
    this->feathers = feathers;
}

void Animal::setFins(bool fins)
{
    this->fins = fins;
}

void Animal::setHair(bool hair)
{
    this->hair = hair;
}

void Animal::setLegs(int legs)
{
    this->legs = legs;
}

void Animal::setMilk(bool milk)
{
    this->milk = milk;
}

void Animal::setName(char* name)
{
    strcpy(this->name, name);
}

void Animal::setPredator(bool predator)
{
    this->predator = predator;
}

void Animal::setTail(bool tail)
{
    this->tail = tail;
}

void Animal::setToothed(bool toothed)
{
    this->toothed = toothed;
}

void Animal::setType(int type)
{
    this->type = type;
}

void Animal::setVenomous(bool venomous)
{
    this->venomous = venomous;
}

ostream& operator <<(ostream & os, Animal animal) {
	os << animal.name << "|";
	if (animal.hair) {
		os << "hair|";
	}
	if (animal.feathers) {
		os << "feathers|";
	}
	if (animal.eggs) {
		os << "eggs|";
	}
	if (animal.milk) {
		os << "milk|";
	}
	if (animal.airborne) {
		os << "airborne|";
	}
	if (animal.aquatic) {
		os << "aquatic|";
	}
	if (animal.predator) {
		os << "predator|";
	}
	if (animal.toothed) {
		os << "toothed|";
	}
	if (animal.backbone) {
		os << "backbone|";
	}
	if (animal.breathes) {
		os << "breathes|";
	}
	if (animal.venomous) {
		os << "venomous|";
	}
	if (animal.fins) {
		os << "fins|";
	}
	os << "legs: " << animal.legs << "|";
	if (animal.tail) {
		os << "tail|";
	}
	if (animal.domestic) {
		os << "domestic|";
	}
	if (animal.catsize) {
		os << "catsize|";
	}
	os << "type: " << animal.type;
	return os;
}


