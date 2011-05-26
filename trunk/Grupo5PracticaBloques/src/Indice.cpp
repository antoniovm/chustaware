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
	desordenar(animales);

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
	RegistroIP rIP;
	streampos posicionIP = indicesPS.buscarClaveP(clave);
	// Leemos el registro
	archivoIP.seekg(posicionIP);
	archivoIP.read((char*)&rIP, sizeof(RegistroIP));

	indicesPS.eliminarRegistro(clave, rIP); // Eliminamos el registro

	if (rIP.getPosRegistro() == -1) { // El bloque se ha quedado vacio al eliminar el registro
		indicesPS.borrarIP(posicionIP); // Eliminamos la entrada del indice, porque no apunta a nada
		archivoIP.close();
		return;
	}
	// Si no hemos tenido que eliminar el registro del IP, lo actualizamos
	archivoIP.seekg(posicionIP);
	archivoIP.tellg();
	archivoIP.write((char*)&rIP, sizeof(RegistroIP)); // Sobreescribimos el registro
	archivoIP.tellg();

	archivoIP.close();
}
/**
 * Muestra por pantalla el animal con esa clave primaria(nombre)
 */
void Indice::buscarP(string clave){
	fstream archivoIP("IP.dat", ios::in | ios::binary);
	fstream archivoDatos("zoo-data.dat", ios::in | ios::binary);
	RegistroIP rIP;
	Bloque bloque;
	Animal* animal = NULL;
	int posIP = indicesPS.buscarClaveP(clave);

	cout << "Animal con clave primaria <" << clave << ">:" << endl;
	archivoIP.seekg((streampos)posIP); //posicionamos el puntero del IP en la posicion en la que esta el registro
	archivoIP.read((char*)&rIP, sizeof(RegistroIP)); //leemos el registro del IP
	archivoDatos.seekg((streampos)rIP.getPosRegistro());
	archivoDatos.read((char*)&bloque, sizeof(Bloque));
	animal = bloque.buscar(clave);
	if (animal) {
		cout << *animal << endl;
		delete animal;
		animal = NULL;
		return;
	}
	cout << "No encontrado" << endl;
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
