//  main.cpp
//  passwordBruteForce
//
//  Created by Alex Gutz on 10/13/17.
//  Copyright © 2017 Alejandro Gutierrez. All rights reserved.
#include <stdio.h>
#include <iostream>
#include <pthread.h>
#define MAX 8 /* tamano del buffer*/
#define ELEMS 10000000 //Limite de palabras a generar

using namespace std;

pthread_mutex_t el_mutex; //Define si el hilo puede entrar o no a la region critica
pthread_cond_t condc,condp;
string bufer[MAX] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL)}; /* búfer utilizado entre productor y consumidor */

bool bufferEmpty(){
	for(){
		if(bufer[i]==)
	}
}

bool bufferFull(){
	return false;
}

//--------------PassGen------------
//"0123456789""!@#$%^&*""ABCDEFGHIJKLMNOPQRSTUVWXYZ""abcdefghijklmnopqrstuvwxyz"
string passGen(){
	string posibilidades[69] = {"0","1","2","3","4","5","6","7","8","9","@","#","$","%","^","&","*","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
	string palabraGen;
	int cont = 1;
	for(int i = 0; ;i++){
		
		if(){
			
		}
	}
	return palabraGen;
}

void *productor(void *ptr) /* produce datos */{
	int i;
	for (i=1; i<=ELEMS; i++) {
		pthread_mutex_lock(&el_mutex); /* obtiene acceso exclusivo al búfer */
		while (bufferFull()) pthread_cond_wait(&condp, &el_mutex);
		bufer[i] = passGen(); /* coloca elemento en el búfer */
		cout<<"coloca"<<endl;
		pthread_cond_signal(&condc); /* despierta al consumidor */
		pthread_mutex_unlock(&el_mutex); /* libera el acceso al búfer */
	}
	pthread_exit(0);
}

void *consumidor(void *ptr) /* consume datos */{
	int i;
	for (i=1; i<=ELEMS; i++) {
		pthread_mutex_lock(&el_mutex); /* obtiene acceso exclusivo al búfer */
		while (bufferEmpty()) pthread_cond_wait(&condc, &el_mutex);
		bufer = 0; /* saca elemento del búfer */
		cout<<"salir"<<endl;
		//Aqui se comparan las palabras
		bufer[i] = 0;//Aqui se libera el buffer
		pthread_cond_signal(&condp); /* despierta al productor */
		pthread_mutex_unlock(&el_mutex); /* libera el acceso al búfer */
	}
	pthread_exit(0);
}

int main(int argc, char **argv){
	pthread_t pro, con;
	pthread_mutex_init(&el_mutex, 0);
	pthread_cond_init(&condc, 0);
	pthread_cond_init(&condp, 0);
	pthread_create(&con, 0, consumidor, 0);
	pthread_create(&pro, 0, productor, 0);
	pthread_join(pro, 0);
	pthread_join(con, 0);
	pthread_cond_destroy(&condc);
	pthread_cond_destroy(&condp);
	pthread_mutex_destroy(&el_mutex);
}
