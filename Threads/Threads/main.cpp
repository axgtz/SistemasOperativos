//  main.cpp
//  Threads
//
//  Created by Alex Gutz on 09/5/17. A01019608
//  Copyright © 2017 Alejandro Gutierrez. All rights reserved.
// "passwd2017" es "8efad6deb6289843a8b8c446e2737709"
/*#include <iostream>
#include <pthread.h>
#include <string>
#include <fstream>
#include "md5.h"

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
    pthread_exit(NULL);
    return 0;
}*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

void *worker_thread(void *arg){
    printf("This is worker_thread #%ld\n", (long)arg);
    pthread_exit(NULL);
}

int main(){
    pthread_t my_thread[N];
    
    long id;
    for(id = 1; id <= N; id++) {
        int ret =  pthread_create(&my_thread[id], NULL, &worker_thread, (void*)id);
        if(ret != 0) {
            printf("Error: pthread_create() failed\n");
            exit(EXIT_FAILURE);
        }
    }

    pthread_exit(NULL);
}
