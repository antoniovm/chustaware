/*
 *  Cabecera.h
 *	Clase que representa la cabecera de un archivo binario
 *  Created on: 23/03/2011
 *  Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#ifndef CABECERA_H_
#define CABECERA_H_

#include "Registro.h"

using namespace std;

class Cabecera {
private:
	long nRegistros;
	long nEliminados;
	long tamRegistro;
	long primerHueco;
public:
	Cabecera();
	Cabecera(long,long,long,long);
	virtual ~Cabecera();
    long getNEliminados() const;
    long getPrimerHueco() const;
    long getNRegistros() const;
    long getTamRegistro() const;
    void setNEliminados(long  nEliminados);
    void setPrimerHueco(long  primerHueco);
    void setNRegistros(long  nRegistros);
    void setTamRegistro(long  tamRegistro);
};

#endif /* CABECERA_H_ */
