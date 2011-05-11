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
	vaciar();
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
		archivo.close();
		return;
	}
	archivo.read((char*)&cabecera,sizeof(Cabecera)); //Leemos cabecera
	if(cabecera.getNRegistros()==0) {
		cout << "No hay ningun registro en el archivo" << endl;
		archivo.close();
		return;
	}
	while(1){							//Bucle de lectura
		archivo.read((char*)&registro,sizeof(registro));
		if(archivo.eof())
			break;
		if(registro.getValido())		//Validar registro
			animals.push_back(registro.getAnimal(true));	//Añadimos animal
	}
	archivo.close();
}
/**
 * Lee un unico registro del archivo. El primer registro es el 0.
 */
streampos EntradaSalida::leerRegistro(int nRegistro) {
	fstream archivo("zoo-data.dat", fstream::in | fstream::binary);
	Cabecera cabecera;
	Registro registro;
	streampos posicion;


	if (!archivo.is_open()) {
		cout << "No existe el archivo" << endl;
		return -1;
	}
	if (comprobarArchivoVacio(archivo)) { // Comprobamos si el tamaño del archivo es 0
		cout << "Archivo vacio" << endl;
		archivo.close();
		return -1;
	}
	archivo.read((char*) &cabecera, sizeof(Cabecera)); //Leemos cabecera
	if (cabecera.getNRegistros() == 0) {
		cout << "No hay ningun registro en el archivo" << endl;
		archivo.close();
		return -1;
	}
	// Comprobamos que el registro indicado esta en el archivo
	if ((nRegistro<0)||(nRegistro >= (cabecera.getNRegistros()+cabecera.getNEliminados()))) {
		cout << "El registro indicado no esta en el archivo" << endl;
		archivo.close();
		return -1;
	}

	posicion = sizeof(Cabecera)+(nRegistro*sizeof(Registro));	//Calculamos la posicion de lectura
	archivo.seekg(posicion);	//Colocamos el puntero en la posicion donde vamos a leer
	archivo.read((char*) &registro, sizeof(Registro)); //Leemos el registro

	//Comprobamos si el registro es valido
	if (registro.getValido()) {
		cout<<*registro.getAnimal(false)<<endl;
		//animals.push_back(registro.getAnimal(true));
	} else {
		cout << "El registro que se intenta leer no es valido" << endl;
		return -1;
	}
	archivo.close();
	return posicion;
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
/**
 * Inserta un animal en el primer hueco del archivo.
 */
int EntradaSalida::insertar(Animal* animal){
	fstream archivoEntrada("zoo-data.dat", fstream::in | fstream::binary);
	fstream archivoSalida("zoo-data.dat", fstream::out|fstream::in | fstream::binary);
	Cabecera cabecera;
	Registro registro;
	streampos posicion;

	if (!archivoEntrada.is_open()) {
		cout << "No existe el archivo" << endl;
		return;
	}


	if (comprobarArchivoVacio(archivoEntrada)) { // Comprobamos si el tamaño del archivo es 0
		archivoEntrada.close();
		generarCabecera(archivoSalida);
		archivoSalida.write((char*)(&registro), sizeof(Registro));
		archivoSalida.close();
		return;
	}
	archivoEntrada.read((char*) &cabecera, sizeof(Cabecera)); //Leemos cabecera


	if (cabecera.getPrimerHueco() == -1) {	//No hay huecos, insercion al final
		registro.setAnimal(animal);
		archivoSalida.seekp(0, ios::end);
		archivoSalida.write((char*)(&registro), sizeof(Registro));
		cabecera.setNRegistros(cabecera.getNRegistros()+1);
		archivoSalida.seekp(0,ios::beg);
		archivoSalida.write((char*)&cabecera,sizeof(Cabecera));	//Actualizacion de la cabecera
		archivoSalida.close();
		return;
	}

	posicion = cabecera.getPrimerHueco();	//Posicion de insercion

	archivoEntrada.seekg(posicion);
	archivoEntrada.read((char*)&registro,sizeof(Registro));
	archivoEntrada.close();

	registro.setAnimal(animal);
	registro.setValido(true);
	delete animal; //Liberar memoria dinamica



	archivoSalida.seekp(posicion);
	archivoSalida.write((char*)(&registro), sizeof(Registro));	//Insercion del nuevo registro


	cabecera.setNEliminados(cabecera.getNEliminados()-1);	//Modificar cabecera
	cabecera.setNRegistros(cabecera.getNRegistros()+1);
	cabecera.setPrimerHueco(registro.getDireccion());
	archivoSalida.seekp(0,ios::beg);
	archivoSalida.write((char*)&cabecera,sizeof(Cabecera));	//Actualizacion de la cabecera

	archivoSalida.close();

	return (int)posicion;
}
bool EntradaSalida::eliminar(long  pos)
{
	fstream entrada("zoo-data.dat",ios::in|ios::binary);
	fstream salida("zoo-data.dat",ios::in|ios::out|ios::binary);

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
	entrada.seekg(posicionReg);

	entrada.read((char*)&registro,sizeof(Registro));


	if(registro.getValido()){	//Si no esta elimindo
		registro.setValido(false);	//Invalidamos el registro
		registro.setDireccion(cabecera.getPrimerHueco());	//Stack linked list
		cabecera.setPrimerHueco(posicionReg);	//Actualizacion de la cabecera
		cabecera.setNEliminados(cabecera.getNEliminados()+1);
		cabecera.setNRegistros(cabecera.getNRegistros()-1);

		salida.seekp(posicionReg);
		salida.write((char*)&registro,sizeof(Registro));


		salida.seekp(0,ios::beg);
		salida.write((char*)&cabecera,sizeof(Cabecera));


	}
	entrada.close();
	salida.close();

	return true;


}

long EntradaSalida::buscar(string  s)
{
	fstream entrada("zoo-data.dat",ios::in|ios::binary);
	Registro registro;
	entrada.seekg(sizeof(Cabecera));
	while(true){
		entrada.read((char*)&registro,sizeof(Registro));
		if(entrada.eof())
			return -1;
		if(registro.getValido())
			if(strcmp(s.data(),registro.getAnimal(false)->getName())==0)
				return ((long)entrada.tellg()-sizeof(Registro)-sizeof(Cabecera))/sizeof(Registro);
	}

}






