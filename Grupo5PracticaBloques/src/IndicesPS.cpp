/*
 * IndicesPS.cpp
 *
 *  Created on: 27/04/2011
 *      Author: Miguel Vicente Linares, Antonio Vicente Martin y Sergio Revueltas Estrada
 */

#include "IndicesPS.h"

IndicesPS::IndicesPS() {
	// TODO Auto-generated constructor stub

}

IndicesPS::~IndicesPS() {
	// TODO Auto-generated destructor stub
}

void IndicesPS::insertarDatos(Animal* animal) {
	fstream archivoIP("IP.dat", fstream::in | fstream::out | fstream::binary);
	fstream archivoDatos("zoo-data.dat", fstream::in | fstream::out | fstream::binary);
	Cabecera cabeceraDatos, cabeceraIP;
	Registro registro;
	RegistroIP rIP;
	Bloque bloque;
	Bloque* bloqueAux = NULL;
	streampos posicion, posicionClaveP;

	if (!archivoDatos.is_open()) {
		cout << "No existe el archivo zoo-data.dat" << endl;
		return;
	}
	if (!archivoIP.is_open()) {
		cout << "No existe el archivo IP.dat" << endl;
		return;
	}

	// Insertamos el animal en el registro de datos
	registro.setAnimal(animal);
	// Comprobamos si en el archivo no hay absolutamente nada
	if (comprobarArchivoVacio(archivoDatos)) {
		generarCabecera(archivoDatos, 0);
		generarCabecera(archivoIP, 1);
		bloque.insertar(registro); // Insertamos el registro en un bloque vacio
		posicion=archivoDatos.tellg(); // Posicion de escritura
		archivoDatos.write((char*) (&bloque), sizeof(Bloque)); // Escribimos el bloque
		archivoDatos.tellg();
		// Inicializamos el registro del IP y lo escibimos
		rIP.setClavePrimaria(bloque.getUltimoRegistro()->getAnimal(false)->getName());
		rIP.setPosRegistro(posicion);
		archivoIP.tellg();
		archivoIP.write((char*)&rIP, sizeof(RegistroIP)); // Escribimos el registro
		archivoIP.tellg();
		// No tocamos las cabeceras porque ya se inicializan con nRegistros=1
		// Cerramos ambos flujos
		archivoDatos.close();
		archivoIP.close();
		return;
	}
	// Si en el archivo ya hay datos...

	// Leemos las cabeceras
	archivoDatos.read((char*) &cabeceraDatos, sizeof(Cabecera));
	archivoIP.read((char*) &cabeceraIP, sizeof(Cabecera));

	posicionClaveP = buscarClaveP(animal->getName()); //Buscamos en IP la posicion del registro que contiene el bloque en el que tenemos que insertar
	archivoIP.seekg(posicionClaveP);
	archivoIP.read((char*)&rIP, sizeof(RegistroIP)); // Leemos el registro
	archivoDatos.seekg((streampos)rIP.getPosRegistro()); // Situamos el puntero del archivo de datos para leer el bloque en el que tenemos que insertar
	archivoDatos.read((char*)&bloque, sizeof(Bloque)); // Leemos el bloque
	bloqueAux = bloque.insertar(registro); // Insertamos el registro en el bloque
	archivoDatos.seekg(archivoDatos.tellg()-(streampos)sizeof(Bloque));
	posicion = archivoDatos.tellg(); //Posicion de escritura
	archivoDatos.write((char*)&bloque, sizeof(Bloque)); // Sobreescribimos el bloque
	archivoDatos.tellg();
	// Actualizamos el registro del IP
	rIP.setClavePrimaria(bloque.getUltimoRegistro()->getAnimal(false)->getName());
	rIP.setPosRegistro(posicion);
	archivoIP.seekg(posicionClaveP);
	archivoIP.tellg();
	archivoIP.write((char*)&rIP, sizeof(RegistroIP));
	archivoIP.tellg();
	// Si no se ha creado un bloque auxiliar hemos terminado la insercion
	if (!bloqueAux) {
		archivoDatos.close();
		archivoIP.close();
		return;
	}
	// Si se ha creado un bloque auxiliar lo insertamos en el archivo de datos y creamos la entrada correspondiente en el indice
	if (cabeceraDatos.getPrimerHueco() == -1) { //No hay huecos, insercion al final
		archivoDatos.seekp(0, ios::end);
		posicion = archivoDatos.tellg();
		archivoDatos.tellg();
		archivoDatos.write((char*)bloqueAux, sizeof(Bloque)); // Escribimos el registro al final
		archivoDatos.tellg();
		cabeceraDatos.setNRegistros(cabeceraDatos.getNRegistros() + 1); // Actualizamos la cabecera
		archivoDatos.seekp(0, ios::beg);
		archivoDatos.tellg();
		archivoDatos.write((char*) &cabeceraDatos, sizeof(Cabecera)); // Sobreescribimos la cabecera
		archivoDatos.tellg();
		// Inicializamos el registro del IP y lo escibimos
		rIP.setClavePrimaria(bloqueAux->getUltimoRegistro()->getAnimal(false)->getName());
		rIP.setPosRegistro(posicion);
		insertarIP(archivoIP, rIP);
		// Cerramos los flujos
		archivoDatos.close();
		archivoIP.close();
		// Liberamos memoria
		delete bloqueAux;
		bloqueAux = NULL;
		return;
	}
	// Si hay huecos insertamos en el primer hueco
	posicion = cabeceraDatos.getPrimerHueco(); //Posicion de insercion
	archivoDatos.seekg(posicion);
	archivoDatos.read((char*)&bloque, sizeof(Bloque)); //leemos para saber la direccion del siguiente hueco
	archivoDatos.seekp(posicion);
	archivoDatos.tellg();
	archivoDatos.write((char*) bloqueAux, sizeof(Bloque)); //Insercion del nuevo bloque en el hueco
	archivoDatos.tellg();
	// Actualizamos la cabecera
	cabeceraDatos.setNEliminados(cabeceraDatos.getNEliminados() - 1);
	cabeceraDatos.setNRegistros(cabeceraDatos.getNRegistros() + 1);
	cabeceraDatos.setPrimerHueco(bloque.getSiguiente()); // Direccion que tenia el registro eliminado
	archivoDatos.seekp(0, ios::beg);
	archivoDatos.tellg();
	archivoDatos.write((char*) &cabeceraDatos, sizeof(Cabecera)); // Sobreescribimos la cabecera
	archivoDatos.tellg();
	// Inicializamos el registro del IP y lo escibimos
	rIP.setClavePrimaria(bloqueAux->getUltimoRegistro()->getAnimal(false)->getName());
	rIP.setPosRegistro(posicion);
	insertarIP(archivoIP, rIP);
	// Cerramos los flujos
	archivoDatos.close();
	archivoIP.close();
	// Liberamos memoria
	delete bloqueAux;
	bloqueAux = NULL;
	return;
}
/*
 * Insercion ordenada de un RegistroIP en el indice.
 */
