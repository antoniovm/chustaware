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
	menu(indice);
	cout << "Fin de Main";
	return 0;
}

void menu(Indice &indice){
	char c;
	string s;
	Animal* animal;
	cout << "**********************************************************************" << endl;
	cout << "*                         GRUPO 5. PRACTICA 2.                       *" << endl;
	cout << "*     GESTOR DE FICHEROS POR INDEXACION CON BLOQUES DE REGISTROS     *" << endl;
	cout << "**********************************************************************" << endl;
	do{
		cout << "---------------------------------MENU---------------------------------\n";
		cout <<	"t"; cout << " - Leer del archivo de texto y generar ficheros de datos e indices.\n";
		cout <<	"i"; cout << " - Insertar un Animal.\n";
		cout << "d"; cout << " - Eliminar un Animal.\n";
		cout << "k"; cout << " - Lectura ordenada por clave Primaria.\n";
		cout << "p"; cout << " - Buscar animal por clave Primaria.\n";
		cout << "m"; cout << " - Mostrar estado fichero de indice primario.\n";
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
				indice.mostrar("IP.dat");
				break;
			case 'p':
				cout<< "Introduzca una clave primaria (nombre de animal)"<<endl;
				ws(cin);
				getline(cin,s);
				indice.buscarP(s);
				break;

			default:	break;
		}
	}while(c!='e');
	cout<<"Saliendo..."<<endl;
}



