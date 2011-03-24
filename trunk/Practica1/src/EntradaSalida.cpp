/*
 * EntradaSalida.cpp
 *
 *  Created on: 16/03/2011
 *  Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#include "EntradaSalida.hpp"

EntradaSalida::EntradaSalida() {

}

EntradaSalida::~EntradaSalida() {

}

void EntradaSalida::generarCabecera(fstream & archivo) {
	Cabecera cabecera(0,0,sizeof(Animal)+1,-1);
	archivo.write((char*)(&cabecera), sizeof(Cabecera));
}

void EntradaSalida::leerTexto() {
	fstream archivo("zoo-data.txt", fstream::in);
	string buffer;	//Cadena temporal
	char* cadena;	//Puntero buffer
	Animal* animal;	//Objeto temporal
	while(!archivo.eof()){
		getline(archivo, buffer);
		if(archivo.eof())break;
		cadena = new char[buffer.size()];	//Reserva de memoria para un registro
		strcpy(cadena, buffer.data());
		animal = new Animal(strtok(cadena, ","), *strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","),	*strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","), *strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","),	atoi(strtok(NULL, ",")), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","), atoi(strtok(NULL, ",")));	//Construccion de un animal

		animals.push_back(animal);

		delete [] cadena;		//Borrado de buffer
	}
	archivo.close();
}

void EntradaSalida::leerBinario() {
	fstream archivo("zoo-data.dat", fstream::in | fstream::binary);
	Cabecera cabecera;
	Animal* animal;
	long tamano=sizeof(Animal)+sizeof(long)+sizeof(char);//Registro Animal+validez+direccion

	archivo.read((char*)&cabecera,sizeof(Cabecera));

	if(archivo.bad()){
		cout<< "No existe el archivo"<<endl;
		return;
	}

	if(archivo.eof()||(cabecera.getNRegistros()==0)){  // No hay ná que leer
		cout<< "Archivo vacio"<<endl;
		return;
	}


	while(!archivo.eof()){	//Bucle de lectura
		Registro* registro = new Registro();
		/*archivo.read(temp,tamano);
		if(temp[0]!=0){ //Validar registro
			animal=new Animal();
			memcpy((char*)animal,&temp[5],sizeof(Animal));	//Hacemos una copia de la memoria que nos interesa
			animals.push_back(animal);	//Añadimos animal
		}
		delete [] temp;*/


	}
	archivo.close();



}

void EntradaSalida::escribir() {
	fstream archivoEntrada("zoo-data.dat", fstream::in | fstream::binary);
	fstream archivoSalida("zoo-data.dat", fstream::out | fstream::binary | fstream::app);
	string buffer;
	long direccion;	//Variable temporal para la direccion del siguiente "hueco"
	char* cadena;
	Animal* animal;
	Cabecera cabecera;
	if(archivoEntrada.eof())	//Si el archivo esta vacio
		generarCabecera(archivoSalida);

	archivoEntrada.read((char*)(&cabecera), sizeof(Cabecera));


	//while (!archivoEntrada.eof()) {
		if(cabecera.getPrimerHueco()!=-1){	//Si no apunta a "NULL"
			archivoEntrada.seekp(cabecera.getPrimerHueco()+1);	//Posicionamos para leer la direccion del siguiente eliminado saltandonos el byte de validez
			archivoEntrada.read((char*)&direccion, sizeof(long));	//Leemos la direccion del siguiente hueco
			archivoEntrada.seekp(cabecera.getPrimerHueco()+sizeof(long)+1);	//Posicionamos para escribir un animal (saltando validez y direccion)
		}

		archivoSalida.write((char*)animal,sizeof(Animal));//Escribimos el animal
		cabecera.setPrimerHueco(direccion);	//Almacenamos en la cabecera el primer hueco
		// terminar
	//}
}

void EntradaSalida::mostrar() {
	list<Animal*>::iterator it;
	int i=1;
	for(it=animals.begin(); it!=animals.end(); it++, i++) {
		cout <<i<<"-"<< **it << endl;
	}
}




