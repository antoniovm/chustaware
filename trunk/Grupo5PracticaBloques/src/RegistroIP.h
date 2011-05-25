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
public:
	RegistroIP();
	RegistroIP(string, int);
    virtual ~RegistroIP();
    string getClavePrimaria() const;
    int getPosRegistro() const;
    void setClavePrimaria(string);
    void setPosRegistro(int);

};

#endif /* REGISTROIP_H_ */
