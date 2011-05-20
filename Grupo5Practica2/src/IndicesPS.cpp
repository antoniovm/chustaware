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

void IndicesPS::crearIS()
{
	ofstream salida;
	salida.open("IS.dat", ios::binary);
	salida.close();
}
/*
 * Inserta en el indice secundario y actualiza la lista encadenada del fichero aux
 */
void IndicesPS::insertarIS(Animal* animal, int posAux) {
	//EntradaSalida es;
	Cabecera cabecera;
	RegistroIS* rIS = new RegistroIS(animal->getLegs(), posAux);	//Preparamos los datos del nuevo registro
	RegistroAux* rAux = new RegistroAux(false,"",0,0);
	int posIS = 0;
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

	/*if (cabecera.getPrimerHueco() == -1) {	//No hay huecos, insercion al final
			rIS->.setAnimal(animal);
			archivoSalida.seekp(0, ios::end);
			posicion = archivoSalida.tellg();
			archivoSalida.write((char*)(&registro), sizeof(Registro));
			cabecera.setNRegistros(cabecera.getNRegistros()+1);
			archivoSalida.seekp(0,ios::beg);
			archivoSalida.write((char*)&cabecera,sizeof(Cabecera));	//Actualizacion de la cabecera
			archivoSalida.close();
			return (int)posicion;
		}
*/
	archivoIS.seekg(0,ios::end);
	if(cabecera.getNRegistros()*sizeof(RegistroIS)==(int)ios::beg){//si no hay ninguna entrada(archivo vacio)
		archivoIS.tellg();
		archivoIS.write((char*)(rIS),sizeof(RegistroIS));
		archivoIS.tellg();
		archivoIS.close();
		return;
	}
	posIS=buscarClaveS(animal->getLegs());
	if (posIS == -1) {//si no hay entrada con esa clave secundaria en archivoIS
		archivoIS.seekg(sizeof(Cabecera)+(int)cabecera.getNRegistros()*sizeof(RegistroIS));//ios::end
		while (archivoIS.tellg() > sizeof(Cabecera)) {
			archivoIS.seekg(archivoIS.tellg() - (streampos) sizeof(RegistroIS)); // Posicionamos el puntero en la posicion del registro anterior.
			//delete rIS;
			archivoIS.read((char*) (rIS), sizeof(RegistroIS)); // Leemos el registro.
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
		rIS = new RegistroIS(animal->getLegs(), posAux); // Primera entrada del fichero(en el top)
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

	//archivoAux.seekg(primero);




	//Recorremos todos los animales con ese numero de patas y cuando lleguemos al final de la lista
	//insertamos el animal.
	/*while (1) {
		archivoAux.read((char*) (rAuxLista), sizeof(RegistroAux));
		if (rAuxLista->getSiguiente() == -1) { //si es el final de la lista encadenada, hacemos que apunte al nuevo regAux
			rAuxLista->setSiguiente(posAux);
			archivoAux.seekg(archivoAux.tellg() - (streampos)sizeof(RegistroAux)); //actualizar registro
			archivoAux.write((char*)(rAuxLista),sizeof(RegistroAux));
			archivoIS.close();
			archivoAux.close();
			delete rAuxLista;
			return;
		}
		if(rAux->getClavePrimaria()<rAuxLista->getClavePrimaria())

		archivoAux.seekg(rAux->getSiguiente());
	}*/
}
void IndicesPS::borrarIS(int int1)
{
}
/**
 * Devuelve la posicion del primer elemento de la lista encadenada con esa clave secundaria.-1 si no esta en el archivoIS.
 */
int IndicesPS::buscarClaveS(int patas)
{

	fstream archivo("IS.dat", ios::in | ios::out | ios::binary);//ojo con el ios::ate
	Cabecera cabecera;
	archivo.read((char*)(&cabecera),sizeof(Cabecera));
	archivo.seekg(0,ios::end);
	archivo.tellg();

	int inf = 0;
	//numero de registros
	int sup = ((archivo.tellg()-sizeof(Cabecera))-(streampos)sizeof(RegistroIS))/sizeof(RegistroIS);
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
 * inserta reg en el archivo aux y devuelve la posicion en la que se inserto
 */
int IndicesPS::insertarAux( Animal* animal, int posDatos) {

		RegistroAux* rAux;
		rAux = new RegistroAux(true,animal->getName(), -1,posDatos);// Creamos el registro.
		// Si el archivo esta vacio insertamos directamente.
		fstream archivoAux("IAux.dat",ios::binary|ios::in|ios::out);
		archivoAux.seekg(0,ios::end);
		streampos posicion=0, tamano=archivoAux.tellg();

		if (archivoAux.tellg() == ios::beg) {
			archivoAux.write((char*)(rAux), sizeof(RegistroAux));
			archivoAux.tellg();
			delete rAux;
			archivoAux.close();
			return posicion;
		}
		//comprueba si hay hueco libre para insercion apilada
		archivoAux.seekp(ios::beg);

		while(archivoAux.tellg()<tamano){
			archivoAux.read((char*)(rAux), sizeof(RegistroAux));
			if(!rAux->getValido()){
				archivoAux.seekg(archivoAux.tellg()-(streampos)sizeof(RegistroAux));
				posicion=(int)archivoAux.tellg();
				rAux = new RegistroAux(true,animal->getName(), -1,posDatos);
				archivoAux.write((char*)(rAux),sizeof(RegistroAux));
				delete rAux;
				archivoAux.close();
				return posicion;
			}
		}
		//si no ha encontrado hueco, inserta al final
		archivoAux.seekg(0,ios::end);
		posicion=archivoAux.tellg();
		rAux = new RegistroAux(true,animal->getName(), -1,posDatos);
		archivoAux.write((char*)(rAux),sizeof(RegistroAux));
		delete rAux;
		archivoAux.close();
		return posicion;
}

//esto no vale pa na....inicializacion cutre <<<<--------------------------------
void IndicesPS::crearIP(fstream of, Animal* a)
{
/*
	RegistroIP regIP();
	int posicion=0;
	//fstream salida("IP.dat",ios::binary|ios::out);
	//fstream salidaBinario("zoo-data.dat",ios::binary|ios::out);
	//es.leerTexto();
	//animales=es.getAnimals();

	regIP.setClavePrimaria(a->getName());
	posicion = es.insertar(a);
	regIP.setPosRegistro(posicion);
	salida.write((char*) (&regIP), sizeof(RegistroIP));
	while(!animales.empty()){

		delete animales.begin();
		animales.pop_front();
	}
	salida.close();*/
}
/**
 * Inserta un registro en el indice primario y devuelve su posicion o -1 sino ha insertado.
 */
int IndicesPS::insertarIP(Animal* a)
{
	fstream archivo("IP.dat", ios::out | ios::in | ios::binary );
	int posicion=es.insertar(a);
	RegistroIP* rIP= new RegistroIP(a->getName(), posicion);// Creamos el registro.


	archivo.seekg(0,ios::end);




	while(archivo.tellg() > ios::beg) {
		archivo.seekg(archivo.tellg()-(streampos)sizeof(RegistroIP));	// Posicionamos el puntero en la posicion del registro anterior.
		archivo.read((char*)(rIP), sizeof(RegistroIP));	// Leemos el registro.
		// Si la clave del registro que vamos a insertar es mayor que la clave del registro que acabamos de leer, insertamos el registro.
		archivo.tellg();//-----------------------------------------------IS THE KEY!!
		if (a->getName() > rIP->getClavePrimaria()) {
			rIP = new RegistroIP(a->getName(), posicion);	// Creamos el nuevo registro.
			archivo.write((char*) (rIP), sizeof(RegistroIP));



			delete rIP;
			archivo.close();
			return posicion;
		}
		// Si no, copiamos el registro en la siguiente posicion y posicionamos el puntero en la posicion anterior.
		archivo.write((char*) (rIP), sizeof(RegistroIP));
		archivo.seekg(archivo.tellg() - (streampos)(sizeof(RegistroIP)*2));
	}

	// Si el archivo esta vacio o es la primera posicion
	archivo.write((char*) (rIP), sizeof(RegistroIP));
	delete rIP;
	archivo.close();
	return posicion;
}
/**
 * Elimina un registro en el indice primario.
 */
void IndicesPS::borrarIP(string clave) {
	fstream archivo("IP.dat", ios::in | ios::out | ios::binary);
	RegistroIP* rIP = NULL;
	vector<RegistroIP*> registros;
	vector<RegistroIP*>::iterator it;
	int posicion = buscarClaveP(clave);

	if (posicion == -1) {
		archivo.close();
		return;
	}

	// Cargamos en memoria todos los registros excepto el registro que queremos eliminar.
	while (!archivo.eof()) {
		if (archivo.tellg() == posicion) {
			archivo.seekg(posicion + (streampos)sizeof(RegistroIP));
		}
		archivo.read((char*) (rIP), sizeof(RegistroIP));
		registros.push_back(rIP);
	}
	archivo.close();

	// Sobreescribimos el archivo con los datos que tenemos en memoria.
	archivo.open("IP.dat", ios::out | ios::binary);
	for (it = registros.begin(); it != registros.end(); it++) {
		archivo.write((char*)(rIP), sizeof(RegistroIP));
	}
	archivo.close();

	// Liberamos memoria.
	delete rIP;
	for (it = registros.begin(); it != registros.end(); it++) {
		delete (*it);
	}
	registros.clear();
}

/**
 * Busqueda Binaria en Indice Primario (IP.dat)
 * Devuelve la posicion del Registro en el fichero de datos o -1 sino esta.
 */
long IndicesPS::buscarClaveP(string clave)
{
	fstream archivo("IP.dat", ios::in | ios::out | ios::binary | ios::ate);//ojo con el ios::ate
	int inferior=0;
	int superior=(archivo.tellg()/(streampos)sizeof(RegistroIP))-1;
	int centro=0;
	long posicionReg;
	RegistroIP* rIP = new RegistroIP("",0);

	while(inferior <= superior){
		centro=((superior-inferior)/2)+inferior;
		archivo.seekg(centro*sizeof(RegistroIP),ios::beg);//ios::beg o cero??
		archivo.read((char*)(rIP), sizeof(RegistroIP));
		if(rIP->getClavePrimaria()==clave){
			posicionReg=rIP->getPosRegistro();
			delete rIP;
			archivo.close();
			return posicionReg;
		}
		if(rIP->getClavePrimaria() > clave)
			superior = centro - 1;
		else
			inferior = centro + 1;

	}
	delete rIP;
	archivo.close();
	return -1;
}
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
