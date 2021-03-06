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
#include "RegistroIS.h"
#include "RegistroAux.h"
#include "Animal.h"
#include <fstream>
#include<vector>
#include<list>

class IndicesPS {
private:
	EntradaSalida es;
public:
	IndicesPS();
	virtual ~IndicesPS();
	int insertarIP(Animal*);
	void borrarIP(string);
	void insertarIS(Animal*, int);
	void borrarIS(string, int);
	int insertarAux(Animal*, int);
	long buscarClaveP(string);
	int buscarClaveS(int);
	EntradaSalida& getES(){return es;}
	void generarCabecera(fstream&);
	bool comprobarArchivoVacio(fstream&);
};

#endif /* INDICESPS_H_ */