void IndicesPS::insertarIP(fstream& archivoIP, RegistroIP rIPInsertar) {
	Cabecera cabeceraIP;
	RegistroIP rIP;

	// Leemos la cabecera
	archivoIP.seekg(0, ios::beg);
	archivoIP.read((char*)&cabeceraIP, sizeof(Cabecera));

	archivoIP.seekg(sizeof(Cabecera)+(int)cabeceraIP.getNRegistros()*sizeof(RegistroIP));//ios::end

	while (archivoIP.tellg() > sizeof(Cabecera)) {
		archivoIP.seekg(archivoIP.tellg() - (streampos) sizeof(RegistroIP)); // Posicionamos el puntero en la posicion del registro anterior.
		archivoIP.tellg();
		archivoIP.read((char*)&rIP, sizeof(RegistroIP)); // Leemos el registro.
		archivoIP.tellg();
		// Si la clave del registro que vamos a insertar es mayor que la clave del registro que acabamos de leer, insertamos el registro.
		if (rIPInsertar.getClavePrimaria() > rIP.getClavePrimaria()) {
			archivoIP.tellg();
			archivoIP.write((char*) &rIPInsertar, sizeof(RegistroIP));
			archivoIP.tellg();
			//Actualizamos la cabecera
			cabeceraIP.setNRegistros(cabeceraIP.getNRegistros() + 1);
			archivoIP.seekg(0, ios::beg);
			archivoIP.tellg();
			archivoIP.write((char*) (&cabeceraIP), sizeof(Cabecera));
			archivoIP.tellg();
			return;
		}
		// Si no, copiamos el registro en la siguiente posicion y posicionamos el puntero en la posicion anterior.
		archivoIP.tellg();
		archivoIP.write((char*)&rIP, sizeof(RegistroIP));
		archivoIP.tellg();
		archivoIP.seekg(archivoIP.tellg() - (streampos) (sizeof(RegistroIP) * 2));
		archivoIP.tellg();
	}
	archivoIP.tellg();
	archivoIP.write((char*) &rIPInsertar, sizeof(RegistroIP));
	archivoIP.tellg();
	// Actualizamos la cabecera
	cabeceraIP.setNRegistros(cabeceraIP.getNRegistros() + 1);
	archivoIP.seekg(0, ios::beg);
	archivoIP.tellg();
	archivoIP.write((char*) (&cabeceraIP), sizeof(Cabecera));
	archivoIP.tellg();
	return;
}

