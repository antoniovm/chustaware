//============================================================================
// Name        : creaIBloques.cpp
// Author	   : Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
// Version     :
// Copyright   : OGA 2011
//============================================================================

#include <iostream>
#include "IndicesPS.h"
#include "EntradaSalida.hpp"
#include "Indice.h"

using namespace std;

void menu(Indice&);

int main() {
	Indice indice;
	//indice.crearFicherosPS();
	//indice.mostrar("IP.dat");
	//indice.mostrar("IS.dat");
	//indice.mostrar("IAux.dat");
	menu(indice);
	cout << "Fin de Main";
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

void menu(Indice &indice){
	char c;
	long l;
	string s;
	Animal* animal;
	cout << "**********************************************************************" << endl;
	cout << "*                         GRUPO 5. PRACTICA 2.                       *" << endl;
	cout << "*                 GESTOR DE FICHEROS POR INDEXACION                  *" << endl;
	cout << "**********************************************************************" << endl;
	do{
		cout << "---------------------------------MENU---------------------------------\n";
		cout <<	"t"; cout << " - Leer del archivo de texto y generar ficheros de datos e indices.\n";
		cout <<	"i"; cout << " - Insertar un Animal.\n";
		cout << "d"; cout << " - Eliminar un Animal.\n";
		cout << "k"; cout << " - Lectura ordenada por clave Primaria.\n";
		cout << "p"; cout << " - Buscar animal por clave Primaria.\n";
		cout << "s"; cout << " - Buscar animales por clave Secundaria.\n";
		cout << "m"; cout << " - Mostrar estado fichero de indice(Primario,Secundario o Auxiliar).\n";
		cout << "e"; cout << " - Exit." << endl;
		cin>>c;
		switch (c) {
			case 't':
				indice.crearFicherosPS();
				cout << "Ficheros creados correctamente "<< endl;
				break;
			case 'd':
				cout<<"Qué animal desea eliminar?"<<endl;
				ws(cin);
				getline(cin,s);
				indice.eliminar(s);
				break;
			case 'i':
				cout<< "Introduzca el nombre"<<endl;
				ws(cin);	//Limpia el buffer de teclado de espacios en blanco
				getline(cin,s);
				animal = new Animal(s, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
				indice.insertar(animal);
				if(animal)
					delete animal;
				break;
			case 'k':
				cout<< "Listado completo por clave primaria de zoo-data.dat"<<endl;
				indice.lecturaOrdenada();
				break;
			case 'm':
				cout<< "Introduzca el nombre del fichero a mostrar (IP.dat ,IS.dat ,IAux.dat)"<<endl;
				ws(cin);
				getline(cin,s);
				indice.mostrar(s);
				break;
			case 'p':
				cout<< "Introduzca una clave primaria (nombre de animal)"<<endl;
				ws(cin);
				getline(cin,s);
				indice.buscarP(s);
				break;
			case 's':
				cout<< "Introduzca una clave secundaria (nº de patas)"<<endl;
				ws(cin);
				cin>>l;
				indice.buscarS(l);
				//es.leerRegistro(es.buscar(s));
				break;

			default:	break;
		}
	}while(c!='e');
	cout<<"Saliendo..."<<endl;
}



