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

/*
 * Inserta en el indice secundario y actualiza la lista encadenada del fichero aux
 */
int IndicesPS::insertarAux( Animal* animal, int posDatos) {
	Cabecera cabecera;
	RegistroAux* rAux = new RegistroAux(true,animal->getName(), -1,posDatos);// Creamos el registro.
		int posAux = 0;
		fstream archivoAux("IAux.dat",ios::binary|ios::in|ios::out);

		if (comprobarArchivoVacio(archivoAux)) { // Comprobamos si el tamaño del archivo es 0
				generarCabecera(archivoAux);
				archivoAux.tellg();
				archivoAux.write((char*)(rAux), sizeof(RegistroAux));
				archivoAux.tellg();
				posAux=archivoAux.tellg()-(streampos)sizeof(RegistroAux);
				archivoAux.close();
				return posAux;
		}
		archivoAux.read((char*) &cabecera, sizeof(Cabecera)); //Leemos cabecera

		if(cabecera.getPrimerHueco() == -1) {	//No hay huecos, insercion al final
			archivoAux.seekg(sizeof(Cabecera)+(int)cabecera.getNRegistros()*sizeof(RegistroAux));//ios::end
			posAux = archivoAux.tellg();
			archivoAux.write((char*)(rAux), sizeof(RegistroAux));
			archivoAux.tellg();
			cabecera.setNRegistros(cabecera.getNRegistros()+1);
			archivoAux.seekg(0,ios::beg);
			archivoAux.tellg();
			archivoAux.write((char*)&cabecera,sizeof(Cabecera));	//Actualizacion de la cabecera
			archivoAux.tellg();
			archivoAux.close();
			return posAux;
		}

		posAux = cabecera.getPrimerHueco();	//Posicion de insercion

		archivoAux.seekg(posAux);
		archivoAux.tellg();
		archivoAux.read((char*)rAux,sizeof(RegistroAux));//leemos el hueco para copiar la posSiguiente hueco a la cabecera
		archivoAux.tellg();
		int posSiguiente=rAux->getSiguiente();

		rAux=new RegistroAux(true,animal->getName(), -1,posDatos);// Creamos el registro.
		delete animal; //Liberar memoria dinamica

		archivoAux.seekp(posAux);
		archivoAux.tellg();
		archivoAux.write((char*)(rAux), sizeof(RegistroAux));	//Insercion del nuevo registro
		archivoAux.tellg();


		cabecera.setNEliminados(cabecera.getNEliminados()-1);	//Modificar cabecera
		cabecera.setNRegistros(cabecera.getNRegistros()+1);
		cabecera.setPrimerHueco(posSiguiente);
		archivoAux.seekp(0,ios::beg);
		archivoAux.write((char*)&cabecera,sizeof(Cabecera));	//Actualizacion de la cabecera

		archivoAux.close();
		delete rAux;
		return posAux;

}

