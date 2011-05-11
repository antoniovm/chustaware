/*
 * RegistroAux.cpp
 *
 *  Created on: 11/05/2011
 *      Author: Sergio
 */

#include "RegistroAux.h"

RegistroAux::RegistroAux() {
	// TODO Auto-generated constructor stub

}

string RegistroAux::getClavePrimaria() const
{
	string cadena(clavePrimaria);
	return cadena;
}

int RegistroAux::getPosDatos() const
{
    return posDatos;
}

int RegistroAux::getSiguiente() const
{
    return siguiente;
}

bool RegistroAux::getValido() const
{
    return valido;
}

void RegistroAux::setClavePrimaria(char clavePrimaria[50])
{
    this->clavePrimaria = clavePrimaria;
}

void RegistroAux::setPosDatos(int posDatos)
{
    this->posDatos = posDatos;
}

void RegistroAux::setSiguiente(int siguiente)
{
    this->siguiente = siguiente;
}

void RegistroAux::setValido(bool valido)
{
    this->valido = valido;
}

RegistroAux::~RegistroAux() {
	// TODO Auto-generated destructor stub
}
