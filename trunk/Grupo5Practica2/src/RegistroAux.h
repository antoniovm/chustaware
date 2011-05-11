/*
 * RegistroAux.h
 *
 *  Created on: 11/05/2011
 *      Author: Sergio
 */

#ifndef REGISTROAUX_H_
#define REGISTROAUX_H_

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class RegistroAux {
private:
	bool valido;
	char clavePrimaria[50];
	int siguiente; //pila de huecos
	int posDatos; //posicion en el archivo de datos
public:
	RegistroAux();
	RegistroAux(bool, string, int, int);
	virtual ~RegistroAux();
    string getClavePrimaria() const;
    int getPosDatos() const;
    int getSiguiente() const;
    bool getValido() const;
    void setClavePrimaria(char*);
    void setPosDatos(int);
    void setSiguiente(int);
    void setValido(bool);

};

#endif /* REGISTROAUX_H_ */
