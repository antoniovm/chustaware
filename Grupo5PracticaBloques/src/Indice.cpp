/*
 * Indice.cpp
 *
 *  Created on: 11/05/2011
 *      Author: Sergio
 */

#include "Indice.h"

Indice::Indice() {
	// TODO Auto-generated constructor stub

}

Indice::~Indice() {
	// TODO Auto-generated destructor stub
}

void Indice::insertar(Animal *animal) {
	indicesPS.insertarDatos(animal);
}
/**
 * Lee del fichero de txt los animales y genera los ficheros binarios de datos e indices(primario,secundario y auxiliar)
 */
void Indice::desordenar(list<Animal*>&l){
	list<Animal*> aux;
	list<Animal*>::iterator it;
	int j=0;
	srand ( time(NULL) );
	while(l.size()>0) {
		j=(rand()%l.size());
		for (it=l.begin(); j>0;it++,j--) {}
			aux.push_back(*it);
			l.erase(it);
	}

	l=aux;



}
void Indice::crearFicherosPS(){
	list<Animal*> animales;
	indicesPS.getES().leerTexto();	//lee el fichero zoo-data.txt para almacenar los animales en MP
	animales=indicesPS.getES().getAnimals();
	//desordenar(animales);
    int posicionDatos=0;

	fstream IP("IP.dat",ios::binary|ios::out);	//borrado de archivos
	fstream zooData("zoo-data.dat",ios::binary|ios::out);
	IP.close();
	zooData.close();

	int i=1;
	for(list<Animal*>::iterator it=animales.begin();it!=animales.end(); it++) {
		cout << i << "\t" << *(*it) << endl;
		i++;
	}

	while(!animales.empty()){
		indicesPS.insertarDatos(animales.front());
		delete *animales.begin();
		animales.pop_front();
	}
}

void Indice::eliminar(string clave){
	fstream archivoIP("IP.dat", ios::in | ios::binary);
	fstream archivoDatos("zoo-data.dat", ios::in | ios::binary);
	RegistroIP rIP;
	Registro rDatos;
	long posicionIP = indicesPS.buscarClaveP(clave);
	if(posicionIP == -1){
		cout << "El animal no esta en el archivo de datos" << endl;
		archivoIP.close();
		return;
	}
	archivoIP.seekg((streampos)posicionIP);
	archivoIP.read((char*)&rIP, sizeof(RegistroIP));
	if(rIP.getPosRegistro() == -1) {
		cout << "El animal no esta en el archivo de datos" << endl;
		archivoIP.close();
		return;
	}
	archivoDatos.seekg((streampos)rIP.getPosRegistro());
	archivoDatos.read((char*)&rDatos, sizeof(Registro));
	archivoDatos.close();
	archivoIP.close();
	indicesPS.getES().eliminar(indicesPS.getES().calcularNumRegistro(rIP.getPosRegistro()));
	indicesPS.borrarIP(clave);
}
/**
 * Muestra por pantalla el animal con esa clave primaria(nombre)
 */
void Indice::buscarP(string clave){
	fstream archivoIP("IP.dat", ios::in | ios::binary);
	RegistroIP rIP;
	int posIP = indicesPS.buscarClaveP(clave);

	if (posIP == -1) {
		cout << "No se ha encontrado ningun registro con clave <" << clave << ">" << endl;
		archivoIP.close();
		return;
	}
	cout << "Animal con clave primaria <" << clave << ">:" << endl;
	archivoIP.seekg((streampos)posIP); //posicionamos el puntero del IP en la posicion en la que esta el animal que buscamos
	archivoIP.read((char*)&rIP, sizeof(RegistroIP)); //leemos el registro del IP
	indicesPS.getES().leerRegistro(indicesPS.getES().calcularNumRegistro(rIP.getPosRegistro())); //leemos y mostramos el animal que se encuentra en el archivo de datos

}

void Indice::lecturaOrdenada(){
	fstream archivoIP("IP.dat", ios::in|ios::binary), archivoDatos("zoo-data.dat", ios::in|ios::binary);
	RegistroIP rIP;
	Registro rDatos;
	Bloque bloque;
	Cabecera cabecera;
	int nBloquesLeidos = 0;

	archivoIP.read((char*)&cabecera,sizeof(Cabecera));

	while(1){
		archivoIP.tellg();
		archivoIP.read((char*)&rIP,sizeof(RegistroIP));
		archivoIP.tellg();
		archivoDatos.seekg(rIP.getPosRegistro());
		archivoIP.tellg();
		archivoDatos.read((char*)&bloque,sizeof(Bloque));
		archivoIP.tellg();
		cout << "Bloque " << nBloquesLeidos+1 << endl;
		bloque.mostrar();
		archivoIP.tellg();
		nBloquesLeidos++;

		if(nBloquesLeidos == cabecera.getNRegistros()) {
			archivoIP.close();
			archivoDatos.close();
			return;
		}
	}


}
/**
 * muestra el contenido del fichero de indices q se le pase por parametro
 */
void Indice::mostrar(string nombre) {
	fstream archivoIndice(nombre.data(), fstream::in | fstream::binary);
	int cont=1;
	Cabecera cabecera;
	if (!archivoIndice.is_open()) {
		cout << "No existe el archivo" << endl;
		return;
	}
	// Comprobamos si el archivo esta vacio
	archivoIndice.seekg(0, ios::end);
	if (archivoIndice.tellg() == 0) {
		cout << "Archivo vacio" << endl;
		archivoIndice.close();
		return;
	}
	archivoIndice.seekg(0,ios::beg);
	if (nombre == "IP.dat") {
		cout << "----------FICHERO IP.dat----------" << endl;
		archivoIndice.tellg();
		archivoIndice.read((char*)&cabecera,sizeof(Cabecera));
		archivoIndice.tellg();
		cout << cabecera << endl;
		RegistroIP registro;
		printf("%-5s%-17s%-20s\n","Num", "Clave primaria", "Posicion en datos");
		while (1) {
			archivoIndice.read((char*) &registro, sizeof(RegistroIP));
			if (archivoIndice.eof())
				break;
			printf("%-5d%-17s%-20d\n", cont, registro.getClavePrimaria().data(), registro.getPosRegistro());
			cont++;
		}
		cout << endl;
	}
	archivoIndice.close();
}

IndicesPS& Indice::getIndicesPS()
{
    return indicesPS;
}

void Indice::crearFicheroBloques(){

}
