/*
 * Indice.h
 *
 *  Created on: 11/05/2011
 *      Author: Sergio
 */

#ifndef INDICE_H_
#define INDICE_H_
#include "IndicesPS.h"
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <ctime>
#include "Animal.h"

using namespace std;


class Indice {
private:
	IndicesPS indicesPS;
public:
	Indice();
	virtual ~Indice();
	void crearFicherosPS();
	void insertar(Animal*);
	void eliminar(string clave);
	void buscarP(string);
	void mostrar(string);
	void lecturaOrdenada();
	void crearFicheroBloques();
    IndicesPS& getIndicesPS();
    void desordenar(list<Animal*>&);
};

#endif /* INDICE_H_ */
