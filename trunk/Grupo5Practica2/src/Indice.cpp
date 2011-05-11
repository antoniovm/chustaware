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
	indicePS.getES().leerTexto();	//lee el fichero zoo-data.txt para almacenar los animales en MP
	animales=indicePS.getES().getAnimals();
	fstream archivoIP("IP.dat",ios::binary|ios::out);
	fstream archivoIS("IS.dat",ios::binary|ios::out);
	fstream archivoAux("IAux.dat",ios::binary|ios::out);
	int posicionDatos;
	int posicionAux;

	while(!animals.empty()){
		//inserta en fichero de datos e Indice Primario y devuelve la posicion en el fichero de datos
		posicionDatos=indicePS.insertarIP(archivoIP,animales.front());
		posicionAux=indicePS.insertarAux(archivoAux,animales.front(),posicionDatos);
		indicePS.insertarIS(archivoIS,animales.front(),posicionAux);
		delete animales.begin();
	}

}

Indice::eliminar(string clave){
	IndicePS.buscarClaveP(clave);
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
