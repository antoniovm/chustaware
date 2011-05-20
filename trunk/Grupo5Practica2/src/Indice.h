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
#include "Animal.h"

using namespace std;

/*
 * TAREAS A REALIZAR:
 *crear fichero con indiceP
 CREAR fichero con indiceS
 Visualizacion de archivos de indices
 Listado ordenado por claveP
 Busqueda por claveP
 Busqueda por claveS
 Eliminar en datos e indices
 Insertar en datos e indices
 Crear archivo de bloques, con registros ordenados
 */
class Indice {
private:
	IndicesPS indicesPS;
public:
	Indice();
	virtual ~Indice();
	void crearFicherosPS();
	void insertar(Animal);
	void eliminar(string clave);
	void buscarP(string);
	void buscarS(int);
	void mostrar(string);
	void crearFicheroBloques();
};

#endif /* INDICE_H_ */
