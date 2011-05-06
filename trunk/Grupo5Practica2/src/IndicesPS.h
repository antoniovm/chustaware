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
#include <fstream>
#include<vector>

class IndicesPS {
private:
	EntradaSalida es;
public:
	IndicesPS();
	virtual ~IndicesPS();
	void crearIP();
	void crearIS();
	RegistroIP leerIP();
	//escribir();
	void insertarIP(string);
	void borrarIP(string);
	void insertarIS(int);
	void borrarIS(int);
	long buscarClaveP(string);
	void buscarClaveS(int);
	EntradaSalida& getES(){return es;}
};

#endif /* INDICESPS_H_ */
