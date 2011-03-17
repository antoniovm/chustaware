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

void EntradaSalida::leerTexto() {
	fstream archivo("zoo-data.txt", fstream::in);
	string buffer;
	char* cadena;
	Animal* animal;
	while(!archivo.eof()){
		getline(archivo, buffer);
		cadena = new char[buffer.size()];
		strcpy(cadena, buffer.data());
		animal = new Animal(strtok(cadena, ","), *strtok(cadena, ","), *strtok(cadena, ","),
				*strtok(cadena, ","), *strtok(cadena, ","),
				*strtok(cadena, ","), *strtok(cadena, ","),
				*strtok(cadena, ","), *strtok(cadena, ","),
				*strtok(cadena, ","), *strtok(cadena, ","),
				*strtok(cadena, ","), *strtok(cadena, ","),
				atoi(strtok(cadena, ",")), *strtok(cadena, ","), *strtok(cadena, ","),
				*strtok(cadena, ","), atoi(strtok(cadena, ",")));
		animales.push_back(animal);
		delete [] cadena;
	}
}

void EntradaSalida::leerBinario() {
	fstream archivo("zoo-data.txt", fstream::in | fstream::binary);
	string buffer;
	char* cadena;
	Animal* animal;
	while(!archivo.eof()){
		archivo.read(cadena, sizeof(Animal));
		cadena = new char[buffer.size()];
		strcpy(cadena, buffer.data());
		animal = new Animal(strtok(cadena, ","), *strtok(cadena, ","), *strtok(cadena, ","),
				*strtok(cadena, ","), *strtok(cadena, ","),
				*strtok(cadena, ","), *strtok(cadena, ","),
				*strtok(cadena, ","), *strtok(cadena, ","),
				*strtok(cadena, ","), *strtok(cadena, ","),
				*strtok(cadena, ","), *strtok(cadena, ","),
				atoi(strtok(cadena, ",")), *strtok(cadena, ","), *strtok(cadena, ","),
				*strtok(cadena, ","), atoi(strtok(cadena, ",")));
		animales.push_back(animal);
		delete [] cadena;
	}
}

void EntradaSalida::escribir() {

}


