/*
 * RegistroIS.cpp
 *
 *  Created on: 27/04/2011
 *      Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#include "RegistroIS.h"

RegistroIS::RegistroIS() {
	this->claveSecundaria = -1;
	this->posPrimero = -1;
}

RegistroIS::RegistroIS(int claveSec, int pos) {
	this->claveSecundaria = claveSec;
	this->posPrimero = pos;
}

int RegistroIS::getClaveSecundaria() const
{
    return claveSecundaria;
}

int RegistroIS::getPosPrimero() const
{
    return posPrimero;
}

void RegistroIS::setClaveSecundaria(int claveSecundaria)
{
    this->claveSecundaria = claveSecundaria;
}

void RegistroIS::setPosPrimero(int posPrimero)
{
    this->posPrimero = posPrimero;
}

RegistroIS::~RegistroIS() {
	// TODO Auto-generated destructor stub
}
