/*
 * RegistroAux.h
 *
 *  Created on: 11/05/2011
 *      Author: Sergio
 */

#ifndef REGISTROAUX_H_
#define REGISTROAUX_H_

using namespace std;

class RegistroAux {
private:
	bool valido;
	char clavePrimaria[50];
	int siguiente; //pila de huecos
	int posDatos; //posicion en el archivo de datos
public:
	RegistroAux();
	virtual ~RegistroAux();
    string getClavePrimaria() const;
    int getPosDatos() const;
    int getSiguiente() const;
    bool getValido() const;
    void setClavePrimaria(char clavePrimaria[50]);
    void setPosDatos(int posDatos);
    void setSiguiente(int siguiente);
    void setValido(bool valido);

};

#endif /* REGISTROAUX_H_ */
