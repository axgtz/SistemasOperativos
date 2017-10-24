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

unsigned int length;//Longitud de palabra a generar
unsigned int stringlLength;
unsigned int indiceAlfabeto;
//bool inicio;

char Alphabet[69] = {'0','1','2','3','4','5','6','7','8','9','@','#','$','%','^','&','*','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
//--------------PassGen------------
//"0123456789""!@#$%^&*""ABCDEFGHIJKLMNOPQRSTUVWXYZ""abcdefghijklmnopqrstuvwxyz"
/*bool generator(bool inicio){
	while(inicio){
		
	}
	
	return false;
}*/

void Generate(string s){
	if(length == 0){ // when length has been reached
		cout << s << "\n"; // print it out
		return;
	}
	for(unsigned int i = 0; i < 69; i++){
		string appended = s + Alphabet[i];
		length--;
		Generate(appended);
	}
}
void Crack(){
	while (1) {
		stringlLength = 1;
		Generate("");
		length++;
	}
}

void *productor(void *ptr) /* produce datos */{
	pthread_mutex_lock(&el_mutex); /* obtiene acceso exclusivo al búfer */
	while (bufer[0] != NULL) pthread_cond_wait(&condc, &el_mutex);
	//inicio = true;
	//generator(inicio);
	if(indiceAlfabeto>=69){
		indiceAlfabeto=0;
		length++;
	}
	
	//bufer[0] = ' ';
	pthread_cond_signal(&condc); /* despierta al consumidor */
	pthread_mutex_unlock(&el_mutex); /* libera el acceso al búfer */
	pthread_exit(0);
}

void *consumidor(void *ptr) /* consume datos */{
	pthread_mutex_lock(&el_mutex); /* obtiene acceso exclusivo al búfer */
	while (bufer[0] == NULL) pthread_cond_wait(&condc, &el_mutex);
	string s = bufer;
	if(md5(s) == hashABuscar){
		cout << "Se encontro: " << s << "\n";
		pthread_exit(0);
		return 0;
	}
	bufer[0] = NULL;
	//Aqui se comparan las palabras
	pthread_cond_signal(&condp); /* despierta al productor */
	pthread_mutex_unlock(&el_mutex); /* libera el acceso al búfer */
	pthread_exit(0);
}

int main(){
	hashABuscar = "32390fa731a71f4cdcf6b76a05334545";
	Crack();
	/*pthread_t pro, con;
	pthread_mutex_init(&el_mutex, 0);
	pthread_cond_init(&condc, 0);
	pthread_cond_init(&condp, 0);
	pthread_create(&con, 0, consumidor, 0);
	pthread_create(&pro, 0, productor, 0);
	//pthread_join(pro, 0);
	//pthread_join(con, 0);
	 
	pthread_cond_destroy(&condc);
	pthread_cond_destroy(&condp);
	pthread_mutex_destroy(&el_mutex);*/
	return 0;
}