void IndicesPS::insertarIS(Animal* animal, int posAux) {
	Cabecera cabecera;
	RegistroIS* rIS = new RegistroIS(animal->getLegs(), posAux);	//Preparamos los datos del nuevo registro
	RegistroAux* rAux = new RegistroAux(false,"",0,0), *rAux2 = new RegistroAux(false,"",0,0);
	int posIS = 0, siguiente = 0, anterior = sizeof(Cabecera);
	fstream archivoIS("IS.dat", ios::binary | ios::out | ios::in);

	if (comprobarArchivoVacio(archivoIS)) { // Comprobamos si el tamaño del archivo es 0
			generarCabecera(archivoIS);
			archivoIS.tellg();
			archivoIS.write((char*)(rIS), sizeof(RegistroIS));
			archivoIS.tellg();
			posIS=archivoIS.tellg()-(streampos)sizeof(RegistroIS);
			archivoIS.close();
			return;
	}
	archivoIS.read((char*) &cabecera, sizeof(Cabecera)); //Leemos cabecera


	posIS=buscarClaveS(animal->getLegs());
	if (posIS == -1) {//si no hay entrada con esa clave secundaria en archivoIS
		archivoIS.seekg(sizeof(Cabecera)+(int)cabecera.getNRegistros()*sizeof(RegistroIS));//ios::end
		while (archivoIS.tellg() > sizeof(Cabecera)) {
			archivoIS.seekg(archivoIS.tellg() - (streampos) sizeof(RegistroIS)); // Posicionamos el puntero en la posicion del registro anterior.
			archivoIS.read((char*) (rIS), sizeof(RegistroIS));					 // Leemos el registro.
			// Si la clave del registro que vamos a insertar es mayor que la clave del registro que acabamos de leer, insertamos el registro.
			if (animal->getLegs() > rIS->getClaveSecundaria()) {
				delete rIS;
				rIS = new RegistroIS(animal->getLegs(), posAux); // Creamos el registro.
				archivoIS.tellg();
				archivoIS.write((char*) (rIS), sizeof(RegistroIS));
				archivoIS.tellg();
				cabecera.setNRegistros(cabecera.getNRegistros()+1);
				archivoIS.seekg(0,ios::beg);
				archivoIS.tellg();
				archivoIS.write((char*) (&cabecera), sizeof(Cabecera));
				archivoIS.tellg();

				delete rIS;
				archivoIS.close();
				return;
			}
			// Si no, copiamos el registro en la siguiente posicion y posicionamos el puntero en la posicion anterior.
			archivoIS.tellg();
			archivoIS.write((char*) (rIS), sizeof(RegistroIS));
			archivoIS.tellg();
			archivoIS.seekg(archivoIS.tellg() - (streampos) (sizeof(RegistroIS)*2));
			archivoIS.tellg();

		}
		delete rIS;
		rIS = new RegistroIS(animal->getLegs(), posAux); // insercion en el top del fichero
		archivoIS.tellg();
		archivoIS.write((char*) (rIS), sizeof(RegistroIS));
		cabecera.setNRegistros(cabecera.getNRegistros()+1);
		archivoIS.seekg(0,ios::beg);
		archivoIS.tellg();
		archivoIS.write((char*) (&cabecera), sizeof(Cabecera));
		archivoIS.tellg();
		delete rIS;
		return;
	}
	//si la clave secundaria ya existia, enlazamos  al principio de la lista encadenada del fichero Aux
	fstream archivoAux("IAux.dat", ios::binary | ios::out | ios::in);
	//leemos los registros
	archivoAux.seekg(posAux);
	archivoAux.read((char*)rAux, sizeof(RegistroAux));	//Lectura del nuevo registro aux ya escrito por el metodo insertar Aux
	archivoIS.seekg(posIS);
	archivoIS.read((char*)rIS, sizeof(RegistroIS));
	//enlazamos los registros

	//posicionamos para leer el primer registro de la lista encadenada

	archivoAux.seekg(rIS->getPosPrimero());
	archivoAux.read((char*)(rAux2), sizeof(RegistroAux));

	if(rAux->getClavePrimaria()<rAux2->getClavePrimaria()){
		rAux->setSiguiente(rIS->getPosPrimero());
		rIS->setPosPrimero(posAux);
		//escribimos los registros actualizados
		archivoIS.seekp(posIS);
		archivoIS.write((char*)rIS, (streampos)sizeof(RegistroIS));
		archivoIS.tellg();
		archivoAux.seekg(posAux);
		archivoAux.write((char*)rAux, sizeof(RegistroAux));
		archivoIS.tellg();

		archivoAux.close();
		archivoIS.close();
		return;
	}
	siguiente=rIS->getPosPrimero();
	while(rAux2->getSiguiente()>0){

		if(rAux->getClavePrimaria()<rAux2->getClavePrimaria()){
			rAux->setSiguiente(siguiente);	//enganchyamos en la lista
			archivoAux.seekg(anterior);		//posicionamos para leer y actualizar
			archivoAux.read((char*)rAux2,sizeof(RegistroAux));
			rAux2->setSiguiente(posAux);	//actualizamos
			archivoAux.seekg(anterior);		//reposicionamos para escribir
			archivoAux.tellg();
			archivoAux.write((char*)rAux2,sizeof(RegistroAux));
			archivoAux.tellg();
			archivoAux.seekg(posAux);
			archivoAux.tellg();
			archivoAux.write((char*)rAux,sizeof(RegistroAux));
			archivoAux.tellg();
			archivoAux.close();
			archivoIS.close();
			return;
		}

		anterior=siguiente;
		siguiente=rAux2->getSiguiente();

		archivoAux.seekg(siguiente);
		archivoAux.read((char*)(rAux2), sizeof(RegistroAux));

	}
	archivoAux.seekg(siguiente);
	archivoAux.read((char*)rAux2,sizeof(RegistroAux));
	rAux2->setSiguiente(posAux);
	archivoAux.seekg(siguiente);
	archivoAux.tellg();
	archivoAux.write((char*)rAux2,sizeof(RegistroAux));
	archivoAux.tellg();
	archivoAux.seekg(posAux);
	rAux->setSiguiente(-1);
	archivoAux.tellg();
	archivoAux.write((char*)rAux,sizeof(RegistroAux));
	archivoAux.tellg();
	archivoAux.close();
	archivoIS.close();
	return;

}
/**
 * Inserta en fichero de datos e Indice Primario y devuelve la posicion del fichero de datos
 */
