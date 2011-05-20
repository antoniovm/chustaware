/*
 * Indice.cpp
 *
 *  Created on: 11/05/2011
 *      Author: Sergio
 */

#include "Indice.h"

Indice::Indice() {
	// TODO Auto-generated constructor stub

}

Indice::~Indice() {
	// TODO Auto-generated destructor stub
}
void Indice::crearFicherosPS(){
	list<Animal*> animales;
	indicesPS.getES().leerTexto();	//lee el fichero zoo-data.txt para almacenar los animales en MP
	animales=indicesPS.getES().getAnimals();
    int posicionDatos=0;
	int posicionAux=0;

	fstream IP("IP.dat",ios::binary|ios::out);	//borrado de archivos
	fstream IS("IS.dat",ios::binary|ios::out);
	fstream Aux("IAux.dat",ios::binary|ios::out);
	fstream zooData("zoo-data.dat",ios::binary|ios::out);
	IP.close();
	IS.close();
	Aux.close();
	zooData.close();

	while(!animales.empty()){
		//inserta en fichero de datos e Indice Primario y devuelve la posicion en el fichero de datos
		posicionDatos=indicesPS.insertarIP(animales.front());
		posicionAux = indicesPS.insertarAux(animales.front(),posicionDatos);
		indicesPS.insertarIS(animales.front(),posicionAux); //-------falla la busquedaBinaria------
		delete *animales.begin();
		animales.pop_front();
	}
}

void Indice::eliminar(string clave){
	long posicion=0;
	posicion=indicesPS.buscarClaveP(clave);
	if(-1==posicion){
		cout << "El animal no esta en el archivo de datos" << endl;
		return;
	}

	indicesPS.getES().eliminar(posicion);
	indicesPS.borrarIP(clave);
}
int Indice::buscarP(string s){

}

int Indice::buscarS(int patas){

}

void Indice::mostrar(string nombre) {
	fstream archivoIndice(nombre.data(), fstream::in | fstream::binary);

	if (!archivoIndice.is_open()) {
		cout << "No existe el archivo" << endl;
		return;
	}
	// Comprobamos si el archivo esta vacio
	archivoIndice.seekg(0, ios::end);
	if (archivoIndice.tellg() == 0) {
		cout << "Archivo vacio" << endl;
		archivoIndice.close();
		return;
	}
	archivoIndice.seekg(0, ios::beg);
	if (nombre == "IP.dat") {
		RegistroIP registro;
		printf("%-17s%-20s\n", "Clave primaria", "Posicion en datos");
		while (1) {
			archivoIndice.read((char*) &registro, sizeof(RegistroIP));
			if (archivoIndice.eof())
				break;
			printf("%-17s%-20d\n", registro.getClavePrimaria().data(), registro.getPosRegistro());
		}
		cout << endl;
	}
	if (nombre == "IS.dat") {
		RegistroIS registro;
		printf("%-20s%-20s\n", "Clave secundaria", "Posicion del primero en aux");
		while (1) {
			archivoIndice.tellg();
			archivoIndice.read((char*) &registro, sizeof(RegistroIS));
			archivoIndice.tellg();
			if (archivoIndice.eof())
				break;
			printf("%-20d%-20d\n", registro.getClaveSecundaria(), registro.getPosPrimero());

		}
		cout << endl;
	}
	if (nombre == "IAux.dat") {
		RegistroAux registro;
		printf("%-17s%-17s%-20s%-20s\n", "Bit de validez", "Clave primaria", "Posicion siguiente", "Posicion datos");
		while (1) {
			archivoIndice.read((char*) &registro, sizeof(RegistroAux));
			if (archivoIndice.eof())
				break;
			printf("%-17s%-17d%-20d%-20d\n", registro.getValido(), registro.getClavePrimaria(), registro.getSiguiente(), registro.getPosDatos());
		}
		cout << endl;
	}

	archivoIndice.close();
}

void Indice::crearFicheroBloques(){

}