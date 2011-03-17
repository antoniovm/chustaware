/*
 * EntradaSalida.hpp
 *
 *  Created on: 16/03/2011
 *      Author: Miguel
 */

#ifndef ENTRADASALIDA_HPP_
#define ENTRADASALIDA_HPP_

#include <list>
#include <cstdio>
#include <fstream>
#include "Animal.h"

using namespace std;

class EntradaSalida {
private:
	list<Animal> animales;
public:
	EntradaSalida();
	virtual ~EntradaSalida();
	void leer();
	void escribir();
};

#endif /* ENTRADASALIDA_HPP_ */
