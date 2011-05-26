/*
 * Bloque.h
 *
 *  Created on: 25/05/2011
 *      Author: Miguel
 */

#ifndef BLOQUE_H_
#define BLOQUE_H_

#include "Registro.h"
#include "Animal.h"

using namespace std;

class Bloque {
private:
	Registro registros[10];
	int nRegistros;
	bool valido;
	int siguiente;
public:
	Bloque();
	virtual ~Bloque();
	Registro* getPrimerRegistro();
    Registro* getUltimoRegistro();
    Bloque* insertar(Registro);
    int eliminar(string);
    Animal* buscar(string);
    void mostrar();
    bool getValido() const;
    void setValido(bool valido);
    int getSiguiente() const;
    void setSiguiente(int siguiente);

};

#endif /* BLOQUE_H_ */