int IndicesPS::insertarIP(Animal* a)
{
	fstream archivoIP("IP.dat", ios::out | ios::in | ios::binary );
	int posDatos=es.insertar(a);	//inserta el animal en el archivo de datos
	RegistroIP* rIP= new RegistroIP(a->getName(), posDatos);// Creamos el registro.
	Cabecera cabecera;

	if (comprobarArchivoVacio(archivoIP)) { // Comprobamos si el tamaño del archivo es 0
		generarCabecera(archivoIP);
		archivoIP.tellg();
		archivoIP.write((char*)(rIP), sizeof(RegistroIP));
		archivoIP.tellg();
		archivoIP.close();
		return posDatos;
	}
	archivoIP.read((char*) &cabecera, sizeof(Cabecera)); //Leemos cabecera
	//posIP=buscarClaveP(a->getName()); //o hace falta buscar,al ser clave primaria seguro que no esta
	archivoIP.seekg(sizeof(Cabecera)+(int)cabecera.getNRegistros()*sizeof(RegistroIP));//ios::end

	while (archivoIP.tellg() > sizeof(Cabecera)) {
		archivoIP.seekg(archivoIP.tellg() - (streampos) sizeof(RegistroIP)); // Posicionamos el puntero en la posicion del registro anterior.
		archivoIP.read((char*) (rIP), sizeof(RegistroIP)); // Leemos el registro.
		// Si la clave del registro que vamos a insertar es mayor que la clave del registro que acabamos de leer, insertamos el registro.
		archivoIP.tellg();//-----------------------------------------------IS THE KEY!!
		if (a->getName() > rIP->getClavePrimaria()) {
			delete rIP;
			rIP = new RegistroIP(a->getName(), posDatos); // Creamos el nuevo registro.
			archivoIP.tellg();
			archivoIP.write((char*) (rIP), sizeof(RegistroIP));
			archivoIP.tellg();
			cabecera.setNRegistros(cabecera.getNRegistros() + 1); //Actualizamos la cabecera
			archivoIP.seekg(0, ios::beg);
			archivoIP.tellg();
			archivoIP.write((char*) (&cabecera), sizeof(Cabecera));
			archivoIP.tellg();
			delete rIP;
			archivoIP.close();
			return posDatos;
		}
		// Si no, copiamos el registro en la siguiente posicion y posicionamos el puntero en la posicion anterior.
		archivoIP.tellg();
		archivoIP.write((char*) (rIP), sizeof(RegistroIP));
		archivoIP.tellg();
		archivoIP.seekg(archivoIP.tellg()
				- (streampos) (sizeof(RegistroIP) * 2));
		archivoIP.tellg();

	}
	delete rIP;
	rIP = new RegistroIP(a->getName(), posDatos); // insercion en el top del fichero
	archivoIP.tellg();
	archivoIP.write((char*) (rIP), sizeof(RegistroIP));
	cabecera.setNRegistros(cabecera.getNRegistros()+1);
	archivoIP.seekg(0,ios::beg);
	archivoIP.tellg();
	archivoIP.write((char*) (&cabecera), sizeof(Cabecera));
	archivoIP.tellg();
	delete rIP;
	return posDatos;

}
void IndicesPS::borrarIS(string clavePrimaria, int claveSecundaria)
{
	vector<RegistroAux>vAux;
	vector<RegistroAux>::iterator it;
	fstream archivoIS("IS.dat", ios::in | ios::out | ios::binary);
	fstream archivoAux("IAux.dat", ios::in | ios::out | ios::binary);
	RegistroIS rIS;
	RegistroAux rAux;
	Cabecera cabeceraAux;
	int posicionIS = buscarClaveS(claveSecundaria);
	streampos posAnterior = -1;
	streampos posSiguiente = -1;

	if (posicionIS == -1) {
		cout << "No hay ningun registro con clave secundaria " << claveSecundaria << endl;
		archivoIS.close();
		archivoAux.close();
		return;
	}

	// Leemos la cabecera del IAux
	archivoAux.read((char*)&cabeceraAux, sizeof(Cabecera));
	// Leemos el registro del IS
	archivoIS.seekg((streampos)posicionIS);
	archivoIS.read((char*)&rIS, sizeof(RegistroIS));
	// Si no apunta a ningun registro no hacemos nada
	if (rIS.getPosPrimero() == -1) {
		archivoIS.close();
		archivoAux.close();
		return;
	}
	// Recorremos la lista encadenada de animales con la misma clave secundaria
	archivoAux.seekg((streampos)rIS.getPosPrimero());
	while (1) {
		archivoAux.read((char*) &rAux, sizeof(RegistroAux));
		if (rAux.getClavePrimaria() == clavePrimaria) {
			// Si posAnterior es -1 significa que es el primero de la lista
			if (posAnterior == -1) {
				rIS.setPosPrimero(rAux.getSiguiente());
				archivoIS.seekg((streampos) posicionIS);
				archivoIS.tellg();
				archivoIS.write((char*) &rIS, sizeof(RegistroIS));
				archivoIS.tellg();
				rAux.setValido(false); //Ponemos el bit de validez a 0
				archivoAux.seekg(archivoAux.tellg()	- (streampos) sizeof(RegistroAux));
				archivoAux.tellg();
				archivoAux.write((char*) &rAux, sizeof(RegistroAux)); // Escribimos el registro con el bit a 0
				archivoAux.tellg();
				//Modificamos y sobreeescribimos la cabecera
				cabeceraAux.setNRegistros(cabeceraAux.getNRegistros() - 1);
				cabeceraAux.setNEliminados(cabeceraAux.getNEliminados() + 1);
				archivoAux.seekg(0, ios::beg);
				archivoAux.tellg();
				archivoAux.write((char*) &cabeceraAux, sizeof(Cabecera));
				archivoAux.tellg();
				archivoIS.close();
				archivoAux.close();
				return;
			}
			// Si el anterior es un registro de IAux (posAnterior != -1)...
			posSiguiente = rAux.getSiguiente(); // Guardamos la posicion del siguiente
			rAux.setValido(false); // Desactivamos el registro
			archivoAux.seekg(archivoAux.tellg()	- (streampos) sizeof(RegistroAux)); // Nos posicionamos para sobreescribirlo
			archivoAux.tellg();
			archivoAux.write((char*) &rAux, sizeof(RegistroAux)); //Sobreescribimos el registro desactivado
			archivoAux.tellg();
			archivoAux.seekg(posAnterior); // Nos posicionamos para leer el anterior
			archivoAux.read((char*) &rAux, sizeof(RegistroAux)); // Leemos el anterior
			rAux.setSiguiente(posSiguiente); // Enganchamos en el anterior el siguiente al actual
			archivoAux.seekg(posAnterior); // Nos posicionamos de nuevo para sobreescribir el anterior
			archivoAux.tellg();
			archivoAux.write((char*) &rAux, sizeof(RegistroAux)); // Escribimos el anterior modificado
			archivoAux.tellg();
			archivoIS.close();
			archivoAux.close();
			return;

		}
		// Si la clave primaria no coincide
		else {
			// posAnterior es la posicion del que acabamos de leer
			posAnterior = archivoAux.tellg() - (streampos) sizeof(RegistroAux);
			if (rAux.getSiguiente() == -1) {
				// No hay ningun animal con la clave primaria y secundaria indicadas
				archivoIS.close();
				archivoAux.close();
				return;
			} else {
				archivoAux.seekg((streampos) rAux.getSiguiente());
			}
		}
	}
}
/**
 * Devuelve la posicion del primer elemento de la lista encadenada con esa clave secundaria.-1 si no esta en el archivoIS.
 */
