/*
 *  Registro.h
 *	Clase que representa un registro RLF (Validez(bool) + direccion(long) + Animal)
 *  Created on: 24/03/2011
 *      Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_

#include "Animal.h"

using namespace std;

class Registro {
private:
	bool valido;
	long direccion;
	Animal animal;
public:
	Registro();
	Registro(bool valido, long dir, Animal* animal);
	virtual ~Registro();
    Animal *getAnimal(bool) ;
    long getDireccion() const;
    bool getValido() const;
    void setAnimal(Animal *animal);
    void setDireccion(long  direccion);
    void setValido(bool valido);
    friend ofstream& operator<<(ofstream&, Registro);
    friend ifstream& operator>>(ifstream&, Registro);

};

#endif /* REGISTRO_H_ */
