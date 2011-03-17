/*
 * EntradaSalida.cpp
 *
 *  Created on: 16/03/2011
 *      Author: Miguel
 */

#include "EntradaSalida.hpp"

EntradaSalida::EntradaSalida() {
	// TODO Auto-generated constructor stub

}

EntradaSalida::~EntradaSalida() {
	// TODO Auto-generated destructor stub
}

void EntradaSalida::leer() {
	fstream archivo("zoo-data.txt", fstream::in);
	string buffer;
	char* ptr;
	char* cadena;
	Animal* animal;
	while(!archivo.eof()){
		getline(archivo, buffer);
		cadena = new char[buffer.size()];
		strcpy(cadena, buffer.data());
		animal = new Animal();
	}
}

void EntradaSalida::escribir() {

}


