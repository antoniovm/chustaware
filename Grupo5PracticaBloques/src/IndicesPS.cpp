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

/**
 * Inserta en fichero de datos e Indice Primario y devuelve la posicion del fichero de datos
 */
int IndicesPS::insertarIP(Animal* a)
{
	fstream archivoIP("IP.dat", ios::out | ios::in | ios::binary );
	int posDatos=es.insertar(a);	//inserta el animal en el archivo de datos
	RegistroIP* rIP= new RegistroIP(a->getName(), posDatos);// Creamos el registro.
	Cabecera cabecera;

	if (comprobarArchivoVacio(archivoIP)) { // Comprobamos si el tamaño del archivo es 0
		generarCabecera(archivoIP);
		archivoIP.tellg();
		archivoIP.write((char*)(rIP), sizeof(RegistroIP));
		archivoIP.tellg();
		archivoIP.close();
		return posDatos;
	}
	archivoIP.read((char*) &cabecera, sizeof(Cabecera)); //Leemos cabecera

	if(buscarClaveP(a->getName())>0){
		cout << "Ya existe un animal con ese nombre" << endl;
		return -1;	//Ya esta insertado
	}

	archivoIP.seekg(sizeof(Cabecera)+(int)cabecera.getNRegistros()*sizeof(RegistroIP));//ios::end

	while (archivoIP.tellg() > sizeof(Cabecera)) {
		archivoIP.seekg(archivoIP.tellg() - (streampos) sizeof(RegistroIP)); // Posicionamos el puntero en la posicion del registro anterior.
		archivoIP.tellg();
		archivoIP.read((char*) (rIP), sizeof(RegistroIP)); // Leemos el registro.
		// Si la clave del registro que vamos a insertar es mayor que la clave del registro que acabamos de leer, insertamos el registro.
		archivoIP.tellg();//-----------------------------------------------IS THE KEY!!
		if (a->getName() > rIP->getClavePrimaria()) {
			delete rIP;
			rIP = new RegistroIP(a->getName(), posDatos); // Creamos el nuevo registro.
			archivoIP.tellg();
			archivoIP.write((char*) (rIP), sizeof(RegistroIP));
			archivoIP.tellg();
			cabecera.setNRegistros(cabecera.getNRegistros() + 1); //Actualizamos la cabecera
			archivoIP.seekg(0, ios::beg);
			archivoIP.tellg();
			archivoIP.write((char*) (&cabecera), sizeof(Cabecera));
			archivoIP.tellg();
			delete rIP;
			archivoIP.close();
			return posDatos;
		}
		// Si no, copiamos el registro en la siguiente posicion y posicionamos el puntero en la posicion anterior.
		archivoIP.tellg();
		archivoIP.write((char*) (rIP), sizeof(RegistroIP));
		archivoIP.tellg();
		archivoIP.seekg(archivoIP.tellg()
				- (streampos) (sizeof(RegistroIP) * 2));
		archivoIP.tellg();

	}
	delete rIP;
	rIP = new RegistroIP(a->getName(), posDatos); // insercion en el top del fichero
	archivoIP.tellg();
	archivoIP.write((char*) (rIP), sizeof(RegistroIP));
	cabecera.setNRegistros(cabecera.getNRegistros()+1);
	archivoIP.seekg(0,ios::beg);
	archivoIP.tellg();
	archivoIP.write((char*) (&cabecera), sizeof(Cabecera));
	archivoIP.tellg();
	delete rIP;
	archivoIP.close();
	return posDatos;

}

/**
 * Busqueda Binaria.Devuelve la posicion del regIP en el ficheroIP o -1 si no esta
 */
long IndicesPS::buscarClaveP(string clave)
{
	fstream archivo("IP.dat", ios::in | ios::out | ios::binary);
	Cabecera cabecera;
	archivo.read((char*)(&cabecera),sizeof(Cabecera));
	archivo.seekg(0,ios::end);
	archivo.tellg();

	//inf,sup y centro indican el numRegistro no la posicion
	int inferior=0;
	int superior=((archivo.tellg()-(streampos)sizeof(Cabecera))-(streampos)sizeof(RegistroIP))/(streampos)sizeof(RegistroIP);
	int centro=0;
	RegistroIP* rIP = new RegistroIP("",0);

	while(inferior <= superior){
		centro=((superior-inferior)/2)+inferior;
		archivo.seekg(centro*sizeof(RegistroIP)+sizeof(Cabecera));
		archivo.tellg();
		archivo.read((char*)(rIP), sizeof(RegistroIP));
		archivo.tellg();

		if(rIP->getClavePrimaria()==clave){
			archivo.close();
			return centro*sizeof(RegistroIP)+sizeof(Cabecera);
		}
		if(rIP->getClavePrimaria() > clave){
			superior = centro - 1;
			continue;
		}
		if(rIP->getClavePrimaria() < clave){
			inferior = centro + 1;
			continue;
		}
	}
	archivo.close();
	return -1;
}
/**
 * Elimina un registro en el indice primario.
 */
void IndicesPS::borrarIP(string clave) {
	fstream archivo("IP.dat", ios::in | ios::out | ios::binary);
	RegistroIP rIP;
	Cabecera cabecera;
	vector<RegistroIP> registros;
	vector<RegistroIP>::iterator it;

	// Leemos la cabecera
	archivo.read((char*)&cabecera, sizeof(Cabecera));
	// Cargamos en memoria todos los registros excepto el registro que queremos eliminar.
	while (!archivo.eof()) {
		archivo.tellg();
		archivo.read((char*) (&rIP), sizeof(RegistroIP));
		archivo.tellg();
		if (archivo.eof()) break;
		if (rIP.getClavePrimaria() != clave) {
			registros.push_back(rIP);
		}
	}
	archivo.close();

	// Sobreescribimos el archivo con los datos que tenemos en memoria.
	archivo.open("IP.dat", ios::out | ios::binary);
	cabecera.setNEliminados(cabecera.getNEliminados()+1);
	cabecera.setNRegistros(cabecera.getNRegistros()-1);
	archivo.tellg();
	archivo.write((char*)&cabecera, sizeof(Cabecera));
	archivo.tellg();
	for (it = registros.begin(); it != registros.end(); it++) {
		archivo.tellg();
		archivo.write((char*)(&*it), sizeof(RegistroIP));
		archivo.tellg();
	}
	archivo.close();
}

/**
 * Busqueda Binaria en Indice Primario (IP.dat)
 * Devuelve la posicion del Registro en el fichero de datos o -1 sino esta.
 */
void IndicesPS::generarCabecera(fstream & archivo) {
	Cabecera cabecera(1,0,sizeof(Animal)+1,-1);	//se inicializa con nReg a uno porq se inserta justo despues
	archivo.tellg();
	archivo.write((char*)(&cabecera), sizeof(Cabecera));
	archivo.tellg();
}
/**
 * Devuelve true si el archivo esta vacio
 */
bool IndicesPS::comprobarArchivoVacio(fstream & archivo) {
	int tam = 0;
	streampos posActual = archivo.tellg();
	archivo.seekg(0, ios::end);	// Ponemos el puntero al final del archivo
	tam = archivo.tellg();
	archivo.seekg(posActual); // Volvemos a poner el puntero donde estaba
	return (tam == 0);
}
