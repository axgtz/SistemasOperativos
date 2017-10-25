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
string hashABuscar;

static unsigned int stringlength = 1;

char Alphabet[69] = {'0','1','2','3','4','5','6','7','8','9','@','#','$','%','^','&','*','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

void Generate(unsigned int length,string s){
    if(length == 0){//cuando llegue a length
        std::cout << s << "\n";
        return;
    }
    unsigned int i;
    for(i = 0; i < 69; i++){
        string appended = s + Alphabet[i];
        Generate(length-1,appended);
    }
}

void Crack(){
    while(1){
        Generate(stringlength,"");
        stringlength++;
    }
}

int main(){
    hashABuscar = "32390fa731a71f4cdcf6b76a05334545";
    Crack();
    return 0;
}
