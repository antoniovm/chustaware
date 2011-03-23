/*
 * EntradaSalida.cpp
 *
 *  Created on: 16/03/2011
 *  Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#include "EntradaSalida.hpp"

EntradaSalida::EntradaSalida() {

}

EntradaSalida::~EntradaSalida() {

}

void EntradaSalida::generarCabecera(fstream & archivo) {
	Cabecera cabecera(0,0,sizeof(Animal)+1,-1);
	archivo.write((char*)(&cabecera), sizeof(Cabecera));
}

void EntradaSalida::leerTexto() {
	fstream archivo("zoo-data.txt", fstream::in);
	string buffer;	//Cadena temporal
	char* cadena;	//Puntero buffer
	Animal* animal;	//Objeto temporal
	while(!archivo.eof()){
		getline(archivo, buffer);
		cadena = new char[buffer.size()];	//Reserva de memoria para un registro
		strcpy(cadena, buffer.data());
		animal = new Animal(strtok(cadena, ","), *strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","),	*strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","), *strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","),	atoi(strtok(NULL, ",")), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","), atoi(strtok(NULL, ",")));	//Construccion de un animal

		animals.push_back(animal);
		delete [] cadena;		//Borrado de buffer
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
		// terminar
	}
}


