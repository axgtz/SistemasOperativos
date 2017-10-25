#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include "md5.cpp"

// Número de threads
#define NUM_THREADS 2

// Número de caracteres
#define MIN 1
#define MAX 2

// Tamaño del hash
#define HASH_LEN 33


// Mutex y condiciones
pthread_mutex_t tmutex;
pthread_cond_t condc, condp;

using namespace std;

// Alfabeto a usar para el brute force password
char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    '0','1','2','3','4','5','6','7','8','9','\0'};

// Hash buscado por el usuario
char searched_hash[HASH_LEN] = "";

// Tamaño del alfabeto
int alphabet_size = strlen(alphabet);

// Buffer
char *buffer = new char[MAX];


// Bandera para el hash encontrado
int flag = 1;


// Función recursiva para la generación de passwords
void passGeneratorRec(char aphabet[], char password[], int index, int size) {
    for (int i = 0; i < alphabet_size; ++i) {
        password[index] = alphabet[i];
        if (index == size - 1) {
            if (flag){
                // Obtiene acceso exclusivo al buffer
                pthread_mutex_lock(&tmutex);
                while (buffer[0] != ' ') pthread_cond_wait(&condp, &tmutex);
                // Copia de la password generada
                strcpy(buffer, password);
                
                //cout << password << endl;
                //password[index] == ' ';
                // Despierta al productor
                pthread_cond_signal(&condc);
                // Libera el acceso al buffer
                pthread_mutex_unlock(&tmutex);
            }
        }
        else {
            passGeneratorRec(alphabet, password, index + 1, size);
            
        }
    }
    
}

// Función secuencial para la generación de passwords y delimitar
// el rango del número de caracteres
void passGenerator(int size_min, int size_max) {
    char *password = new char[size_max];
    // Delimitamos el rango de caracteres
    while(size_min <= size_max) {
        memset(password, 0, size_max);
        passGeneratorRec(alphabet, password, 0, size_min);
        size_min++;
    }
}

// Genera passwords
void *producer(void *ptr) {
    passGenerator(MIN, MAX);

    //cout << buffer << endl;
    
    // Checamos el último elemento
    // de la combinación del buffer
    if (flag){
        if (md5(buffer) == searched_hash) {
            cout << endl << "Password found: " << buffer << endl;
            flag = 0;
        }
        
        else{
            // Imprimimos error si no
            // encuentra ninguna coincidencia
            cout << endl << "Not found" << endl;
            flag = 0;
        }
        buffer[0] = ' ';
    }
    pthread_exit(0);
}

// Genera el hash de las passwords
void *consumer(void *ptr) {
    char * buffer_copy = new char[MAX];
    while (flag) {
        // Obtiene acceso exclusivo al buffer
        pthread_mutex_lock(&tmutex);
        
        // Espera
        while (buffer[0] == ' ') pthread_cond_wait(&condc, &tmutex);
        // Copia del buffer
        strcpy(buffer_copy, buffer);
        
        // Impresión de password en el buffer
        //cout << buffer_copy << endl;
        
        // Sacamos el MD5
        string generated_hash = md5(buffer);
        
        // Verificamos si encontramos la coincidencia
        if (generated_hash == searched_hash) {
            cout << endl << "Password found: " << buffer_copy << endl;
            flag = 0;
        }
        
        // Limpiamos el buffer
        buffer[0] = ' ';
        
        // Despierta al productor
        pthread_cond_signal(&condp);
        // Libera el acceso al buffer
        pthread_mutex_unlock(&tmutex);
        
    }
    
    pthread_exit(0);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    long t;
    int rc;
    cout << "..:: BRUTE FORCE PASSWORD ::.." << endl;
    cout << "Enter a hash: ";
    cin >> searched_hash;
    
    // a ---> 0cc175b9c0f1b6a831c399e269772661
    // 99 --> ac627ab1ccbdb62ec96e702f07f6425b
    // cc --> e0323a9039add2978bf5b49550572c7c
    // abc -> 900150983cd24fb0d6963f7d28e17f72
    // dmGb-> f2642988cae262cedf93a5a2fbed524d
    
    for (t = 0; t < NUM_THREADS; t++) {
        if (t == 0) {
            rc = pthread_create(&threads[t], &attr, producer, 0);
        }
        if (t == 1){
            rc = pthread_create(&threads[t], &attr, consumer, 0);
        }
        if (rc) {
            cout << "ERROR; return code from pthread_create() is" << rc << endl;
            exit(-1);
        }
    }
    cout << "Searching... ";
    
    // Término de threads
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }
    
    // Destruir attr, condiciones y mutex
    pthread_attr_destroy(&attr);
    pthread_cond_destroy(&condp);
    pthread_cond_destroy(&condc);
    pthread_mutex_destroy(&tmutex);
    
    return 0;
}
