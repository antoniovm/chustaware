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
	void crearIP(fstream,Animal*);
	void crearIS();
	RegistroIP leerIP();
	//escribir();
	void insertarIP(fstream,Animal*);
	void borrarIP(string);
	void insertarIS(Registro, int);
	void borrarIS(int);
	long buscarClaveP(string);
	long buscarClaveS(int);
	EntradaSalida& getES(){return es;}
};

#endif /* INDICESPS_H_ */