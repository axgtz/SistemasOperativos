//  main.cpp
//  Threads
//
//  Created by Alex Gutz on 09/5/17. A01019608
//  Copyright © 2017 Alejandro Gutierrez. All rights reserved.
// "passwd2017" es "8efad6deb6289843a8b8c446e2737709"
#include <iostream>
#include <pthread.h>
#include <string>
#include <fstream>
#include "md5.cpp"

#define NUM_THREADS 5

using namespace std;

string palabraABuscar;

void *BuscaArchivo(void *threadid){
    const char *archivos[5] = { "diccionario1.txt", "diccionario2.txt", "diccionario3.txt", "diccionario4.txt", "diccionario5.txt" };
    long tid;
    tid = (long)threadid;
    
    FILE *fichero;
    char linea[100];
    
    fichero = fopen(archivos[tid], "r");
    
    while (!feof(fichero)) {
        fgets(linea, sizeof(linea), fichero);
        if(md5(palabraABuscar) == md5(linea)){
            cout << "Se encontro la clave \""<<palabraABuscar << "\" en la thread numero: " << tid << "\n";
        }
    }
    //Imprimir que no lo encontro
    cout << "No se encontro la clave \"passwd2017\" en la thread numero: " << tid << "\n";
    fclose(fichero);
    pthread_exit(NULL);
}

int main(int argc, const char * argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc;
    long i;
    string palabraABuscar ="passwd2017";
    for(i = 0; i< NUM_THREADS;i++){
        cout << "Creating thread num" << i << "\n";
        rc = pthread_create(&threads[i], NULL, BuscaArchivo, (void *)i);
        if(rc){
            cout << "Error unable to create thread" << rc << "\n";
            return 0;
        }
        
    }
    cout << md5(palabraABuscar)  << endl;
    pthread_exit(NULL);
    return 0;
}
