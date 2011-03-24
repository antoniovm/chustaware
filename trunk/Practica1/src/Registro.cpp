/*
 * Registro.cpp
 *
 *  Created on: 24/03/2011
 *      Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#include "Registro.h"

Registro::Registro() {
	this->valido = true;
	this->direccion = 0;
}

Registro::Registro(bool valido, long  dir, Animal* animal) {
	this->valido = valido;
	this->direccion = dir;
	memcpy(&(this->animal), animal, sizeof(Animal));
}

Animal *Registro::getAnimal() const
{
	// Devolvemos una copia dinamica del animal.
	Animal* a = new Animal();
	memcpy(a, &animal, sizeof(Animal));
    return a;
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
	memcpy(&(this->animal), animal, sizeof(Animal));
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
