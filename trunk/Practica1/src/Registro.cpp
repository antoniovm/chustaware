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

Registro::~Registro() {
	// TODO Auto-generated destructor stub
}
