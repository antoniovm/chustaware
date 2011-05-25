/*
 * Bloque.cpp
 *
 *  Created on: 25/05/2011
 *      Author: Miguel
 */

#include "Bloque.h"

Bloque::Bloque() {
	this->nRegistros = 0;
	this->valido = true;
	this->siguiente = -1;
}

Bloque::~Bloque() {

}

Registro* Bloque::getPrimerRegistro()
{
	if (nRegistros>0) {
		return &registros[0];
	}
    return NULL;
}

Registro* Bloque::getUltimoRegistro()
{
	if (nRegistros>0) {
		return &registros[nRegistros-1];
	}
    return NULL;
}

Bloque* Bloque::insertar(Registro registro)
{
	Bloque* bloque;
    if (nRegistros == 0) {
		registros[0] = registro;
		nRegistros++;
		return NULL;
	}
	if (nRegistros < 10) {
    	// Insercion ordenada
		for (int i = nRegistros-1; i >= 0; i--) {
			if (registros[i].getAnimal(false)->getName() < registro.getAnimal(false)->getName()) {
				registros[i] = registro;
				nRegistros++;
				return NULL;
			}
			registros[i+1] = registros[i];
		}
	}
    bloque = new Bloque();
    // Dividimos los registros en 2 bloques
    for (int i = nRegistros - 1; i >= 5; i--) {
		bloque->insertar(registros[i]);
		nRegistros--;
	}
    // Si la clave que queremos insertar es menor que la primera clave del bloque nuevo, insertamos en el antiguo
    if (registro.getAnimal(false)->getName() < bloque->getPrimerRegistro()->getAnimal(false)->getName()) {
    	registros[nRegistros++] = registro;
    	return bloque;
	}
    // Si no, insertamos en el nuevo
    bloque->insertar(registro);
    return bloque;
}

int Bloque::eliminar(string clave) {
	bool eliminado = false;

	for (int i = 0; i < nRegistros-1; i++) {
		if ((registros[i].getAnimal(false)->getName() == clave) && !eliminado) {
			eliminado = true;
		}
		if (eliminado) {
			registros[i] = registros[i+1];
		}
	}
	if (registros[nRegistros-1].getAnimal(false)->getName() == clave) {
		eliminado = true;
	}
	if (eliminado) {
		nRegistros--;
	}
	if (nRegistros == 0) return -1;
	if (eliminado) return 1;
	return 0;
}

bool Bloque::getValido() const
{
    return valido;
}

int Bloque::getSiguiente() const
{
    return siguiente;
}

void Bloque::setSiguiente(int siguiente)
{
    this->siguiente = siguiente;
}

void Bloque::setValido(bool valido)
{
    this->valido = valido;
}

void Bloque::mostrar() {
	for (int i = 0; i < nRegistros; i++) {
		cout << registros[i].getAnimal(false) << endl;
	}
	cout << endl;
}
