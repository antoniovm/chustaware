//============================================================================
// Name        : creaIndices.cpp
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
	int posDatos=0;
	int posAux=0;
	Animal* animal;
	do{
		cout<<"---¿Qué desea hacer?--- \n"
				"t - Leer del archivo de texto y generar ficheros de datos e indices.\n"
				"i - Insertar un Animal.\n"
				"d - Eliminar un Animal.\n"
				"k - Listado completo ordenado por clave Primaria.\n"
				"p - Buscar animal por clave Primaria.\n"
				"s - Buscar animales por clave Secundaria.\n"
				"m - Mostrar estado fichero de indice(Primario,Secundario o Auxiliar).\n"
				"e - Exit."<<endl;
		cin>>c;
		switch (c) {
			case 't':
				indice.crearFicherosPS();
				cout << "Ficheros creados correctamente "<< endl;
				break;
			case 'd':
				cout<<"Qué registro desea eliminar?"<<endl;
				ws(cin);
				getline(cin,s);
				//es.eliminar(es.buscar(s));break;
				break;
			case 'i':
				cout<< "Introduzca el nombre"<<endl;
				ws(cin);	//Limpia el buffer de teclado de espacios en blanco
				getline(cin,s);
				animal=new Animal(s,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
				posDatos=indice.getIndicesPS().insertarIP(animal);
				posAux=indice.getIndicesPS().insertarAux(animal,posDatos);
				indice.getIndicesPS().insertarIS(animal,posAux);
				break;
			case 'k':
				cout<< "Listado completo por clave primaria de zoo-data.dat"<<endl;
				//ws(cin);
				//getline(cin,s);
				//indice.mostrar(s);
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
				posAux=indice.getIndicesPS().buscarClaveP(s);
				if(posAux==-1){
					cout << "El animal no esta" << endl;
					break;
				}else{
					fstream archivoIP("IP.dat",ios::binary|ios::in);
					fstream archivoDatos("zoo-data.dat",ios::binary|ios::in);
					RegistroIP rIP;
					Registro rDatos;
					archivoIP.seekg(posAux);
					archivoIP.tellg();
					archivoIP.read((char*)(&rIP),sizeof(RegistroIP));//leemos el regIP
					archivoIP.close();
					posDatos=rIP.getPosRegistro();
					archivoDatos.tellg();
					archivoDatos.seekg(posDatos);
					archivoDatos.tellg();
					archivoDatos.read((char*)(&rDatos),sizeof(Registro));
					archivoDatos.tellg();
					cout << *rDatos.getAnimal(false) <<"\nPosicion en IP: "<< posAux <<"\nPosicion en Datos: "<< posDatos<< endl;
					archivoDatos.close();
				}
				break;
			case 's':
				cout<< "Introduzca una clave secundaria (nº de patas)"<<endl;
				ws(cin);
				cin>>l;
				//es.leerRegistro(es.buscar(s));
				break;

			default:	break;
		}
	}while(c!='e');
	cout<<"Saliendo..."<<endl;
}



