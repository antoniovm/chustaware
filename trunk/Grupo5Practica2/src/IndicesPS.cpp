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

void IndicesPS::insertarIS(fstream &archivoIS, Animal* animal, int posAux)
{
	RegistroIS* rIS;
	RegistroAux* rAux;

	if (buscarClaveS(animal->getLegs()) == -1) {
		rAux = new RegistroAux(true, animal->getName(), -1, es.buscar(animal->getName()));
		rIS = new RegistroIS(animal->getLegs(), 0);
	}

}

void IndicesPS::borrarIS(int int1)
{
}

long IndicesPS::buscarClaveS(int patas)
{
	fstream archivo("IS.dat",ios::binary|ios::in | ios::out);
	archivo.close();
}

int IndicesPS::insertarAux(fstream &archivoAux, Animal* animal, int posDatos) {
	return -1;
}

//esto no vale pa na....inicializacion cutre <<<<--------------------------------
void IndicesPS::crearIP(fstream of, Animal* a)
{
/*
	RegistroIP regIP();
	int posicion=0;
	//fstream salida("IP.dat",ios::binary|ios::out);
	//fstream salidaBinario("zoo-data.dat",ios::binary|ios::out);
	//es.leerTexto();
	//animales=es.getAnimals();

	regIP.setClavePrimaria(a->getName());
	posicion = es.insertar(a);
	regIP.setPosRegistro(posicion);
	salida.write((char*) (&regIP), sizeof(RegistroIP));
	while(!animales.empty()){

		delete animales.begin();
		animales.pop_front();
	}
	salida.close();*/
}
/**
 * Inserta un registro en el indice primario.
 */
int IndicesPS::insertarIP(fstream &archivo, Animal* a)
{
	//fstream archivo("IP.dat", ios::in | ios::out | ios::binary | ios::ate);
	int posicion;
	RegistroIP* rIP = NULL;

	posicion=es.insertar(a);

	// Si el archivo esta vacio insertamos directamente.
	if (archivo.tellg() == ios::beg) {
		rIP = new RegistroIP(a->getName(), posicion);	// Creamos el registro.
		archivo.write((char*)(rIP), sizeof(RegistroIP));
		delete rIP;
		archivo.close();
		return -1;
	}

	while(archivo.tellg() > ios::beg) {
		archivo.seekg(archivo.tellg()-(streampos)sizeof(RegistroIP));	// Posicionamos el puntero en la posicion del registro anterior.
		archivo.read((char*)(rIP), sizeof(RegistroIP));	// Leemos el registro.
		// Si la clave del registro que vamos a insertar es mayor que la clave del registro que acabamos de leer, insertamos el registro.
		if (a->getName() > rIP->getClavePrimaria()) {
			rIP = new RegistroIP(a->getName(), posicion);	// Creamos el registro.
			archivo.write((char*) (rIP), sizeof(RegistroIP));
			delete rIP;
			archivo.close();
			return posicion;
		}
		// Si no, copiamos el registro en la siguiente posicion y posicionamos el puntero en la posicion anterior.
		archivo.write((char*) (rIP), sizeof(RegistroIP));
		archivo.seekg(archivo.tellg() - (streampos)(sizeof(RegistroIP)*2));
	}
	//archivo.close();
}
/**
 * Elimina un registro en el indice primario.
 */
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
		archivo.seekg(centro*sizeof(RegistroIP),ios::beg);//ios::beg o cero??
		archivo.read((char*)(rIP), sizeof(RegistroIP));
		if(rIP->getClavePrimaria()==clave){
			posicionReg=rIP->getPosRegistro();
			delete rIP;
			archivo.close();
			return posicionReg;
		}
		if(rIP->getClavePrimaria() > clave)
			superior = centro - 1;
		else
			inferior = centro + 1;

	}
	delete rIP;
	archivo.close();
	return -1;
}
/*
 * Muestra el fichero indice primario
 */
RegistroIP IndicesPS::leerIP()
{
	fstream archivo("IP.dat", ios::in | ios::binary);
	RegistroIP* rIP;
	while(1){
		archivo.read((char*)(&rIP),sizeof(RegistroIP));
		if(archivo.eof())
			break;
		cout << rIP->getClavePrimaria() << " - " << rIP->getPosRegistro() << endl;
	}
	delete rIP;
	archivo.close();
}


