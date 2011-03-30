//============================================================================
// Name        : Practica1.cpp
// Author      : Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
// Version     :
// Copyright   : OGA 2011
//============================================================================

#include <iostream>
#include "EntradaSalida.hpp"

using namespace std;
void menu(EntradaSalida&);

int main() {
	EntradaSalida es;
	menu(es);

	return 0;
}

void menu(EntradaSalida &es){
	char c;
	do{
		cout<<"---�Qu� desea hacer?--- \nb-Leer del archivo binario.\nt-Leer del archivo de texto.\ne-Escribir todo en fichero.\nd-Eliminar un registro.\ni-Insertar un registro.\nv-Vaciar memoria.\nl-Leer un solo registro.\nm-Mostrar todo.\ns-Salir."<<endl;
		cin>>c;
		switch (c) {
			case 'b':	es.leerBinario();break;
			case 't':	es.leerTexto();break;
			case 'e':	es.escribir();break;
			case 'd':	es.eliminar(0);break;	//Pedir por teclado el registro
			case 'i':	break;
			case 'm':	es.mostrar();break;
			case 'v':	es.vaciar();break;
			case 'l':	es.leerRegistro(0);break;	//Idem
			default:	break;
		}
	}while(c!='s');
}
