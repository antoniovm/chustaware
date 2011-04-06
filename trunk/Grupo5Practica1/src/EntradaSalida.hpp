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
#include "Registro.h"

using namespace std;

class EntradaSalida {
private:
	list<Animal*> animals;

	void generarCabecera(fstream&);
	bool comprobarArchivoVacio(fstream&);

public:
	EntradaSalida();
	virtual ~EntradaSalida();
	void leerTexto();
	void leerBinario();
	void leerRegistro(int);
	void escribir();
	void mostrar();
	void insertar(Animal*);
	bool eliminar(long);
	void vaciar();
	long buscar(string);
};

#endif /* ENTRADASALIDA_HPP_ */
