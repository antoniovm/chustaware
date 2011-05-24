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
	int posDatos=0, posAux=0;
	posDatos = indicesPS.insertarIP(animal);
	if(posDatos>0){
		posAux = indicesPS.insertarAux(animal, posDatos);
		indicesPS.insertarIS(animal, posAux);
	}
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
	while(aux.size()>0) {
		l.push_back(*aux.begin());
		aux.erase(aux.begin());
	}



}
void Indice::crearFicherosPS(){
	list<Animal*> animales;
	indicesPS.getES().leerTexto();	//lee el fichero zoo-data.txt para almacenar los animales en MP
	animales=indicesPS.getES().getAnimals();
	desordenar(animales);
    int posicionDatos=0;
	int posicionAux=0;

	fstream IP("IP.dat",ios::binary|ios::out);	//borrado de archivos
	fstream IS("IS.dat",ios::binary|ios::out);
	fstream Aux("IAux.dat",ios::binary|ios::out);
	fstream zooData("zoo-data.dat",ios::binary|ios::out);
	IP.close();
	IS.close();
	Aux.close();
	zooData.close();

	while(!animales.empty()){
		posicionDatos=indicesPS.insertarIP(animales.front());
		if(posicionDatos>0){
			posicionAux = indicesPS.insertarAux(animales.front(),posicionDatos);
			indicesPS.insertarIS(animales.front(),posicionAux);
		}
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
	indicesPS.borrarIS(clave, rDatos.getAnimal(false)->getLegs());
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
/**
 * Muestra por pantalla todos los animales con esa clave segundaria (patas)
 */
void Indice::buscarS(int nPatas){
	fstream archivoIS("IS.dat", ios::in | ios::binary);
	fstream archivoIAux("IAux.dat", ios::in | ios::binary);
	RegistroIS rIS;
	RegistroAux rAux;
	bool finPila = false;
	int posIS = indicesPS.buscarClaveS(nPatas);

	if (posIS == -1) {
		cout << "No se ha encontrado ningun registro con " << nPatas << " patas" << endl;
		archivoIS.close();
		archivoIAux.close();
		return;
	}
	archivoIS.seekg((streampos)posIS); //posicionamos el puntero en la posicion en la que esta el registro
	archivoIS.read((char*)&rIS, sizeof(RegistroIS)); //leemos el registro del indice secundario
	if (rIS.getPosPrimero() == -1) {
		cout << "No se ha encontrado ningun registro con " << nPatas << " patas" << endl;
		archivoIS.close();
		archivoIAux.close();
		return;
	}
	cout << "Animales con clave secundaria <" << nPatas << ">:" << endl;
	archivoIAux.seekg((streampos)rIS.getPosPrimero()); //posicionamos el puntero del IAux en la posicion donde apunta el registro del IS
	while (!finPila) {
		archivoIAux.read((char*) &rAux, sizeof(RegistroAux)); //leemos el registro en el IAux
		if (rAux.getValido()) {
			indicesPS.getES().leerRegistro(indicesPS.getES().calcularNumRegistro(rAux.getPosDatos())); //mostramos el animal
			if (rAux.getSiguiente() == -1) {
				finPila = true;
			} else {
				archivoIAux.seekg((streampos) rAux.getSiguiente()); //posicionamos el puntero de IAux en el siguiente registro con la misma clave secundaria
			}
		}
	}
	archivoIS.close();
	archivoIAux.close();
}
void Indice::lecturaOrdenada(){
	fstream archivoIP("IP.dat", ios::in|ios::binary), archivoDatos("zoo-data.dat", ios::in|ios::binary);
	RegistroIP rIP;
	Registro rDatos;
	Cabecera cabecera;
	int cont=1;
	archivoIP.read((char*)&cabecera,sizeof(Cabecera));

	while(1){
		archivoIP.read((char*)&rIP,sizeof(RegistroIP));

		archivoDatos.seekg(rIP.getPosRegistro());

		archivoDatos.read((char*)&rDatos,sizeof(Registro));

		cout<< cont <<"   "<< *rDatos.getAnimal(false)<<endl;

		cont++;

		if(archivoIP.tellg()>=cabecera.getNRegistros()*sizeof(RegistroIP))
			return;

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
	if (nombre == "IS.dat") {
		cout << "----------FICHERO IS.dat----------" << endl;
		archivoIndice.tellg();
		archivoIndice.read((char*)&cabecera,sizeof(Cabecera));
		archivoIndice.tellg();
		cout << cabecera << endl;
		RegistroIS registro;
		printf("%-5s%-20s%-20s\n","Num", "Clave secundaria", "Posicion del primero en aux");
		while (1) {
			archivoIndice.tellg();
			archivoIndice.read((char*) &registro, sizeof(RegistroIS));
			archivoIndice.tellg();
			if (archivoIndice.eof())
				break;
			printf("%-5d%-20d%-20d\n",cont ,registro.getClaveSecundaria(), registro.getPosPrimero());
			cont++;

		}
		cout << endl;
	}
	if (nombre == "IAux.dat") {
		cout << "----------FICHERO IAux.dat----------" << endl;
		archivoIndice.tellg();
		archivoIndice.read((char*)&cabecera,sizeof(Cabecera));
		archivoIndice.tellg();
		cout << cabecera << endl;
		RegistroAux registro;
		printf("%-15s%-17s%-20s%-20s\n","PosRegistroAux", "Clave primaria", "Posicion siguiente", "Posicion en datos");
		while (1) {
			archivoIndice.read((char*) &registro, sizeof(RegistroAux));
			if (archivoIndice.eof())
				break;
			if(registro.getValido())
				printf("%-15d%-17s%-20d%-20d\n",(int)archivoIndice.tellg()-sizeof(RegistroAux) , registro.getClavePrimaria().data(), registro.getSiguiente(), registro.getPosDatos());
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
