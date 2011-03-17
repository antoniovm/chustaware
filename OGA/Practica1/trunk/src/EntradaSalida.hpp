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
	list<Animal*> animals;

	void generarCabecera(fstream&);
public:
	EntradaSalida();
	virtual ~EntradaSalida();
	void leerTexto();
	void leerBinario();
	void escribir();
};

#endif /* ENTRADASALIDA_HPP_ */
