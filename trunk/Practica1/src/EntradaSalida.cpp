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
/**
 * Inicializa la cabecera del archivo
 */
void EntradaSalida::generarCabecera(fstream & archivo) {
	Cabecera cabecera(0,0,sizeof(Animal)+1,-1);
	archivo.write((char*)(&cabecera), sizeof(Cabecera));
}
/**
 * Devuelve true si el archivo esta vacio
 */
bool EntradaSalida::comprobarArchivoVacio(fstream & archivo) {
	int tam = 0;
	streampos posActual = archivo.tellg();
	archivo.seekg(0, ios::end);	// Ponemos el puntero al final del archivo
	tam = archivo.tellg();
	archivo.seekg(posActual); // Volvemos a poner el puntero donde estaba
	return (tam == 0);
}
/**
 * Elimina todos los animales de memoria.
 */
void EntradaSalida::vaciar() {
	list<Animal*>::iterator it;
	for(it=animals.begin(); it!=animals.end(); it++){
		delete (*it);
	}
	animals.clear();
}
/**
 * Lee el archivo de texto zoo-data.txt y lo almacena en memoria en una lista de Animales
 */
void EntradaSalida::leerTexto() {
	fstream archivo("zoo-data.txt", fstream::in);
	string buffer;	//Cadena temporal
	char* cadena;	//Puntero buffer
	Animal* animal;	//Objeto temporal
	while(!archivo.eof()){
		getline(archivo, buffer);
		if(archivo.eof())break;
		cadena = new char[buffer.size()];	//Reserva de memoria para un registro
		strcpy(cadena, buffer.data());		//string to char*
											//Construccion de un animal
		animal = new Animal(strtok(cadena, ","), *strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","),	*strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","), *strtok(NULL, ","), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","),	atoi(strtok(NULL, ",")), *strtok(NULL, ","),
				*strtok(NULL, ","), *strtok(NULL, ","), atoi(strtok(NULL, ",")));

		animals.push_back(animal);	//se añade a la lista de animales

		delete [] cadena;		//Borrado de buffer
	}
	archivo.close();
}
/**
 * Lee los RLFs del archivo binario zoo-data.dat y los almacena en memoria en una list<Animal>
 */
void EntradaSalida::leerBinario() {
	fstream archivo("zoo-data.dat", fstream::in | fstream::binary);
	Cabecera cabecera;
	Registro registro;



	if(!archivo.is_open()){
		cout << "No existe el archivo" << endl;
		return;
	}
	if(comprobarArchivoVacio(archivo)){	// Comprobamos si el tamaño del archivo es 0
		cout << "Archivo vacio" << endl;
		return;
	}
	archivo.read((char*)&cabecera,sizeof(Cabecera)); //Leemos cabecera
	if(cabecera.getNRegistros()==0) {
		cout << "No hay ningun registro en el archivo" << endl;
		return;
	}
	while(1){							//Bucle de lectura
		archivo.read((char*)&registro,sizeof(registro));
		if(archivo.eof())
			break;
		if(registro.getValido())		//Validar registro
			animals.push_back(registro.getAnimal());	//Añadimos animal
	}
	archivo.close();
}
/**
 * Lee un unico registro del archivo. El primer registro es el 0.
 */
void EntradaSalida::leerRegistro(int nRegistro) {
	fstream archivo("zoo-data.dat", fstream::in | fstream::binary);
	Cabecera cabecera;
	Registro registro;
	streampos posicion;


	if (!archivo.is_open()) {
		cout << "No existe el archivo" << endl;
		return;
	}
	if (comprobarArchivoVacio(archivo)) { // Comprobamos si el tamaño del archivo es 0
		cout << "Archivo vacio" << endl;
		return;
	}
	archivo.read((char*) &cabecera, sizeof(Cabecera)); //Leemos cabecera
	if (cabecera.getNRegistros() == 0) {
		cout << "No hay ningun registro en el archivo" << endl;
		return;
	}

	if (nRegistro >= cabecera.getNRegistros()) {	// Comprobamos que el registro indicado esta en el archivo
		cout << "El registro indicado no esta en el archivo" << endl;
		return;
	}

	posicion = sizeof(Cabecera)+(nRegistro*sizeof(Registro));	//Calculamos la posicion de lectura
	archivo.seekg(posicion);	//Colocamos el puntero en la posicion donde vamos a leer
	archivo.read((char*) &registro, sizeof(Registro)); //Leemos el registro

	//Comprobamos si el registro es valido
	if (registro.getValido()) {
		animals.push_back(registro.getAnimal());
	} else {
		cout << "El registro que se intenta leer no es valido" << endl;
	}
}

/**
 * Escribe(vacia) la lista de animales en RLFs en el archivo binario zoo-data.dat
 */
void EntradaSalida::escribir() {
	fstream archivoSalida("zoo-data.dat", fstream::out | fstream::binary );
	Cabecera cabecera;
	Registro registro;	//reg auxiliar
	long nRegistros = 0;

	generarCabecera(archivoSalida);	//escribe en archivo la cabecera por defecto
	while(!animals.empty()){
		registro.setAnimal(animals.front());	//asignamos a RLF un animal
		archivoSalida.write((char*) (&registro), sizeof(Registro));	//se escribe en archivo
		delete *animals.begin();	//liberamos memoria
		animals.pop_front();	//se saca el puntero de la lista
		nRegistros++;
	}
	cabecera.setNRegistros(nRegistros);	//actualiza nReg en cabecera
	archivoSalida.seekp(0, ios::beg);	//cursor al inicio
	archivoSalida.write((char*)(&cabecera), sizeof(Cabecera));	//se reescribe la cabecera
	archivoSalida.close();

}

/**
 * Muestra la lista de animales en memoria
 */
void EntradaSalida::mostrar() {
	list<Animal*>::iterator it;
	int i=1;
	if(animals.empty())
		cout << "No hay animales en memoria" << endl;
	for(it=animals.begin(); it!=animals.end(); it++, i++)
		cout <<i<<"-"<< **it << endl;
	cout << endl;
}
bool EntradaSalida::eliminar(long  pos)
{
	fstream entrada("zoo-data.dat",ios::in|ios::binary);
	fstream salida("zoo-data.dat",ios::out|ios::binary|ios::app);
	Registro registro;
	Cabecera cabecera;
	long posicionReg;
	entrada.read((char*)&cabecera,sizeof(Cabecera));

								//Comprobamos que la posicion es valida
	if(((cabecera.getNRegistros()+cabecera.getNEliminados()) < pos)||(pos < 0)){
		return false;
	}
	posicionReg=pos*sizeof(Registro)+sizeof(Cabecera);
	//Posicionamos tras de la cabecera, con offset nRegistros acceder al registro
	entrada.seekg(0,(std::_Ios_Seekdir)posicionReg);

	entrada.read((char*)&registro,sizeof(Registro));
	entrada.close();

	registro.setValido(false);	//Invalidamos el registro
	registro.setDireccion(cabecera.getPrimerHueco());	//Stack linked list
	cabecera.setPrimerHueco(posicionReg);	//Actualizacion de la cabecera

	salida.seekg(0,(std::_Ios_Seekdir)posicionReg);
	salida.write((char*)&registro,sizeof(Registro));

	salida.seekg(0,ios::beg);
	salida.write((char*)&cabecera,sizeof(Cabecera));

	salida.close();

	return true;


}


