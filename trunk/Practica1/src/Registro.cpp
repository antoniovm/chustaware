/*
 *  Registro.cpp
 *  Clase que representa un registro RLF (Validez(bool) + direccion(long) + Animal)
 *  Created on: 24/03/2011
 *      Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#include "Registro.h"
/**
 * Construye un registro valido con direccion 0
 */
Registro::Registro() {
	this->valido = true;
	this->direccion = 0;
}
/**
 * Construye un RLF(validez,direccion,Animal)
 */
Registro::Registro(bool valido, long  dir, Animal* animal) {
	this->valido = valido;
	this->direccion = dir;
	memcpy(&(this->animal), animal, sizeof(Animal));
}
Registro::~Registro() {
}
/**
 * Devuelve una copia dinamica del Animal
 */
Animal* Registro::getAnimal() const
{
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


