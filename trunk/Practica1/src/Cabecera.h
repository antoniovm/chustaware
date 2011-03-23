/*
 * Cabecera.h
 *
 *  Created on: 23/03/2011
 *      Author: Miguel
 */

#ifndef CABECERA_H_
#define CABECERA_H_

using namespace std;

class Cabecera {
private:
	long nRegistros;
	long nEliminados;
	long tamRegistro;
	long primerHueco;
public:
	Cabecera();
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
