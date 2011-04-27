/*
 * RegistroIP.h
 *
 *  Created on: 27/04/2011
 *      Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#ifndef REGISTROIP_H_
#define REGISTROIP_H_

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class RegistroIP {
private:
	char clavePrimaria[50];
	int posRegistro;
	int siguiente;
public:
	RegistroIP();
	RegistroIP(string, int, int);
    virtual ~RegistroIP();
    char* getClavePrimaria() const;
    int getPosRegistro() const;
    int getSiguiente() const;
    void setClavePrimaria(char*);
    void setPosRegistro(int posRegistro);
    void setSiguiente(int siguiente);
};

#endif /* REGISTROIP_H_ */
