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
	fstream archivoIP("IP.dat",ios::binary|ios::in|ios::out);
	fstream archivoIS("IS.dat",ios::binary|ios::in|ios::out);
	fstream archivoAux("IAux.dat",ios::binary|ios::in|ios::out);
	int posicionDatos=0;
	int posicionAux=0;

	while(!animales.empty()){
		//inserta en fichero de datos e Indice Primario y devuelve la posicion en el fichero de datos
		posicionDatos=indicesPS.insertarIP(archivoIP,animales.front());
		posicionAux = indicesPS.insertarAux(archivoAux,animales.front(),posicionDatos);
		indicesPS.insertarIS(archivoIS,animales.front(),posicionAux);
		delete *animales.begin();
		animales.pop_front();
	}
	archivoIP.close();
	archivoIS.close();
	archivoAux.close();
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

void Indice::mostrarIP(){

}
void Indice::mostrarIS(){

}

void Indice::crearFicheroBloques(){

}
