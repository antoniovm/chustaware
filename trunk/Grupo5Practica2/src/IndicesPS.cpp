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
/*
 * Inserta en el indice secundario y actualiza la lista encadenada del fichero aux
 */
void IndicesPS::insertarIS(fstream &archivoIS, Animal* animal, int posAux) {
	RegistroIS* rIS;
	RegistroAux* rAux;
	int primero = 0;
	primero=buscarClaveS(animal->getLegs());
	if (primero == -1) {//si no hay entrada en archivoIS
		rIS = new RegistroIS(animal->getLegs(), 0);
		archivoIS.seekg(ios::ate);
		while (archivoIS.tellg() > ios::beg) {
			archivoIS.seekg(archivoIS.tellg() - (streampos) sizeof(RegistroIS)); // Posicionamos el puntero en la posicion del registro anterior.
			archivoIS.read((char*) (rIS), sizeof(RegistroIS)); // Leemos el registro.
			// Si la clave del registro que vamos a insertar es mayor que la clave del registro que acabamos de leer, insertamos el registro.
			if (animal->getLegs() > rIS->getClaveSecundaria()) {
				rIS = new RegistroIS(animal->getLegs(), posAux); // Creamos el registro.
				archivoIS.write((char*) (rIS), sizeof(RegistroIS));
				delete rIS;
				archivoIS.close();
				return;
			}
			// Si no, copiamos el registro en la siguiente posicion y posicionamos el puntero en la posicion anterior.
			archivoIS.write((char*) (rIS), sizeof(RegistroIS));
			archivoIS.seekg(archivoIS.tellg() - (streampos) (sizeof(RegistroIS)*2));
		}
	}
	//si la clave secundaria ya existia, enlazamos la lista encadenada del fichero Aux
	fstream archivoAux("IAux.dat", ios::binary | ios::out);
	archivoAux.seekg(primero);
	while (1) {
		archivoAux.read((char*) (rAux), sizeof(RegistroAux));
		if (rAux->getSiguiente() == -1) { //si es el final de la lista
			rAux->setSiguiente(posAux);
			archivoIS.close();
			archivoAux.close();
			delete rAux;
			return;
		}
		archivoAux.seekg(rAux->getSiguiente());
	}
}
void IndicesPS::borrarIS(int int1)
{
}
/**
 * Devuelve la posicion del primer elemento de la lista encadenada con esa clave secundaria.-1 si no esta en el archivoIS.
 */
int IndicesPS::buscarClaveS(int patas)
{
	fstream archivo("IS.dat", ios::in | ios::out | ios::binary | ios::ate);//ojo con el ios::ate
		int inferior=0;
		int superior=(archivo.tellg()/(streampos)sizeof(RegistroIS))-1;
		int centro=0;
		int posicionPrimero;
		RegistroIS* rIS = NULL;

		while(inferior <= superior){
			centro=((superior-inferior)/2)+inferior;
			archivo.seekg(centro*sizeof(RegistroIS),ios::beg);//ios::beg o cero??
			archivo.read((char*)(rIS), sizeof(RegistroIS));
			if(rIS->getClaveSecundaria()==patas){
				posicionPrimero=rIS->getPosPrimero();
				delete rIS;
				archivo.close();
				return posicionPrimero;
			}
			if(rIS->getClaveSecundaria() > patas)
				superior = centro - 1;
			else
				inferior = centro + 1;

		}
		delete rIS;
		archivo.close();
		return -1;
}
/**
 * inserta reg en el archivo aux y devuelve la posicion en la que se inserto
 */
int IndicesPS::insertarAux(fstream &archivoAux, Animal* animal, int posDatos) {
	int posicion=0;
		RegistroAux* rAux = NULL;
		// Si el archivo esta vacio insertamos directamente.
		archivoAux.seekp(ios::ate);
		if (archivoAux.tellg() == ios::beg) {
			rAux = new RegistroAux(true,animal->getName(), -1,posDatos);	// Creamos el registro.
			archivoAux.write((char*)(rAux), sizeof(RegistroAux));
			delete rAux;
			archivoAux.close();
			return posicion;
		}
		//comprueba si hay hueco libre para insercion apilada
		archivoAux.seekp(ios::beg);
		while(!archivoAux.eof()){
			archivoAux.read((char*)(rAux), sizeof(RegistroAux));
			if(!rAux->getValido()){
				archivoAux.seekg(archivoAux.tellg()-(streampos)sizeof(RegistroAux));
				posicion=(int)archivoAux.tellg();
				rAux = new RegistroAux(true,animal->getName(), -1,posDatos);
				archivoAux.write((char*)(rAux),sizeof(RegistroAux));
				delete rAux;
				archivoAux.close();
				return posicion;
			}
		}
		//si no ha encontrado hueco, inserta al final
		posicion=(int)archivoAux.tellg();
		rAux = new RegistroAux(true,animal->getName(), -1,posDatos);
		archivoAux.write((char*)(rAux),sizeof(RegistroAux));
		delete rAux;
		archivoAux.close();
		return posicion;
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
		return posicion;
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


