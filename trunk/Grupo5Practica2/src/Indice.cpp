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
		//indicesPS.insertarIS(animales.front(),posicionAux); //-------falla la busquedaBinaria------
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

void Indice::mostrarIP(){

}
void Indice::mostrarIS(){

}

void Indice::crearFicheroBloques(){

}
