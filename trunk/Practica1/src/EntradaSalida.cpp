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
/**
 * Inicializa la cabecera del archivo
 */
void EntradaSalida::generarCabecera(fstream & archivo) {
	Cabecera cabecera(0,0,sizeof(Animal)+1,-1);
	archivo.write((char*)(&cabecera), sizeof(Cabecera));
}
/**
 * Devuelve true si el archivo esta vacio
 */
bool EntradaSalida::comprobarArchivoVacio(fstream & archivo) {
	int tam = 0;
	streampos posActual = archivo.tellg();
	archivo.seekg(0, ios::end);	// Ponemos el puntero al final del archivo
	tam = archivo.tellg();
	archivo.seekg(posActual); // Volvemos a poner el puntero donde estaba
	return (tam == 0);
}
/**
 * Lee el archivo de texto zoo-data.txt y lo almacena en memoria en una lista de Animales
 */
void EntradaSalida::leerTexto() {
	fstream archivo("zoo-data.txt", fstream::in);
	string buffer;	//Cadena temporal
	char* cadena;	//Puntero buffer
	Animal* animal;	//Objeto temporal
	while(!archivo.eof()){
		getline(archivo, buffer);
		if(archivo.eof())break;
		cadena = new char[buffer.size()];	//Reserva de memoria para un registro
		strcpy(cadena, buffer.data());		//string to char*
											//Construccion de un animal
		animal = new Animal(strtok(cadena, ","), *strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","),	*strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","), *strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","),	atoi(strtok(NULL, ",")), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","), atoi(strtok(NULL, ",")));

		animals.push_back(animal);	//se a�ade a la lista de animales

		delete [] cadena;		//Borrado de buffer
	}
	archivo.close();
}
/**
 * Lee los RLFs del archivo binario zoo-data.dat y los almacena en memoria en una list<Animal>
 */
void EntradaSalida::leerBinario() {
	fstream archivo("zoo-data.dat", fstream::in | fstream::binary);
	Cabecera cabecera;
	Registro *registro;

	if(!archivo.is_open()){
		cout << "No existe el archivo" << endl;
		return;
	}

	if(comprobarArchivoVacio(archivo)){	// Comprobamos si el tama�o del archivo es 0
		cout << "Archivo vacio" << endl;
		return;
	}
	archivo.read((char*)&cabecera,sizeof(Cabecera)); //Leemos cabecera

	if(cabecera.getNRegistros()==0) {
		cout << "No hay ningun registro en el archivo" << endl;
		return;
	}

	while(!archivo.eof()){	//Bucle de lectura
		registro = new Registro();
		archivo.read((char*)registro,sizeof(registro));
		if(registro->getValido()){ //Validar registro
			animals.push_back(registro->getAnimal());	//A�adimos animal
		}
		delete registro;
	}
	archivo.close();
}
/**
 * Escribe la lista de animales con RLFs en el archivo binario zoo-data.dat
 */
void EntradaSalida::escribir() {
	fstream archivoEntrada("zoo-data.dat", fstream::in | fstream::binary);
	fstream archivoSalida("zoo-data.dat", fstream::out | fstream::binary | fstream::app);

	/*string buffer;
	long direccion;	//Variable temporal para la direccion del siguiente "hueco"
	char* cadena;
	Animal* animal;*/

	Cabecera cabecera;
	Registro registro;
	list<Animal*>::iterator it;
	int nRegistros = 0;

	if(comprobarArchivoVacio(archivoEntrada))	//Si el archivo esta vacio
		generarCabecera(archivoSalida);

	archivoEntrada.read((char*)(&cabecera), sizeof(Cabecera)); // Leemos la cabecera

	if(cabecera.getNRegistros() == 0) {
		for (it = animals.begin(); it != animals.end(); it++) {
			registro.setAnimal(*it);
			archivoSalida.write((char*) (&registro), sizeof(Registro));
			nRegistros++;
		}

		cabecera.setNRegistros(nRegistros);
		archivoSalida.seekp(0, ios::beg);
		archivoSalida.write((char*)(&cabecera), sizeof(Cabecera));
	}

	/*while (!animals.empty()) {
		if(cabecera.getPrimerHueco()!=-1){	//Si no apunta a "NULL"
			archivoEntrada.seekp(cabecera.getPrimerHueco());	//Posicionamos para leer la direccion del siguiente eliminado saltandonos el byte de validez
			archivoEntrada.read((char*)&direccion, sizeof(long));	//Leemos la direccion del siguiente hueco
			archivoEntrada.seekp(cabecera.getPrimerHueco()+sizeof(long)+1);	//Posicionamos para escribir un animal (saltando validez y direccion)
		}

		archivoSalida.write((char*)animal,sizeof(Animal));//Escribimos el animal
		cabecera.setPrimerHueco(direccion);	//Almacenamos en la cabecera el primer hueco
		// terminar
	}*/

	archivoEntrada.close();
	archivoSalida.close();

}
/**
 * Muestra la lista de animales en memoria
 */
void EntradaSalida::mostrar() {
	list<Animal*>::iterator it;
	int i=1;
	for(it=animals.begin(); it!=animals.end(); it++, i++) {
		cout <<i<<"-"<< **it << endl;
	}
}




