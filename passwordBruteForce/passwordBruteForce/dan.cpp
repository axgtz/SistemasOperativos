#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include "md5.cpp"

#define MAX 1
#define NUM_THREADS 2
#define MIN 2
#define HASH_LEN 33

using namespace std;
char alphabet[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

char searched_hash[HASH_LEN]="";
int alphabet_size= strlen(alphabet);
pthread_mutex_t el_mutex;
pthread_cond_t condc,condp;
char *buffer =new char [MAX];

void passGeneratorRec(char alphabet[], char password[], int index, int size) {
    for (int i = 0; i < alphabet_size; ++i) {
        password[index] = alphabet[i];
        if (index == size - 1) {
            pthread_mutex_lock(&el_mutex);
            while (buffer[0] != ' ') pthread_cond_wait(&condp, &el_mutex);
            strcpy(buffer, password);
            pthread_cond_signal(&condc);
            pthread_mutex_unlock(&el_mutex);
            
        }else {
            passGeneratorRec(alphabet, password, index + 1, size);
        }
    }
}

void passGenerator(int size_min, int size_max) {
    char *password = new char[size_max];
    while(size_min <= size_max) {
        memset(password, 0, size_max);
        passGeneratorRec(alphabet, password, 0, size_min);
        size_min++;
    }
}

void *producer(void *ptr) {
    passGenerator(MIN, MAX);
    cout << "FAKE" << endl;
    if (md5(buffer) == searched_hash) {
        cout << endl << "Password found: " << buffer << endl;
    }else{
        cout << endl << "Not found" << endl;
    }
    buffer[0] = ' ';
    pthread_exit(0);
}

void *consumer(void *ptr) {
    char * buffer_copy = new char[MAX];
    
    
    pthread_mutex_lock(&el_mutex);
    while (buffer[0] == ' ') pthread_cond_wait(&condc, &el_mutex);
    string generated_hash = md5(buffer);
    if (generated_hash == searched_hash) {
        cout << endl << "Password found: " << buffer_copy << endl;
        
    }
    buffer[0] = ' ';
    pthread_cond_signal(&condp);
    pthread_mutex_unlock(&el_mutex);
    
    
    
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
    
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }
    
    pthread_attr_destroy(&attr);
    pthread_cond_destroy(&condp);
    pthread_cond_destroy(&condc);
    pthread_mutex_destroy(&el_mutex);
    
    return 0;
}
