/*
 * Cabecera.cpp
 *
 *  Created on: 23/03/2011
 *      Author: Miguel
 */

#include "Cabecera.h"

Cabecera::Cabecera() {
	// TODO Auto-generated constructor stub

}

Cabecera::~Cabecera() {
	// TODO Auto-generated destructor stub
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
