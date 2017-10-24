//
//  generatorTest.cpp
//  passwordBruteForce
//
//  Created by Alex Gutz on 10/23/17.
//  Copyright © 2017 Alejandro Gutierrez. All rights reserved.
#include <iostream>
#include <string>
#include "md5.cpp"

using namespace std;
// Create some alphabet tables
string hashABuscar;

static unsigned int length;//Longitud de palabra a generar
static unsigned int stringLength;
unsigned int indiceAlfabeto;

char Alphabet[69] = {'0','1','2','3','4','5','6','7','8','9','@','#','$','%','^','&','*','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

// Recursive function, keeps clocking characters
// until length is reached


void Generate(string s){
    if(length == 0){ // when length has been reached
        cout << s << "\n"; // print it out
        return;
    }
    for(unsigned int i = 0; i < 69; i++){
        string appended = s + Alphabet[i];
        
        if(length>0){
            length--;
        }
        Generate(appended);
    }
}
void Crack(){
    length = 1;
    while (1) {
        Generate("");
        length++;
    }
}

int main(){
    hashABuscar = "32390fa731a71f4cdcf6b76a05334545";
    Crack();
    return 0;
}
