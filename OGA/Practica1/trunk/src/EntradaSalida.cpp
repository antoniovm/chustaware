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

void EntradaSalida::generarCabecera(fstream & archivo) {
	char* cabecera = new char[250];
	memset(cabecera, 0, 250);
	long primerHueco = -1;
	strncpy(&cabecera[8],((char*)&primerHueco), sizeof(long));	//Copia 4 bytes
	archivo.write(cabecera, 250);
	delete[]cabecera;
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
		animal = new Animal(strtok(cadena, ","), *strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","),	*strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","), *strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","),	atoi(strtok(NULL, ",")), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","), atoi(strtok(NULL, ",")));

		animals.push_back(animal);
		delete [] cadena;
	}
}

void EntradaSalida::leerBinario() {
	/*fstream archivo("zoo-data.txt", fstream::in | fstream::binary);
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
	}*/
}

void EntradaSalida::escribir() {
	fstream archivo("zoo-data.dat", fstream::in | fstream::binary | fstream::ate);
	string buffer;
	char* cadena;
	Animal* animal;
	if(archivo.eof()) {
		generarCabecera(archivo);
	} else {
		archivo.read(cadena, 250);
	}

	while (!archivo.eof()) {
		archivo.read(cadena, sizeof(Animal));
	}
}


