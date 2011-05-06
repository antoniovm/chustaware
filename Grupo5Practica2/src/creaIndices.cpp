//============================================================================
// Name        : creaIndices.cpp
// Author	   : Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
// Version     :
// Copyright   : OGA 2011
//============================================================================

#include <iostream>
#include "IndicesPS.h"
#include "EntradaSalida.hpp"

using namespace std;

void menu(EntradaSalida&);

int main() {
	IndicesPS indices;
	menu(indices.getES());

	return 0;
}
/*
 * TAREAS A REALIZAR:
 *crear fichero con indiceP
 CREAR fichero con indiceS
 Visualizacion de archivos de indices
 Listado ordenado por claveP
 Busqueda por claveP
 Busqueda por claveS
 Eliminar en datos e indices
 Insertar en datos e indices
 Crear archivo de bloques, con registros ordenados
 */

void menu(EntradaSalida &es){
	char c;
	long l;
	string s;
	do{
		cout<<"---¿Qué desea hacer?--- \n"
				"b-Leer del archivo binario.\n"
				"t-Leer del archivo de texto.\n"
				"e-Escribir todo en fichero.\n"
				"d-Eliminar un registro.\n"
				"i-Insertar un registro.\n"
				"v-Vaciar memoria.\n"
				"l-Leer un solo registro.\n"
				"m-Mostrar todo.\n"
				"f-Buscar por nombre.\n"
				"r-Restaurar Archivo.\n"
				"s-Salir."<<endl;
		cin>>c;
		switch (c) {
			case 'b':
				es.vaciar();	//Limipamos memoria principal para sincronizar con el fichero binario
				es.leerBinario();break;
			case 't':	es.leerTexto();break;
			case 'e':	es.escribir();break;
			case 'd':
				cout<<"Qué registro desea eliminar?"<<endl;
				ws(cin);
				getline(cin,s);
				es.eliminar(es.buscar(s));break;
			case 'i':
				cout<< "Introduzca el nombre"<<endl;
				ws(cin);	//Limpia el buffer de teclado de espacios en blanco
				getline(cin,s);
				es.insertar(new Animal(s,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1));break;
			case 'm':	es.mostrar();break;
			case 'v':	es.vaciar();break;
			case 'r':	restaurarArchivo(es);break;
			case 'f':
				cout<< "Introduzca el nombre"<<endl;
				ws(cin);
				getline(cin,s);
				es.leerRegistro(es.buscar(s));break;
			case 'l':
				cout<<"Qué registro desea leer?"<<endl;
				cin>>l;
				es.leerRegistro(l);break;
			default:	break;
		}
	}while(c!='s');
	cout<<"Saliendo..."<<endl;
}
