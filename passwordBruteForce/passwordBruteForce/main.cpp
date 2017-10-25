//  main.cpp
//  passwordBruteForce
//
//  Created by Alex Gutz on 10/13/17.
//  Copyright © 2017 Alejandro Gutierrez. All rights reserved.
#include <stdio.h>
#include <iostream>
#include <string>
#include <pthread.h>
#include "md5.cpp"

//#define ELEMS 1000000 //Limite de palabras a generar
#define NUM_THREADS 2

using namespace std;

pthread_mutex_t el_mutex; //Define si el hilo puede entrar o no a la region critica
pthread_cond_t condc,condp;
string bufer; /* búfer utilizado entre productor y consumidor */
string hashABuscar;

static unsigned int stringlength = 1;
//unsigned int indiceAlfabeto;

char Alphabet[69] = {'0','1','2','3','4','5','6','7','8','9','@','#','$','%','^','&','*','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

void Generate(unsigned int length,string s){
	if(length == 0){//cuando llegue a length
		//cout << s << "\n";
		bufer = s;
		pthread_cond_signal(&condc);
		pthread_mutex_unlock(&el_mutex);
		return;
	}
	unsigned int i;
	for(i = 0; i < 69; i++){
		string appended = s + Alphabet[i];
		Generate(length-1,appended);
	}
}

void *productor(void *ptr) /* produce datos */{
	cout << "prod" <<"\n";

	pthread_mutex_lock(&el_mutex); /* obtiene acceso exclusivo al búfer */
	while (bufer[0] != NULL) pthread_cond_wait(&condc, &el_mutex);
	while(1){
		Generate(stringlength,"");
		stringlength++;
	}
	
	pthread_cond_signal(&condc); /* despierta al consumidor */
	pthread_mutex_unlock(&el_mutex); /* libera el acceso al búfer */
	pthread_exit(0);
}

void *consumidor(void *ptr){
	cout << "con" <<"\n";
	pthread_mutex_lock(&el_mutex); /* obtiene acceso exclusivo al búfer */
	while (bufer[0] == NULL) pthread_cond_wait(&condc, &el_mutex);
	if(md5(bufer) == hashABuscar){
		cout << "Se encontro: " << bufer << "\n";
		pthread_cond_signal(&condp); /* despierta al productor */
		pthread_mutex_unlock(&el_mutex); /* libera el acceso al búfer */
		pthread_exit(0);
	}
	bufer[0] = NULL;
	//Aqui se comparan las palabras
	pthread_cond_signal(&condp); /* despierta al productor */
	pthread_mutex_unlock(&el_mutex); /* libera el acceso al búfer */
	pthread_exit(0);
}

int main(){
	hashABuscar = "32390fa731a71f4cdcf6b76a05334545";
	pthread_t pro, con;
	pthread_mutex_init(&el_mutex, 0);
	pthread_cond_init(&condc, 0);
	pthread_cond_init(&condp, 0);
	pthread_create(&con, NULL, consumidor, NULL);
	pthread_create(&pro, NULL, productor, NULL);

	pthread_join(pro, 0);
	pthread_join(con, 0);
	 
	pthread_cond_destroy(&condc);
	pthread_cond_destroy(&condp);
	pthread_mutex_destroy(&el_mutex);
	return 0;
}
