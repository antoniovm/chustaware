/*
 * RegistroIS.h
 *
 *  Created on: 27/04/2011
 *      Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#ifndef REGISTROIS_H_
#define REGISTROIS_H_

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class RegistroIS {
private:
	int claveSecundaria;
	int posPrimero;
public:
	RegistroIS();
	RegistroIS(int, int);
	virtual ~RegistroIS();
    int getClaveSecundaria() const;
    int getPosPrimero() const;
    void setClaveSecundaria(int claveSecundaria);
    void setPosPrimero(int posPrimero);
};

#endif /* REGISTROIS_H_ */
