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

void IndicesPS::borrarIP(string clave)
{
}



void IndicesPS::buscarClaveS(int int1)
{
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



void IndicesPS::crearIP()
{
	ofstream salida;
	salida.open("IP.dat",ios::binary);
	salida.close();
}



void IndicesPS::insertarIP(string clave)
{
	fstream archivo("IP.dat", ios::in | ios::out | ios::binary | ios::ate);
	int posicion;
	RegistroIP* rIP = NULL;

	posicion = es.buscar(clave);
	if (posicion == -1) {
		return;
	}

	rIP = new RegistroIP(clave, posicion);

	if (archivo.tellg() == ios::beg) {
		archivo.write((char*)(rIP), sizeof(RegistroIP));
		delete rIP;
		archivo.close();
		return;
	}
	while(archivo.tellg() > ios::beg) {
		archivo.seekg(archivo.tellg()-(streampos)sizeof(RegistroIP));
		archivo.read((char*)(rIP), sizeof(RegistroIP));

		if (rIP->getClavePrimaria() < clave) {
			archivo.write((char*) (rIP), sizeof(RegistroIP));
			delete rIP;
			archivo.close();
			return;
		}
		archivo.write((char*) (rIP), sizeof(RegistroIP));
		archivo.seekg(archivo.tellg() - (streampos) sizeof(RegistroIP));
	}
	archivo.close();
}



long IndicesPS::buscarClaveP(string clave)
{
}



RegistroIP IndicesPS::leerIP()
{
}


