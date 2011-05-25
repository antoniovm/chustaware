/*
 * RegistroIP.cpp
 *  Created on: 27/04/2011
 *      Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#include "RegistroIP.h"

RegistroIP::RegistroIP() {
	strcpy(this->clavePrimaria, "");
	this->posRegistro = -1;
}

RegistroIP::RegistroIP(string clavePri, int posicion) {
	strcpy(this->clavePrimaria, clavePri.data());
	this->posRegistro = posicion;
}

RegistroIP::~RegistroIP() {
}

string RegistroIP::getClavePrimaria() const
{
	string cadena(clavePrimaria);
	return cadena;
}

int RegistroIP::getPosRegistro() const
{
    return posRegistro;
}

void RegistroIP::setClavePrimaria(string clave)
{
	strcpy(this->clavePrimaria, clave.data());
}

void RegistroIP::setPosRegistro(int posRegistro)
{
    this->posRegistro = posRegistro;
}
