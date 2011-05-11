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
Indice::crearFicherosPS(){
	list<Animals*> animales;
	indicePS.getES().leerTexto();
	animales=indicePS.getES().getAnimals();
	fstream archivoIP("IP.dat",ios::binary|ios::out);
	fstream archivoIS("IS.dat",ios::binary|ios::out);
	fstream archivoAux("IAux.dat",ios::binary|ios::out);

	while(!animals.empty()){
		indicePS.insertarIP(archivoIP,animales.front());
		indicePS.insertarAux();
		indicePS.insertarIS();
		delete animales.begin();
	}

}

Indice::eliminar(Animal){

}
Indice::buscarP(){

}

Indice::buscarS(int patas){

}

Indice::mostrarIP(){

}
Indice::mostrarIS(){

}

Indice::crearFicheroBloques(){

}
