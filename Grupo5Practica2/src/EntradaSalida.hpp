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

public:
	EntradaSalida();
	virtual ~EntradaSalida();
	void leerTexto();
	void leerBinario();
	streampos leerRegistro(int);
	void escribir();
	void mostrar();
	int insertar(Animal*);
	bool eliminar(long);
	void vaciar();
	long buscar(string);
	int calcularNumRegistro(int);
	list<Animal*>& getAnimals(){return animals;};
	//void generarCabecera(fstream&);
	bool comprobarArchivoVacio(fstream&);
};

#endif /* ENTRADASALIDA_HPP_ */
