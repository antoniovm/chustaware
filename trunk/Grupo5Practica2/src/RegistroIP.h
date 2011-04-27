/*
 * RegistroIP.h
 *
 *  Created on: 27/04/2011
 *      Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#ifndef REGISTROIP_H_
#define REGISTROIP_H_

class RegistroIP {
private:
	char clavePrimaria[50];
	int posRegistro;
public:
	RegistroIP();
	virtual ~RegistroIP();
};

#endif /* REGISTROIP_H_ */
