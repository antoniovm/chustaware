/*
 * Animal.h
 *
 *  Created on: 16/03/2011
 *  Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class Animal {
private:
	char name[50];
	bool hair;
	bool feathers;
	bool eggs;
	bool milk;
	bool airborne;
	bool aquatic;
	bool predator;
	bool toothed;
	bool backbone;
	bool breathes;
	bool venomous;
	bool fins;
	bool tail;
	bool domestic;
	bool catsize;
	int legs;
	int type;

	bool isTrue(char);
public:
	Animal();
	Animal(char* name, char hair, char feathers, char eggs, char milk,
			char airborne, char aquatic, char predator, char toothed,
			char backbone, char breathes, char venomous, char fins, int legs,
			char tail, char domestic, char catsize, int type);
	virtual ~Animal();

    bool getAirborne() const;
    bool getAquatic() const;
    bool getBackbone() const;
    bool getBreathes() const;
    bool getCatsize() const;
    bool getDomestic() const;
    bool getEggs() const;
    bool getFeathers() const;
    bool getFins() const;
    bool getHair() const;
    int getLegs() const;
    bool getMilk() const;
    char* getName();
    bool getPredator() const;
    bool getTail() const;
    bool getToothed() const;
    int getType() const;
    bool getVenomous() const;
    void setAirborne(bool airborne);
    void setAquatic(bool aquatic);
    void setBackbone(bool backbone);
    void setBreathes(bool breathes);
    void setCatsize(bool catsize);
    void setDomestic(bool domestic);
    void setEggs(bool eggs);
    void setFeathers(bool feathers);
    void setFins(bool fins);
    void setHair(bool hair);
    void setLegs(int legs);
    void setMilk(bool milk);
    void setName(char name[50]);
    void setPredator(bool predator);
    void setTail(bool tail);
    void setToothed(bool toothed);
    void setType(int type);
    void setVenomous(bool venomous);

    friend ostream& operator<<(ostream&, Animal);
};

#endif /* ANIMAL_H_ */