int IndicesPS::buscarClaveS(int patas)
{

	fstream archivo("IS.dat", ios::in | ios::out | ios::binary);
	Cabecera cabecera;
	archivo.read((char*)(&cabecera),sizeof(Cabecera));
	archivo.seekg(0,ios::end);
	archivo.tellg();

	int inf = 0;
	//numero de registros
	int sup = ((archivo.tellg()-(streampos)sizeof(Cabecera))-(streampos)sizeof(RegistroIS))/(streampos)sizeof(RegistroIS);
	int centro = 0;
	RegistroIS* rIS = new RegistroIS(0,0);


	while(inf <= sup) {
	  centro = ((sup - inf) / 2) + inf;
	  archivo.seekg(centro*sizeof(RegistroIS)+sizeof(Cabecera));
	  archivo.tellg();
	  archivo.read((char*)rIS, sizeof(RegistroIS));
	  archivo.tellg();
	  if (rIS->getClaveSecundaria() == patas) {
		  archivo.close();
		  return centro*sizeof(RegistroIS)+sizeof(Cabecera);
	  }
	  if (patas < rIS->getClaveSecundaria()) {
		sup = centro - 1;
		continue;
	  }
	  if (patas > rIS->getClaveSecundaria()) {
		inf = centro + 1;
		continue;
	  }
	}
	archivo.close();
	return -1;
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

	while(inferior <= superior){
		centro=((superior-inferior)/2)+inferior;
		archivo.seekg(centro*sizeof(RegistroIP)+sizeof(Cabecera));
		archivo.tellg();
		archivo.read((char*)(rIP), sizeof(RegistroIP));
		archivo.tellg();

		if(rIP->getClavePrimaria()==clave){
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
	return -1;
}
/**
 * Elimina un registro en el indice primario.
 */
void IndicesPS::borrarIP(string clave) {
	fstream archivo("IP.dat", ios::in | ios::out | ios::binary);
	RegistroIP rIP;
	Cabecera cabecera;
	vector<RegistroIP> registros;
	vector<RegistroIP>::iterator it;

	// Leemos la cabecera
	archivo.read((char*)&cabecera, sizeof(Cabecera));
	// Cargamos en memoria todos los registros excepto el registro que queremos eliminar.
	while (!archivo.eof()) {
		archivo.tellg();
		archivo.read((char*) (&rIP), sizeof(RegistroIP));
		archivo.tellg();
		if (archivo.eof()) break;
		if (rIP.getClavePrimaria() != clave) {
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
void IndicesPS::generarCabecera(fstream & archivo) {
	Cabecera cabecera(1,0,sizeof(Animal)+1,-1);	//se inicializa con nReg a uno porq se inserta justo despues
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
