/*
 * EntradaSalida.hpp
 *
 *  Created on: 16/03/2011
 *  Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#ifndef ENTRADASALIDA_HPP_
#define ENTRADASALIDA_HPP_

#include <list>
#include <cstdio>
#include <fstream>
#include "Animal.h"
#include "Cabecera.h"

using namespace std;

class EntradaSalida {
private:
	//Cabecera cabecera;
	list<Animal*> animals;

	void generarCabecera(fstream&);
public:
	EntradaSalida();
	virtual ~EntradaSalida();
	void leerTexto();
	void leerBinario();
	void escribir();
	void mostrar();
};

#endif /* ENTRADASALIDA_HPP_ */
