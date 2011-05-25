/*
 * IndicesPS.h
 *
 *  Created on: 27/04/2011
 *      Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#ifndef INDICESPS_H_
#define INDICESPS_H_

#include "EntradaSalida.hpp"
#include "RegistroIP.h"
#include "Bloque.h"
#include "Animal.h"
#include <fstream>
#include <vector>
#include <list>

class IndicesPS {
private:
	EntradaSalida es;
public:
	IndicesPS();
	virtual ~IndicesPS();
	void insertarDatos(Animal*);
	void insertarIP(fstream&, RegistroIP*);
	int insertarIP(Animal*);
	void borrarIP(string);
	long buscarClaveP(string);
	void generarCabecera(fstream&, int);
	bool comprobarArchivoVacio(fstream&);
	EntradaSalida& getES() {return es;};
};

#endif /* INDICESPS_H_ */
