/*
 * Indice.h
 *
 *  Created on: 11/05/2011
 *      Author: Sergio
 */

#ifndef INDICE_H_
#define INDICE_H_
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
	IndicePS indicePS;
public:
	Indice();
	virtual ~Indice();
	void crearFicherosPS();
	void insertar(Animal);
	void eliminar(Animal);
	void buscarP(string);
	void buscarS(int);
	void mostrarIP();
	void mostrarIS();
	void crearFicheroBloques();
};

#endif /* INDICE_H_ */