/**
 * Busqueda Binaria.Devuelve la posicion del regIP en el ficheroIP o -1 si no esta
 */
long IndicesPS::buscarClaveP(string clave)
{
	fstream archivo("IP.dat", ios::in | ios::out | ios::binary);
	Cabecera cabecera;
	archivo.read((char*)(&cabecera),sizeof(Cabecera));
	archivo.seekg(0,ios::end);
	archivo.tellg();

	//inf,sup y centro indican el numRegistro no la posicion
	int inferior=0;
	int superior=((archivo.tellg()-(streampos)sizeof(Cabecera))-(streampos)sizeof(RegistroIP))/(streampos)sizeof(RegistroIP);
	int centro=0;
	RegistroIP* rIP = new RegistroIP("",0);

	if (superior == 0) {
		return sizeof(Cabecera);
	}
	while(inferior <= superior){
		centro=((superior-inferior)/2)+inferior;
		archivo.seekg(centro*sizeof(RegistroIP)+sizeof(Cabecera));
		archivo.tellg();
		archivo.read((char*)(rIP), sizeof(RegistroIP));
		archivo.tellg();

		if(rIP->getClavePrimaria() == clave){
			archivo.close();
			return centro*sizeof(RegistroIP)+sizeof(Cabecera);
		}
		if (superior - inferior == 0) {
			if ((rIP->getClavePrimaria() < clave) && (centro+1 < cabecera.getNRegistros())) {
				centro += 1;
			}
			archivo.close();
			return centro*sizeof(RegistroIP)+sizeof(Cabecera);
		}
		if(rIP->getClavePrimaria() > clave){
			superior = centro - 1;
			continue;
		}
		if(rIP->getClavePrimaria() < clave){
			inferior = centro + 1;
			continue;
		}
	}
	archivo.close();
	return inferior*sizeof(RegistroIP)+sizeof(Cabecera);
}

/*
 * Elimina un registro de un bloque del archivo de datos.
 * El registroIP que se le pasa por referencia es el que apunta al bloque que contiene el registro.
 * Tras eliminar, el registro va a contener la posicion del bloque en datos, o -1 en caso de que el bloque
 * haya quedado vacio al eliminar el registro.
 */
