/*
 *  Cabecera.cpp
 *
 *  Created on: 23/03/2011
 *  Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#include "Cabecera.h"

Cabecera::Cabecera() {
	this->nRegistros = 0;
	this->nEliminados = 0;
	this->primerHueco = -1;
	this->tamRegistro = sizeof(Registro);
}

Cabecera::Cabecera(long  nReg, long  nElim, long  tamReg, long  primHueco)
{
	this->nRegistros=nReg;
	this->nEliminados=nElim;
	this->tamRegistro=tamReg;
	this->primerHueco=primHueco;
}

Cabecera::~Cabecera() {
}

long Cabecera::getNEliminados() const
{
    return nEliminados;
}

long Cabecera::getPrimerHueco() const
{
    return primerHueco;
}

long Cabecera::getNRegistros() const
{
    return nRegistros;
}

long Cabecera::getTamRegistro() const
{
    return tamRegistro;
}

void Cabecera::setNEliminados(long  nEliminados)
{
    this->nEliminados = nEliminados;
}

void Cabecera::setPrimerHueco(long  primerHueco)
{
    this->primerHueco = primerHueco;
}

void Cabecera::setNRegistros(long  nRegistros)
{
    this->nRegistros = nRegistros;
}

void Cabecera::setTamRegistro(long  tamRegistro)
{
    this->tamRegistro = tamRegistro;
}
ostream& operator <<(ostream & os, Cabecera cabecera) {
	os << "Numero de Registros: " << cabecera.getNRegistros() << endl;
	os << "Numero de Eliminados: " << cabecera.getNEliminados()<< endl;
	os << "Primer Hueco: " << cabecera.getPrimerHueco() << endl;
	os << "Tamaño del Registro: " << cabecera.getTamRegistro() << endl;
	return os;

}
