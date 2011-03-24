/*
 * Registro.cpp
 *
 *  Created on: 24/03/2011
 *      Author: Miguel
 */

#include "Registro.h"

Registro::Registro() {
	// TODO Auto-generated constructor stub

}

Registro::Registro(bool valido, long  dir, Animal *animal) {
	this->valido = valido;
	this->direccion = dir;
	this->animal = animal;
}

Animal *Registro::getAnimal() const
{
    return animal;
}

long Registro::getDireccion() const
{
    return direccion;
}

bool Registro::getValido() const
{
    return valido;
}

void Registro::setAnimal(Animal *animal)
{
    this->animal = animal;
}

void Registro::setDireccion(long  direccion)
{
    this->direccion = direccion;
}

void Registro::setValido(bool valido)
{
    this->valido = valido;
}

Registro::~Registro() {
	// TODO Auto-generated destructor stub
}
