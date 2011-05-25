/*
 * Bloque.h
 *
 *  Created on: 25/05/2011
 *      Author: Miguel
 */

#ifndef BLOQUE_H_
#define BLOQUE_H_

#include "Registro.h"

using namespace std;

class Bloque {
private:
	Registro registros[10];
	int nRegistros;
public:
	Bloque();
	virtual ~Bloque();
	Registro* getPrimerRegistro();
    Registro* getUltimoRegistro();
    Bloque* insertar(Registro);
    int eliminar(string);
    void mostrar();
};

#endif /* BLOQUE_H_ */