void IndicesPS::eliminarRegistro(string clave, RegistroIP& rIP) {
	fstream archivoDatos("zoo-data.dat", ios::in | ios::out | ios::binary);
	Cabecera cabeceraDatos;
	Bloque bloque;
	int ret, posicion;

	archivoDatos.read((char*)&cabeceraDatos, sizeof(Cabecera));

	archivoDatos.seekg((streampos)rIP.getPosRegistro());
	archivoDatos.read((char*)&bloque, sizeof(Bloque));
	ret = bloque.eliminar(clave);

	if (ret == -1) { // No se ha eliminado nada
		archivoDatos.close();
		return;
	}
	if (ret == 0) { // El bloque se ha quedado vacio
		// Desactivamos el bloque
		bloque.setValido(false);
		bloque.setSiguiente(cabeceraDatos.getPrimerHueco());
		archivoDatos.seekg(archivoDatos.tellg()-(streampos)sizeof(Bloque));
		posicion = archivoDatos.tellg(); // Posicion del bloque en datos
		archivoDatos.write((char*)&bloque, sizeof(Bloque)); // Sobreescribimos el bloque
		archivoDatos.tellg();
		// Actualizamos la cabecera
		cabeceraDatos.setNEliminados(cabeceraDatos.getNEliminados()+1);
		cabeceraDatos.setNRegistros(cabeceraDatos.getNRegistros()-1);
		cabeceraDatos.setPrimerHueco(posicion);
		archivoDatos.seekg(0, ios::beg);
		archivoDatos.tellg();
		archivoDatos.write((char*)&cabeceraDatos, sizeof(Cabecera)); // Sobreescribimos la cabecera
		archivoDatos.tellg();
		// Actualizamos la posicion del registro del IP
		// Como el bloque queda vacio apuntamos a -1, habra que comprobar fuera del metodo si rIP apunta a -1 y eliminarlo
		rIP.setPosRegistro(-1);

		archivoDatos.close();
		return;
	}
	if (ret == 1) { // El registro ha sido eliminado pero el bloque no esta vacio
		archivoDatos.seekg((streampos)rIP.getPosRegistro());
		archivoDatos.tellg();
		archivoDatos.write((char*)&bloque, sizeof(Bloque)); // Sobreescribimos el bloque
		archivoDatos.tellg();
		// Actualizamos la clave del registro del IP
		rIP.setClavePrimaria(bloque.getUltimoRegistro()->getAnimal(false)->getName());

		archivoDatos.close();
		return;
	}
}

/**
 * Elimina un registro en el indice primario.
 */
void IndicesPS::borrarIP(streampos posRegistro) {
	fstream archivo("IP.dat", ios::in | ios::out | ios::binary);
	RegistroIP rIP;
	Cabecera cabecera;
	vector<RegistroIP> registros;
	vector<RegistroIP>::iterator it;
	streampos posicion;

	// Leemos la cabecera
	archivo.read((char*)&cabecera, sizeof(Cabecera));
	// Cargamos en memoria todos los registros excepto el registro que queremos eliminar.
	while (!archivo.eof()) {
		posicion = archivo.tellg();
		archivo.read((char*) (&rIP), sizeof(RegistroIP));
		archivo.tellg();
		if (archivo.eof()) break;
		if (posicion != posRegistro) {
			registros.push_back(rIP);
		}
	}
	archivo.close();

	// Sobreescribimos el archivo con los datos que tenemos en memoria.
	archivo.open("IP.dat", ios::out | ios::binary);
	cabecera.setNEliminados(cabecera.getNEliminados()+1);
	cabecera.setNRegistros(cabecera.getNRegistros()-1);
	archivo.tellg();
	archivo.write((char*)&cabecera, sizeof(Cabecera));
	archivo.tellg();
	for (it = registros.begin(); it != registros.end(); it++) {
		archivo.tellg();
		archivo.write((char*)(&*it), sizeof(RegistroIP));
		archivo.tellg();
	}
	archivo.close();
}

/**
 * Busqueda Binaria en Indice Primario (IP.dat)
 * Devuelve la posicion del Registro en el fichero de datos o -1 sino esta.
 */
void IndicesPS::generarCabecera(fstream & archivo, int tipoRegistro) {
	int tamRegistro = 0;
	switch (tipoRegistro) {
		case 0: tamRegistro = sizeof(Registro); break;
		case 1: tamRegistro = sizeof(RegistroIP); break;
		default: break;
	}
	Cabecera cabecera(1,0,tamRegistro,-1);	//se inicializa con nReg a uno porq se inserta justo despues
	archivo.tellg();
	archivo.write((char*)(&cabecera), sizeof(Cabecera));
	archivo.tellg();
}
/**
 * Devuelve true si el archivo esta vacio
 */
bool IndicesPS::comprobarArchivoVacio(fstream & archivo) {
	int tam = 0;
	streampos posActual = archivo.tellg();
	archivo.seekg(0, ios::end);	// Ponemos el puntero al final del archivo
	tam = archivo.tellg();
	archivo.seekg(posActual); // Volvemos a poner el puntero donde estaba
	return (tam == 0);
}
