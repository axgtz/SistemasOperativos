//  main.cpp
//  passwordBruteForce
//
//  Created by Alex Gutz on 10/13/17.
//  Copyright © 2017 Alejandro Gutierrez. All rights reserved.
#include <string>
#include <stdio.h>
#include <iostream>
#include <pthread.h>

#define MAX 1000000000 /* cuántos números debe producir */
using namespace std;

//--------------PassGen------------
//"0123456789""!@#$%^&*""ABCDEFGHIJKLMNOPQRSTUVWXYZ""abcdefghijklmnopqrstuvwxyz""!@#$%^&*"
string passGen(int tamMin, int tamMax){//(a-z)(A-Z)(0-9)
	string palabraGen;
	
	return palabraGen;
}

//--------------Productor------------
pthread_mutex_t el_mutex;
pthread_cond_t condc,condp;
int bufer = 0; /* búfer utilizado entre productor y consumidor */

void *productor(void *ptr) /* produce datos */{
	int i;
	for (i=1; i<=MAX; i++) {
		pthread_mutex_lock(&el_mutex); /* obtiene acceso exclusivo al búfer */
		while (bufer!=0) pthread_cond_wait(&condp, &el_mutex);
		
		bufer = i; /* coloca elemento en el búfer */
		cout<<"coloca"<<endl;
		
		pthread_cond_signal(&condc); /* despierta al consumidor */
		pthread_mutex_unlock(&el_mutex); /* libera el acceso al búfer */
	}
	pthread_exit(0);
}

//--------------Consumidor------------
void *consumidor(void *ptr) /* consume datos */{
	int i;
	for (i=1; i<=MAX; i++) {
		pthread_mutex_lock(&el_mutex); /* obtiene acceso exclusivo al búfer */
		while (bufer==0) pthread_cond_wait(&condc, &el_mutex);
		
		bufer = 0; /* saca elemento del búfer */
		cout<<"salir"<<endl;
		
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
