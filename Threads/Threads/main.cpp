//Roberto Alejandro Gutiérrez Guillén		A01019608
// "passwd2017" es "8efad6deb6289843a8b8c446e2737709"
#include <iostream>
#include <fstream>
#include <pthread.h>

using namespace std;

void *BuscaArchivo(void *threadid)
{
	char *archivos[5] = { "diccionario1.txt", "diccionario2.txt", "diccionario3.txt", "diccionario4.txt", "diccionario5.txt" };

	long tid;
	tid = (long)threadid;

	FILE *fichero;
	char linea[100];

	fichero = fopen(archivos[tid], "r");
	while (!feof(fichero)) {
		fgets(linea, sizeof(linea), fichero);
		fprintf(stdout, "%s", linea);
	}
	fclose(fichero);
	pthread_exit(NULL);
}

int main() {

	return 0;
}