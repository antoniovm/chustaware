/*
 * RegistroIP.cpp
 *  Created on: 27/04/2011
 *      Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#include "RegistroIP.h"

RegistroIP::RegistroIP() {
	strcpy(this->clavePrimaria, "");
	this->posRegistro = -1;
	this->siguiente = -1;
}

RegistroIP::RegistroIP(string clavePri, int posicion, int siguiente) {
	strcpy(this->clavePrimaria, clavePri.data());
	this->posRegistro = posicion;
	this->siguiente = siguiente;
}

RegistroIP::~RegistroIP() {
}

char* RegistroIP::getClavePrimaria() const
{
	char* cadena;
	cadena = new char[50];
	strcpy(cadena, clavePrimaria);
	return cadena;
}

int RegistroIP::getPosRegistro() const
{
    return posRegistro;
}

int RegistroIP::getSiguiente() const
{
    return siguiente;
}

void RegistroIP::setClavePrimaria(char* clave)
{
	strcpy(this->clavePrimaria, clave);
}

void RegistroIP::setPosRegistro(int posRegistro)
{
    this->posRegistro = posRegistro;
}

void RegistroIP::setSiguiente(int siguiente)
{
    this->siguiente = siguiente;
}
