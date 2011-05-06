/*
 * IndicesPS.cpp
 *
 *  Created on: 27/04/2011
 *      Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#include "IndicesPS.h"

IndicesPS::IndicesPS() {
	// TODO Auto-generated constructor stub

}

IndicesPS::~IndicesPS() {
	// TODO Auto-generated destructor stub
}

void IndicesPS::crearIS()
{
	ofstream salida;
	salida.open("IS.dat", ios::binary);
	salida.close();
}

void IndicesPS::borrarIS(int int1)
{
}

void IndicesPS::insertarIS(int int1)
{
}
//esto no vale pa na
void IndicesPS::crearIP()
{
	list<Animals*> animales;
	RegistroIP* regIP=NULL;
	fstream salida("IP.dat",ios::binary|ios::out);
	es.leerBinario();
	animales=es.getAnimals();

	while(!animales.empty()){
		regIP->setClavePrimaria((animales.front())->getName());
		salida.write((char*)(&regIP), sizeof(RegistroIP));
		delete *animales.begin();
		animales.pop_front();
	}
	salida.close();
}
/**
 * Inserta un registro en el indice primario.
 */
void IndicesPS::insertarIP(string clave)
{
	fstream archivo("IP.dat", ios::in | ios::out | ios::binary | ios::ate);
	int posicion;
	RegistroIP* rIP = NULL;

	// Si el registro no esta en el archivo de datos, no insertamos en el indice primario.
	posicion = es.buscar(clave);
	if (posicion == -1) {
		return;
	}

	rIP = new RegistroIP(clave, posicion);	// Creamos el registro.
	// Si el archivo esta vacio insertamos directamente.
	if (archivo.tellg() == ios::beg) {
		archivo.write((char*)(rIP), sizeof(RegistroIP));
		delete rIP;
		archivo.close();
		return;
	}

	while(archivo.tellg() > ios::beg) {
		archivo.seekg(archivo.tellg()-(streampos)sizeof(RegistroIP));	// Posicionamos el puntero en la posicion del registro anterior.
		archivo.read((char*)(rIP), sizeof(RegistroIP));	// Leemos el registro.
		// Si la clave del registro que vamos a insertar es mayor que la clave del registro que acabamos de leer, insertamos el registro.
		if (clave > rIP->getClavePrimaria()) {
			archivo.write((char*) (rIP), sizeof(RegistroIP));
			delete rIP;
			archivo.close();
			return;
		}
		// Si no, copiamos el registro en la siguiente posicion y posicionamos el puntero en la posicion anterior.
		archivo.write((char*) (rIP), sizeof(RegistroIP));
		archivo.seekg(archivo.tellg() - (streampos) sizeof(RegistroIP));
	}
	archivo.close();
}

void IndicesPS::borrarIP(string clave) {
	fstream archivo("IP.dat", ios::in | ios::out | ios::binary);
	RegistroIP* rIP = NULL;
	vector<RegistroIP*> registros;
	vector<RegistroIP*>::iterator it;
	int posicion = buscarClaveP(clave);

	if (posicion == -1) {
		archivo.close();
		return;
	}

	// Cargamos en memoria todos los registros excepto el registro que queremos eliminar.
	while (!archivo.eof()) {
		if (archivo.tellg() == posicion) {
			archivo.seekg(posicion + (streampos)sizeof(RegistroIP));
		}
		archivo.read((char*) (rIP), sizeof(RegistroIP));
		registros.push_back(rIP);
	}
	archivo.close();

	// Sobreescribimos el archivo con los datos que tenemos en memoria.
	archivo.open("IP.dat", ios::out | ios::binary);
	for (it = registros.begin(); it != registros.end(); it++) {
		archivo.write((char*)(rIP), sizeof(RegistroIP));
	}
	archivo.close();

	// Liberamos memoria.
	delete rIP;
	for (it = registros.begin(); it != registros.end(); it++) {
		delete (*it);
	}
	registros.clear();
}

void IndicesPS::buscarClaveS(int patas)
{
	fstream archivo("IS.dat",ios::binary|ios::in | ios::out);
}
/**
 * Busqueda Binaria en Indice Primario (IP.dat)
 * Devuelve la posicion del Registro en el fichero de datos o -1 sino esta.
 */
long IndicesPS::buscarClaveP(string clave)
{
	fstream archivo("IP.dat", ios::in | ios::out | ios::binary | ios::ate);//ojo con el ios::ate
	int inferior=0;
	int superior=(archivo.tellg()/(streampos)sizeof(RegistroIP))-1;
	int centro=0;
	long posicionReg;
	RegistroIP* rIP = NULL;

	while(inferior <= superior){
		centro=((superior-inferior)/2)+inferior;
		archivo.seekg(ios::beg, centro*sizeof(RegistroIP));//ios::beg o cero??
		archivo.read((char*)(rIP), sizeof(RegistroIP));
		if(rIP->getClavePrimaria()==clave){
			posicionReg=rIP->posRegistro();
			delete rIP;
			return posicionReg;
		}
		if(rIP->getClavePrimaria() > clave)
			superior = centro - 1;
		else
			inferior = centro + 1;

	}
	delete rIP;
	return -1;
}

RegistroIP IndicesPS::leerIP()
{
}


